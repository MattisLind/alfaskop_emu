#ifndef _RING_BUFFER_
#define _RING_BUFFER_
#define SIZE 260

class RingBuffer {
  volatile int inPtr, outPtr, bufferFull, bufferEmpty;
  int buffer[SIZE];
public:
  int isBufferFull () {
    return bufferFull;
  };
  int isBufferEmpty () {
    return bufferEmpty;
  }
  void writeBuffer (int data);
  int readBuffer ();
  void  initBuffer ();
};
#endif
