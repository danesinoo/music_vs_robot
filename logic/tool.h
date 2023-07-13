#pragma once
#include "damage.h"
#include "include.h"

class Tool : public Cloneable, public AcceptGUI {
private:
  short int durability;

public:
  Tool(int = 0);
  bool isBroken() const;
  virtual u32 attack();
  virtual bool sufferDamage(Damage *);
  virtual u32 move();
  virtual u32 value() const;

  Tool *clone() const override;
  void accept(VisitorGUI *) const override;
};

class ToolWeapon : public Tool {
private:
  u32 a;

public:
  ToolWeapon(u32, u32 = 0);
  u32 attack() override;
  bool sufferDamage(Damage *) override;
  ToolWeapon *clone() const override;
  void accept(VisitorGUI *) const override;
};

class ToolArmor : public Tool {
public:
  ToolArmor(u32);
  bool sufferDamage(Damage *) override;
  ToolArmor *clone() const override;
  void accept(VisitorGUI *) const override;
};

class ToolBoots : public Tool {
private:
  u32 s;

public:
  ToolBoots(u32, u32);
  bool sufferDamage(Damage *) override;
  u32 move() override;
  ToolBoots *clone() const override;
  void accept(VisitorGUI *) const override;
};

class ToolRing : public Tool {
private:
  u32 v;

public:
  ToolRing(u32, u32);
  u32 value() const override;
  ToolRing *clone() const override;
  void accept(VisitorGUI *) const override;
};
