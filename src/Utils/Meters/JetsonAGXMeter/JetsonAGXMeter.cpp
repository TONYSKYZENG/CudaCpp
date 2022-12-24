//
// Created by tony on 16/12/22.
//
#include <Utils/Meters/JetsonAgxMeter/JetsonAgxMeter.hpp>
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
#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
#define DEVICE_NAME "/sys/bus/i2c/drivers/ina3221/1-"
void DIVERSE_METER::JetsonAGXMeter::SamplingThread::init() {
  string sysSrc=DEVICE_NAME;
  sysSrc+="0040/hwmon/hwmon";
  unsigned int x=0;
  devFdsVol=vector<int>(3);
  devFdsCurr=vector<int>(3);
  strVol=vector<string>(3);
  strCurr=vector<string>(3);
  /**
   * @brief the 0x40-3 sys
   */
  devFdsVol[0]=-1;
  while(devFdsVol[0]==-1)
  { x++;
    string str=sysSrc+ to_string(x);
    //cout<<str+"/in3_input"<<endl;
    devFdsVol[0]= open((str+"/in3_input").data(),O_RDONLY);

  }

  close(devFdsVol[0]);
  strVol[0]=sysSrc+ to_string(x)+"/in3_input";
  strCurr[0]=sysSrc+ to_string(x)+"/curr3_input";
  //cout<<"Jetson can open"+ strCurr[0]+","+strVol[0]+"\r\n";
}
double DIVERSE_METER::JetsonAGXMeter::SamplingThread::readFd(int fd) {
  char buff[256];
  int nread;
  nread = read(fd, buff, 256);
  buff[nread]=0;
  double ru=std::atof(buff);
  //printf("%s\r\n",buff);
  return ru;
}
void DIVERSE_METER::JetsonAGXMeter::SamplingThread::inlineMain() {
  shouldStop=false;
  devFdsVol[0]= open(strVol[0].data(),O_RDONLY);
  devFdsCurr[0]= open(strCurr[0].data(),O_RDONLY);
  cumulatedEnergySys=0;
  maxPowerSys=0;
  if(!devFdsVol[0]||!devFdsCurr[0])
  {
    METER_ERROR("something wrong in opening jetson meter\r\n");
    return;
  }
  while (!shouldStop)
  {
    devFdsVol[0]= open(strVol[0].data(),O_RDONLY);
    devFdsCurr[0]= open(strCurr[0].data(),O_RDONLY);
  double ti= readFd(devFdsCurr[0]);
  double tv= readFd(devFdsVol[0]);
  double tw=ti*tv/1000.0;
  if(tw>maxPowerSys)
   {
    maxPowerSys=tw;
   }
   cumulatedEnergySys+=tw*5/1000.0;
    close(devFdsVol[0]);
    close(devFdsCurr[0]);
   // usleep(5000);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    /*cout<<ti<<endl;
    cout<<tv<<endl;
    cout<<tw<<endl;*/
  }


}
double DIVERSE_METER::JetsonAGXMeter::getE() {
  return mySamp.getSysEne()/1000.0;
}
double DIVERSE_METER::JetsonAGXMeter::getPeak() {
  return mySamp.getSysPower();
}
void DIVERSE_METER::JetsonAGXMeter::startMeter() {
  mySamp.startThread();
}

void DIVERSE_METER::JetsonAGXMeter::stopMeter() {
  mySamp.setStop();
  mySamp.joinThread();
}
