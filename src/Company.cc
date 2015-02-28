

#include "Company.hh"
#include "Settings.hh"

#include "RandomManager.hh"

Company::Company(EconomicActorManager* man ) : EconomicActor(man){

  Employees2Salary.clear();


}


Company::~Company(){
  //  cout<<"~company()"<<endl;


}

void Company::AddEmployee(Person *a ,double salary){
  
  auto it =Employees2Salary.find(a);

  if(it == Employees2Salary.end()){//Employee isn't there
    Employees2Salary.insert(make_pair(a,salary));
  }
}


void Company::RemoveEmployee(Person * p){
  auto it = Employees2Salary.find(p);
  
  if (it != Employees2Salary.end()){//Employees is there
    Employees2Salary.erase(it);
  }

}