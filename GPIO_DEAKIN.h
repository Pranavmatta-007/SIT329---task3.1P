#ifndef GPIO_DEAKIN_H
#define GPIO_DEAKIN_H

class GPIO_DEAKIN {
public:
  bool Config_GPIO(char PortNum, char PinNum, char Mode);
  bool Write_GPIO(char PortNum, char PinNum, bool State);
  bool Read_GPIO(char PortNum, char PinNum);
};

#endif
