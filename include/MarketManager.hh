


#ifndef __MARKETMANAGER_HH
#define __MARKETMANAGER_HH

#include <vector>
#include <map>
#include <iostream>
#include <string>
using namespace std;
class EconomicActor;
class Company;
class Person;

#include "DataLogger.hh"

/**Small container class to hold in formation on market orders

 */
class OrderInfo{
public:
  int SellerId;
  int Quantity;
  double Price;
  OrderInfo(int id,int q,double p) : SellerId(id), Quantity(q),Price(p){}
  OrderInfo() : SellerId(-1),Quantity(-1),Price(-1){}

  ~OrderInfo(){
    SellerId=-1000;
    Quantity=-1000;
    Price=-1000;
  }
};



class JobInfo{
public:
  JobInfo(){}

  JobInfo(int d,double s) :EmployerID(d),salary(s){}

  int EmployerID;
  double salary;
};


/**This class will be responsible for holding by and sell orders from companies and 
   maybe people too

 */


class MarketManager 
{
public:

  MarketManager(DataLogger *);
  virtual ~MarketManager();
  


  void PlaceSellOrder(int GoodNumber,int SellerID, int Quantity,double Price);
  
  int GetCheapestSeller(int GoodNumber,OrderInfo & Info);

  void CleanUpOrder(int GoodNumber,double price, int SellerId,int quantity);

  void BrokerJob(Person * employee, Company * employer,double salary);
  void PlaceJobPosting(double salary, int EmployerId);

  JobInfo GetBestJob();

  void ClearMarket();
   
  void Dump();
  void DumpCurrentGoodsForSale();


  const vector <int> & GetCurrentGoodsForSale(){return rCurrentGoodsForSale;}
  
private:
 
  DataLogger * rTheDataLogger;

  //For each good make a map of prices
  vector < multimap <double,OrderInfo> > rSellPrices;
  multimap <double,JobInfo> rJobListings;

  vector <int> rCurrentGoodsForSale;

  double rAveragePrice;
  int rNumberOfDailySales;
};



#endif /* __MARKETMANAGER_HH */
