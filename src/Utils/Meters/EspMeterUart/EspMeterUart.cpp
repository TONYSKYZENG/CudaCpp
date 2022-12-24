#include <Utils/Meters/EspMeterUart/EspMeterUart.hpp>
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
#include <configs/EspMeterUart/EspMeterUart_config.h>
#include     <stdio.h>
#include     <stdlib.h>
#include     <unistd.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>
#include     <termios.h>
#include     <errno.h>
#include    <string.h>
#include <stdint.h>
#ifndef  METER_UART_NAME
#error Please specify the uart device of meter
#endif
#define DEVICE_NAME METER_UART_NAME
#include <signal.h>
using namespace DIVERSE_METER;
enum {
  UART_VCMD_START = 1,
  UART_VCMD_STOP,
  UART_VCMD_I,
  UART_VCMD_V,
  UART_VCMD_P,
  UART_VCMD_E,
  UART_VCMD_PEAK,

};
EspMeterUart::EspMeterUart(/* args */) {
  devFd = open(DEVICE_NAME, O_RDWR | O_NOCTTY);
  if (devFd == -1) {

    METER_ERROR("can not open device meter");
  }
  //char *welcome="hello world";
  struct termios termios_p;
  tcgetattr(devFd, &termios_p);
  termios_p.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
  termios_p.c_oflag &= ~OPOST;
  termios_p.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  termios_p.c_cflag &= ~(CSIZE | PARENB);
  termios_p.c_cflag =B1152000 | CS8 | CLOCAL | CREAD;
  termios_p.c_cc[VTIME] = 0;
  termios_p.c_cc[VMIN] = 1;
  tcsetattr(devFd, TCSANOW, &termios_p);
  //设置为非阻塞模式
  tcflush(devFd, TCIOFLUSH);
  fcntl(devFd, F_SETFL, O_NONBLOCK);
}

EspMeterUart::EspMeterUart(string name) {
  devFd = open(name.data(), O_RDWR);
  if (devFd == -1) {

    METER_ERROR("can not open device meter");
  }
}
EspMeterUart::~EspMeterUart() {
  if (devFd != -1) {
    close(devFd);
  }
}
void EspMeterUart::startMeter() {
  uint8_t cmdSend=UART_VCMD_START;
  //double ru=0;
  write(devFd, &cmdSend,  1);
}
void EspMeterUart::stopMeter() {
  uint8_t cmdSend=UART_VCMD_STOP;
  //double ru=0;
  write(devFd, &cmdSend,  1);
}
double EspMeterUart::getI() {

  return 0;
}

double EspMeterUart::getV() {

  return 0;
}

double EspMeterUart::getP() {

  return 0;
}

double EspMeterUart::getE() {
  double ru=0;
  uint8_t cmdSend=UART_VCMD_E;
  write(devFd, &cmdSend,  1);
//usleep(1000);
//double ru;
  int ret=-1;
  while (ret<0)
  {
    ret=read(devFd, &ru, sizeof(double));
  }
  return ru;
}

double EspMeterUart::getPeak() {
  double ru=0;
  uint8_t cmdSend=UART_VCMD_PEAK;
  write(devFd, &cmdSend,  1);
//usleep(1000);
//double ru;
  int ret=-1;
  while (ret<0)
  {
    ret=read(devFd, &ru, sizeof(double));
  }
  return ru;
}