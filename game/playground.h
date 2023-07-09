#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include "../view/observers/playgroundObserverInterface.h"
#include "include.h"
#include "timer.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>

class Playground : DataManagerInterface {
  private:
    std::unique_ptr<MusicInstruments> player[ROWS][COLUMNS];
    deque<RobotWTool> enemy[ROWS][FRAME_COLUMNS * COLUMNS + 1];
    static Playground *instance;
    Playground();
    void reset();
    u32 nearestPlayer(u32 row, u32 col) const;
    template <typename S> void iterRobot(u32 row, u32 col, S fun);
    void playerLoad(u32 row, u32 col, MusicInstruments *mi);

    static std::vector<PlaygroundObserverInterface *> observers;
    static void notifyMusicObservers(int row, int col);
    static void notifyRobotObservers(int row, int col);
    ~Playground();

  public:
    u32 damagePos;
    static void cleanUp();
    void enemyInsert(u32 row, u32 difficulty);
    bool isEmpty(u32 row, u32 col) const;
    const MusicInstruments *playerGet(u32 row, u32 col) const;
    deque<const RobotWTool *> enemyGet(u32 row, u32 col) const;
    void playerRemove(u32 row, u32 col);
    bool playerInsert(u32 row, u32 col, MusicInstruments *mi);
    bool playerLevelUp(u32 row, u32 col);
    bool lose() const;
    void playerAttack(u32 colonna);
    void damagePropagate(u32 colonna);
    void enemyAttack(u32 colonna);
    bool enemyMove();
    static void battle();
    //  std::ostream &print(std::ostream &) const;
    static Playground *getInstance();

    static void registerObserver(PlaygroundObserverInterface *obs);

    virtual std::string saveData() const override;
    virtual Playground *loadData(std::string) override;
};

template <typename S> void Playground::iterRobot(u32 row, u32 col, S fun) {
    std::for_each(&enemy[row][col * FRAME_COLUMNS], &enemy[row][(col + 1) * FRAME_COLUMNS], fun);
}
#endif

/* come mi immagino il main, il realtà damagePropagate(i) dovrebbe essere
 * incluso in playerAttack(i)
void Playground::battle() {
}
*/
