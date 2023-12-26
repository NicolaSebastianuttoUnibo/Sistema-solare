#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

class ParticleType{
private:

const char* fName;
const double fMass;
const int fCharge;
public:

const char* GetName() const;
double GetMass() const;
 int GetCharge() const;
virtual void Print();
virtual double GetWidth() const ;

ParticleType(const char* name,const  double mass, const int charge);
//ParticleType(const char* name);

 bool operator==(const ParticleType* pt) const;
 
};


#endif




