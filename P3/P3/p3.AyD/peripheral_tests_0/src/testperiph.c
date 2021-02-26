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

#define XPAR_RS232_UART_1_BASEADDR 0x84000000

int getNumber (){

	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;

	while(1){
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		//get bytes from uart until RETURN is entered

		while(byte != 0x0d && byte != 0x0A){
			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			uartBuffer[digitIndex] = byte;
			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,byte);
			digitIndex++;
		}

		//calculate number from string of digits

		for(c = 0; c < (digitIndex - 1); c++){
			if(c == 0){
				//check if first byte is a "-"
				if(uartBuffer[c] == 0x2D){
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if((uartBuffer[c] >> 4) == 0x03){
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			else{
				//check byte is a digit
				if((uartBuffer[c] >> 4) == 0x03){
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;
		}
		number *= sign;
		if(validNumber == XTRUE){
			return number;
		}
		print("This is not a valid number.\n\r");
	}
}

int main()
{


   Xil_ICacheEnable();
   Xil_DCacheEnable();

   print("---Entering main---\n\r");

   /*NOTA: ESTE PROGRAMA SE DEBE EJECUTAR CON APPEND LF!!!*/

   {
	   Xuint32 baseaddr;
	   Xuint32 Reg32Value;
	   int operando;

	   baseaddr = (Xuint32) XPAR_COPROCESADOR_0_BASEADDR;

	   while(1){
  	// escribe un mensaje en la pantalla del hyperterminal
	   xil_printf("Para que se comporte como apartado D introduce un numero con 1 en el 2ºbit. 2, 3, 6, 7.. (NOTA: los switches deben estar a x0xx)\n\r");
	   xil_printf("Para que se comporte como apartado A introduce un numero con 0 en el 2ºbit. 0 para suma y 1 para resta \n\r");


	   operando = getNumber();
	   print("\r\n");

	   xil_printf("   - Escribiendo numero en registro 0...\n\r");
	   COPROCESADOR_mWriteSlaveReg0(baseaddr, 0, operando);
	   Reg32Value = COPROCESADOR_mReadSlaveReg0(baseaddr, 0);
	   xil_printf("   - Se lee %d de registro 0 \n\r", Reg32Value);

	   if(operando & (1<<1)){

		   Reg32Value = COPROCESADOR_mReadSlaveReg3(baseaddr, 0);
		   xil_printf("   - Se lee %d de registro 3 con valor del contador \n\r", Reg32Value);

		   print("\r\n");
	   }

	   else if((operando & (1<<1)) == 0){

			   print("Introduce primer operando\r\n");
			   operando = getNumber();
			   print("\r\n");

			   xil_printf("   - Escribiendo numero en registro 1...\n\r");
			   COPROCESADOR_mWriteSlaveReg1(baseaddr, 0, operando);
			   Reg32Value = COPROCESADOR_mReadSlaveReg1(baseaddr, 0);

			   print("Introduce segundo operando\r\n");
			   operando = getNumber();
			   print("\r\n");

			   xil_printf("   - Escribiendo numero en registro 2...\n\r");
			   COPROCESADOR_mWriteSlaveReg2(baseaddr, 0, operando);

			   if((Reg32Value & (1<<0)) == 0){
				   xil_printf("La suma de reg1 y reg2 es: \n\r");
			   }
			   else if(Reg32Value & (1<<0)){
				   xil_printf("La resta de reg1 y reg2 es: \n\r");
			   }

			   Reg32Value = COPROCESADOR_mReadSlaveReg3(baseaddr, 0);
			   xil_printf(" %d \n\r", Reg32Value);
			   print("\r\n");
		}//else if
	  }//while
   }


   /*
    * Peripheral SelfTest will not be run for xps_uartlite_0
    * because it has been selected as the STDOUT device
    */


   print("---Exiting main---\n\r");

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}

