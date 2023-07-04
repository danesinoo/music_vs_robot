#ifndef PLAYGROUND_OBSERVER_INTERFACE_H
#define PLAYGROUND_OBSERVER_INTERFACE_H

#include "../game/include.h"

class Playground;
class Entity;
class MusicInstruments;
class Robot;

class PlaygroundObserverInterface {
  public:
    virtual void clearPlayground() = 0;
    virtual void updatePlaygroundMusic(u32 row, u32 col, MusicInstruments *mi = nullptr) = 0;
    virtual void updatePlaygroundRobot(u32 row, u32 col, Robot *r = nullptr) = 0;

    virtual ~PlaygroundObserverInterface() = default;
};

#endif