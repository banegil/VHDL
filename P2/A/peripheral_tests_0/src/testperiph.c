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
#include <xstatus.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xuartlite.h"
#include "xuartlite_l.h"
#include "xuartlite_i.h"
#include "xbasic_types.h"
#include "xgpio.h"
/*#include "gpio_header.h"
*/

#define XPAR_RS232_UART_1_BASEADDR 0x84000000
#define LEDs_HW_BASEaddress (0x81420000)

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
	XGpio Gpio_LEDs; /* The driver instance for GPIO Device configured as Salida */
	XGpio GpioSwitches;  /* The driver instance for GPIO Device configured as Entrada */
	Xil_ICacheEnable();
   Xil_DCacheEnable();

   print("---Introduce un numero---\n\r");

   	   	   //���NOTA IMPORTANTE!!! EST� PROGRAMADO PARA QUE SE EJECUTE CON EL TERMITE EN MODO APPEND LF

			// Configuraci�n de la GPIO para los LEDs de la placa extendida
			XGpio_Initialize(&Gpio_LEDs, XPAR_LEDS_DEVICE_ID); /*Obtiene el puntero a la estructura */
			XGpio_SetDataDirection(&Gpio_LEDs, 1, 0x0); /*Coloca la direcci�n de salida */

			// Configuraci�n de la GPIO para los Switches
			XGpio_Initialize(&GpioSwitches, XPAR_SWITCHES_DEVICE_ID); /*Obtiene el puntero a la estructura */
			XGpio_SetDataDirection(&GpioSwitches, 1, 0xFF); /*Coloca la direcci�n de entrada */


{			u32  Data;
			/*para escribir una dato cualquiera (por ejemplo 5) hacemos*/
			Data= getNumber();
			XGpio_DiscreteWrite(&Gpio_LEDs, 1, Data);
			}
   print("---Exiting main---\n\r");

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}






