#include "playerq.h"
#include <iostream>
#include <memory>

Player Playerq::receive()
{
    std::unique_lock<std::mutex> uLock(mtx);
    cond.wait(uLock, [this]{ return !queue.empty(); });
    Player msg = queue.front();
    queue.pop_front();
    return msg;
}

void Playerq::send(Player &&msg)
{
    std::lock_guard<std::mutex> lockGuard(mtx);
    queue.emplace_back(std::move(msg));
    cond.notify_one();
}