#ifndef ADB_INCLUDE_UTILS_EspMeterUartUARY_HPP_
#define ADB_INCLUDE_UTILS_EspMeterUartUART_HPP_
#include <Utils/Logger.hpp>

#include "Utils/Meters/AbstractMeter.hpp"
#include <Utils/UtilityFunctions.hpp>
using namespace std;
namespace DIVERSE_METER {

/*class:EspMeterUart
description:the entity of an esp32s2-based power meter, providing all function including:
I,V,P,E,PeakPower
note: the meter and bus rate is about 1ms, you must have the esp_meter.ko
date:20211202
*/
class EspMeterUart : public AbstractMeter {
 private:
  int devFd;
 // uint64_t accessEsp32(uint64_t cmd);
 public:
  EspMeterUart(/* args */);
  //if exist in another name
  EspMeterUart(string name);
  ~EspMeterUart();
  void startMeter();
  void stopMeter();
  //current in mA
  double getI();
  //voltage in mV
  double getV();
  //power in mW
  double getP();
  //energy in J
  double getE();
  //peak power in mW
  double getPeak();

  bool isValid() {
    return (devFd != -1);
  }
};
typedef std::shared_ptr<EspMeterUart> EspMeterUartPtr;

}

#endif