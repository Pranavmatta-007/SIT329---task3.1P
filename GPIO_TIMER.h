#ifndef TIMER_DEAKIN_H
#define TIMER_DEAKIN_H

#include <stdint.h>

class TIMER_DEAKIN {
public:
    bool config_timer(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms);
    uint16_t getTC3_count();
    void wait(float period_0_1ms);

private:
    bool isTimerValid(uint8_t timer_num);
    uint32_t getTimerBaseAddress(uint8_t timer_num);
    void configureTimerRegisters(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms);
};

#endif
