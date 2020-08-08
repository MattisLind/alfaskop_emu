#define SIZE 1024

class RingBuffer {
  volatile int inPtr, outPtr, bufferFull, bufferEmpty;
  char buffer[SIZE];
public:
  int isBufferFull () {
    return bufferFull;
  };
  int isBufferEmpty () {
    return bufferEmpty;
  }
  void writeBuffer (char data);
  char readBuffer ();
  void  initBuffer ();
};
