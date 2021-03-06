
#include "MarketManager.hh"
#include "GoodManager.hh"
#include "Good.hh"
#include "EconomicActor.hh"
#include "RandomManager.hh"
#include "Settings.hh"
#include "ActorTypes.hh"
#include "DataLogger.hh"
GoodManager * GoodManager::theManager=NULL;

GoodManager::GoodManager(){


}
GoodManager::~GoodManager(){

}


GoodManager* GoodManager::Get(){
  if (theManager == (GoodManager*)NULL){
    cout<<"GoodManager Made"<<endl;
    theManager = new GoodManager();
  }

  return theManager;

}



void GoodManager::RemoveSupply(int id, int copies){
  if (supply.count(id)== 0){
    //Something has gone wrong. The supply isn't there
    cout<<"<GoodManager::RemoveSupply> there is no supply with id "<<id<<endl;
    throw 3;
  }
  int theSupply=supply[id];
  
  if (theSupply - copies < 0 ){
    //Something else has gone wrong.  There aren't that many supplies
    cout<<"<GoodManager::RemoveSupply> there are not enough supplies"<<id<<"to remove "<<theSupply<<" vs "<<copies<<endl;
    throw 3;
  }
  
  supply[id]=theSupply-copies;

}
void GoodManager::RemoveDemand(int id, int copies){
  if (demand.count(id) == 0){
    //something has gone wrong. that demand isn't here
    cout<<"<GoodManager::RemoveDemand> there is no demand with id "<<id<<endl;
    throw 3;
  }
  int theDemand = demand[id];
  
  if (theDemand - copies < 0){
    //something has gone wrong.  There aren't enoughg demands to remove
    cout<<"<GoodManager::RemoveDemand> there are not enough demand "<<id<<" to remove "<<theDemand<<" vs "<<copies<<endl;
    throw 3;
  }
  
  demand[id]= theDemand -copies;
}

void GoodManager::AddSupply(int id, int copies){

  auto theSupply = supply.find(id);
  if (theSupply == supply.end()){
    //Supply is not in the map
    supply[id]=copies;
  }else {
    theSupply->second+=copies;
  }

}
void GoodManager::AddDemand(int id, int copies){
  auto theDemand=demand.find(id);
  if (theDemand == demand.end()){
    demand[id]=copies;
  }else{
    theDemand->second+=copies;
  }

}






/**Dump the total supply and demand 
 */
void GoodManager::Dump(){
  PrintLine('v',30);
  cout<<"Aggregate Supply"<<endl;
  for (auto i : supply ){

    cout<<"Good "<<i.first<<" supply level "<<i.second<<endl;
  }
  
  cout<<"Aggregate Demand"<<endl;
  for (auto i : demand ){

    cout<<"Good "<<i.first<<" demand level "<<i.second<<endl;
  }
  PrintLine('^',30);
}



int GoodManager::FindHighestDemandGood(int &amtOfDemand){
  //Make this function better futrure sam
  //you are making a linear search cuz you are feeling 
  //lazy.
  amtOfDemand =-1;
  int maxDemandGoodNumber=-1;
  for (auto i : demand ){
    if( i.second  >amtOfDemand){
      amtOfDemand=i.second;
      maxDemandGoodNumber=i.first;
    }
  }

  return maxDemandGoodNumber;
}



