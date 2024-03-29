#pragma once
#define u32 unsigned int

template <typename T> class ObserverPlaygroundInterface {
public:
  virtual void update(u32 row, u32 col, const T *e) = 0;
};
