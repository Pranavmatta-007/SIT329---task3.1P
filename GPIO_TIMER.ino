#include "TIMER_DEAKIN.h"

#define TIMER_REG TC4

bool TIMER_DEAKIN::config_timer(uint8_t timerNum, uint16_t startCount, uint16_t endCount, uint8_t resolution) {
 
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(TC4_GCLK_ID) | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
    while (GCLK->STATUS.bit.SYNCBUSY);

    TIMER_REG->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16;  // Set timer to 16-bit mode
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);

    TIMER_REG->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024 | TC_CTRLA_ENABLE;  // Set prescaler and enable
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);

    TIMER_REG->COUNT16.CC[0].reg = (uint16_t)(endCount * resolution);
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);

    return true;
}

uint32_t TIMER_DEAKIN::getTC_count(uint8_t timerNum) {
    return TIMER_REG->COUNT16.COUNT.reg;
}

void TIMER_DEAKIN::wait(uint16_t period) {
    uint32_t startTime = getTC_count(4);
    while ((getTC_count(4) - startTime) < period);
}

void TIMER_DEAKIN::enable_timer(uint8_t timerNum) {
    TIMER_REG->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);
}

void TIMER_DEAKIN::disable_timer(uint8_t timerNum) {
    TIMER_REG->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);
}
