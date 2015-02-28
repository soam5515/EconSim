





#ifndef __MANUFACTURER_HH
#define __MANUFACTURER_HH

#include <vector>
#include <iostream>
#include <string>



//Local Headers 
#include "Company.hh"

using namespace std;

class Manufacturer : public Company {
public:
  Manufacturer(double money,EconomicActorManager*man) : Company(man){
    fMoney=money;
  };
  virtual ~Manufacturer(){
    //    cout<<"IN ~Manufacture()"<<endl;
  }

  
  /**Required Abstract methods */
  void Initialize();
  ActorActions EndOfStep();
  ActorActions BeginningOfStep();
  void DoStep(){}
  bool CheckTransactionMatch(int, EconomicActor*){return true;}


  //Return the type ID for this type of actor
  virtual int GetActorType(){return ActorTypes::Manufacturer;}


  void DumpConnections();
  int GetGoodToManufacture(){return GoodToManufacture;}

  void PrintInfo();
private:

  int GoodToManufacture;

  double Conservativeness;//How likely company is too sell all of its supply
  double Steadfastness;//How likely company will lower it's price
  
  int MaxVolume;//Max amount of good that company can make
  
  int rStartingSalary;
  
  int rTotalVolumeCreated;
};



#endif /* __MANUFACTURER_HH */