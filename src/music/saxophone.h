#include "music_instrument.h"

#ifndef SAXOPHONE_H
#define SAXOPHONE_H
class Saxophone : public MusicInstruments {
  private:
    static const u32 maxHealth = 100;
    static const u32 updatePrice = 50;
    static const u32 healthIncrease = 100;
    static const u32 powerIncrease = 0;

  protected:
    u32 getMaxHealth() const override;
    u32 getUpdatePrice() const override;

  public:
    Saxophone();
    bool levelUp() override;
};
#endif
