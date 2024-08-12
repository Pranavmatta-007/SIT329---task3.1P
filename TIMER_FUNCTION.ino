#include "GPIO_DEAKIN.h"
#include "GPIO_TIMER.h"

GPIO_DEAKIN gpio;
TIMER_DEAKIN timer;

void setup() {
    gpio.Config_GPIO('A', 18, 'O');  // Configure pin A18 as output
}

void loop() {
    gpio.Write_GPIO('A', 18, true);   // Turn LED on
    timer.wait(10000.0);              // Wait for 1 second (10000 * 0.1ms)
    gpio.Write_GPIO('A', 18, false);  // Turn LED off
    timer.wait(10000.0);              // Wait for 1 second
}
