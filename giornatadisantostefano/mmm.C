#include "Particle.hpp"
#include <TH1F.h>
#include <TCanvas.h>
#include <cstring>


void makeParticle(Particle* particle, int n, TH1F *h2, TH1F *h3){
(*particle).SetfIndex(n);
double phi=gRandom->Uniform(0,2*TMath::Pi());
double theta=gRandom->Uniform(0,TMath::Pi());
double impulse=gRandom->Exp(1);

(*particle).SetP(impulse*sin(theta)*cos(phi),impulse*sin(theta)*sin(phi),impulse*cos(theta));

h2->Fill(phi); 
h3->Fill(theta); 

}



void mmm(){
int c1{0};
int c2{0};
int c3{0};



gRandom->SetSeed();




//Particle pt("ci",5,5,5);











int n=Particle::fParticleType.size();


Particle::AddParticleType("pione+",0.13957,+1,0);
Particle::AddParticleType( "pione-",0.13957,-1,0);
Particle::AddParticleType( "kaone+",0.49367,+1,0);
Particle::AddParticleType( "kaone-",0.49367,-1,0);
n=Particle::fParticleType.size();

//Particle::AddParticleType( "kaone-",4,-5,0);
//if(kap==kam){std::cout<<"uguali";}
Particle::AddParticleType( "protone+",0.93827,+1,0);
Particle::AddParticleType( "protone-",0.93827,-1,0);
Particle::AddParticleType( "risonanza",0.89166,0,0.050);
n=Particle::fParticleType.size();





TH1F *h1 = new TH1F("tipi di particelle","Title", Particle::fParticleType.size(), 0, Particle::fParticleType.size());
TH1F *h2 = new TH1F("angoli azitumali","Title", 10000, 0,2*TMath::Pi());
TH1F *h3 = new TH1F("angoli polari","Title", 10000, 0,TMath::Pi());
TH1F *h4 = new TH1F("impulso","Title", 10000,0,2);
TH1F *h5 = new TH1F("impulso trasverso","Title", 10000,0,2);
TH1F *h6 = new TH1F("energia","Title", 10000,0, 2);
TH1F *h7 = new TH1F("invariante di massa","Title", 10000,0,1e1);
TH1F *h8 = new TH1F("massa invarianti di particelle discorde","Title", 10000,0,1e1);
TH1F *h9 = new TH1F("massa invarianti di particelle concorde","Title", 10000,0,1e1);
TH1F *h10 = new TH1F("kaone+- pione+- discordi","Title", 10000,0,1e1);
TH1F *h11 = new TH1F("kaone+- pione+- concordi","Title", 10000,0,1e1);
TH1F *h12 = new TH1F("risonanza","Title", 10000,0,1e1);













Particle EventParticles[300];

int count{0};

 for (int i=0;i<1000;i++)
{
 count=0;
 
   for(int j=0;j<100; j++) // qlz: sicuramente darà problemi
   {
    
   double x=gRandom->Rndm();
  
   if(x<0.4)
   {
    makeParticle(&EventParticles[j],0,h2,h3);
   }
  
   else if(x<0.8)
   {
   
    makeParticle(&EventParticles[j],1,h2,h3);


   }
   else if(x<0.85)
   {
    makeParticle(&EventParticles[j],2,h2,h3);


   }
   else if(x<0.9)
   {
    makeParticle(&EventParticles[j],3,h2,h3);


   }
   else if(x<0.945)
   {
    makeParticle(&EventParticles[j],4,h2,h3);


   }
   else if(x<0.99)
   {
    makeParticle(&EventParticles[j],5,h2,h3);


   }
  
   else
   {
    makeParticle(&EventParticles[j],6,h2,h3);
    

    
     
    double y=gRandom->Rndm();
  
     if(y<0.5)
     {

       Particle* a= new Particle("pione+",0.13957,+1,0);
       Particle* b=new Particle("kaone-",0.49367,-1,0);


     
       int z=EventParticles[j].Decay2body(*a, *b);
       
      
       if(z==0)
       {
           EventParticles[100+count]=*a;
           EventParticles[101+count]=*b;

          // makeParticle(&EventParticles[100+count],0,h2,h3); 
          // makeParticle(&EventParticles[101+count],3,h2,h3);

            count+=2;
       }
    

   
     }

else{

///

Particle* a= new Particle("pione-",0.13957,-1,0);
       Particle* b=new Particle("kaone+",0.49367,+1,0);


     
       int z=EventParticles[j].Decay2body(*a, *b);
       
      
       if(z==0)
       {
          EventParticles[100+count]=*a;
          EventParticles[101+count]=*b;

          //        makeParticle(&EventParticles[100+count],1,h2,h3);
          // makeParticle(&EventParticles[101+count],2,h2,h3);
            count+=2;
       }
       /////
    
}



   }//fine else
    

h1->Fill(EventParticles[j].GetfIndex()); 
h4->Fill(EventParticles[j].GetImpulse());
h5->Fill(std::sqrt(EventParticles[j].GetPx()*EventParticles[j].GetPx()  +EventParticles[j].GetPy()*EventParticles[j].GetPy()          ));
h6->Fill(EventParticles[j].GetEnergy());





// std::cout<<count<<"\n";
  }//fine secondo for (j)

    Particle p("gg",3,3,3);

for(int m=0;m<100+count;m++){
for(int n=m+1;n<100+count;n++){
double invmass=EventParticles[m].InvMass(EventParticles[n]);
if(invmass==0){std::cout<<"INVMASS è zero!!!!\n";}
if(invmass<0){std::cout<<"INVMASS è minore di  zero!!!!\n";}
h7->Fill(invmass);

 if((p.fParticleType[EventParticles[m].GetfIndex()])->GetCharge()*(p.fParticleType[EventParticles[n].GetfIndex()])->GetCharge()<0){
h8->Fill(invmass);
 }
 else
 {
h9->Fill(invmass);
 }
 const char* p1=(p.fParticleType[EventParticles[m].GetfIndex()])->GetName();
 const char* p2=(p.fParticleType[EventParticles[n].GetfIndex()])->GetName();


if (p1 && p2) {

if(
(std::strcmp(p1,"pione+")==0&&std::strcmp(p2,"kaone-")==0)||
(std::strcmp(p1,"pione-")==0&&std::strcmp(p2,"kaone+")==0)||
(std::strcmp(p1,"kaone+")==0&&std::strcmp(p2,"pione-")==0)||
(std::strcmp(p1,"kaone-")==0&&std::strcmp(p2,"pione+")==0)
){
h10->Fill(invmass);
}

if(
(std::strcmp(p1,"pione+")==0&&std::strcmp(p2,"kaone+")==0)||
(std::strcmp(p1,"pione-")==0&&std::strcmp(p2,"kaone-")==0)||
(std::strcmp(p1,"kaone+")==0&&std::strcmp(p2,"pione+")==0)||
(std::strcmp(p1,"kaone-")==0&&std::strcmp(p2,"pione-")==0)
){
h11->Fill(invmass);
}

}

}
}


for(int i=100;i<100+count;i+=2){

// std::cout<<EventParticles[0+i].GetEnergy()<<"\n";
// std::cout<<EventParticles[1+i].GetEnergy()<<"\n";

double aaa=std::sqrt(
    std::pow(EventParticles[0+i].GetEnergy()+EventParticles[1+i].GetEnergy(),2)
   -(std::pow(EventParticles[0+i].GetPx()+EventParticles[1+i].GetPx(),2)
   +std::pow(EventParticles[0+i].GetPy()+EventParticles[1+i].GetPy(),2)
   +std::pow(EventParticles[0+i].GetPz()+EventParticles[1+i].GetPz(),2))
    );
    // std::cout<<"E1"<<EventParticles[0+i].GetEnergy()<<"\n";
    // std::cout<<"E2"<<EventParticles[1+i].GetEnergy()<<"\n";
    // std::cout<<"x1"<<EventParticles[0+i].GetPx()<<"\n";
    // std::cout<<"x2"<<EventParticles[1+i].GetPx()<<"\n";
    // std::cout<<"y1"<<EventParticles[0+i].GetPy()<<"\n";
    // std::cout<<"y2"<<EventParticles[1+i].GetPy()<<"\n";
    // std::cout<<"z1"<<EventParticles[0+i].GetPz()<<"\n";
    // std::cout<<"z2"<<EventParticles[1+i].GetPz()<<"\n";
    // std::cout<<"r"<<aaa<<"\n\n";

double invmass=EventParticles[i].InvMass(EventParticles[i+1]);

if(invmass==0){std::cout<<"invmass è zero!!!!\n";}
if(invmass<0){std::cout<<"invmass è minore di zero!!!!\n";}

h12->Fill(invmass);

}




} ///fine primo for (i)





std::cout <<"\n er brother";
std::cout<<"\nc1: "<<c1<<"\n";



TCanvas*canvas1=new TCanvas("canvas  1","Canvas",800,500);
h1->Draw("E");
canvas1->Draw();


TCanvas*canvas2=new TCanvas("canvas 2","Canvas",800,500);


h2->Draw();
canvas2->Draw();


TCanvas*canvas3=new TCanvas("canvas 3 ","Canvas",800,500);
h3->Draw();
canvas3->Draw();


TCanvas*canvas4=new TCanvas("canvas 4 ","Canvas",800,500);
h4->Draw();
canvas4->Draw();


TCanvas*canvas5=new TCanvas("canvas 5 ","Canvas",800,500);
h5->Draw();
canvas5->Draw();


TCanvas*canvas6=new TCanvas("canvas 6 ","Canvas",800,500);
h6->Draw();
canvas6->Draw();


TCanvas*canvas7=new TCanvas("canvas 7 ","Canvas",800,500);
h7->Draw();
canvas7->Draw();

TCanvas*canvas8=new TCanvas("canvas 8 ","Canvas",800,500);
h8->Draw();
canvas8->Draw();

TCanvas*canvas9=new TCanvas("canvas 9 ","Canvas",800,500);
h9->Draw();
canvas9->Draw();


TCanvas*canvas10=new TCanvas("canvas 10 ","Canvas",800,500);
h10->Draw();
canvas10->Draw();

TCanvas*canvas11=new TCanvas("canvas 11 ","Canvas",800,500);
h11->Draw();
canvas11->Draw();

TCanvas*canvas12=new TCanvas("canvas 12 ","Canvas",800,500);
h12->Draw();
canvas12->Draw();


 TFile *outputFile = new TFile("output.root", "RECREATE");

    // Salva i canvas nel file
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();
    h6->Write();
    h7->Write();
    h8->Write();
    h9->Write();
    h10->Write();
    h11->Write();
    h12->Write();


    // Chiudi il file
    outputFile->Close();

    

}
