#ifndef _SPI_H_
#define _SPI_H_
#define MSBFIRST 0
#define LSBFIRST 1
#define SPI_MODE0 1
#define SPI_RXNE_INTERRUPT 5

class SPIClass {
 public:
  void beginSlave ();
  void setBitOrder (int);
  void setDataMode (int);
  SPIClass(int);
};


struct spi_dev {

};

typedef  struct spi_dev spi_dev;

spi_dev * SPI2 = (spi_dev * ) 0L;

void inline spi_irq_enable(spi_dev * dev, int interrupt) {} 
void inline spi_irq_disable(spi_dev * dev, int interrupt) {} 


#endif 
