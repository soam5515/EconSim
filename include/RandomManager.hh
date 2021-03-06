#ifndef __RandomManager_HH
#define __RandomManager_HH

#include <random>

class RandomManager{
  
public:
  static int GetRand(int n);
  static double GetGaus(double mean,double sigma);
  static double GetUniform(double low=0,double high=1);

  static unsigned GetSeed();
private:
  RandomManager();
  ~RandomManager();
  static bool pSeeded;

  static std::default_random_engine * pTheGenerator;
  static unsigned rTheSeed;


};


#endif
