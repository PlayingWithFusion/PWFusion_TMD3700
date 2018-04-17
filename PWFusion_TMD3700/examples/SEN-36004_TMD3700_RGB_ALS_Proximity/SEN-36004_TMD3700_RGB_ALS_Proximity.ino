/***************************************************************************
* File Name: SEN-36004_TMD3700_RGB_ALS_Proximity.ino
* Processor/Platform: Arduino Uno R3 (tested)
* Development Environment: Arduino 1.8.3
*
* Designed for use with with Playing With Fusion TMD3700 RGB Color, Proximity 
* and Ambient Light Sensor Breakout: SEN-36004
*
*   SEN-36004 (universal applications)
*   ---> http://www.playingwithfusion.com/productview.php?pdid=85
*
* Copyright © 2016-2018, Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author        Date      Comments
* J. Steinlage  2016Sep   Original version
* 
* Playing With Fusion, Inc. invests time and resources developing open-source
* code. Please support Playing With Fusion and continued open-source 
* development by buying products from Playing With Fusion!
**************************************************************************/
/*
*    Circuit:
*    Arduino Uno   Arduino Mega  -->  SEN-36004: TMD3700 Breakout
*    SDA:    SDA        SDA      -->  SDA
*    SCL:    SCL        SCL      -->  SCL
*    GND:    GND        ''       -->  GND
*    5V:     5V         ''       -->  VDD 
*    3V:     3V         ''       -->  LED
*    GPIO0/1 are not used in this example. They could be used for interrupts
*    (note: VDD should match voltage of IO, and can be between 3.3 and 5V)
**************************************************************************/
// The TMD3700 communicates via I2C. 
// This example uses the I2C interface via Wire library
#include "Wire.h"
// include Playing With Fusion TMD3700 libraries
#include <PWFusion_TMD3700.h>
#include <PWFusion_TMD3700_STRUCT.h>

// declare sensor object (see PWFusion_TMD3700.h file for definitions)
PWFusion_TMD3700 tmd3700_snsr0(0x39);

// declare sensor structure
struct var_tmd3700 tmd3700_str_ch0;

void setup()
{
  struct var_tmd3700 *tmd3700_ptr;
  tmd3700_ptr = &tmd3700_str_ch0;
  
  Serial.begin(115200);
  Serial.println("Playing With Fusion: TMD3700 RGB, ALS and Proximity Sensor, SEN-36004");

  delay(500);
  // need to start I2C comms
  Wire.begin();

  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);

  // give the Arduino time to start up
  delay(100);
  // setup for the proximity sensor
  // see PWFusion_TMD3700.h file for definitions
  while(0 == tmd3700_snsr0.Init(tmd3700_ptr));
}

uint8_t state = 0;

void loop()
{
  delay(500);
  struct var_tmd3700 *tmd3700_ptr;
  tmd3700_ptr = &tmd3700_str_ch0;

  tmd3700_snsr0.update_all(tmd3700_ptr);

  if(state == 0){
    digitalWrite(9,HIGH);
    state = 1;
  }
  else{
    digitalWrite(9,LOW);
    state = 0;
  }

  Serial.println("Cdata Rdata Gdata Bdata Pdata Poffst Status");
  Serial.print(tmd3700_ptr->Cdata);
  Serial.print("   ");
  Serial.print(tmd3700_ptr->Rdata);
  Serial.print("   ");
  Serial.print(tmd3700_ptr->Gdata);
  Serial.print("   ");
  Serial.print(tmd3700_ptr->Bdata);
  Serial.print("   ");
  Serial.print(tmd3700_ptr->Pdata);
  Serial.print("   ");
  Serial.print(tmd3700_ptr->Poffset);
  Serial.print("   ");
  Serial.print(tmd3700_ptr->status, BIN);
  Serial.println(" ");
}

