#include <FAB_PIC_FM.h>

//#use rs232(baud=9600,uart1,parity=N,xmit=PIN_B6,rcv=PIN_B7,bits=8,stream=PC)

#use rs232(UART1,baud=9600,parity=N,bits=8,stream=MPIC,ERRORS)

#use spi(MASTER, CLK = PIN_C3, DI = PIN_C4, DO = PIN_C5,ENABLE = PIN_C2, BAUD = 9600, BITS = 16, STREAM = PORT2, MODE = 2 )

int8 fabData[45] = {0};                                                          //FAB data array
//int8 adcsData[26] = {0};                                                         //Array for adcs data
unsigned int16 SRC_current = 0;
unsigned int16 bat_current = 0;
unsigned int16 RAW_current = 0;
unsigned int16 Ipz_current = 0;
unsigned int16 Imy_current = 0;
unsigned int16 Imz_current = 0;
unsigned int16 Ipy_current = 0;
unsigned int16 Imx_current = 0;
int8 heaterManual = 0;
#include <ADC_reading_func.c>

BYTE rx_chars[8] = {0};//array to get main PIC command

#int_rda                                                                         //UART1 Interrupt
void serial_isr(){
 
  rx_chars[0] = fgetc(MPIC);                                                     //Get main PIC command
  //CMD_FROM_MPIC[0] = fgetc(MPIC);
} 


void main()
{  
   heaterManual = 1;                                                             //Heater Auto mode as default
   fabData[0] = 0x33;                                                            //FAB data header
  
   TRISD7 = 0; LATD7 = 1;                                                        //RD7=HIGH, enabling buffer for voltage measurements (PWR_BAT, SRC_V, RAW_V)
   
   TRISD0 = 0; LATD0 = 0;                                                        //RD0=LOW, disabling battery heater
   
   check = read_eeprom(check_memory);                                            //reads position 5 from EEPROM, returns int8
   kill_flag = read_eeprom(memory);                                              //reads position 10 from EEPROM, returns int8

   if ((check!=8)&&(kill_flag!=5))
      {
        kill_fab_forward();                                                      //kill switch FAB forward mode
        kill_OBC_forward();                                                      //kill switch OBC forward mode
      }
   else
      {     
        kill_fab_reverse();                                                      //kill switch FAB reverse mode
        kill_OBC_reverse();                                                      //kill switch OBC reverse mode
      }
      
   
    SETUP_ADC(ADC_CLOCK_INTERNAL);                                               //Use internal clock
    SETUP_ADC_PORTS(ALL_ANALOG);                                                 //setting all analog ports (A0 A1 A2 A3 A5 E0 E1 E2 B2 B3 B1 B4 B0 B5 D1)
   
    enable_interrupts(INT_RDA);                                                  //UART interrupt
    enable_interrupts(global); 

   while(TRUE)
   {
     
      //battery_heater();                                                        //Control Heater, Check battery temperature and battery voltage. fabData[37] REMOVED FOR POWER SAVING
      kill_status();                                                             //Check KILL_FAB_STAT and KILL_OBC_FAB_STAT fabData[38]
      if(rx_chars[0] == 0x61)                                                    //receiving sensor data request interrupt
      {
         fabData[0] = 0x33; 
         temperature();                                                          //reads the temperature values ??and saves them in the array fabDATA []
         voltages();                                                              //reads the voltage values ??and saves them in the array fabDATA []
         adc_FAB();                                                              //read the ADC from the PIC
         
         rx_chars[0]=0;
         
         delay_ms(5);
         RD0 = 0;                                                                //HEAT_CTL = LOW
         kill_status();                                                          //Check KILL_FAB_STAT and KILL_OBC_FAB_STAT fabData[38]
         for (int i=0;i<45;i++)
         {                                                                       //Send fabDATA to Main PIC
            fputc(fabData[i],MPIC);
            delay_ms(1);
         }
         CLR_FAB_DATA();
      }
            
//! /* Command for sending panels info for adcs*/   
//!      if(rx_chars[0] == 0x69)                                                   //receiving panels data request interrupt
//!      {             
//!         temperature();                                                             //reads the temperature values ??and saves them in the array fabDATA []
//!         voltages();                                                             //reads the voltage values ??and saves them in the array fabDATA []
//!         adc_FAB();                                                              //read the ADC from the PIC
//!         rx_chars[0]=0; 
//!         delay_ms(10);
//!         make_adcsData();                                                        //make adcsData array
//!         for (int i=0;i<26;i++)
//!         {                                                                       //Send adcsDATA to Main PIC
//!            fputc(adcsData[i],MPIC);        
//!         }  
//!      }            
            
/*Command for Kill switch*/         
      if(rx_chars[0] == 0x17)
      {                                                                          //receiving Kill switch off interrupt
         rx_chars[0]=0;
         
         delay_ms(10);
         
         kill_fab_reverse();                                                      //kill switch FAB reverse mode
         kill_OBC_reverse();                                                      //kill switch OBC reverse mode
         
         write_eeprom(check_memory,8);
         check=8;
         write_eeprom(memory,5);
         kill_flag=5;
      }
      
      if(rx_chars[0] == 0x18)                                                     //receiving Kill switch on interrupt
      {                                              
      
         rx_chars[0]=0;
         
         delay_ms(10);
         
         kill_fab_forward();                                                        //kill switch FAB forward mode
         kill_OBC_forward();                                                        //kill switch OBC forward mode
         
         write_eeprom(check_memory,1);
         check=1;
         write_eeprom(memory,1);
         kill_flag=1;
      }
      
      /*Command for Battery Heater*/           
//!      if(rx_chars[0] == 0x01)                                                 //receiving Battery Heater Turn ON CMD
//!      {                                              
//!         rx_chars[0]=0;
//!         delay_ms(10);
//!         RD0 = 1;                                                             //HEAT_CTL = HIGH
//!         fabData[37] = 1;                                                     //Flag in HIGH
//!         heaterManual = 1;                                                    //heater Manual Mode  
//!      }
//!      
      if(rx_chars[0] == 0x02)                                                     //receiving Battery Heater Turn OFF CMD
      {                                              
         rx_chars[0]=0;
         delay_ms(10);
         RD0 = 0;                                                                //HEAT_CTL = LOW
         fabData[37] = 0;                                                        //Heater Flag in LOW
         heaterManual = 1;                                                       //heater Manual Mode
      }
//!      
//!      if(rx_chars[0] == 0x03)                                                 //receiving Battery Heater Auto Mode
//!      {                                              
//!         rx_chars[0]=0;
//!         delay_ms(10);
//!         heaterManual = 0;                                                      //heater Auto Mode
//!      }
//!      
   }

}


