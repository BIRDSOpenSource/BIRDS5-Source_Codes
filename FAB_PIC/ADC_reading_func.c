
//________________________READ VOLTAGE CHANNELS OF ADC_______________________________________________________________________________________//

unsigned int16 READ_vol_CHANNEL(int16 Address)                                   //read the voltage value of the memory position received
{
  
    RC2 = 0;
    
    spi_xfer(PORT2, Address);
                
    unsigned int16 vol_X = spi_xfer(PORT2);
         
    unsigned int16 adc_res16 = vol_X & 0x0FFF;                                   //removing the address bits
                                
    RC2 = 1;
      
    delay_us(20);
    
    return adc_res16;
}

//________________________READ TEMPERATURE CHANNEL OF ADC_________________________________________________________________________________________________________//


int16 READ_temp_CHANNEL(int16 Address)                                           //read the temp value from the memory location received
{
  
   RC2 = 0;
                
   spi_xfer(PORT2, Address);
   
   unsigned int16 temp_X = spi_xfer(PORT2);
   
   unsigned int16 adc_temp16 = temp_X & 0x0FFF;                                  //leave the 12-bit data
         
   RC2 = 1;
   
   delay_us(20);
   
   return adc_temp16;
}
//________________________CALIBRATE TEMPERATURE CHANNEL OF ADC_________________________________________________________________________________________________________//

void temperature(void)                                                           //reads the temperature values and saves them in the array fabDATA []
{

//        fprintf(PC,"\n\rTemperature measurement\r\n");
          temp_pY = READ_temp_CHANNEL(pY_temp);                                  //pass the address to the function to read temp_pY from the ADC +Y         
          fabData[1] = (temp_pY >> 8) & 0xFF;
          fabData[2] = temp_pY & 0x00FF;                                      
    
    //-------------------------------------------------------//
          temp_pX = READ_temp_CHANNEL(pX_temp);                                  //pass the address to the function to read temp_pX from the ADC +X
          fabData[3] = (temp_pX >> 8) & 0xFF;
          fabData[4] = temp_pX & 0x00FF;       
     
     //-------------------------------------------------------//
          temp_mZ = READ_temp_CHANNEL(mZ_temp);                                  //pass the address to the function to read temp_mZ from the ADC -Z          
          fabData[5] = (temp_mZ >> 8) & 0xFF;
          fabData[6] = temp_mZ & 0x00FF;       
   
    //-------------------------------------------------------//
          temp_mX = READ_temp_CHANNEL(mX_temp);                                  //pass the address to the function to read temp_mX from the ADC -X          
          fabData[7] = (temp_mX >> 8) & 0xFF;
          fabData[8] = temp_mX & 0x00FF;       

    //-------------------------------------------------------//                  //pass the address to the function to read temp_mY from the ADC -Y           
          temp_mY = READ_temp_CHANNEL(mY_temp);         
          fabData[9] = (temp_mY >> 8) & 0xFF;
          fabData[10] = temp_mY & 0x00FF;       
    
    //-------------------------------------------------------//
//!          temp_BPB = READ_temp_CHANNEL(BPB_temp);                                //pass the address to the function to read temp_BPB from the ADC
//!          
//!          fabData[9] = (temp_BPB >> 8) & 0xFF;
//!          fabData[10] = temp_BPB & 0x00FF;       
    //-------------------------------------------------------//         
//!          temp_pZ1 = READ_temp_CHANNEL(pZ_temp1);
//!          
//!          fabData[13] = (temp_pZ1 >> 8) & 0xFF;
//!          fabData[14] = temp_pZ1 & 0x00FF;       

    //-------------------------------------------------------//  
    
          temp_pZ2 = READ_temp_CHANNEL(pZ_temp2);                                //pass the address to the function to read temp_pZ2 from the ADC +Z          
          fabData[11] = (temp_pZ2 >> 8) & 0xFF;
          fabData[12] = temp_pZ2 & 0x00FF;  
          
          return;
}

//________________________CALIBRATE VOLTAGE CHANNEL OF ADC_________________________________________________________________________________________________________//

void voltages(void)                                                              //reads the voltage values and saves them in the array fabDATA []
{                                                            
//        fprintf(PC,"\n\rVoltage measurement\r\n");
          vol_pY = READ_vol_CHANNEL(pY_vol);                                     //pass the address to the function to read vol_pY from the ADC  +Y                                           
          fabData[13] = (vol_pY >> 8) & 0xFF;
          fabData[14] = vol_pY & 0x00FF;                             
    
    //-------------------------------------------------------//
//!          vol_pX = READ_vol_CHANNEL(pX_vol);                                     //pass the address to the function to read vol_pX from the ADC +X
//!          
//!          fabData[15] = (vol_pX >> 8) & 0xFF;
//!          fabData[16] = vol_pX & 0x00FF;       
     //-------------------------------------------------------//
     
    //-------------------------------------------------------//      
          vol_mY = READ_vol_CHANNEL(mY_vol);         
          fabData[15] = (vol_mY >> 8) & 0xFF;
          fabData[16] = vol_mY & 0x00FF;       

    //-------------------------------------------------------//  
    
          vol_mZ = READ_vol_CHANNEL(mZ_vol);                                     //pass the address to the function to read vol_mZ from the ADC -Z         
          fabData[17] = (vol_mZ >> 8) & 0xFF;
          fabData[18] = vol_mZ & 0x00FF;       
          
    //-------------------------------------------------------//     
          vol_mX = READ_vol_CHANNEL(mX_vol);                                     //pass the address to the function to read vol_mX from the ADC -X          
          fabData[19] = (vol_mX >> 8) & 0xFF;
          fabData[20] = vol_mX & 0x00FF;       
                    
    //-------------------------------------------------------//      
//!          vol_mY = READ_vol_CHANNEL(mY_vol);
//!          
//!          fabData[25] = (vol_mY >> 8) & 0xFF;
//!          fabData[26] = vol_mY & 0x00FF;       
//!
    //-------------------------------------------------------//         
          vol_pZ = READ_vol_CHANNEL(pZ_vol);                                     //pass the address to the function to read vol_pZ from the ADC +Z          
          fabData[21] = (vol_pZ >> 8) & 0xFF;
          fabData[22] = vol_pZ & 0x00FF;     
          
          return;
}

//________________________READ ADC CHANNEL OF FAB CURRENT_________________________________________________________________________________________________________//

int8 READ_PIC_ADC(int8 port_name)
{
   
   SET_ADC_CHANNEL(port_name);                                                   //  routing nth channel to adc
   unsigned int16 ADC_VALUE;
   delay_us(20);
   ADC_VALUE = READ_ADC();   
   
   int8 bit8value = ADC_VALUE/16;                                                //TODO: decide if we should bit shift to the right 4 times or if we should mask the lower 8 bits
   //int8 bit8value =  ADC_VALUE & 0x0FF;
   //unsigned int8 bit8value = (int8) ADC_VALUE;                                              //Change to first method (first comment) if this doesn't work well
   return bit8value;
}

//======================16bit value reading ADC==============================//

int16 READ_PIC_ADC16(int8 port_name)
{

   unsigned int16 ADC_VALUE16[100] = {0};
   unsigned int16 avg_val = 0;
   SET_ADC_CHANNEL(port_name);                                                   //  routing nth channel to adc
   delay_us(20);
   for(int k=0; k<100; k++)
   {
      ADC_VALUE16[k] = READ_ADC(); 
      delay_us(10);                                                               //uncomment if FAB data is sent out of order
   }
   avg_val = (ADC_VALUE16[49] + ADC_VALUE16[50] + ADC_VALUE16[51])/3;
   
   return avg_val;                                                               //return median ADC reading
}

//________________________CREATE ARRAY OF FAB DATA________________________//

void adc_FAB(void)                                                               //read the ADC from the PIC
{
   //      fprintf(PC,"ADC_FAB measurement\r\n");
   
   Imx_current = READ_PIC_ADC16(4);                                              // I_panel -X connected to analog input 4 (pin RA5(AN4)) on FAB PIC
   fabData[23] = (Imx_current >> 8)& 0xff;
   fabData[24] = Imx_current & 0x00ff;
   //fabData[23] = READ_PIC_ADC(0);                                              
  
   Ipy_current = READ_PIC_ADC16(3);                                              // I_panel +Y connected to analog input 3 (AN3) on FAB PIC
   fabData[25] = (Ipy_current >> 8)& 0xff;
   fabData[26] = Ipy_current & 0x00ff;   
   //fabData[24] = READ_PIC_ADC(1);                                              
   
   Imz_current = READ_PIC_ADC16(2);                                              // I_panel -Z connected to analog input 2 (AN2) on FAB PIC
   fabData[27] = (Imz_current >> 8)& 0xff;
   fabData[28] = Imz_current & 0x00ff;     
   //fabData[25] = READ_PIC_ADC(2);
   
   Imy_current = READ_PIC_ADC16(1);                                              // I_panel -Y connected to analog input 1 (AN1) on FAB PIC
   fabData[29] = (Imy_current >> 8)& 0xff;
   fabData[30] = Imy_current & 0x00ff;     
   //fabData[26] = READ_PIC_ADC(3);
   
   Ipz_current = READ_PIC_ADC16(5);                                              // I_panel +Z connected to analog input 5 (AN5) on FAB PIC
   fabData[31] = (Ipz_current >> 8)& 0xff;
   fabData[32] = Ipz_current & 0x00ff;   
   //fabData[27] = READ_PIC_ADC(5);
      
   RAW_current = READ_PIC_ADC16(6);                                              // Raw Current (I_raw - measures the raw battery output to load after passing through many components) 
   fabData[33] = (RAW_current >> 8)& 0xff;                                       // This should be similar to Ibat. It is connected to analog input 6 (AN6) on FAB PIC
   fabData[34] = RAW_current & 0x00ff; 
   //fabData[28] = READ_PIC_ADC(6);
   
   fabData[35] = READ_PIC_ADC(8);                                                // Source Voltage (Vsrc - Combined Voltage from solar panels) connected to analog input 8 (AN8) on FAB PIC    
   
   fabData[36] = READ_PIC_ADC(9);                                                // Raw Voltage (Vraw - measures the raw battery output to load after passing through many components)    
                                                                                 // This should be similar to Vbat. It connected to analog input 9 (AN9) on FAB PIC 
 //====================== reading the SRC current ===========================// 
   
    
   SRC_current = READ_PIC_ADC16(11);                                            // Source Current (Isrc - Combined Current from solar panels) connected to analog input 8 (AN8) on FAB PIC 
   fabData[37] = (SRC_current >> 8)& 0xff;                                      // This should match the ~sum of the currents from all the individual panels
   fabData[38] = SRC_current & 0x00ff;
   
//!   for(int k=0; k<100; k++)
//!   {
//!      SET_ADC_CHANNEL(11);                                                      //  routing nth channel to adc
//!      delay_us(10);
//!      SRC_current = SRC_current + READ_ADC(); 
//!      delay_ms(1);
//!   }
//!   
//!   SRC_current= SRC_current/100;
//!   
//!   fabData[31] = (SRC_current >> 8)& 0xff;
//!   fabData[32] = SRC_current & 0x00ff;
//!   
//!   SRC_current = 0;
       
//======================end of reading SRC Current===========================//
      
   fabData[39] = READ_PIC_ADC(10);                                                //battery voltage - Ibatt to analog input 10 (AN5) on FAB PIC
      
//============================ reading the Battery current ==================================// 
   
   bat_current = READ_PIC_ADC16(12);
   fabData[40] = (bat_current >> 8)& 0xff;
   fabData[41] = bat_current & 0x00ff;
   
//!   for(int j=0; j<100; j++)
//!   {
//!      SET_ADC_CHANNEL(12);                                                     //routing nth channel to adc
//!      delay_us(10);
//!      bat_current = bat_current + READ_ADC(); 
//!      delay_ms(1);      
//!   }
//!   
//!   bat_current= bat_current/100;
//!   
//!   fabData[34] = (bat_current >> 8)& 0xff;
//!   fabData[35] = bat_current & 0x00ff;
//!   
//!   bat_current = 0; 
       
//==================================end of reading battery Current==============================//     
        
   fabData[42] = READ_PIC_ADC(13);                                          //BAT_TEMP (battery temperature)
   fabData[43] = 0;                                                         //BAT_HEATER = 0
   
}

//!void battery_heater()
//!{
//!   fabData[36] = READ_PIC_ADC(13);                                            //BAT_TEMP (battery temperature)
//!   fabData[33] = READ_PIC_ADC(10);                                            //battery voltage
//!   if (heaterManual==0)                                                       //automatic mode only operate if heaterManual flag is low
//!   {
//!      if ((fabData[36] > 0xB0) && (fabData[33] > 0x93))                       //battery temperature > 176(menor a 8C) && battery voltage > 147(mayor a 3.8v)
//!      {
//!         RD0 = 1;                                                             //HEAT_CTL = HIGH
//!         fabData[37] = 1;                                                     //Heater Flag in HIGH
//!      }
//!      
//!      else
//!      {
//!         RD0 = 0;                                                              //HEAT_CTL = LOW
//!         fabData[37] = 0;                                                     //Heater Flag in LOW
//!      }
//!   }
//!}

void kill_status(void)                                                           //Check KILL_FAB_STAT and KILL_OBC_FAB_STAT
{
   if(RD3 == 1 && RC1 == 0)
   {
    
      fabData[44] = 0x10;
    
   }
   
    else if(RD3 == 1 && RC1 == 1)
    {
    
      fabData[44] = 0x11;
    
    }
   
   else if(RD3 == 0 && RC1 == 1)
   {
    
      fabData[44] = 0x01;

   }
   
   else
   {
    
      fabData[44] = 0x00;

   }
   
   return;
}

void CLR_FAB_DATA()
{
   for(int i=0; i<45; i++)
   {
      fabData[i] = 0;
   }
}

//!void make_adcsData()                                                             // make adcs data array -> adcsData[26]
//!{
//!   adcsData[0] = 0xAA;
//!   for(int i=1; i<9; i++)
//!   {
//!      adcsData[i] = fabData[i];
//!   }
//!   for( i=11; i<28; i++)
//!   {
//!      adcsData[i-2] = fabData[i];
//!   }   
//!      return;
//!}
