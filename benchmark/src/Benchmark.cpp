// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

/**
 * @brief This is the main entry point of the entire program.
 * We use this as the entry point for benchmarking.
 */
#include <Utils/Logger.hpp>
#include <Utils/MicroDataSet.hpp>
#include <Utils/UtilityFunctions.hpp>
using namespace std;
using namespace INTELLI;
 void vecAdd(float *h_a, float *h_b, float *h_c, int n,int intensity);
void vecAdd_cpu(float *a, float *b, float *c, int n,int intensity)
{
   for(int id=0;id<n;id++)
   {
     float ru=0;
     float ta=0,tb=0;
     ta=a[id];
     tb=b[id];
     for(int k=0;k<intensity;k++)
     {
       ru+= ta+tb;
     }

     c[id] = ru;
   }
}
int main(int argc, char **argv) {
  int len=10000;
  int intensity=10;
  if(argc>=2)
  {
    len= atoi(argv[1]);

  }
  if(argc>=3)
  {
    intensity= atoi(argv[2]);

  }
  cout<<"len="+ to_string(len)+"\r\n";
  cout<<"intensity="+ to_string(intensity)+"\r\n";
  //Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  INTELLI::MicroDataSet md(999);
  std::vector<float>a=md.genRandInt<float>(len,10000,0);
  std::vector<float>b=md.genRandInt<float>(len,10000,0);
  std::vector<float>c=md.genRandInt<float>(len,10000,0);
  float *h_a=a.data();
  float *h_b=a.data();
  float *h_c=a.data();
  struct timeval timeBase;
  gettimeofday(&timeBase,NULL);

  vecAdd_cpu(h_a,h_b,h_c,a.size(),intensity);
  uint64_t tEnd=UtilityFunctions::timeLastUs(timeBase);
 /*for(int i=0;i<6;i++)
  {
    printf("%lf,",h_c[i]);
  }*/
  cout<<"CPU run ="+ to_string(tEnd)+" us\r\n";
  gettimeofday(&timeBase,NULL);
  vecAdd(h_a,h_b,h_c,a.size(),intensity);

  tEnd=UtilityFunctions::timeLastUs(timeBase);
  cout<<"GPU run ="+ to_string(tEnd)+" us\r\n";
  //Run the test here.
  INTELLI_INFO("Nothing to run." << argc << argv);
}

