#ifndef GPIO_TIMER_H
#define GPIO_TIMER_H

class GPIO_TIMER {
public:
    bool config_timer(uint8_t timerNum, uint16_t startCount, uint16_t endCount, uint8_t resolution);
    uint32_t getTC_count(uint8_t timerNum);
    void wait(uint16_t period);
private:
    void enable_timer(uint8_t timerNum);
    void disable_timer(uint8_t timerNum);
};

#endif
