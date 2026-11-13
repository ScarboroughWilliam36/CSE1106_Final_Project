#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#define PIN 17

void testLed();

int main() {
  gpioInitialise();
  if (gpioInitialise() < 0) {
    printf("Failed to initialize pigpio\n");
    return 1;
  }
  gpioSetMode(PIN, PI_OUTPUT);

  testLed();
  gpioTerminate();
  return 0;
}

void testLed() {
  gpioWrite(PIN, 1); //LED ON
  getchar();
  gpioWrite(PIN, 0);
  printf("LED test complete\n");
  getchar();
}
