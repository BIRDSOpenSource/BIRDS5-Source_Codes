/*
#include <Mission Boss.h>
BYTE command[7];
BYTE command_ID;
unsigned char CPLD_flag;
int i;   //for counter
//LED Turn on and off
void LED(a)
{
   #define LED1 PIN_G2
   #define LED2 PIN_G3
   #define LED3 PIN_G4
   output_high (a); //LED_turn_on
   delay_ms (1000);
   output_low (a); //LED_turn_off
   delay_ms (1000);
}
//Send the one byte to OBC
void us_OBC(byte a)
{
   fputc (a, OBC);
   delay_ms (1000);
}
//Send the one byte to MB1
void us_MB1(byte a)
{
   fputc (a, MB1);
}
//Send the one byte to MB2
void us_MB2(byte a)
{
   fputc (a, MB2);
}
//Send the one byte to RAB
void us_RAB(byte a)
{
   fputc (a, RAB);
}
//continue transmit to MB1
void ct_MB1()
{
   for (int i = 0; i < 7; i++)
   {
      fputc (command[0], MB1);
   }
}
//Change the line on CPLD
//Basically, MCAM1, MCAM2, and PINO are connected to MB
//When the pin is high, the connection changes to ADCS, S&F, and DLP
//Put the sel1, sel2, or cl_RAB
void cl_CPLD(a)
{
   output_high (a);
   CPLD_flag = a;
}
//Change the nominarl connection on CPLD
void cl_CPLD_clear()
{
   output_low (CPLD_flag);
}
//UART transmisfer test1
void ut_test1()
{
   if (fgetc (MB1) > 0)
   {
      for (i = 0; i < 7; i++)
      {
         command[i] = fgetc (MB1);
      }
      
      //LED (LED1);
      
      for (i = 0; i < 7; i++)
      {
         fputc (command[i], MB1);
      }
      //LED (LED2);
   }
}
//UART transfer test2
void ut_test2()
{
   if (fgetc (MB1) > 0)
   {
      for (i = 0; i < 7; i++)
      {
         command[i] = fgetc (MB1);
      }
      if (command[0] = 0x01)
      {
         //LED (LED1);
      }
      else if (command[0] = 0x02)
      {
         //LED (LED2);
      }
   }
}
//UARt transfer test3
void ut_test3()
{
   if (fgetc (MB1) > 0)
   {
      for (i = 0; i < 7; i++)
      {
         command[i] = fgetc (MB1);
      }
      
      
      switch (command[0])
      {
         case 49:
         fprintf (MB1, "Good");
         break;
         case 2:
         //LED (LED2);
         break;
         case 3:
         //LED (LED3);
         break;
      }
   }
}

#define sel0 PIN_D1   //CPLD(I)
#define sel1 PIN_D2   //CPLD(H)
#define sel2 PIN_D3   //CPLD(G)
           0 1  2
PINO       0      0      0
MCAM-1     0      1      0
MCAM-2     0      0      1
APRS&SF    1      0      1
ADCS       1      1      0
IC&DLP     1      0      0

void set_CPLD(command_ID)
{
   BYTE MP_ID = command_ID>>4;
   
   switch (MP_ID)
   {
      case 0x01:
      break;
      
      case 0x02://MCAM - 1
      output_low (sel0);
      output_high (sel1);
      output_low (sel2);
      break;
      
      case 0x03://MCAM - 2
      output_low (sel0);
      output_low (sel1);
      output_high (sel2);
      break;
      
      case 0x04://ADCS
      output_high (sel0);
      output_high (sel1);
      output_low (sel2);
      break;
      
      case 0x05://S&F
      output_high (sel0);
      output_low (sel1);
      output_high (sel2);
      break;
      
      case 0x06://APRS
      output_high (sel0);
      output_low (sel1);
      output_high (sel2);
      break;
      
      case 0x07://DLP
      output_high (sel0);
      output_low (sel1);
      output_low (sel2);
      break;
      
      case 0x08://I - C
      output_high (sel0);
      output_low (sel1);
      output_low (sel2);
      break;
      
      case 0x09://PINO
      output_low (sel0);
      output_low (sel1);
      output_low (sel2);
      break;
   }
}
BYTE command_data[39];
BYTE operate_data[1];
void get_command()
{
   for (int i = 0; i < 39; i++)
   {
      command_data[i] = fgetc (OBC);
   }
}

void command_operate()
{
   operate_data[0] = command_data[0] << 4;
   switch (command_data[0])
   {
      case 0x02:
      set_MCAM1 ();
      do_MCAM1 ();
      
      case 0x03:
      set_MCAM2 ();
      do_MCAM2 ();
      
      case 0x04:
      set_ADCS ();
      do_ADCS ();
      
      case 0x05:
      set_SF ();
      do_SF ();
      
      case 0x06:
      set_APRS ();
      do_APRS ();
      
      case 0x07:
      set_DLP ();
      do_DLP ();
      
      case 0x08:
      set_IC ();
      do_IC ();
      
      case 0x90:
      set_PINO ();
      do_PINO ();
   }
}

#include <MCAM1.h>
*/

int8 command_data[39] = {};

void DEL_CMD_DATA()
{
   for (int8 m = 0; m < 9; m++)
   {
      command_data[m] = 0;
   }
   return;
}
void return_CMD_DATA()
{
   if (command_data[0])
   {
      for (int8 m = 0; m < 9; m++)
      {
         fputc (command_data[m], OBC);
         delay_ms (5);
      }
   }
   return;
}
void DEL_DOWN_DATA()
{
   for (int8 m = 0; m < 81; m++)
   {
      Down_data[m] = 0;
   }
   return;
}
void return_DOWN_DATA()
{
   delay_ms (50);
   for (int8 m = 0; m < 81; m++)
   {
      fputc (Down_data[m], OBC);
      delay_ms (5);
   }
   return;
}

