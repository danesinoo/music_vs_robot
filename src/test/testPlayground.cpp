#include "main.h"

// controllare se un robot si sposta nella colonna dei danni e nel caso
// calcolare i danni che si prende

Playground *get() {
  Playground::cleanUp();
  return Playground::getInstance();
}

bool TestInsertEnemy() {
  get()->insertEnemy(0, 1);
  return true;
}

bool TestInsertPlayer() {
  Playground *tmp = get();
  // dobbiamo avere abbastanza soldi per inserire uno strumento
  Cash::getInstance()->add(Flute().getCost());
  if (!tmp->insertPlayer(0, 0, NORMIE))
    return false;
  if (tmp->insertPlayer(0, 0, NORMIE))
    return false;
  Cash::getInstance()->add(Flute().getCost());
  if (!tmp->insertPlayer(0, 1, NORMIE))
    return false;
  return true;
}

bool TestLose() {
  Playground *tmp = get();
  tmp->insertEnemy(2, 59);
  for (u32 i = 0; i < 60; i++)
    tmp->moveRobots();
  return tmp->lose();
}

bool TestPlayerAttack() {
  Playground *tmp = get();

  // row 1 -- three flutes
  Cash::getInstance()->add(Flute().getCost());
  tmp->insertPlayer(0, 0, NORMIE);
  Cash::getInstance()->add(Flute().getCost());
  tmp->insertPlayer(0, 1, NORMIE);
  Cash::getInstance()->add(Flute().getCost());
  tmp->insertPlayer(0, 2, NORMIE);
  // row 2 -- empty
  // row 3 -- 1 trumpet (should do damage on 3 rows)
  Cash::getInstance()->add(Trumpet().getCost());
  tmp->insertPlayer(2, 0, THREE_R);
  // row 4 -- 1 drum (should do damage for 3 more columns)
  Cash::getInstance()->add(Drum().getCost());
  tmp->insertPlayer(3, 0, THREE_C);
  // row 5 -- 1 violin (should slow down the first enemy)
  Cash::getInstance()->add(Violin().getCost());
  tmp->insertPlayer(4, 0, SLOW);

  u32 i = 0;
  tmp->playerAttack(i++);
  if (tmp->damage[3][1] != music::New(THREE_C)->attack())
    return false;

  // check the other instruments
  for (; i < COLUMNS; i++)
    tmp->playerAttack(i);
  if (tmp->damage[0][0] != Flute().attack() * 3)
    return false;
  if (tmp->damage[1][0] != Trumpet().attack() ||
      tmp->damage[2][0] != Trumpet().attack() ||
      tmp->damage[3][0] != Trumpet().attack())
    return false;
  if (tmp->slowDown[4] == 0)
    return false;
  return true;
}
