
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

#define PIN 17

int main() {
    float temperature;
    float total = 0;
    int count = 0;

    // Default acceptable temperature range
    float minTemp = 68;
    float maxTemp = 76;

    FILE *file;
    FILE *statusFile;

    // Initialize Raspberry Pi GPIO
    if (gpioInitialise() < 0) {
        printf("GPIO initialization failed.\n");
        return 1;
    }

    gpioSetMode(PIN, PI_OUTPUT);

    // Create temperature log
    file = fopen("temperature_log.csv", "w");

    if (file == NULL) {
        printf("Could not open temperature file.\n");
        gpioTerminate();
        return 1;
    }

    fprintf(file, "Temperature,Status\n");

    printf("SMART CLASSROOM COMFORT MONITOR\n");
    printf("Acceptable range: %.1f - %.1f F\n", minTemp, maxTemp);
    printf("Enter -1 to finish.\n\n");

    while (1) {
        printf("Would you like to change the current acceptable range?");
        printf("1. Yes");
        printf("2. No");

        int input;
        printf("Enter either 1 or 2: ");
        scanf("%d", &input);
        if (input == 1) {
          printf("Enter the new maximum temperature in Fahrenheit: ");
          scanf("%f", &maxTemp);
          printf("Enter the new minimum temperature in Fahrenheit: ");
          scanf("%f", &minTemp);

          printf("New temperature range created!");
          printf("Acceptable range: %.1f - %.1f F\n", minTemp, maxTemp);
        } 
      
        printf("Enter classroom temperature: ");
        if (scanf("%f", &temperature) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        if (temperature == -1) {
            break;
        }

        total += temperature;
        count++;

        if (temperature >= minTemp && temperature <= maxTemp) {

            printf("Status: NORMAL\n");
            printf("Warning LED: OFF\n");

            gpioWrite(PIN, 0);
            fprintf(file, "%.1f,NORMAL\n", temperature);

            statusFile = fopen("status.txt", "w");
            if (statusFile != NULL) {
                fprintf(statusFile, "NORMAL");
                fclose(statusFile);
            }

        } else {

            printf("Status: WARNING\n");
            printf("Warning LED: ON\n");

            gpioWrite(PIN, 1);
            fprintf(file, "%.1f,WARNING\n", temperature);

            statusFile = fopen("status.txt", "w");
            if (statusFile != NULL) {
                fprintf(statusFile, "WARNING");
                fclose(statusFile);
            }
        }

        printf("\n");
    }

    fclose(file);

    // Display average temperature
    if (count > 0) {
        printf("Average temperature: %.2f F\n",
               total / count);
    } else {
        printf("No temperatures were recorded.\n");
    }

    gpioWrite(PIN, 0);
    gpioTerminate();

    printf("Temperature monitoring complete.\n");

    return 0;
}
