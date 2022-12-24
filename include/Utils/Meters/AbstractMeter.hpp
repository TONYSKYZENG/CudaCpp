/*! \file AbstractMeter.hpp*/
#ifndef _ADB_INCLUDE_UTILS_AbstractMeter_HPP_
#define _ADB_INCLUDE_UTILS_AbstractMeter_HPP_
//#include <Utils/Logger.hpp>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
//#include <Utils/UtilityFunctions.hpp>
using namespace std;
namespace DIVERSE_METER {
#define METER_ERROR(n) printf ("%s\r\n",n)
/***
 * @defgroup D_METER The diverse meter package
 * @{
 * This is the group of energy meters in software level
 * @}
 */
/**
 * @ingroup D_METER
 * @class AbstractMeter Utils/Meters/AbstractMeter.hpp
 * @brief The entity of an abstract power meter, providing all basic function of energy measurement
*/
class AbstractMeter {
 private:

 public:
  AbstractMeter(/* args */) {

  }
  //if exist in another name

  ~AbstractMeter() {

  }
  /**
   * @brief Start the meter recording
   */
  virtual void startMeter() {

  }
  /**
   * @brief Stop the meter recording
   */
  virtual void stopMeter() {

  }
  /**
   * @brief The measured energy in Joule
   * @return The result of energy
   */
  virtual double getE() {
    return 0.0;
  }
  /**
   * @brief The measured energy in Joule, only the specific channel
   * @param ch The channel, 0 is invalid by default
   * @return The result of energy
   */
  virtual double getE(size_t ch) {
    assert(ch);
    return getE();
  }
  /**
   * @brief The measured peak power in mW
   * @return The result of peak power i
   */
  virtual double getPeak() {
    return 0.0;
  }
  /**
  * @brief To acquire whether this meter is valid
  * @return true if this meter is valid
  */
  virtual bool isValid() {
    return false;
  }
};

 /**
 * @typedef AbstractMeterPtr
 * @ingroup DIVERSE_METER
 * @brief The class to describe a shared pointer to @ref AbstractMeter
 */
typedef std::shared_ptr<AbstractMeter> AbstractMeterPtr;

}

#endif