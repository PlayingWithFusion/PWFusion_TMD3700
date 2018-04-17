/***************************************************************************
* File Name: PWFusion_TMD3700.h
* Processor/Platform: Arduino Uno R3 (tested)
* Development Environment: Arduino 1.8.3
*
* Designed for use with with Playing With Fusion TMD3700 RGB Color, Proximity 
* and Ambient Light Sensor Breakout: SEN-36004
*
*   SEN-36004 (universal applications)
*   ---> http://www.playingwithfusion.com/productview.php?pdid=85
*
* Copyright © 2016 Playing With Fusion, Inc.
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

#ifndef PWFusion_TMD3700_H
#define PWFusion_TMD3700_H

#include "Arduino.h"
#include "Wire.h"
#include "PWFusion_TMD3700_STRUCT.h"

// REGISTER DEFINITIONS
#define TMD3700_ENABLE				0x80
#define TMD3700_ATIME				0x81
#define TMD3700_PRATE				0x82
#define TMD3700_WTIME				0x83
#define TMD3700_AILTL				0x84
#define TMD3700_AILTH				0x85
#define TMD3700_AIHTL				0x86
#define TMD3700_AIHTH				0x87
#define TMD3700_PILT				0x88
#define TMD3700_PIHT				0x8A
#define TMD3700_PERS				0x8C
#define TMD3700_CFG0				0x8D
#define TMD3700_PCFG0				0x8E
#define TMD3700_PCFG1				0x8F
#define TMD3700_CFG1				0x90
#define TMD3700_REVID				0x91
#define TMD3700_ID					0x92
#define TMD3700_STATUS				0x93
#define TMD3700_CDATAL				0x94
#define TMD3700_CDATAH				0x95
#define TMD3700_RDATAL				0x96
#define TMD3700_RDATAH				0x97
#define TMD3700_GDATAL				0x98
#define TMD3700_GDATAH				0x99
#define TMD3700_BDATAL				0x9A
#define TMD3700_BDATAH				0x9B
#define TMD3700_PDATA				0x9C
#define TMD3700_CFG2				0x9F
#define TMD3700_CFG3				0xAB
#define TMD3700_POFFSET_L			0xC0
#define TMD3700_POFFSET_H			0xC1
#define TMD3700_CALIB				0xD7
#define TMD3700_CALIBCFG			0xD9
#define TMD3700_CALIBSTAT			0xDC
#define TMD3700_INTENAB				0xDD


// Optical Characteristics for reference. See Fig 8 in TMD3700 datasheeet
// 465nm wavelength: 112 count/(uW/cm^2)
// 530nm wavelength: 152 count/(uW/cm^2)
// 620nm wavelength: 193 count/(uW/cm^2)
// Warm white LED:   152 count/(uW/cm^2)
// Warm white LED, 45.6uW/cm^2: 7000 counts (typ)
// 950nm wavelength: 137 count/(uW/cm^2)
// LUX accuracy (White LED, 2700K): 90-110%

class PWFusion_TMD3700
{
public:	
  PWFusion_TMD3700(uint8_t address);
  uint8_t Init(struct var_tmd3700 *prx_str);
  void update_all(struct var_tmd3700 *prx_str);
  
private:
  uint8_t _dev_add;
  uint8_t read_reg_byte(uint8_t RegAdd);
  uint16_t read_reg_2byte(uint16_t RegAdd);
  void write_reg_byte(uint8_t RegAdd, uint8_t RegData);
  void write_reg_2byte(uint8_t RegAddLow, uint16_t RegData);

};
#endif // PWFusion_TMD3700_H
