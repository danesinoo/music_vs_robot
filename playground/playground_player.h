#pragma once
#include "../entity/player.h"
#include "../include.h"
#include "playground_damage.h"

class PlaygroundPlayer : public ObservablePlaygroundInterface<PlayerAbstract>, public DataManagerInterface {
  private:
    ptr<PlayerAbstract> player[ROWS][COLS - 1];

  public:
    bool insert(u32 row, u32 col, const PlayerAbstract &player);
    bool remove(u32 row, u32 col);
    bool isEmpty(u32 row, u32 col) const;
    bool levelUp(u32 row, u32 col);
    PlayerAbstract &get(u32 row, u32 col);
    const PlayerAbstract &get(u32 row, u32 col) const;
    void attack(PlaygroundDamage &) const;

    void notifyObservers(u32 row, u32 col) const override;

    std::string toString() const override;
    DataManagerInterface *fromString(std::string) override;
    void load(u32 row, u32 col, PlayerAbstract *player);
};
