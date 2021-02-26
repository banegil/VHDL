/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */


#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xbram.h"
#include "bram_header.h"
#include "coprocesador.h"


int main() 
{


	   print("---Entering main---\n\r");



	   {
			  int     Index;
			  Xuint32 baseaddr;
			  Xuint8  Reg8Value;
			  Xuint16 Reg16Value;
			  Xuint32 Reg32Value;

			  /*
			   * Check and get the device address
			   */
			  /*
			   * Base Address maybe 0. Up to developer to uncomment line below.
			  XASSERT_NONVOID(baseaddr_p != XNULL);
			   */
			  baseaddr = (Xuint32) XPAR_COPROCESADOR_0_BASEADDR;

			  xil_printf("******************************\n\r");
			  xil_printf("* User Peripheral Self Test\n\r");
			  xil_printf("******************************\n\n\r");

			  /*
			   * Write to user logic slave module register(s) and read back
			   */
			  xil_printf("User logic slave module test...\n\r");
			  xil_printf("   - write 1 to slave register 0 word 0\n\r");
			  COPROCESADOR_mWriteSlaveReg0(baseaddr, 0, 1);
			  Reg32Value = COPROCESADOR_mReadSlaveReg0(baseaddr, 0);
			  xil_printf("   - read %d from register 0 word 0\n\r", Reg32Value);
			  if ( Reg32Value != (Xuint32) 1 )
			  {
			    xil_printf("   - slave register 0 word 0 write/read failed\n\r");
			    return XST_FAILURE;
			  }
			  xil_printf("   - write 2 to slave register 1 word 0\n\r");
			  COPROCESADOR_mWriteSlaveReg1(baseaddr, 0, 2);
			  Reg32Value = COPROCESADOR_mReadSlaveReg1(baseaddr, 0);
			  xil_printf("   - read %d from register 1 word 0\n\r", Reg32Value);
			  if ( Reg32Value != (Xuint32) 2 )
			  {
			    xil_printf("   - slave register 1 word 0 write/read failed\n\r");
			    return XST_FAILURE;
			  }
			  xil_printf("   - write 3 to slave register 2 word 0\n\r");
			  COPROCESADOR_mWriteSlaveReg2(baseaddr, 0, 3);
			  Reg32Value = COPROCESADOR_mReadSlaveReg2(baseaddr, 0);
			  xil_printf("   - read %d from register 2 word 0\n\r", Reg32Value);
			  if ( Reg32Value != (Xuint32) 3 )
			  {
			    xil_printf("   - slave register 2 word 0 write/read failed\n\r");
			    return XST_FAILURE;
			  }
			  xil_printf("   - write 4 to slave register 3 word 0\n\r");
			  COPROCESADOR_mWriteSlaveReg3(baseaddr, 0, 4);
			  Reg32Value = COPROCESADOR_mReadSlaveReg3(baseaddr, 0);
			  xil_printf("   - read %d from register 3 word 0\n\r", Reg32Value);
			  if ( Reg32Value != (Xuint32) 4 )
			  {
			    xil_printf("   - slave register 3 word 0 write/read failed\n\r");
			    return XST_FAILURE;
			  }
			  xil_printf("   - slave register write/read passed\n\n\r");
			  while(1);
			  return XST_SUCCESS;
	   }


	   /*
	    * Peripheral SelfTest will not be run for xps_uartlite_0
	    * because it has been selected as the STDOUT device
	    */


	   print("---Exiting main---\n\r");

   return 0;
}

