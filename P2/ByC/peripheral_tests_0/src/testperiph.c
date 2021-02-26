#include <stdio.h>
#include <xstatus.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xuartlite.h"
#include "xbasic_types.h"
#include "xgpio.h"
/*#include "gpio_header.h"*/

#define LEDs_HW_BASEaddress (0x81420000)
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


int operando, operando2, sum;
char key;
int main()
{
	//���NOTA IMPORTANTE!!! EST� PROGRAMADO PARA QUE SE EJECUTE CON EL TERMITE EN MODO APPEND LF

	XGpio Gpio_LEDs; /* The driver instance for GPIO Device configured as Salida */
	XGpio GpioSwitches;  /* The driver instance for GPIO Device configured as Entrada */
	Xil_ICacheEnable();
    Xil_DCacheEnable();
    u32 DataRead;


	// Configuraci�n de la GPIO para los LEDs de la placa extendida
	XGpio_Initialize(&Gpio_LEDs, XPAR_LEDS_DEVICE_ID); /*Obtiene el puntero a la estructura */
	XGpio_SetDataDirection(&Gpio_LEDs, 1, 0x0); /*Coloca la direcci�n de salida */

	// Configuraci�n de la GPIO para los Switches
	XGpio_Initialize(&GpioSwitches, XPAR_SWITCHES_DEVICE_ID); /*Obtiene el puntero a la estructura */
	XGpio_SetDataDirection(&GpioSwitches, 1, 0xFF); /*Coloca la direcci�n de entrada */

	// escribe un mensaje en la pantalla del hyperterminal
	xil_printf("a.- Introducir primer operando y visualizarlo en los leds y en la pantalla\n\r");
	xil_printf("b.- Introducir segundo operando y visualizarlo en los leds y en la pantalla\n\r");
	xil_printf("c.- Sumar y visualizar el resultado en los leds y en la pantalla\n\r");
	xil_printf("d.-visualizar en los leds y en la pantalla el dato le�do en los switches.\n\r");

	// lee una letra de teclado

	key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
	XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);

	if(key == 'a'){

		xil_printf("Introduce un primer operando\n\r");
    // lee un n�mero de teclado

		operando = getNumber();
		print("\r\n");

	// muestra por led el primer operando
		XGpio_DiscreteWrite(&Gpio_LEDs, 1, operando);

		xil_printf("Introduce letra b\n\r");
		key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
		XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);

		if(key == 'b'){

				xil_printf("Introduce un segundo operando\n\r");
		    // lee un n�mero de teclado

				operando2 = getNumber();
				print("\r\n");

			//muestra en los leds el segundo operando
				XGpio_DiscreteWrite(&Gpio_LEDs, 1, operando2);

				xil_printf("Introduce letra c\n\r");
				key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
				XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);

				if(key == 'c'){

						sum = operando + operando2;
						// escribe la suma en la pantalla del hyperterminal
						XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,sum+'0');

						//muestra la suma de ambos operandos
							XGpio_DiscreteWrite(&Gpio_LEDs, 1, sum);
						print("\r\n");
				}
		}
	}
	else if(key == 'd'){
		DataRead = XGpio_DiscreteRead(&GpioSwitches, XPAR_SWITCHES_DEVICE_ID);

		XGpio_DiscreteWrite(&Gpio_LEDs, 1, DataRead);

		xil_printf("%x",DataRead);
		print("\r\n");
	}
   print("-- Exiting main() --\r\n");

   Xil_DCacheDisable();
   Xil_ICacheDisable();
   return 0;


}





