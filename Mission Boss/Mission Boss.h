#include <18F67J94.h>
#include <PIC18F67J94_registers.h>
#device ADC=16
#use delay(clock=16MHz, internal=16MHz)


#include <stdlib.h>
#pin_select TX1 = PIN_A2   //Main PIC
#pin_select RX1 = PIN_A3   //Main PIC
#pin_select TX2 = PIN_G1   //MB1, CPLD(84)
#pin_select RX2 = PIN_G0   //MB1, CPLD(83)
#pin_select TX3 = PIN_A1   //MB2, CPLD(88)
#pin_select RX3 = PIN_A0   //MB2, CPLD(89)
#pin_select TX4 = PIN_E1   //RAB, CPLD(81)
#pin_select RX4 = PIN_E0   //RAB, CPLD(82)
#use rs232(baud=9600, parity=N, UART1, bits=8, stream=OBC, ERRORS)
#use rs232(baud=9600, parity=N, UART2, bits=8, stream=MB1, ERRORS)
#use rs232(baud=9600, parity=N, UART3, bits=8, stream=MB2, ERRORS)
#use rs232(baud=9600, parity=N, UART4, bits=8, stream=RAB, ERRORS)
//#use rs232(baud=115200,parity=N,UART1,bits=8,stream=pc)
//#define LLL PIN_A5
/*
#define LED1 PIN_G2
#define LED2 PIN_G3
#define LED3 PIN_G4
*/
/*
-- sel(0) = CPLD(G) 72 sel for RAB
-- sel(1) = CPLD(H) 89 sel for MB2
-- sel(2) = CPLD(I) 92 sel for MB1
*/

#define PINO_sel PIN_F7
#define PINO_shut PIN_F6
#define cl_RAB PIN_D3   //CPLD(G) sel0 72
#define cl_MB2 PIN_D2   //CPLD(H) sel1 89
#define cl_MB1 PIN_D1   //CPLD(I) sel2 92




