#include "Particle.hpp"


 std::vector<ParticleType*> Particle::fParticleType;
 std::vector<ParticleType*>* Particle::lochifo=&fParticleType;


int Particle::findParticle(ParticleType* rt){

int index{-1};

  int i=0;
     for ( auto it=fParticleType.begin();it<fParticleType.end();it++) {

if(*rt==(*it)){return i; }
i++;

  
    } 
    
     
return index;



}


Particle::Particle(const char* name, double px, double py, double pz): fPx{px},fPy{py},fPz{pz}{


// std::cout<<"["<<fParticleType.size()<<".";
ParticleType b=ParticleType(name,0.,0);
fIndex=findParticle(&b);

// if(fIndex<0){std::cout<<"N";}
// else{std::cout<<"("<<fIndex<<")";}
// std::cout<<"."<<fParticleType.size()<<"]";

// fParticleType.push_back(&(*it));




}
/*Particle::Particle(const char* name): fPx{0},fPy{0},fPz{0}{
    ParticleType b=ParticleType(name,0.,0);
fIndex=findParticle(&b);
   if(fIndex<0){std::cout<<"Particella non trovata";}
for(auto it=istParticleType.begin(); it<istParticleType.end();it++){
  fParticleType.push_back(&(*it));}

}*/

void Particle::Setter(const char* name){
  //const char* names="kaone-";
    ParticleType* a=new ParticleType(name,0,0);

    fIndex=findParticle(a);
   //int aa=findParticle(a);
   
  
}

//
/*void Particle::Setter(int index){
    fIndex=index;
}*/
//

 void Particle::PrintAll(){
  
    for( unsigned int i=0;i<fParticleType.size();i++){
        
        if(fParticleType[i]!=nullptr){
        
         
        fParticleType[i]->Print();
        std::cout<<"\n";
        }
    } 
} 
void Particle::PrintParticle(){
    std::cout<<"\nindex: "<<fIndex<<"\n"<<"Name: "<< (*(fParticleType[fIndex])).GetName()<<"\nPx: "<<fPy<<"\nPy: "<<fPz<<"\nPz: "<<fPx<<"\n";

  
}


 int Particle::GetfIndex(){return fIndex;}
 

void Particle::AddParticleType (const char* name, const double mass, const int charge, const double width ){
  
  
  
   if(width==0)
   {

////////

    ParticleType* rt=new  ParticleType (name, mass, charge);
   
 
 
    if (fParticleType.size()<fMaxNumParticleType && findParticle(rt)==-1)
    { 
    fParticleType.push_back(rt);
    }
    
    
    
    
     }


///////////
    else{
      ResonanceType* rt=new ResonanceType (name, mass, charge, width);
   
   
    if (fParticleType.size()<=fMaxNumParticleType && findParticle(rt)==-1)
    { 
    fParticleType.push_back(rt);
    } 
    }




}

void  Particle::SetfIndex(int index) {
    fIndex=index;


}


double Particle::GetPx(){
  return fPx;
}
double Particle::GetPy(){
  return fPy;
}
double Particle::GetPz(){
  return fPz;
}

double Particle::GetMassParticle() const{ //togliere commenti qua

    // if(fIndex<fParticleType.size()){
  return fParticleType[fIndex]->GetMass();
  //  }
  // return -1;
}

double Particle::GetImpulse(){
  double P=std::sqrt(fPx*fPx+fPy*fPy+fPz*fPz);
  // std::cout<<"impulse="<<P<<"\n";
  return P;
}

double Particle::GetEnergy() const{
    Particle a=*this;
  double E=std::sqrt((a.GetMassParticle())*(a.GetMassParticle())+(a.GetImpulse())*(a.GetImpulse()));
  return E;
}

double Particle::InvMass(Particle &p)
{
  double Minv=std::sqrt(
    std::pow(this->GetEnergy()+p.GetEnergy(),2)
   -(std::pow(fPx+p.GetPx(),2)+std::pow(fPy+p.GetPy(),2)+std::pow(fPz+p.GetPz(),2))
    );
    //std::cout<<"m:"<<Minv<<"\n";
    return Minv;
}

void Particle::SetP(double Px, double Py, double Pz)
{
  fPx=Px;
  fPy=Py;
  fPz=Pz;
}

int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMassParticle() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMassParticle();
  double massDau1 = dau1.GetMassParticle();
  double massDau2 = dau2.GetMassParticle();

  if(fIndex > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;

    massMot += fParticleType[fIndex]->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

  double bx = fPx/energy;
  double by = fPy/energy;
  double bz = fPz/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}


void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx + by*fPy + bz*fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx += gamma2*bp*bx + gamma*bx*energy;
  fPy += gamma2*bp*by + gamma*by*energy;
  fPz += gamma2*bp*bz + gamma*bz*energy;
}
