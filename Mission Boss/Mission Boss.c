#include <Mission Boss.h>

int8 CMD_FROM_OBC[9] = {};
int8 OBC_DATA = 0; 
int8 count = 0;
int8 command_data[39] = {};
int8 Down_data[81] = {};
int8 Down_data_p[81] = {};
int8 MCAM1_ack = 0;
int8 MCAM2_ack = 0;
int8 IMGCLS_ack = 0;
int8 ADCS_data[14] = {};
int8 IMG_data[14] = {};
int8 t;
int8 packet_No;
int num;
int8 ADCS_ACK = 0;
static int8 p_flag = 0;
static int32 t_counter = 0;
//!#int_rda                                                                         //PC Interrupt, RS232 receive data available in buffer 1
//!void UART1_RXD(void)
//!{
//!   CMD_FROM_OBC[OBC_DATA] = fgetc (OBC); //carga el array CMD_FROM_PC[] con los datos enviados por PC
//!   OBC_DATA = ( (OBC_DATA + 1) % 9); //cuando se obtenga el dato en la posicion 6, PC_DATA=0
//!}
//!#int_timer0                                                                      //TMR0 Interrupt
//!void intval()
//!{
//!   //the variable is activated as global, it maintains its value when entering and exiting the function
//!   t_counter++; //increases every 16.384ms
//!   if ((t_counter > 300) && (p_flag == 1) ) //the counters within the if are incremented approx every 1s (counter = 60)
//!   {
//!      for (t = 0; t < 81; t++)
//!      {
//!         fputc (Down_data_p[t], RAB);
//!         fputc (Down_data_p[t], OBC);
//!      }
//!      p_flag = 2;
//!      t_counter = 0;
//!      fprintf (RAB, "Time out\r\n");
//!      break;
//!   }
//!}
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


void main()
{
   
   
   set_tris_b (0b11010000);
   //enable_interrupts (int_rda);
   //setup_timer_0 (RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_BIT);
   //enable_interrupts (int_timer0);
   //enable_interrupts (global);
   output_low (PIN_B4); //ADCS OFF 
   output_low (PIN_B0); //APRS and SFWD OFF
   output_low (PIN_B1);
   output_low (PIN_B5);
   while (TRUE)
   {
      
      count = 0;
      for (int32 num = 0; num < 1000000; num++)
      {
         if (kbhit (OBC) )
         {
            command_data[count] = fgetc (OBC);
            count++;
            if (count == 9)
            {
               break;
            }
         }
      }
      
      BYTE command_ID = command_data[0];
      command_ID &= 0xF0;
      
      if (command_ID == 0x20) //MCAM1
      {
         output_low (cl_RAB);
         output_high (cl_MB2);
         output_low (cl_MB1);
         delay_ms(50);
         //Operation_M1(command_data[0], command_data[2], command_data[3], command_data[4], command_data[5], command_data[6], command_data[7], command_data[8]);
      }
      
      if (command_ID == 0x30) //MCAM2
      {
         output_low (cl_RAB);
         output_low (cl_MB2);
         output_high (cl_MB1);
      }
      
      if (command_ID == 0x40) //ADCS
      {
         output_high (cl_RAB);
         output_high (cl_MB2);
         output_low (cl_MB1);
      }
      
      if (command_ID == 0x50||command_ID == 0x60) //S - FWD or APRS - DP
      {
         output_high (cl_RAB);
         output_low (cl_MB2);
         output_high (cl_MB1);
      }
      if (command_ID == 0x70||command_ID == 0x80) //IMGCLS or DLP
      {
         output_high (cl_RAB);
         output_low (cl_MB2);
         output_low (cl_MB1);
      }
      
      if (command_ID == 0x90) //PINO
      {
         output_low (cl_RAB);
         output_low (cl_MB2);
         output_low (cl_MB1);
      }
      switch (command_data[0])
      {
      
         
         
         /////////////////////////////MCAM - 1//////////////////////////////////////////
         case 0x20: //Turn off MCAM1
         
         //Main PIC controls MCAM Power
         DEL_CMD_DATA ();
         
         break;
         
         case 0x2E: // Turn on MCAM1
         
         //Main PIC controls MCAM Power
         DEL_CMD_DATA ();
         
         break;
         
         case 0x21: //Real time uplink
         
         fputc (command_data[0], MB1);
         delay_ms (25);
         fputc (command_data[2], MB1);
         delay_ms (25);
         fputc (command_data[3], MB1);
         delay_ms (25);
         fputc (command_data[4], MB1);
         delay_ms (25);
         fputc (command_data[5], MB1);
         delay_ms (25);
         fputc (command_data[6], MB1);
         delay_ms (25);
         fputc (command_data[7], MB1);
         delay_ms (25);
         fputc (command_data[8], MB1);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x22: //Real Time Data Downlink (1 packet)
         
         fputc (command_data[0], MB1);
         delay_ms (30);
         fputc (command_data[2], MB1);
         delay_ms (30);
         fputc (command_data[3], MB1);
         delay_ms (30);
         fputc (command_data[4], MB1);
         delay_ms (30);
         fputc (command_data[5], MB1);
         delay_ms (30);
         fputc (command_data[6], MB1);
         delay_ms (30);
         fputc (command_data[7], MB1);
         delay_ms (30);
         fputc (command_data[8], MB1);
         delay_ms (30);
         
         count = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB1) )
            {
               Down_data[count] = fgetc (MB1);
               count++;
               if (count == 81)
               {
                  break;
               }
            }
         }
         
         return_DOWN_DATA ();
         
         int8 counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (MB1) )
            {
               Down_data[counter] = fgetc (MB1);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         DEL_CMD_DATA ();
         DEL_DOWN_DATA ();
         
         break;
         
         case 0x23: 
         case 0x24:
         case 0x26:
         case 0x27:
         case 0x28:
         case 0x29:
         
         fputc (command_data[0], MB1);
         delay_ms (25);
         fputc (command_data[2], MB1);
         delay_ms (25);
         fputc (command_data[3], MB1);
         delay_ms (25);
         fputc (command_data[4], MB1);
         delay_ms (25);
         fputc (command_data[5], MB1);
         delay_ms (25);
         fputc (command_data[6], MB1);
         delay_ms (25);
         fputc (command_data[7], MB1);
         delay_ms (25);
         fputc (command_data[8], MB1);
         
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB1) )
            {
               MCAM1_ack = fgetc (MB1);
               break;
            }
         }
         
         fputc (MCAM1_ack, OBC);
         
         MCAM1_ack = 0;
         
         DEL_CMD_DATA ();
         
         break;
         
         ///////////////////////////////MCAM - 2///////////////////////////////
         
         case 0x30: //Turn off MCAM2
         
         //Main PIC controls MCAM Power
         DEL_CMD_DATA ();
         
         break;
         
         case 0x3E: //Turn on MCAM2
         
         //Main PIC controls MCAM Power
         DEL_CMD_DATA ();
         break;
         
         case 0x31: //Real time Uplink
         
         fputc (command_data[0], MB2);
         delay_ms (25);
         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         delay_ms (25);
         fputc (command_data[8], MB2);
         
         DEL_CMD_DATA ();
         break;
         
         case 0x32: //Real Time Data Downlink (1 packet) from MCAM2
         fputc (command_data[0], MB2);
         delay_ms (25);
         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         delay_ms (25);
         fputc (command_data[8], MB2);
         
         count = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB2) )
            {
               Down_data[count] = fgetc (MB2);
               count++;
               if (count == 81)
               {
                  break;
               }
            }
         }
         
         return_DOWN_DATA ();
         
         counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (MB2) )
            {
               Down_data[counter] = fgetc (MB2);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         DEL_CMD_DATA ();
         DEL_DOWN_DATA ();
         
         break;
         
         case 0x33: 
         case 0x34:
         case 0x36:
         case 0x37:
         case 0x38:
         case 0x39:
         
         fputc (command_data[0], MB2);
         delay_ms (25);
         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         delay_ms (25);
         fputc (command_data[8], MB2);
         
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB2) )
            {
               MCAM2_ack = fgetc (MB2);
               break;
            }
         }
         
         fputc (MCAM2_ack, OBC);
         
         MCAM2_ack = 0;
         
         DEL_CMD_DATA ();
         
         break;
         
         ///////////////////////////////ADCS////////////////////////////////////////////
         case 0x40: // Turn off ADCS
         
         output_low (PIN_B4);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x4E: //Turn on ADCS
         
         output_high (PIN_B4);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x41: // Real time Uplink to ADCS (sends 8 bytes)
         
         fputc (command_data[0], MB1);
         delay_ms (5);
         for (t = 2; t < 9; t++)
         {
            fputc (command_data[t], MB1);
            delay_ms (5);
         }
         DEL_CMD_DATA ();
         
         break;
         
         case 0x42: // Real time Downlink from ADCS (sends 14 bytes)
         
         fputc (command_data[1], MB1);
         delay_ms (5);
         
         int8 ADCS_counter = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB1) )
            {
               ADCS_data[ADCS_counter] = fgetc (MB1);
               ADCS_counter++;
               if (ADCS_counter == 14)
               {
                  break;
               }
            }
         }
         
         
         for (int8 m = 0; m < 14; m++)
         {
            fputc (ADCS_data[m], OBC);
            delay_ms (5);
         }
         
         ADCS_counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (MB1) )
            {
               ADCS_data[ADCS_counter] = fgetc (MB1);
               ADCS_counter++;
               if (ADCS_counter == 81)
               {
                  break;
               }
            }
         }
         
         for (m = 0; m < 14; m++)
         {
            ADCS_data[m] = 0;
         }
         
         DEL_CMD_DATA ();
         
         break;
         
         case 0x43:
         fputc(0xCC, OBC);
         
         break;
         
         
         ///////////////////////////////S&F/////////////////////////////////////////////
         
         case 0x50:// Turn off S - FWD and APRS - DP
         
         output_low (PIN_B0);
         output_low (PIN_B1);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x5E: // Turn on S - FWD (turns on both S - FWD and APRS - DP)
         
         output_high (PIN_B0);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x51://S&F
         
         fputc (command_data[0], MB2);
         delay_ms (5);
         for (t = 2; t < 9; t++)
         {
            fputc (command_data[t], MB2);
            delay_ms (5);
         }
         DEL_CMD_DATA ();
         break;
         
         case 0x52: // Real - time Downlink (1 packet)
         
         fputc (command_data[0], MB2);
         delay_ms (25);
         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         delay_ms (25);
         fputc (command_data[8], MB2);

         counter = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB2) )
            {
               Down_data[counter] = fgetc (MB2);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         return_DOWN_DATA ();
         
         counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (MB2) )
            {
               Down_data[counter] = fgetc (MB2);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         DEL_DOWN_DATA ();
         DEL_CMD_DATA ();
         
         break;
         
         case 0x53:
         case 0x54:

         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         delay_ms (25);
         fputc (command_data[8], MB2);
         
         packet_No = command_data[8];
         counter = 0;
         
         int16 w = 0;
         int16 input=0;
         for (int32 i = 0; i < 10000000; i++)
         {
            if (kbhit (MB2) )
            {
               input = fgetc (MB2);
               fputc(input, OBC);
               w++;
               if (counter == 81*packet_No)
               {
                  break;
               }
            }
         }
         
         
         delay_ms(5000);
         DEL_DOWN_DATA ();
         DEL_CMD_DATA ();
         
         break;
         
         
         case 0x55:
         
         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         delay_ms (25);
         fputc (command_data[8], MB2);
         
         DEL_DOWN_DATA ();
         DEL_CMD_DATA ();
         
         break;
         
         ////////////////////////////APRS///////////////////////////////////////////////
         case 0x60: //Turn off APRS - DP
         
         output_low (PIN_B1);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x6E: //Turn on APRS - DP
         
         output_high (PIN_B1);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x61://Real time Uplink
         
         fputc (command_data[0], MB2);
         delay_ms (5);
         for (t = 2; t < 9; t++)
         {
            fputc (command_data[t], MB2);
            delay_ms (5);
         }
         DEL_CMD_DATA ();
         
         break;
         
         case 0x62://Real time Downlink
         
         fputc (command_data[1], MB2);
         delay_ms (25);
         fputc (command_data[2], MB2);
         delay_ms (25);
         fputc (command_data[3], MB2);
         delay_ms (25);
         fputc (command_data[4], MB2);
         delay_ms (25);
         fputc (command_data[5], MB2);
         delay_ms (25);
         fputc (command_data[6], MB2);
         delay_ms (25);
         fputc (command_data[7], MB2);
         
         counter = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (MB2) )
            {
               Down_data[counter] = fgetc (MB2);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         return_DOWN_DATA ();
         
         counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (MB2) )
            {
               Down_data[counter] = fgetc (MB2);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         DEL_DOWN_DATA ();
         DEL_CMD_DATA ();
         
         break;
         ////////////////////////////DLP////////////////////////////////////////////////
         case 0x70://Turn off DLP
         
         fputc (command_data[0], RAB);
         delay_ms (25);
         fputc (command_data[2], RAB);
         delay_ms (25);
         fputc (command_data[3], RAB);
         delay_ms (25);
         fputc (command_data[4], RAB);
         delay_ms (25);
         fputc (command_data[5], RAB);
         delay_ms (25);
         fputc (command_data[6], RAB);
         delay_ms (25);
         fputc (command_data[7], RAB);
         delay_ms (25);
         fputc (command_data[8], RAB);
         DEL_CMD_DATA ();
         
         //add delay here after Pi shuts down itself before lowering power pin
         output_low (PIN_B5);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x7E://Turn on DLP
         
         output_high (PIN_B5);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x71:// Real time uplink
         
         fputc (command_data[0], RAB);
         delay_ms (25);
         fputc (command_data[2], RAB);
         delay_ms (25);
         fputc (command_data[3], RAB);
         delay_ms (25);
         fputc (command_data[4], RAB);
         delay_ms (25);
         fputc (command_data[5], RAB);
         delay_ms (25);
         fputc (command_data[6], RAB);
         delay_ms (25);
         fputc (command_data[7], RAB);
         delay_ms (25);
         fputc (command_data[8], RAB);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x72://Real time Downlink
         
         fputc (command_data[0], RAB);
         delay_ms (25);
         fputc (command_data[2], RAB);
         delay_ms (25);
         fputc (command_data[3], RAB);
         delay_ms (25);
         fputc (command_data[4], RAB);
         delay_ms (25);
         fputc (command_data[5], RAB);
         delay_ms (25);
         fputc (command_data[6], RAB);
         delay_ms (25);
         fputc (command_data[7], RAB);
         delay_ms (25);
         fputc (command_data[8], RAB);
         
         count = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (RAB) )
            {
               Down_data[count] = fgetc (RAB);
               count++;
               if (count == 81)
               {
                  break;
               }
            }
         }
         
         return_DOWN_DATA ();
         
         counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (RAB) )
            {
               Down_data[counter] = fgetc (RAB);
               counter++;
               if (counter == 81)
               {
                  break;
               }
            }
         }
         
         DEL_CMD_DATA ();
         DEL_DOWN_DATA ();
         
         break;
         
         case 0x73: //SPI Test
         
         fputc (command_data[0], RAB);
         delay_ms (25);
         fputc (command_data[2], RAB);
         delay_ms (25);
         fputc (command_data[3], RAB);
         delay_ms (25);
         fputc (command_data[4], RAB);
         delay_ms (25);
         fputc (command_data[5], RAB);
         delay_ms (25);
         fputc (command_data[6], RAB);
         delay_ms (25);
         fputc (command_data[7], RAB);
         delay_ms (25);
         fputc (command_data[8], RAB);
         DEL_CMD_DATA ();
         
         break;
         
         /////////////////////////////I - C/////////////////////////////////////////////
         case 0x80://I - C off
         
         output_low (PIN_B5);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x8E://I - C on
         
         output_high (PIN_B5);
         DEL_CMD_DATA ();
         
         break;
         
         case 0x81:
         case 0x83: 
         case 0x84:
         case 0x85:
         case 0x86:
         case 0x87:
         case 0x88:
         case 0x89:
         case 0x8A:
         case 0x8B:
         case 0x8C:
         case 0x8D:
         
         fputc (command_data[0], RAB);
         delay_ms (25);
         fputc (command_data[2], RAB);
         delay_ms (25);
         fputc (command_data[3], RAB);
         delay_ms (25);
         fputc (command_data[4], RAB);
         delay_ms (25);
         fputc (command_data[5], RAB);
         delay_ms (25);
         fputc (command_data[6], RAB);
         delay_ms (25);
         fputc (command_data[7], RAB);
         delay_ms (25);
         fputc (command_data[8], RAB);
         
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (RAB) )
            {
               IMGCLS_ack = fgetc (RAB);
               break;
            }
         }
         
         fputc (IMGCLS_ack, OBC);
         
         IMGCLS_ack = 0;
         
         DEL_CMD_DATA ();
         
         break;
         
         case 0x82://Real time Downlink
         
         fputc (command_data[0], RAB);
         delay_ms (25);
         fputc (command_data[2], RAB);
         delay_ms (25);
         fputc (command_data[3], RAB);
         delay_ms (25);
         fputc (command_data[4], RAB);
         delay_ms (25);
         fputc (command_data[5], RAB);
         delay_ms (25);
         fputc (command_data[6], RAB);
         delay_ms (25);
         fputc (command_data[7], RAB);
         delay_ms (25);
         fputc (command_data[8], RAB);
         
         count = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (RAB) )
            {
               IMG_data[count] = fgetc (RAB);
               count++;
               if (count == 14)
               {
                  break;
               }
            }
         }
         
         for (int8 k = 0; k < 14; k++)
         {
            fputc (IMG_data[k], OBC);
            delay_ms (5);
         }
         
         counter = 0;
         for (num = 0; num < 100000; num++)
         {
            if (kbhit (RAB) )
            {
               IMG_data[counter] = fgetc (RAB);
               counter++;
               if (counter == 14)
               {
                  break;
               }
            }
         }
         
         for (int c = 0; c < 14; c++)
         {
            IMG_data[c] = 0;
         }
         
         DEL_CMD_DATA ();
         
         break;
        
         
         //////////////////////PINO/////////////////////////////////////////////////////
         
         case 0x90:
         //Main PIC controls PINO Power
         DEL_CMD_DATA ();
         
         break;
         
         case 0x9E:
         
         //Main PIC controls PINO Power
         DEL_CMD_DATA ();
         
         break;
         
         case 0x91:
         //fprintf (RAB, "aaa\r\n") ;
         
         fputc (command_data[0], RAB);
         delay_ms (5);
         for (t = 2; t < 9; t++)
         {
            fputc (command_data[t], RAB);
            delay_ms (5);
         }
         DEL_CMD_DATA ();
         
         break;
         
         case 0x92:
         //BYTE po[81];
         delay_ms (100);
         fputc (command_data[0], RAB);
         delay_ms (5);
         for (t = 2; t < 9; t++)
         {
            fputc (command_data[t], RAB);
            delay_ms (5);
         }
         delay_ms (50);
         //fputc (0xFF, RAB) ;
         
         //set_timer0 (0);
         count = 0;
         for (num = 0; num < 1000000; num++)
         {
            if (kbhit (RAB) )
            {
               Down_data[count] = fgetc (RAB);
               count++;
               if (count == 81)
               {
                  break;
               }
            }
         }
         
         
         for (count = 0; count < 81; count++)
         {
            fputc (Down_data[count], OBC);
         }
         for (count = 0; count < 81; count++)
         {
            Down_data[count] = 0x00;
         }
         
         for (num = 0; num < 1000; num++)
         {
            if (kbhit (RAB) )
            {
               Down_data[count] = fgetc (RAB);
               count++;
               if (count == 81)
               {
                  break;
               }
            }
         }
         break;
         
         case 0x9C:
         int tt_count= 0;
         BYTE PINO_Down_data[39] = {0x00};
         
         for(num=0; num=1000000; num++)
         {
            if (kbhit (OBC) )
            {
               PINO_Down_data[tt_count] = fgetc (OBC);
               tt_count++;
               if(tt_count == 39)
                  {
                  break;
                  }
            }
         }
         
         for (tt_count = 0; tt_count < 39; tt_count++)
         {
            fputc (PINO_Down_data[tt_count], RAB);
            delay_ms(50);
         }
         for (tt_count = 0; tt_count < 39; tt_count++)
         {
            PINO_Down_data[tt_count] = 0x00;
         }
         
         
         break;
         
         default:
         DEL_CMD_DATA ();
         break;
      }
      
      DEL_CMD_DATA ();
   }
}

