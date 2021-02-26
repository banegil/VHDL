/*****************************************************************************
* Filename:          C:\Users\baneg\Desktop\p3.C\otro/drivers/altavozumbador_v1_00_a/src/altavozumbador_selftest.c
* Version:           1.00.a
* Description:       Contains a diagnostic self-test function for the altavozumbador driver
* Date:              Wed Feb 17 14:29:18 2021 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "altavozumbador.h"


/************************** Constant Definitions ***************************/


/************************** Variable Definitions ****************************/


/************************** Function Definitions ***************************/

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the ALTAVOZUMBADOR instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */

#define SILENCIO 	0x00000000
#define DO 			0x00000BAA
#define RE 			0x00000A64
#define MI 			0x00000942
#define FA 			0x000008BD
#define SOL 		0x000007C9
#define LA 			0x000006F0
#define SI 			0x0000062E
#define OCTAVA 	3
#define XPAR_ALTAVOZ_0_BASEADDR 0xC9400000
#define XPAR_RS232_UART_1_BASEADDR 0x84000000

void my_delay(int delay){
	int i, j;
	for (i=0; i<delay; i=i+1)
		for (j=0; j<500; j=j+1){}
}

void ALTAVOZ_suena(Xuint32 nota, Xuint32 octava){
	ALTAVOZUMBADOR_mWriteSlaveReg0(XPAR_ALTAVOZ_0_BASEADDR, 0, nota << octava);
}

void ALTAVOZ_calla(){
	ALTAVOZUMBADOR_mWriteSlaveReg0(XPAR_ALTAVOZ_0_BASEADDR, 0, SILENCIO);
}

XStatus ALTAVOZUMBADOR_SelfTest(char key)
{
  Xuint32 baseaddr;

  baseaddr = XPAR_ALTAVOZ_0_BASEADDR;

  //ZUMBADOR
  while(key != 's'){
	  if(key == 'c'){
		  //Enciendo zumbador
		  ALTAVOZUMBADOR_mWriteSlaveReg1(baseaddr, 0, 0);
		  my_delay(3000);
		  //Apago zumbador
		  ALTAVOZUMBADOR_mWriteSlaveReg1(baseaddr, 0, 1);

	  }
	  //ALTAVOZ
	  else{
		  ALTAVOZ_suena(DO, OCTAVA);
		  my_delay(300); print("DO\n\r");
		  ALTAVOZ_suena(RE, OCTAVA);
		  my_delay(300); print("RE\n\r");
		  ALTAVOZ_suena(MI, OCTAVA);
		  my_delay(300); print("MI\n\r");
		  ALTAVOZ_suena(FA, OCTAVA);
		  my_delay(300); print("FA\n\r");
		  ALTAVOZ_suena(SOL, OCTAVA);
		  my_delay(300); print("SL\n\r");
		  ALTAVOZ_suena(LA, OCTAVA);
		  my_delay(300); print("LA\n\r");
		  ALTAVOZ_suena(SI, OCTAVA);
		  my_delay(300); print("SI\n\r");
		  ALTAVOZ_suena(DO, (OCTAVA-1));
		  my_delay(300); print("DO\n\r");
		  ALTAVOZ_calla();
		  my_delay(300); print("--\n\r");
		  ALTAVOZ_suena(DO, (OCTAVA-1));
		  my_delay(300); print("DO\n\r");
		  ALTAVOZ_suena(SI, OCTAVA);
		  my_delay(300); print("SI\n\r");
		  ALTAVOZ_suena(LA, OCTAVA);
		  my_delay(300); print("LA\n\r");
		  ALTAVOZ_suena(SOL, OCTAVA);
		  my_delay(300); print("SL\n\r");
		  ALTAVOZ_suena(FA, OCTAVA);
		  my_delay(300); print("FA\n\r");
		  ALTAVOZ_suena(MI, OCTAVA);
		  my_delay(300); print("MI\n\r");
		  ALTAVOZ_suena(RE, OCTAVA);
		  my_delay(300); print("RE\n\r");
		  ALTAVOZ_suena(DO, OCTAVA);
		  my_delay(300); print("DO\n\r");
		  ALTAVOZ_calla();
	  }
	  xil_printf("Escribe 's' si quieres salir del modo altavoz/zumbador \n\r");
		// lee una letra de teclado
		key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
		XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
  }

  return XST_SUCCESS;
}
