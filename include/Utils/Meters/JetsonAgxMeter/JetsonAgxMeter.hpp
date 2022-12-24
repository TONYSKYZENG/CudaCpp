/*! \file JetsonAGXMeter.hpp*/
#ifndef _ADB_INCLUDE_UTILS_JETSONAGXMETER_HPP_
#define _ADB_INCLUDE_UTILS_JETSONAGXMETER_HPP_
//#include <Utils/Logger.hpp>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <Utils/Meters/AbstractMeter.hpp>
#include <Utils/AbstractC20Thread.hpp>
#include <atomic>
#include <vector>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

namespace DIVERSE_METER {
#define METER_ERROR(n) printf ("%s\r\n",n)
/**
 * @ingroup D_METER
 * @class JetsonAGXMeter Utils/Meters/JetsonAGXMeter.hpp
 * @brief The entity of embeded energy meter in jetson agx platform
 * @note dependencies
 * - @ref AbstractC20Thread, as there will be a sampling thread
*/
 class JetsonAGXMeter: public DIVERSE_METER::AbstractMeter{
 private:
   class SamplingThread:public INTELLI::AbstractC20Thread{
    public:
     SamplingThread(){}
     ~SamplingThread(){}
     void init();
     double getSysEne(){
       return cumulatedEnergySys;
     }
     double getSysPower(){
       return maxPowerSys;
     }
     void setStop()
     {
       shouldStop=true;
     }
    protected:
    double cumulatedEnergySys,cumulatedEnergyCpu,cumulatedEnergyGpu,cumulatedEnergyDdr,maxPowerSys;
     atomic_bool shouldStop= false;
     /**
      * @brief the handle of current reader
      */
    std::vector<int>devFdsCurr;
     /**
     * @brief the name of current reader
     */
     std::vector<string>strCurr;
     /**
     * @brief the handle of voltage reader
     */
     std::vector<int>devFdsVol;
     /**
     * @brief the name of voltage reader
     */
     std::vector<string>strVol;
     /**
    * @brief The 'main' function of SamplingThread
    * @note This is a re-implementation of AbstractC20Thread
    */
     void inlineMain();
     double readFd(int fd);
   };
   SamplingThread mySamp;
 public:
  JetsonAGXMeter(/* args */) {
   mySamp.init();
  }

  //if exist in another name

  ~JetsonAGXMeter() {

  }
  /**
   * @brief Start the meter recording
   */
  virtual void startMeter() ;
  /**
   * @brief Stop the meter recording
   */
  virtual void stopMeter() ;
  /**
   * @brief The measured energy in Joule
   * @return The result of energy
   */
  virtual double getE();
  /**
   * @brief The measured peak power in mW
   * @return The result of peak power i
   */
  virtual double getPeak();
  /**
  * @brief To acquire whether this meter is valid
  * @return true if this meter is valid
  */
  virtual bool isValid() {
    return true;
  }
};

 /**
 * @typedef AbstractMeterPtr
 * @ingroup DIVERSE_METER
 * @brief The class to describe a shared pointer to @ref AbstractMeter
 */
typedef std::shared_ptr<JetsonAGXMeter> JetsonAGXMeterPtr;

}

#endif