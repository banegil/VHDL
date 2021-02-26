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
#include "xuartlite.h"
#include "xbasic_types.h"
#include "pantalla.h"
#define AZUL 				0x000001C0
#define VERDE 				0x00000038
#define VERDE_OSCURO			0x00000018
#define ROJO 				0x00000007
#define BLANCO				0X000001FF
#define nfilas				16
#define ncolumnas			8


#define PANTALLA_BASE_ADDR 0xCD400000
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

   
   /*
    * Peripheral SelfTest will not be run for RS232
    * because it has been selected as the STDOUT device
    */

   Xuint32 baseaddr;
   Xuint32 Data;
   char filas, columnas;

   baseaddr = PANTALLA_BASE_ADDR;

   while(1){
	// escribe un mensaje en la pantalla del hyperterminal
   xil_printf("Elige numero maximo de filas:\n\r");
   filas = getNumber();

   xil_printf("Elige numero maximo de columnas:\n\r");
   columnas = getNumber();

   Data=   ((0xF & columnas) << 12 | (0xF & filas) << 16) ;
   PANTALLA_mWriteToFIFO(baseaddr, 0, Data);

   }

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}











