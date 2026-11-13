#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#define PIN 17

void testLed();

int main(argc, char* argv[]) {
  gpioInitialise();
  gpioSetMode(PIN, PI_OUTPUT);

  testLed();
}

void testLed() {
  gpioWrite(Pin, 1); //LED ON
  getchar();
  gpioWrite(Pin, 0);
  printf("LED test complete");
  getchar();
}
