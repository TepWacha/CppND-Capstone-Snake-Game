#ifndef PLAYERQ_H
#define PLAYERQ_H
#include <mutex>
#include <deque>
enum class Player {plyr1, plyr2, noPlyr};
class Playerq
{
public:
    Player receive();
    void send(Player &&msg);

private:
    std::deque<Player> queue;
    std::condition_variable cond;
    std::mutex mtx;
};
#endif