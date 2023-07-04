#ifndef ENTITY_H
#define ENTITY_H
#include "../view/visitors/entityVisitorInterface.h"
#include "cash.h"

/// Classe astratta che rappresenta le entità del gioco
class Entity {
  private:
    u32 health;
    u32 power;

  public:
    Entity(u32 health, u32 power);
    virtual ~Entity() = default;
    virtual Entity *clone() const = 0;

    virtual bool takeDamage(u32 &amount) = 0;
    virtual u32 attack() const = 0;

    u32 &getHealth();
    u32 &getPower();

    /// Funzione che permette di visitare l'entità
    virtual void accept(EntityVisitorInterface &visitor) const = 0;
};
#endif