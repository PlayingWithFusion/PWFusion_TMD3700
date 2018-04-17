#ifndef PWF_TMD3700_STRUCT_H
#define PWF_TMD3700_STRUCT_H

struct var_tmd3700{
	uint8_t  IC_found;			// 1 = chip found, 0 = chip not found
	uint8_t  IC_RevID;			// Revision ID
	uint8_t  status;			// interrupt statuses
	uint16_t Cdata;				// clear ALS data
	uint16_t Rdata;				// Red ALS data
	uint16_t Gdata;				// Green ALS data
	uint16_t Bdata;				// Blue ALS data
	uint16_t  Pdata;				// Proximity data
	uint16_t Poffset;			// Proximity Offset data
};

#endif /* PWF_TMD3700_STRUCT_H */
