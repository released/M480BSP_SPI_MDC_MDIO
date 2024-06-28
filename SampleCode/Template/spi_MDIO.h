/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

#define SPI_CLK_FREQ                                    (2500000)
#define SPI_PORT                                        (SPI2)

#define MDIO_ST_OFFSET                                  (30)
#define MDIO_OP_OFFSET                                  (28)
#define MDIO_PHY_OFFSET                                 (23)
#define MDIO_REG_OFFSET                                 (18)
#define MDIO_TA_OFFSET                                  (16)

#define MDIO_ST_CAUSE_22                                (0x01)
#define MDIO_ST_CAUSE_45                                (0x00)

#define MDIO_OP_W                                       (0x01)
#define MDIO_OP_R                                       (0x02)

#define MDIO_TA                                         (0x02)

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

void MDC_MDIO_Init(void);
uint16_t spi_MDIO_ReadRegister(uint8_t phyAddr, uint8_t regAddr);
void spi_MDIO_WriteRegister(uint8_t phyAddr, uint8_t regAddr, uint16_t wdata);

