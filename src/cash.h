#ifndef CASH_H
#define CASH_H
#include "include.h"
class Cash {
  private:
    static Cash *instance;
    u32 total;
    Cash();

  public:
    static Cash *getInstance();
    void add(u32 amount);
    bool sub(u32 amount); // returns false if not enough cash
    u32 getTotal();
};
#endif
