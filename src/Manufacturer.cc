



#include "Manufacturer.hh"

#include "RandomManager.hh"

#include "Settings.hh"

#include "MarketManager.hh"
#include "GoodManager.hh"
#include "Person.hh"
#include "Good.hh"
#include "EconomicActorManager.hh"
#include "Death.hh"
#include "Calendar.hh"
#include "ActorLogger.hh"
void Manufacturer::Initialize(){


  //Pick a good to manufacturer
  //  GoodToManufacture=RandomManager::GetRand(Settings::MaxGoodNumber);
  
  //Randomly assign some attributes
  rConservativeness=RandomManager::GetRand(1000)/1000.0;
  rSteadfastness=RandomManager::GetRand(1000)/2000.0 + 0.5;

  MaxVolume = RandomManager::GetRand(500)+10;///CAN"T BE 0
  rPriceChangeLevel= RandomManager::GetRand(100)/100.;
  


  for (unsigned int i=0;i<fGoodPriorities.size();i++){
    fGoodPriorities[i]=41;//RandomManager::GetRand(Settings::MaxGoodPriority);
  }

  fSupplies.clear();
  fDemands.clear();




  rTotalVolumeCreated=0;
  rStartOfStepMoney=0;
  rStartOfStepSupply=0;

  rFirstStep=true;


  numberOfSteps=0;
  numberOFProductions=0;
  

  rStartingSalary=RandomManager::GetRand(100000);

  rHireMorePeople=true;
}


ActorActions Manufacturer::BeginningOfStep(){


  rStartOfStepMoney=fMoney;

  if (fMyActorLogger!=NULL){
    fMyActorLogger->BeforeMessage("Hello from manufacturer");
    fMyActorLogger->LogBeforeStepState(this);
  }

  ////////////////////////////////////////////////////////////
  // if the company has employees it can manufacture goods  //
  ////////////////////////////////////////////////////////////
  if (fSupplies.find(GoodToManufacture) == fSupplies.end()){
    Good temp(GoodToManufacture,0,fGoodPriorities[GoodToManufacture],"supply");
    fSupplies[GoodToManufacture]=temp;
  }
    
  if ( Employees2Salary.size() > 2 && Calendar::DayNumber < 1200){

    int t=Employees2Salary.size();
    fSupplies[GoodToManufacture].AddCopies(t);
    rTotalVolumeCreated+=t;

    numberOFProductions++;
  }
  
  if ( fSupplies[GoodToManufacture].GetNumberOfCopies()<0){
    cout<<"Less than zero"<<endl;
    throw 1;
  }
  
  
  if (fSupplies.size() !=0 && fSupplies[GoodToManufacture].GetNumberOfCopies()!=0){
    
    MarketManager::Get()->PlaceSellOrder(GoodToManufacture,this->GetBaseId(),
					 fSupplies[GoodToManufacture].GetNumberOfCopies(),
					 fGoodPriorities[GoodToManufacture]);
  }
  

  if (rHireMorePeople || Employees2Salary.size()==0){
    for (int i=0;i<5;i++){
      MarketManager::Get()->PlaceJobPosting(rStartingSalary,this->GetBaseId());
    }
    rHireMorePeople=false;
  }

  auto it_temp=fSupplies.find(GoodToManufacture);
  if (it_temp != fSupplies.end()){
    rStartOfStepSupply=it_temp->second.GetNumberOfCopies();
  }else{
    rStartOfStepSupply=0;
  }

  return ActorActions::None;
}

void Manufacturer::DoStep(){
  if (fMyActorLogger!=NULL){
    fMyActorLogger->DuringMessage("Durring Message");
  }
 }
ActorActions Manufacturer::EndOfStep(){
  stringstream ss;
   

  
  //Compare how much was earned to how much needs to be payed to employees
  double thisStepProfit = fMoney-rStartOfStepMoney;
  double thisStepSoldVolume=0;
  
  auto it_temp=fSupplies.find(GoodToManufacture);
  if (it_temp != fSupplies.end()){
    thisStepSoldVolume=rStartOfStepSupply-it_temp->second.GetNumberOfCopies();
  }



  if (thisStepProfit >0 ){//Made money
    //give 10% to the owner of the company
    // if (fTheOwner !=NULL){
    //   fTheOwner->GetPaid(0.1*thisStepProfit,"Receiving returns from owning company");
    //   this->SubtractMoney(0.1*thisStepProfit);
    // }
    rHireMorePeople=true;
    ss<<"I made money so I am gonna try to hire more people"<<endl;
  }else {//We are not making moeny

  }

  if (RandomManager::GetRand(100)/100. > rSteadfastness){
    if (thisStepSoldVolume < 10){
      int temp =fGoodPriorities[GoodToManufacture];
      //      cout<<"before price "<<temp<<endl;
      temp = temp - temp*rPriceChangeLevel;
      //      cout<<"after price "<<temp<<endl;
      
      if (temp < 10){
	temp=10;
      }
      
      fGoodPriorities[GoodToManufacture]=temp;

      // cout<<"This is manufacturer "<<this->GetBaseId()<<" in lower price"<<endl;
      // cout<<"Steadfastneess "<<rSteadfastness<<endl;
      // cout<<"Volume sold "<<thisStepSoldVolume<<endl;
      // cout<<"rPriceChangelevel "<<rPriceChangeLevel<<endl;
      // cin.get();

      ss<<"I am lowering my price "<<endl;
      
    }else if (thisStepSoldVolume > 0.85*rStartOfStepSupply){
      int temp =fGoodPriorities[GoodToManufacture];
      // cout<<"before price "<<temp<<endl;
      temp = temp + temp*rPriceChangeLevel;
      // cout<<"after price "<<temp<<endl;
      fGoodPriorities[GoodToManufacture]=temp;
      // cout<<"This is manufacturer "<<this->GetBaseId()<<" in raise price"<<endl;
      // cout<<"Steadfastneess "<<rSteadfastness<<endl;
      // cout<<"Volume sold "<<thisStepSoldVolume<<endl;
      // cout<<"rPriceChangelevel "<<rPriceChangeLevel<<endl;
      // cin.get();
      ss<<"I am raising my price "<<endl;
   
    }
  }
  ActorActions ret=ActorActions::None;

  //Pay the employees if able
  for (auto & i : Employees2Salary){
    double moneyToPay=i.second;
    if (moneyToPay > fMoney){
      // cout<<"Comapny "<<this->GetBaseId()<<" going bankrupt "<<endl;
      // cout<<"I have this number of employeees "<<Employees2Salary.size()<<endl;
      // for (auto j : Employees2Salary){
      // 	cout<<"Employee "<<j.first<<" pay "<<j.second<<endl;
      // }
      // cout<<"Num productions "<<numberOFProductions<<endl;
      // cout<<"steps "<<numberOfSteps<<endl;
      // cin.get();



      ss<<"Going Bankrupt. Trying to pay employee "<<i.first->GetBaseId()<<" "<<moneyToPay<<" but only have "<<fMoney<<"\n";


      //Can't pay that going bankrupt
      fTheEconomicActorManager->MarkForDeath(this);
      ret=ActorActions::Died;
      break;
    }else {
      stringstream stemp;stemp<<"Company "<<GetBaseId()<<" is paying salary "<<moneyToPay<<endl;
      i.first->GetPaid(moneyToPay,stemp.str());
      this->SubtractMoney(moneyToPay);
      ss<<" I Paid an employee "<<i.first->GetBaseId()<<" "<<moneyToPay<<" I have "<<fMoney<<" money left"<<endl;
    }
  }

  if (RandomManager::GetRand(100) <=1 &&Employees2Salary.size()!=0){
    //

    auto it= Employees2Salary.begin();
    it->first->YourFired();
    Employees2Salary.erase(it);

  }

  if (fMyActorLogger!=NULL){
    fMyActorLogger->EndMessage(ss.str());
    fMyActorLogger->LogAfterStepState(this);
  }

  
  numberOfSteps++;
  return ret;
}


void Manufacturer::DumpConnections(){
  cout<<"Connections For Manufacturer "<<this->GetBaseId()<<endl;
  for (auto & ii : fConnections){
    cout<<"    Manufacturer "<<this->GetBaseId()<<" connects to "<<ii.first<<endl;
  }


}

void Manufacturer::PrintInfo(){
  PrintLine('v',30);
  cout<<"Info for <Manufacturer> base id "<<this->GetBaseId()<<" actor type "<<this->GetActorType()<<endl;
  cout<<"I have "<<Employees2Salary.size()<<" employees.  I make "<<GoodToManufacture<<endl;
  cout<<"My Maximum volume is "<<MaxVolume<<" I have made "<<rTotalVolumeCreated<<" total"<<endl;
  cout<<"I have "<<fMoney<<" monies"<<endl;
  PrintLine('^',30);
}
