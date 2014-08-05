#ifndef __PERSONMANAGER_HH
#define __PERSONMANAGER_HH

//
// Person Manager class. 
//
//


#include "Base.hh"
#include <vector>

//Foward Declarations
class Person;


class PersonManager : public Base {
public:
  PersonManager();

  ~PersonManager();

  void BuildList(int NumberOfPeople);
  void Initialize();

  void PrintConnections();
  void PrintHavesWants();
  void PrintHavesWants(int);
  void MakeTransactions();

private:
  int rInitialTopConectivity;
  int rNumInteractingPeoplePerStep;
  int rNumPeople;
  std::vector <Person> rTheListOfPeople;

};


#endif
