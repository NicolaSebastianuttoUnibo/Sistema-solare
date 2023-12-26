#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "iostream"
#include "ParticleType.hpp"

class ResonanceType : public ParticleType
{
public:
  ResonanceType(const char*,const double, const int , const double);
  
   double GetWidth() const;
   void Print();



  private:
    double const fWidth;

};

#endif


