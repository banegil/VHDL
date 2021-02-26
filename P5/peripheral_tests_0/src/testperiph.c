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

#define XPAR_RS232_UART_1_BASEADDR 0x84000000

char key = 'e';

int main() 
{


   Xil_ICacheEnable();
   Xil_DCacheEnable();

   // escribe un mensaje en la pantalla del hyperterminal
   xil_printf("Proyecto Final\n\r");
   xil_printf("\n\r");

   

   {
		while(key != 's'){
			xil_printf("a.-KEYPAD Y RECEPTOR/EMISOR INFRARROJOS\n\r");
			xil_printf("b.-ALTAVOZ\n\r");
			xil_printf("c.-ZUMBADOR\n\r");
			xil_printf("d.-LCD\n\r");

			// lee una letra de teclado
			key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);

			if(key == 'a')
				KEYPAD_SelfTest(key);
			else if(key == 'b' || key == 'c')
				ALTAVOZUMBADOR_SelfTest(key);
			else if(key == 'd')
				LCD_CONTROLLER_SelfTest(key);

			xil_printf("Escribe 's' si quieres terminar la ejecucion\n\r");
		}

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





