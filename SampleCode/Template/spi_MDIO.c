/*_____ I N C L U D E S ____________________________________________________*/
// #include <stdio.h>
#include "NuMicro.h"

#include "spi_MDIO.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/


#pragma arm section code="fastcode"

void MDC_MDIO_Init(void) 
{
    /* Set IP clock divider. SPI clock rate = 1MHz */
    SPI_Open(SPI_PORT, SPI_MASTER, SPI_MODE_0, 32, SPI_CLK_FREQ);

    /* Enable the automatic hardware slave select function. Select the SS pin and configure as low-active. */
    SPI_EnableAutoSS(SPI_PORT, SPI_SS, SPI_SS_ACTIVE_LOW);
}


void MDIO_Init_To_SPI(void)
{
    SYS->GPA_MFPH &= ~( SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= ( SYS_GPA_MFPH_PA15MFP_SPI2_MOSI);
}

void MDIO_Init_To_GPIO(void)
{
    SYS->GPA_MFPH &= ~( SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= ( SYS_GPA_MFPH_PA15MFP_GPIO);
    GPIO_SetMode(PA, BIT15, GPIO_MODE_INPUT);
}

uint16_t spi_MDIO_ReadRegister(uint8_t phyAddr, uint8_t regAddr) 
{
    unsigned int MDIO_temp = 0;
    uint16_t rdata = 0;

    __disable_irq();
    
    SPI_ClearTxFIFO(SPI_PORT);
    // SPI_ClearRxFIFO(SPI_PORT);

    SPI_SET_DATA_WIDTH(SPI_PORT, 32);

    //PREAMBLE : send 32  x bit 1 
    SPI_WRITE_TX(SPI_PORT, 0xFFFFFFFF);
    /* Check SPI port busy status */
    // while (SPI_IS_BUSY(SPI_PORT));
    while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_PORT));

    //START OF FRAME , 01
    MDIO_temp |= MDIO_ST_CAUSE_22 << MDIO_ST_OFFSET;

    //OP , READ : 10
    MDIO_temp |= MDIO_OP_R << MDIO_OP_OFFSET;

    //PATAD : PHY addr 5 bit
    MDIO_temp |= phyAddr << MDIO_PHY_OFFSET;

    //DEVAD : reg addr 5 bit
    MDIO_temp |= regAddr << MDIO_REG_OFFSET;

    //TA : turn around , 2 clock , Z0
    MDIO_temp |= MDIO_TA << MDIO_TA_OFFSET;

    SPI_SET_DATA_WIDTH(SPI_PORT, 16);

    MDIO_temp = (MDIO_temp >> 16) & 0xFFFF;

    SPI_WRITE_TX(SPI_PORT, MDIO_temp);
    /* Check SPI port busy status */
    // while (SPI_IS_BUSY(SPI_PORT));
    while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_PORT));

    // read data 16 bit , change MOSI as GPIO input
    // MAKE SURE connect MISO pin and MOSI pin together to MDIO pin with pull high
    MDIO_Init_To_GPIO();

    SPI_ClearRxFIFO(SPI_PORT);
    /* Send dummy data for receiving data */
    SPI_WRITE_TX(SPI_PORT, 0xFFFF);
    /* Check SPI port busy status */
    // while (SPI_IS_BUSY(SPI_PORT));
    while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_PORT));
    /* Read received data */
    rdata = SPI_READ_RX(SPI_PORT);

    /* Restore to initial settings */
    MDIO_Init_To_SPI();

    // SPI_SET_DATA_WIDTH(SPI_PORT, 32) ;

    //TA : turn around

    __enable_irq();

    return rdata;
}

void spi_MDIO_WriteRegister(uint8_t phyAddr, uint8_t regAddr, uint16_t wdata) 
{
    unsigned int MDIO_temp = 0;

    __disable_irq();

    SPI_ClearTxFIFO(SPI_PORT);
    // SPI_ClearRxFIFO(SPI_PORT);

    SPI_SET_DATA_WIDTH(SPI_PORT, 32);

    //PREAMBLE : send 32  x bit 1 
    SPI_WRITE_TX(SPI_PORT, 0xFFFFFFFF);
    /* Check SPI port busy status */
    // while (SPI_IS_BUSY(SPI_PORT));
    while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_PORT));

    //START OF FRAME , 01
    MDIO_temp |= MDIO_ST_CAUSE_22 << MDIO_ST_OFFSET;

    //OP , WRITE :01
    MDIO_temp |= MDIO_OP_W << MDIO_OP_OFFSET;

    //PATAD : PHY addr 5 bit
    MDIO_temp |= phyAddr << MDIO_PHY_OFFSET;

    //DEVAD : reg addr 5 bit
    MDIO_temp |= regAddr << MDIO_REG_OFFSET;

    //TA : turn around , 2 clock , 10
    MDIO_temp |= MDIO_TA << MDIO_TA_OFFSET;

    // write data 16 bit
    MDIO_temp |= wdata;

    SPI_WRITE_TX(SPI_PORT, MDIO_temp);
    /* Check SPI port busy status */
    // while (SPI_IS_BUSY(SPI_PORT));
    while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_PORT));

    //TA : turn around

    __enable_irq();
}


#pragma arm section
