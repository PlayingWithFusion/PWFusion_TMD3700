/***************************************************************************
* File Name: PWFusion_TMD3700.cpp
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
#include "PWFusion_TMD3700.h"

PWFusion_TMD3700::PWFusion_TMD3700(uint8_t address)
{
	// device address... default is 0x39
	_dev_add = address;
}

uint8_t PWFusion_TMD3700::Init(struct var_tmd3700 *prx_str)
{
	uint8_t temp;
	temp = read_reg_byte(TMD3700_ID);
	
	// Verify TMD3700 is connected - read ID register
	if(0xC0 == temp)	// TMD3700 found
	{
		// found TMD3700, set 'found' variable instruct
		prx_str->IC_found = 1;
		// Get model ID information, store info in struct
		prx_str->IC_RevID = read_reg_byte(TMD3700_REVID);
		
		// Write ENABLE register: turn off IC during start-up
		write_reg_byte(TMD3700_ENABLE, 0x00);
		// Write ATIME register: set to 64 to be able to reach ALS full scale
		write_reg_byte(TMD3700_ATIME, 0x40);
		// Write PRATE register: default is ~2.8ms... 0x1F
		write_reg_byte(TMD3700_PRATE, 0x1F);	// default is x1F
		// Write WTIME register: wait between ALS cycles. x46 = ~200ms
		write_reg_byte(TMD3700_WTIME, 0x46);
		
		// Set high/low threshold values for interrupts
		// Write AIL Threshold register: 2 bytes, see fig 22-23 
		write_reg_2byte(TMD3700_AILTL, 0x0000);
		// Write AIH Threshold register: 2 bytes, see fig 24-25 
		write_reg_2byte(TMD3700_AIHTL, 0xFFFF);
		
		
		// Write PIL Threshold register: 1 bytes, see fig 26 
		write_reg_byte(TMD3700_PILT, 0x00);
		// Write PIH Threshold register: 1 bytes, see fig 27 
		write_reg_byte(TMD3700_PIHT, 0xFF);
		
		
//		PGAIN = 2 (4x)
//		PLDRIVE = 16 (102mA)
//		PPULSE = 15 (16 pulses)
//		PPULSE_LEN = 2 (16μs)

		// Write PERS register: 7:4 sets # consecutive prox readings to set interrupt
		// 3:0 sets # consecutive ALS readings to set interrupt
		write_reg_byte(TMD3700_PERS, 0x11); // set to 5 consecutive for both (fig 28)
		// Write CFG0 register: wlong set to 0. All other bits set to required value (fig 29)
		write_reg_byte(TMD3700_CFG0, 0x80);
		// Write PCFG0 register: prox pulse length, # pulses... default 1, 15 (fig 30)
		write_reg_byte(TMD3700_PCFG0, 0xFF);  // default = x2F
		// Write PCFG1 register: Prox gain, LED drive... default 2(4x), 0(6mA) (fig 31)
		write_reg_byte(TMD3700_PCFG1, 0xC3);
		// Write CFG1 register: ALS Gain control, default 0 (1x gain) (fig 32)
		write_reg_byte(TMD3700_CFG1, 0x01);
//		// Write CFG2 register: algainl (LSB of ALS gain). Default 1 (fig 45-46)
//		write_reg_byte(TMD3700_CFG2, 0x04);
		// Write CFG3 register: int clear on read ON, sleep after int OFF (fig 47)
		write_reg_byte(TMD3700_CFG3, 0x80);
		
		// Write INTENAB register: disable all interrupts (0x00). See Fig 53 for details
			// enable all... 0xF8
		write_reg_byte(TMD3700_INTENAB, 0xF8);
		
		// Write CALIBCFG register: disable all interrupts. See Fig 53 for details
//		write_reg_byte(TMD3700_CALIBCFG, 0xE0);
		
		// Clear status register by reading the value (see Fig 35)
		prx_str->status = read_reg_byte(TMD3700_STATUS);		// read/save status	
		
		
		
		// now enable device... 
		// Write ENABLE register: turn on wait, proximity, ALS, power (Fig 18)
		write_reg_byte(TMD3700_ENABLE, 0x07);
		delay(100);
//		write_reg_byte(TMD3700_CALIB, 0x21);
//		while(0 == read_reg_byte(TMD3700_CALIBSTAT)){delay(10); Serial.println(read_reg_byte(TMD3700_STATUS));};
		delay(5000);	// give the IC time to start-up
		// Write CALIB register: start offset calibration using optical (fig 50)
		
		// Write CALIB register: start offset calibration using optical (fig 50)
		
		// Write POFFSET_L register: offset value
//		write_reg_byte(TMD3700_POFFSET_L, 0x01);
		// Write POFFSET_H register: sign config
//		write_reg_byte(TMD3700_POFFSET_H, 0x00);
//		Serial.println(read_reg_byte(TMD3700_CALIBSTAT), HEX);
//		write_reg_byte(TMD3700_CALIBSTAT, 0x00);

		return 1;		// TMD3700 init complete
	}
	else				// TMD3700 not found
	{
		prx_str->IC_found = 0;	// 1 = found, 0 = not found
		return 0; // IC not found, failed setup
	} 
}

void PWFusion_TMD3700::update_all(struct var_tmd3700 *prx_str)
{
	write_reg_byte(TMD3700_ENABLE, 0x07);
	delay(100);
	// Read values from TMD3700 chip
	prx_str->status = read_reg_byte(TMD3700_STATUS);		// read/save status	
	prx_str->Cdata  = read_reg_2byte(TMD3700_CDATAL);		// read/save clear data	
	prx_str->Rdata  = read_reg_2byte(TMD3700_RDATAL);		// read/save red data	
	prx_str->Gdata  = read_reg_2byte(TMD3700_GDATAL);		// read/save green data	
	prx_str->Bdata  = read_reg_2byte(TMD3700_BDATAL);		// read/save blue data	
	prx_str->Poffset = read_reg_2byte(TMD3700_POFFSET_L);	// read/save Prox offset
	prx_str->Pdata  = read_reg_byte(TMD3700_PDATA);			// read/save Prox data
}

uint8_t PWFusion_TMD3700::read_reg_byte(uint8_t RegAdd)
{
	uint8_t data;
	Wire.beginTransmission(_dev_add);		// write address
	Wire.write(RegAdd);						// write register
	Wire.endTransmission();					// end transmission
	Wire.requestFrom(_dev_add, (uint8_t)1);	// read data from register
	data = Wire.read();						// store data
	return data;
}

uint16_t PWFusion_TMD3700::read_reg_2byte(uint16_t RegAdd)
{
	uint8_t data_arr[2];
	uint16_t data;
	Wire.beginTransmission(_dev_add);		// write address
	Wire.write(RegAdd);						// write low byte register address
	Wire.endTransmission();					// end transmission
	Wire.requestFrom(_dev_add, (uint8_t)2);	// read 2 bytes of data from device
	data_arr[0] = Wire.read();	// low byte
	data_arr[1] = Wire.read();  // high byte
	data = ((uint16_t)data_arr[1] << 8) | ((uint16_t)data_arr[0]); // combine bytes
	return data;
}

void PWFusion_TMD3700::write_reg_byte(uint8_t RegAdd, uint8_t RegData)
{
	Wire.beginTransmission(_dev_add);		// write address
	Wire.write(RegAdd);						// write register
	Wire.write(RegData);					// write register data
	Wire.endTransmission();					// end transmission
}

void PWFusion_TMD3700::write_reg_2byte(uint8_t RegAddLow, uint16_t RegData)
{
	uint8_t RegDataL, RegDataH;
	RegDataL = RegData & 0xFF;
	RegDataH = (RegData >> 8) & 0xFF;
	Wire.beginTransmission(_dev_add);		// write address
	Wire.write(RegAddLow);					// write address of low byte
	Wire.write(RegDataL);					// write low byte data
	Wire.write(RegDataH);					// write high byte data
	Wire.endTransmission();					// end transmission
}
