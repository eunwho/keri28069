/*
//###########################################################################
//
// FILE:    origin  path : eunwho@eunwho-desktop:~/ti/c2000/C2000Ware_1_00_01_00/device_support/f2806x/common/cmd$ 28069_RAM_lnk.cmd
			28065_RAM_lnk_jsk.cmd

// TITLE:   Linker Command File For F28065 examples that run out of RAM
//          Keep in mind that L0,L1,L2,L3 and L4 are protected by the code
//          security module.
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
// The header linker files are found in <base>\headers\cmd
//
// For BIOS applications add:      F2806x_Headers_BIOS.cmd
// For nonBIOS applications add:   F2806x_Headers_nonBIOS.cmd
========================================================= */

/* Define the memory block start/length for the F2806x
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F28065 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         Contiguous SARAM memory blocks can be combined
         if required to create a larger memory block.
*/

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN      : origin = 0x000000, length = 0x000002
   RAMM0      : origin = 0x000050, length = 0x0003B0
   RAML0_L3   : origin = 0x008000, length = 0x002000	 /* RAML0-3 combined for size of .text */
   														 /* in Example_F2806xSWPrioritezedInterrupts */
   RESET      : origin = 0x3FFFC0, length = 0x000002
   FPUTABLES  : origin = 0x3FD860, length = 0x0006A0	 /* FPU Tables in Boot ROM */
   IQTABLES   : origin = 0x3FDF00, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2  : origin = 0x3FEA50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3  : origin = 0x3FEADC, length = 0x0000AA	 /* IQ Math Tables in Boot ROM */

   BOOTROM    : origin = 0x3FF3B0, length = 0x000C10


PAGE 1 :

   BOOT_RSVD   : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML4       : origin = 0x00A000, length = 0x002000     /* on-chip RAM block L4 */
   RAML5_L8    : origin = 0x00C000, length = 0x008000     /* on-chip RAM block L4 */
   USB_RAM     : origin = 0x040000, length = 0x000800     /* USB RAM		  */
}


SECTIONS
{
   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAMM0,     PAGE = 0
/*   .text            : > RAML0_L3,  PAGE = 0   */
   .text            : > RAML5_L8,  PAGE = 1
   .cinit           : > RAMM0,     PAGE = 0
   .pinit           : > RAMM0,     PAGE = 0
   .switch          : > RAML0_L3,  PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

/*   .stack           : > RAMM1,     PAGE = 1  */
   .stack           : > RAML0_L3,  PAGE = 0
   .ebss            : > RAML4,     PAGE = 1
   .econst          : > RAML0_L3,  PAGE = 0
   .esysmem         : > RAML4,     PAGE = 1

   IQmath           : > RAML0_L3,  PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
