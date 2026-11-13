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

  printf("===================================\n");
  printf("  SMART CLASSROOM COMFORT MONITOR  \n");
  printf("===================================\n");


  // Menu Run
  while(input != 4) {
    printf("MENU:\n");
    printf("1. Enter temperature reading\n");
    printf("2. Display previous readings\n");
    printf("3. Display average temperature\n");
    printf("4. Exit");
    printf("Enter your Menu Choice: ");

    scanf("%d", &input);
    if(input == 1)
      enterReading();
    else if(input == 2)
      displayReadings();
    else if(input == 3)
      displayAvg();
    else if(input == 4)
      continue;
    else
      printf("\n\nERROR: INVALID INPUT. ENTER INTEGER (1-4)\n\n");
  }

  
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
