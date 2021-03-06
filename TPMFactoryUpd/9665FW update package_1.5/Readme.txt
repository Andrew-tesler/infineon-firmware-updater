--------------------------------------------------------------------------------
                       Infineon TPM Firmware Update Tools
                   For Use with UEFI and Microsoft Windows PE
                            Infineon Technologies AG

All information in this document is
Copyright 2014 - 2017 Infineon Technologies AG ( www.infineon.com ).
All rights reserved.

Microsoft and Windows are registered trademarks of Microsoft Corporation in the
United States and/or other countries.
--------------------------------------------------------------------------------

Contents:

1. Welcome
1.1 Prerequisites
1.2 Contents of the Package
1.3 Firmware Images
1.4 Installation

2. Usage of IFXTPMUpdate

3. Usage of TPMFactoryUpd

4. If You Have Questions

5. Release Info
5.1 About This Release
5.2 New Features, Fixes, and Improvements
5.3 Known Bugs and Limitations

================================================================================

1. Welcome

Welcome to Infineon TPM Firmware Update Tools.

The package contains the following tools:

- IFXTPMUpdate.efi is a UEFI (Unified Extensible Firmware Interface) service
  driver that can be used by applications updating the firmware of an
  Infineon TPM (Trusted Platform Module).

- TPMFactoryUpd.efi is a UEFI shell application that enables a
  manufacturing/service facility to update the firmware of an
  Infineon TPM (Trusted Platform Module) from a UEFI shell.

- TPMFactoryUpd.exe is a Microsoft Windows PE (Preinstallation Environment)
  command line application that enables a manufacturing/service facility to
  update the firmware of an Infineon TPM (Trusted Platform Module) on
  Microsoft Windows PE.

For further information about TPM and TCG (Trusted Computing Group) please visit
https://www.trustedcomputinggroup.org


1.1 Prerequisites

- Operating System:
   UEFI 2.3.1 or higher (64-bit)
  or
   Microsoft Windows PE 5.1 (32-bit or 64-bit) without
   WinPE-SecureStartup component
- A system equipped with Trusted Platform Module:
   Infineon TPM SLB 9660 TPM1.2 FW4.40.119.0 or FW4.42.132.0 or FW4.43.257.0
  or
   Infineon TPM SLB 9665 TPM2.0 FW5.51.2098.0 or FW5.60.2677.0 or FW5.61.2785.0
   or FW5.61.2789.0 or FW5.62.3126.0

ATTENTION:

To avoid any interruption of the update process, it is necessary to suspend all
usage of the TPM during the update process.

Do not turn off or shut down the system during the update process.

It is recommended to always restart the system directly after the TPM Firmware
Update, since certain system hardware and software components might not be aware
of a TPM Firmware Update without a restart (especially in case the TPM family
has been changed with the update).


1.2 Contents of the Package

File name                             Description
=========                             ===========
Doc\Programmers_Reference_Manual.chm  Programmers Reference Manual for
                                      IFXTPMUpdate

Doc\TPMFactoryUpd_UserManual.pdf      Infineon TPM Factory Update Tool User's
                                      Manual

Firmware\License_FW_Images.pdf        Legal disclaimer for firmware images

Firmware\TPM12_4.40.119.0_to_         Firmware image to update TPM1.2 to newer
TPM12_4.43.257.0.BIN                  version

Firmware\TPM12_4.40.119.0_to_         Firmware image to update TPM1.2 to TPM2.0
TPM20_5.62.3126.0.BIN                 

Firmware\TPM12_4.42.132.0_to_         Firmware image to update TPM1.2 to newer
TPM12_4.43.257.0.BIN                  version

Firmware\TPM12_4.42.132.0_to_         Firmware image to update TPM1.2 to TPM2.0
TPM20_5.62.3126.0.BIN                 

Firmware\TPM12_4.43.257.0_to_         Firmware image to update TPM1.2 to TPM2.0
TPM20_5.62.3126.0.BIN                 

Firmware\TPM12_4.43.257.0_to_         Firmware image to update TPM1.2 to TPM2.0
TPM20_5.80.2910.2.BIN                 FIPS 140-2 compliant version

Firmware\TPM12_latest.cfg             Config file to update to latest TPM1.2
                                      firmware version

Firmware\TPM20_5.51.2098.0_to_        Firmware image to update TPM2.0 to TPM1.2
TPM12_4.43.257.0.BIN                  

Firmware\TPM20_5.51.2098.0_to_        Firmware image to update TPM2.0 to newer
TPM20_5.62.3126.0.BIN                 version

Firmware\TPM20_5.60.2677.0_to_        Firmware image to update TPM2.0 to TPM1.2
TPM12_4.43.257.0.BIN                  

Firmware\TPM20_5.60.2677.0_to_        Firmware image to update TPM2.0 to newer
TPM20_5.62.3126.0.BIN                 version

Firmware\TPM20_5.61.2785.0_to_        Firmware image to update TPM2.0 to TPM1.2
TPM12_4.43.257.0.BIN                  

Firmware\TPM20_5.61.2785.0_to_        Firmware image to update TPM2.0 to newer
TPM20_5.62.3126.0.BIN                 version

Firmware\TPM20_5.61.2789.0_to_        Firmware image to update TPM2.0 to TPM1.2
TPM12_4.43.257.0.BIN                  

Firmware\TPM20_5.61.2789.0_to_        Firmware image to update TPM2.0 to newer
TPM20_5.62.3126.0.BIN                 version

Firmware\TPM20_5.62.3126.0_to_        Firmware image to update TPM2.0 to TPM1.2
TPM12_4.43.257.0.BIN                  

Firmware\TPM20_latest.cfg             Config file to update to latest TPM2.0
                                      firmware version

Tools\UEFI\Application\Include\       UEFI service driver header file
IFXTPMUpdate.h

Tools\UEFI\Application\    			  UEFI sample application source code file
RunIFXTPMUpdate.c                     demonstrating usage of IFXTPMUpdate driver

Tools\UEFI\Application\               EDK II Declaration file for UEFI sample
RunIFXTPMUpdate.dec	                  application

Tools\UEFI\Application\               EDK II Platform Description file for UEFI
RunIFXTPMUpdate.dsc					  sample application

Tools\UEFI\Application\               EDK II Build Information file for UEFI 
RunIFXTPMUpdate.inf					  UEFI sample application

Tools\UEFI\Bin\x64\IFXTPMUpdate.efi   UEFI service driver binary

Tools\UEFI\Bin\x64\TPMFactoryUpd.efi  Infineon TPM Factory Update Tool UEFI
                                      shell application

Tools\WinPE\Bin\x64\TPMFactoryUpd.exe Infineon TPM Factory Update Tool for
                                      Microsoft Windows PE (64-bit)

Tools\WinPE\Bin\x64\TVicPort.sys      Microsoft Windows PE (64-bit) driver for
                                      TPM access

Tools\WinPE\Bin\x86\TPMFactoryUpd.exe Infineon TPM Factory Update Tool for
                                      Microsoft Windows PE (32-bit)

Tools\WinPE\Bin\x86\TVicPort.sys      Microsoft Windows PE (32-bit) driver for
                                      TPM access

Tools\License_Tools.txt               Legal disclaimer for tools

Readme.txt                            This file


1.3 Firmware Images

The Firmware folder contains TPM firmware images to enable updating firmware
back and forth between TPM1.2 and TPM2.0 families. The total number of firmware
updates allowed by the TPM is limited (please consult your local Infineon
representative for further details). Once the limit has been reached, no
further TPM Firmware Update will be possible.
Each TPM firmware image file name indicates the source firmware version (to
which the update can be applied) and the resulting firmware version after the
update. An update must be initiated using the image with source firmware version
matching the current TPM firmware version.
TPM firmware versions 4.xx implement TPM1.2.
TPM firmware versions 5.xx implement TPM2.0.


1.4 Installation

Extract the contents of the deployment package archive file into a folder
accessible from UEFI/Microsoft Windows PE.


2. Usage of IFXTPMUpdate

Please refer to the Programmers Reference Manual and the sample application.


3. Usage of TPMFactoryUpd

Please refer to the Infineon TPM Factory Update Tool User's Manual.


4. If You Have Questions

If you have any questions or problems, please contact your local Infineon
representative. Further information is available at
https://www.infineon.com/tpm


5. Release Info


5.1 About This Release

Infineon TPM Firmware Update Tools release version is 01.01.2481.00.
TPMFactoryUpd in this release is version 01.01.2212.00.
IFXTPMUpdate.efi in this release is version 01.01.2212.00.
TVicPort.sys in this release is version 4.0.

Supported TPM Firmware Update path(s) for this release:
4.40.119.0 (Common Criteria certified) -> 4.43.257.0 (Common Criteria certified)
4.40.119.0 (Common Criteria certified) -> 5.62.3126.0 (Common Criteria
certified)
4.42.132.0 (Common Criteria certified) -> 4.43.257.0 (Common Criteria certified)
4.42.132.0 (Common Criteria certified) -> 5.62.3126.0 (Common Criteria
certified)
4.43.257.0 (Common Criteria certified) -> 5.80.2910.2 (FIPS 140-2 
compliant version)
4.43.257.0 (Common Criteria certified) <-> 5.62.3126.0 (Common Criteria
certified)
5.51.2098.0 (Common Criteria certified) -> 4.43.257.0 (Common Criteria
certified)
5.51.2098.0 (Common Criteria certified) -> 5.62.3126.0 (Common Criteria
certified)
5.60.2677.0 (Common Criteria certified) -> 4.43.257.0 (Common Criteria
certified)
5.60.2677.0 (Common Criteria certified) -> 5.62.3126.0 (Common Criteria
certified)
5.61.2785.0 (Common Criteria certified) -> 4.43.257.0 (Common Criteria
certified)
5.61.2785.0 (Common Criteria certified) -> 5.62.3126.0 (Common Criteria
certified)
5.61.2789.0 (Common Criteria certified) -> 4.43.257.0 (Common Criteria
certified)
5.61.2789.0 (Common Criteria certified) -> 5.62.3126.0 (Common Criteria
certified)

ATTENTION:
Once the TPM has been updated to the FIPS firmware the TPM firmware can no
longer be updated to a Common Criteria certified version.

Please note that TPM Firmware Update between TPM1.2 and TPM2.0 families or to a
FIPS version resets the TPM to factory defaults. For further details about TPM
factory defaults please refer to IFXTPMUpdate Programmers Reference Manual.


5.2 New Features, Fixes, and Improvements

[N]ew Features, [R]emoved Features, [F]ixes, and [I]mprovements.

Changes since version 01.00.1619.00
- [I] TPMFactoryUpd: Documented the maximum log file path length
- [N] TPMFactoryUpd: Show additional TPM attributes in -info command line
      TPM1.2: TPM deferred physical presence, TPM enabled, TPM activated
      TPM2.0: platformAuth
- [I] TPMFactoryUpd: Improved user interface when TPM2.0 is in failure mode
- [I] TPMFactoryUpd: Improved behavior when resuming an interrupted firmware
      update
- [I] TPMFactoryUpd: Ensure orderly shutdown if system firmware is not TPM2.0
      aware
- [N] TPMFactoryUpd: Added new update type config-file to update a TPM to
      the latest version configured in that file.
- [I] TPMFactoryUpd and IFXTPMUpdate: Added error handling for TPM_RESOURCE
      return code from TPM_FieldUpgradeInfoRequest2 TPM command.

Changes since version 01.00.1573.00
- [I] TPMFactoryUpd: Use CRLF line endings in log files consistently

Changes since version 01.00.1525.00
- [I] TPMFactoryUpd: Performance improvements for Microsoft Windows PE

Changes since version 01.00.1370.00
- [I] TPMFactoryUpd: Stability improvements for Microsoft Windows PE

Changes since version 01.00.1122.00
- [N] TPMFactoryUpd: Setting TPM to factory defaults triggers a message
- [N] IFXTPMUpdate: Flag IMAGE_UPDATABLE_IFXTPM_FACTORY_DEFAULTS to indicate
       that an update with this image resets the TPM back to factory defaults
- [N] IFXTPMUpdate: Return codes 0xE02900000000600F to 0xE029000000006012 and
       corresponding error messages
- [N] TPMFactoryUpd: Return code 0xE0295516 and corresponding error message
- [I] IFXTPMUpdate: Firmware version display format for TPM1.2 aligned with
       firmware version display format for TPM2.0
- [I] TPMFactoryUpd: Display number of remaining updates
- [N] IFXTPMUpdate: Accepts only firmware images with content digitally signed
       by Infineon
- [N] TPMFactoryUpd: Accepts only firmware images with content digitally signed
       by Infineon
- [N] TPMFactoryUpd: -tpm12-clearownership command line option, return codes
       0xE0295522 and 0xE0295523 and corresponding error messages

Changes since version 01.00.1065.00
- [N] IFXTPMUpdate: Return codes 0xE02900000000600D and 0xE02900000000600E
       for unsupported newer firmware images and Infineon TPMs
- [N] TPMFactoryUpd: Return code 0xE0295515 and corresponding error message
- [I] TPMFactoryUpd: Firmware version display format for TPM1.2 aligned with
       firmware version display format for TPM2.0

Changes since version 01.00.0903.00
- [N] TPMFactoryUpd: Support for Microsoft Windows PE (32-bit and 64-bit)
- [N] IFXTPMUpdate: Driver is signed by Microsoft Windows UEFI Driver Publisher
- [N] TPMFactoryUpd: Return codes 0xE0295513 and 0xE0295514 and corresponding
       error messages for unsupported newer firmware images and Infineon TPMs

Changes since version 01.00.0686.00
- [N] TPMFactoryUpd: Return codes 0xE0295510 to 0xE0295511 and corresponding
       error messages
- [N] TPMFactoryUpd: Capability to execute owner authorized
       TPM1.2 Firmware Update
- [N] TPMFactoryUpd.efi and IFXTPMUpdate.efi are signed with
       Infineon Technologies AG code signing certificate
- [I] TPMFactoryUpd: Direct TPM communication not utilizing IFXTPMUpdate UEFI
       driver anymore
- [R] TPMFactoryUpd: -driver command line option, return codes 0xE0295501 to
       0xE0295502 and corresponding error messages
- [N] TPMFactoryUpd: Return code 0xE0295512 and corresponding error message

Changes since version 01.00.0604.00
- [N] IFXTPMUpdate: Capability to execute owner authorized
       TPM1.2 Firmware Update
- [N] TPMFactoryUpd: Capability to execute Physical Presence authorized
       TPM1.2 Firmware Update
- [N] TPMFactoryUpd: Option <update_type> for command line parameter -update
- [N] TPMFactoryUpd: Return codes 0xE029550B to 0xE029550F and corresponding
       error messages


5.3 Known Bugs and Limitations

- Once the TPM has been updated to the FIPS firmware the TPM firmware can no
  longer be updated to a Common Criteria certified version.

- On some platforms after performing TPM Firmware Update no UEFI application can
  be started. The workaround is to restart the platform and start the 
  application again.

- In case TPM Firmware Update process has been interrupted, you need to reboot
  your system before retrying the update.
  In this case TPM Firmware Update must be resumed with the exact same firmware
  image that was used when the interruption occurred.
  The number of resume attempts is limited. For the exact number of resume
  attempts supported by a particular TPM model please consult TPM documentation
  or contact your local Infineon representative.

- TPMFactoryUpd can only be executed from within the same directory containing
  all application files. Thus, you first have to navigate to the application
  folder before starting the application.

- On Windows PE with additional TPM components (such as WinPE-SecureStartup)
  TPM Firmware Update may sporadically fail due to concurrent TPM operations 
  by the Windows PE operating system. The workaround is to restart the platform
  and retry the update. It is recommended to run TPM Firmware Update on 
  Windows PE without additional TPM components (such as WinPE-SecureStartup)
  and not to run any other applications in parallel to TPMFactoryUpd.