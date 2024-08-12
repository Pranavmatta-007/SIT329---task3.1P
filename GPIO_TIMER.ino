#include "GPIO_TIMER.h"
#include <Arduino.h>
#include <stdint.h>
#include <wiring_private.h>


bool TIMER_DEAKIN::isTimerValid(uint8_t timer_num) {
    return (timer_num == 3);  
}

// Get base address of the timer
uint32_t TIMER_DEAKIN::getTimerBaseAddress(uint8_t timer_num) {
    if (!isTimerValid(timer_num)) return 0;
    return (uint32_t) &TC3->COUNT16;  
}

void TIMER_DEAKIN::configureTimerRegisters(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms) {
    if (!isTimerValid(timer_num)) return;

    TcCount16* TC = (TcCount16*) getTimerBaseAddress(timer_num);

    TC->CTRLA.reg = 0;
    TC->CTRLBSET.reg = 0;

    TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;


    uint16_t prescaler = (uint16_t)(resolution_0_1ms * 48 - 1);
    TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1 + prescaler;


    TC->COUNT.reg = start_value;
    TC->CC[0].reg = end_value;

    TC->CTRLA.reg |= TC_CTRLA_ENABLE;
}


bool TIMER_DEAKIN::config_timer(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms) {
    if (!isTimerValid(timer_num)) return false;
    configureTimerRegisters(timer_num, start_value, end_value, resolution_0_1ms);
    return true;
}

uint16_t TIMER_DEAKIN::getTC3_count() {
    return TC3->COUNT16.COUNT.reg;
}


void TIMER_DEAKIN::wait(float period_0_1ms) {
    if (!isTimerValid(3)) return;

    TcCount16* TC = (TcCount16*) getTimerBaseAddress(3);
    uint32_t start_count = TC->COUNT.reg;
    uint32_t wait_ticks = (uint32_t)(period_0_1ms * 48);


    while ((TC->COUNT.reg - start_count) < wait_ticks) {
        delay(1); 
    }
}
