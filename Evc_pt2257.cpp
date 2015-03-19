/*
  Evc_pt2257.h - Library for using PT2257 - Electronic Volume Controller IC.
  Created by Victor NPB, December 9, 2014.
*/

#include "Arduino.h"
#include "Evc_pt2257.h"


//Include Soft I2C library
//modify this if you want to change ports
#define SCL_PIN 0 
#define SCL_PORT PORTC 
#define SDA_PIN 1 
#define SDA_PORT PORTC
#include "SoftI2CMaster.h"


/*

PT2257 - Electronic Volume Controller IC
Datasheet - http://www.princeton.com.tw/Portals/0/Product/PT2257.pdf

Pinout
   |-----_-----|
1 -| Lin   Rin |- 8
2 -| Lout Rout |- 7
3 -| Gnd    V+ |- 6
4 -| SDA   SCL |- 5
   |-----------|

The interface protocol consists of the following:
• A Start bit
• A Chip Address byte=88H 10001000
• ACK=Acknowledge bit
• A Data byte
• A Stop bit

Max. clock speed=100K bits/s

FUNCTION BITS
MSB    2    3    4    5    6    7    LSB  Function
----------------------------------------------------------------------------------------
  1    1    1    1    1    1    1    1    Function OFF (-79dB)
  1    1    0    1    A3   A2   A1   A0   2-Channel, -1dB/step
  1    1    1    0    0    B2   B1   B0   2-Channel, -10dB/step
  1    0    1    0    A3   A2   A1   A0   Left Channel, -1dB/step
  1    0    1    1    0    B2   B1   B0   Left Channel, -10dB/step
  0    0    1    0    A3   A2   A1   A0   Right Channel, -1dB/step
  0    0    1    1    0    B2   B1   B0   Right Channel, -10dB/step
  0    1    1    1    1    0    0    M    2-Channel MUTE (M=1 -> MUTE=ON / M=0 -> MUTE=OFF)

ATTENUATION UNIT BIT  
 A3   AB2  AB1  AB0  ATT(-1) ATT(-10)
  0    0    0    0     0      0  
  0    0    0    1    -1    -10
  0    0    1    0    -2    -20
  0    0    1    1    -3    -30
  0    1    0    0    -4    -40
  0    1    0    1    -5    -50
  0    1    1    0    -6    -60
  0    1    1    1    -7    -70
  1    0    0    0    -8  
  1    0    0    1    -9  
  
*/

//instructions
#define PT2257_ADDR 0x88        //Chip address
#define EVC_OFF     0b11111111  //Function OFF (-79dB)
#define EVC_2CH_1   0b11010000  //2-Channel, -1dB/step
#define EVC_2CH_10  0b11100000  //2-Channel, -10dB/step
#define EVC_L_1     0b10100000  //Left Channel, -1dB/step
#define EVC_L_10    0b10110000  //Left Channel, -10dB/step
#define EVC_R_1     0b00100000  //Right Channel, -1dB/step
#define EVC_R_10    0b00110000  //Right Channel, -10dB/step
#define EVC_MUTE    0b01111000  //2-Channel MUTE

/** Constructor */
void evc_init()
{
  delay(200);
  i2c_init();
}

byte evc_level(uint8_t dB){
    
    if(dB>79) dB=79;
    
    uint8_t b = dB/10;  //get the most significant digit (eg. 79 gets 7)
    uint8_t a = dB%10;  //get the least significant digit (eg. 79 gets 9)
    
    b = b & 0b0000111; //limit the most significant digit to 3 bit (7)
    
    return (b<<4) | a; //return both numbers in one byte (0BBBAAAA)
}

void evc_setVolume(uint8_t dB){
    byte bbbaaaa = evc_level(dB);
    
    byte aaaa = bbbaaaa & 0b00001111;
    byte bbb = (bbbaaaa>>4) & 0b00001111;
    
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_2CH_10 | bbb);
        i2c_write(EVC_2CH_1 | aaaa);
        i2c_stop();
    }
}

void evc_setVolumeLeft(uint8_t dB){
    byte bbbaaaa = evc_level(dB);
    
    byte aaaa = bbbaaaa & 0b00001111;
    byte bbb = (bbbaaaa>>4) & 0b00001111;
    
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_L_10 | bbb);
        i2c_write(EVC_L_1 | aaaa);
        i2c_stop();
    }
}

void evc_setVolumeRight(uint8_t dB){
    byte bbbaaaa = evc_level(dB);
    
    byte aaaa = bbbaaaa & 0b00001111;
    byte bbb = (bbbaaaa>>4) & 0b00001111;
    
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_R_10 | bbb);
        i2c_write(EVC_R_1 | aaaa);
        i2c_stop();
    }
}

void evc_mute(bool toggle){
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_MUTE | (toggle & 0b00000001));
        i2c_stop();
    }
}

void evc_off(){
    if (i2c_start(PT2257_ADDR | I2C_WRITE)){
        i2c_write(EVC_OFF);
        i2c_stop();
    }
}

