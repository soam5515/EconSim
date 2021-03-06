

#include "PersonTraitPact.hh"
#include "RandomManager.hh"
#include "Utilities.hh"


float PersonTraitPact::TraitMutationRate=0.05;
int PersonTraitPact::DiscreteTraitMutationRate=2;




bool PersonTraitPact::RunTests(){
  bool status=true;

  PersonTraitPact testPact;
  testPact.InitializeTraits();

  status=DoTest(testPact.Restlessness >0 &&testPact.Restlessness<1,"Restlessness intializes correctly");
  status=DoTest(testPact.InvestmentLevel >0 &&testPact.Restlessness<1,"Investmentlevel intializes correctly");

  status=DoTest(testPact.Gluttoness >0,"Gluttoness inializes correctly");
  status=DoTest(testPact.FoodBuyingThreshold >0,"ttoness inializes correctly");
  status=DoTest(testPact.Gluttoness >0,"Gluttoness inializes correctly");
  
  return status;
}

void PersonTraitPact::InitializeTraits(){

  // for (int i=0;i<theTraitPact.GetSize();i++){
  //   auto trait =theTraitPact.GetTrait(i);
  //   if (trait.type()==typeid(int)){
  //     int *x;
  //     theTraitPact.GetTrait(i,x);
  //   }
  //   if (trait.type()==typeid(float)){
  //   }
  // }

  Restlessness=RandomManager::GetUniform();
  Gluttoness=RandomManager::GetRand(10)+1;
  FoodBuyingThreshold=RandomManager::GetRand(100)+10;
  Food2BuyAtOnce=RandomManager::GetRand(100)+10;
  InvestmentLevel=RandomManager::GetUniform();

  QuitProbability=RandomManager::GetUniform();
  ProbabilityForPayCut=RandomManager::GetUniform();
}

void PersonTraitPact::MutateCopy(const PersonTraitPact & RHS){


  Gluttoness =RHS.Gluttoness + RandomManager::GetRand(DiscreteTraitMutationRate) -
    DiscreteTraitMutationRate/2;
  FoodBuyingThreshold =RHS.FoodBuyingThreshold+ RandomManager::GetRand(DiscreteTraitMutationRate) -
    DiscreteTraitMutationRate/2;
  Food2BuyAtOnce      =RHS.Food2BuyAtOnce+ RandomManager::GetRand(DiscreteTraitMutationRate) -
    DiscreteTraitMutationRate/2;


  InvestmentLevel     =RHS.InvestmentLevel + RandomManager::GetGaus(0,TraitMutationRate);
  Restlessness        =RHS.Restlessness + RandomManager::GetGaus(0,TraitMutationRate);


  QuitProbability    =RHS.QuitProbability+ RandomManager::GetGaus(0,TraitMutationRate);
  ProbabilityForPayCut    =RHS.ProbabilityForPayCut+ RandomManager::GetGaus(0,TraitMutationRate);


  
  BoundAboveZero(QuitProbability);
  BoundAboveZero(ProbabilityForPayCut);
  BoundAboveZero(Gluttoness);
  BoundAboveZero(FoodBuyingThreshold);
  BoundAboveZero(Food2BuyAtOnce);

  BoundZeroToOne(InvestmentLevel);
  BoundZeroToOne(Restlessness);
  
  if (Gluttoness ==0){
    Gluttoness=1;
  }
}
