﻿/**
 *	@brief		Implements the TPM_OwnerClear command.
 *	@details	The module receives the input parameters, marshals these parameters
 *				to a byte array, sends the command to the TPM and unmarshals the response
 *				back to the out parameters.
 *	@file		TPM_OwnerClear.c
 *	@copyright	Copyright 2014 - 2017 Infineon Technologies AG ( www.infineon.com )
 *
 *	@copyright	All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "TPM_OwnerClear.h"
#include "TPM_Marshal.h"
#include "TPM2_Marshal.h"
#include "DeviceManagement.h"
#include "Crypt.h"
#include "Platform.h"

/**
 *	@brief		This function handles the TPM_OwnerClear command
 *	@details	The function receives the input parameters marshals these parameters
 *				to a byte array sends the command to the TPM and unmarshals the response
 *				back to the out parameters
 *
 *	@param		PunAuthHandle			The authorization session handle used for owner authentication.
 *	@param		PpNonceEven				Even nonce previously generated by TPM to cover inputs
 *	@param		PbContinueAuthSession	The continue use flag for the authorization session handle
 *	@param		PpOwnerAuth				The authorization session digest for inputs and owner authentication.
 *										HMAC key: ownerAuth.
 *
 *	@retval		RC_SUCCESS				The operation completed successfully.
 *	@retval		RC_E_BAD_PARAMETER		An invalid parameter was passed to the function.
 *	@retval		RC_E_BUFFER_TOO_SMALL	In case an internal buffer is too small for HASH calculation
 *	@retval		RC_E_INTERNAL			In case an error occurred while preparing the HASH buffer
 *	@retval		...						Error codes from called functions.
 */
_Check_return_
unsigned int
TSS_TPM_OwnerClear(
	_In_	TPM_AUTHHANDLE	PunAuthHandle,
	_Inout_	TPM_NONCE*		PpNonceEven,
	_In_	BYTE			PbContinueAuthSession,
	_In_	TPM_AUTHDATA*	PpOwnerAuth)
{
	unsigned int unReturnValue = RC_SUCCESS;

	do
	{
		BYTE rgbRequest[MAX_COMMAND_SIZE] = {0};
		BYTE rgbResponse[MAX_RESPONSE_SIZE] = {0};
		BYTE* pbBuffer = NULL;
		BYTE* pbDigestBuffer = NULL;
		INT32 nSizeRemaining = sizeof(rgbRequest);
		INT32 nSizeResponse = sizeof(rgbResponse);

		// Request parameters
		TPM_TAG tag = TPM_TAG_RQU_AUTH1_COMMAND;
		UINT32 unCommandSize = 0;
		TPM_COMMAND_CODE commandCode = TPM_ORD_OwnerClear;
		TPM_NONCE sNonceOdd = {{0}};
		TPM_AUTHDATA sAuthData = {{0}};

		BYTE rgbSha1Hash[SHA1_DIGEST_SIZE] = {0};

		// Response parameters
		UINT32 unResponseSize = 0;
		TPM_RESULT responseCode = TPM_RC_SUCCESS;

		// Check Parameters
		if (0 == PunAuthHandle ||
				NULL == PpOwnerAuth ||
				NULL == PpNonceEven)
		{
			unReturnValue = RC_E_BAD_PARAMETER;
			break;
		}

		// Marshal the request
		pbBuffer = rgbRequest;
		unReturnValue = TSS_TPM_TAG_Marshal(&tag, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;
		unReturnValue = TSS_UINT32_Marshal(&unCommandSize, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;

		// Store beginning for digest buffer
		pbDigestBuffer = pbBuffer;

		unReturnValue = TSS_TPM_COMMAND_CODE_Marshal(&commandCode, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;

		// Calculate parameter hash value
		unReturnValue = Crypt_SHA1(pbDigestBuffer, (unsigned short)(pbBuffer - pbDigestBuffer), rgbSha1Hash);
		if (RC_SUCCESS != unReturnValue)
			break;

		// Marshal Authentication handle
		unReturnValue = TSS_TPM_AUTHHANDLE_Marshal(&PunAuthHandle, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;

		// Marshal TPM nonce odd
		unReturnValue = Crypt_GetRandom(sizeof(sNonceOdd.nonce), sNonceOdd.nonce);
		if (RC_SUCCESS != unReturnValue)
			break;

		unReturnValue = TSS_TPM_NONCE_Marshal(&sNonceOdd, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;

		unReturnValue = TSS_BYTE_Marshal(&PbContinueAuthSession, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;

		// Create HMAC input buffer
		{
			BYTE rgbHmacBuffer[sizeof(rgbSha1Hash) + 2 * TPM_NONCE_SIZE + sizeof(BYTE)] = {0};
			int nHmacBufferSize = sizeof(rgbHmacBuffer);
			BYTE* pbHmacBuffer = NULL;

			pbHmacBuffer = rgbHmacBuffer;

			unReturnValue = Platform_MemoryCopy(pbHmacBuffer, nHmacBufferSize, rgbSha1Hash, sizeof(rgbSha1Hash));
			if (RC_SUCCESS != unReturnValue)
				break;

			pbHmacBuffer = (BYTE*) (pbHmacBuffer + sizeof(rgbSha1Hash));
			nHmacBufferSize -= sizeof(rgbSha1Hash);

			unReturnValue = Platform_MemoryCopy(pbHmacBuffer, nHmacBufferSize, PpNonceEven->nonce, TPM_NONCE_SIZE);
			if (RC_SUCCESS != unReturnValue)
				break;

			pbHmacBuffer = (BYTE*) (pbHmacBuffer + TPM_NONCE_SIZE);
			nHmacBufferSize -= TPM_NONCE_SIZE;

			unReturnValue = Platform_MemoryCopy(pbHmacBuffer, nHmacBufferSize, sNonceOdd.nonce, TPM_NONCE_SIZE);
			if (RC_SUCCESS != unReturnValue)
				break;

			pbHmacBuffer = (BYTE*) (pbHmacBuffer + TPM_NONCE_SIZE);
			nHmacBufferSize -= TPM_NONCE_SIZE;

			// Do a size check
			if (nHmacBufferSize < 1)
			{
				unReturnValue = RC_E_BUFFER_TOO_SMALL;
				break;
			}

			*pbHmacBuffer = PbContinueAuthSession;
			nHmacBufferSize--;

			// Check if buffer is filled correctly
			if (0 != nHmacBufferSize)
			{
				unReturnValue = RC_E_INTERNAL;
				break;
			}

			unReturnValue = Crypt_HMAC(rgbHmacBuffer, sizeof(rgbHmacBuffer), PpOwnerAuth->authdata, sAuthData.authdata);
			if (RC_SUCCESS != unReturnValue)
				break;

			unReturnValue = TSS_TPM_AUTHDATA_Marshal(&sAuthData, &pbBuffer, &nSizeRemaining);
			if (RC_SUCCESS != unReturnValue)
				break;
		}

		// Overwrite unCommandSize
		unCommandSize = sizeof(rgbRequest) - nSizeRemaining;
		pbBuffer = rgbRequest + 2;
		nSizeRemaining = 4;
		unReturnValue = TSS_UINT32_Marshal(&unCommandSize, &pbBuffer, &nSizeRemaining);
		if (RC_SUCCESS != unReturnValue)
			break;

		// Transmit the command over TDDL
		unReturnValue = DeviceManagement_Transmit(rgbRequest, unCommandSize, rgbResponse, (unsigned int*)&nSizeResponse);
		if (TPM_RC_SUCCESS != unReturnValue)
			break;

		// Unmarshal the response
		pbBuffer = rgbResponse;
		nSizeRemaining = nSizeResponse;
		unReturnValue = TSS_TPM_TAG_Unmarshal(&tag, &pbBuffer, &nSizeRemaining);
		if (TPM_RC_SUCCESS != unReturnValue)
			break;
		unReturnValue = TSS_UINT32_Unmarshal(&unResponseSize, &pbBuffer, &nSizeRemaining);
		if (TPM_RC_SUCCESS != unReturnValue)
			break;
		unReturnValue = TSS_TPM_RESULT_Unmarshal(&responseCode, &pbBuffer, &nSizeRemaining);
		if (TPM_RC_SUCCESS != unReturnValue)
			break;
		if (responseCode != TPM_RC_SUCCESS)
		{
			unReturnValue = RC_TPM_MASK | responseCode;
			break;
		}
		// Skip unmarshal of further data
	}
	WHILE_FALSE_END;

	return unReturnValue;
}