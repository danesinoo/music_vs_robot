#ifndef CASH_H
#define CASH_H
#include "../view/observers/cashObserverInterface.h"
#include <iostream>
#define u32 unsigned int

class Cash {
private:
  static Cash *instance;
  u32 total;
  Cash();

  static std::vector<CashObserverInterface *> observers;
  static void notifyObservers();
  static Cash &getInstance();

public:
  static void cleanUp();
  static void add(u32 amount);
  static bool sub(u32 amount); // returns false if not enough cash
  static u32 get();            // getTotal -> get

  static void registerObserver(CashObserverInterface *obs);
};
#endif
