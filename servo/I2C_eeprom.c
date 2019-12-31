//
// FILE:    I2c_eeprom.c
// Project : singlePhase inverter
// ASSUMPTIONS:
//    This program requires an external I2C EEPROM connected to
//    the I2C bus at address 0x51.
//

#include	<header.h>
#include	<extern.h>

void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CSAR = I2C_EEPROM_SLAVE_ADDR;		// Slave address - EEPROM control code

	I2caRegs.I2CPSC.all = 6;	    // Prescaler - need 7-12 Mhz on module clk (75M/750 = 0.1MHz)

//   I2caRegs.I2CCLKL = 5;			// NOTE: must be non zero
//   I2caRegs.I2CCLKH = 3;			// NOTE: must be non zero
   I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero

	I2caRegs.I2CIER.all = 0x0;		// disable all i2c irq 2008.05.11

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
   									// Stop I2C when suspended
   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,
}

Uint16 I2CA_WriteData(int iSlaveAddr,int iMemAddr,int iData)
{
    I2caRegs.I2CMDR.all = 0x0020;   // Take I2C out of reset

    BACKUP_ENABLE;
    DELAY_US(100L);

	I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;	 
	I2caRegs.I2CCNT = 3;
    I2caRegs.I2CSAR = iSlaveAddr;
  	I2caRegs.I2CDXR = (iMemAddr >> 8) & 0x00ff;
  	I2caRegs.I2CDXR = iMemAddr & 0x00ff;
	I2caRegs.I2CDXR = iData;		// byte write
  	I2caRegs.I2CMDR.all = 0x6E20;			
  	delay_msecs(5);
//	while(I2caRegs.I2CSTR.bit.SCD == 0); 

  	BACKUP_DISABLE;
	return I2C_SUCCESS;
}

Uint16 I2CA_ReadData(int iSlaveAddr, int iMemAddr, int * data)
{
    I2caRegs.I2CSAR = iSlaveAddr;
    I2caRegs.I2CCNT = 2;
    I2caRegs.I2CDXR = (iMemAddr>>8) & 0x00ff;
    I2caRegs.I2CDXR = iMemAddr & 0x00ff;
//   I2caRegs.I2CMDR.all = 0x6620;			
    I2caRegs.I2CMDR.all = 0x2620;
    delay_msecs(10);
//    DSP28x_usDelay(20000);

    //while(I2caRegs.I2CSTR.bit.ARDY == 0);  // test jsk
	I2caRegs.I2CFFRX.bit.RXFFRST = 0;		// RXFIFO Operation disable	 
	I2caRegs.I2CFFRX.bit.RXFFINT = 1;		// RXFIFO Operation disable	 
	I2caRegs.I2CSAR = iSlaveAddr;
	I2caRegs.I2CCNT = 1;
	I2caRegs.I2CMDR.all = 0x6C20;			// Send restart as master receiver stop
    delay_msecs(10);
	// DSP28x_usDelay(20000);
	//while(I2caRegs.I2CSTR.bit.SCD == 0);  // test jsk
	* data = I2caRegs.I2CDRR;
 	return I2C_SUCCESS;
}

#define ADDR_EEPROM_OFFSET  0

void write_code_2_eeprom(int address,UNION32 data)
{
	int eprom_addr;
	int temp;

	temp = (int)(code_motorId+0.5);

	if( address < 100 ) eprom_addr = address * 4 ;
    else                eprom_addr = (address + 100 * temp )*4;

    I2CA_WriteData(ADDR_24LC32, eprom_addr + 0, data.byte.byte0);
	I2CA_WriteData(ADDR_24LC32, eprom_addr + 1, data.byte.byte1);
	I2CA_WriteData(ADDR_24LC32, eprom_addr + 2, data.byte.byte2);
	I2CA_WriteData(ADDR_24LC32, eprom_addr + 3, data.byte.byte3);
}

void read_eprom_data(int address, UNION32 * u32data)
{
	int eprom_addr, iTemp;
    int temp;

    temp = (int)(code_motorId+0.5);

    if( address < 100 ) eprom_addr = address * 4 ;
    else                eprom_addr = (address + 100 * temp )*4;
	
	I2CA_ReadData(ADDR_24LC32, eprom_addr + 0, & iTemp); (u32data->byte).byte0 = iTemp;
	I2CA_ReadData(ADDR_24LC32, eprom_addr + 1, & iTemp); (u32data->byte).byte1 = iTemp;
	I2CA_ReadData(ADDR_24LC32, eprom_addr + 2, & iTemp); (u32data->byte).byte2 = iTemp;
	I2CA_ReadData(ADDR_24LC32, eprom_addr + 3, & iTemp); (u32data->byte).byte3 = iTemp;
}

//===========================================================================
// No more.
//===========================================================================
