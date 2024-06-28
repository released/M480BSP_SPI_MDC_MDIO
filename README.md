# M480BSP_SPI_MDC_MDIO
 M480BSP_SPI_MDC_MDIO

udpate @ 2024/06/28

1. use SPI mode to emulate MDIO function (2.5MHz)
	
	- PA.15 : SPI2_MOSI , connect to MDIO
		
	- PA.14 : SPI2_MISO , connect to MDIO
		
	- PA.13 : SPI2_CLK , connect to MDC
		
	- PA.12 : SPI2_SS

MAKE SURE connect MISO pin and MOSI pin together to MDIO pin with pull high

2. original code base : refer to below sample code 

http://forum.nuvoton.com/viewtopic.php?f=19&t=11275&sid=68081b19ab6040622c4b31d58aee15d4

3. below is LA capture data 

![image](https://github.com/released/M480BSP_SPI_MDC_MDIO/blob/main/LA_MDC_MDIO.jpg)


single frame

![image](https://github.com/released/M480BSP_SPI_MDC_MDIO/blob/main/LA_MDC_MDIO_single.jpg)


detail frame

![image](https://github.com/released/M480BSP_SPI_MDC_MDIO/blob/main/LA_MDIO_fram_1.jpg)

![image](https://github.com/released/M480BSP_SPI_MDC_MDIO/blob/main/LA_MDIO_fram_2.jpg)

