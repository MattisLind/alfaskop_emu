
#define MSBFIRST 0
#define SPI_MODE0 1

class SPIClass {
 public:
  void beginSlave ();
  void setBitOrder (int);
  void setDataMode (int);
  SPIClass(int);
};


struct spi_dev {

} spi_dev;
