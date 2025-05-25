#include "timer.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <memory>

namespace ose4g{
    
    void Timer::start(){
        if(d_status == Status::RUNNING)
        {
            return;
        }

        d_status =  Status::RUNNING;
        if(p_timerThread && p_timerThread->joinable())
        {
            p_timerThread->join();
        }
        p_timerThread = std::make_unique<std::thread>([this](){
            while(d_status == Status::RUNNING && d_seconds > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                d_seconds--;
            }
            d_status = Status::DEFAULT;
        });
    }

    void Timer::pause(){
        if(d_status == Status::RUNNING)
        {
            d_status = Status::PAUSED;
        }
    }

    int Timer::getSeconds() const
    {
        return d_seconds;
    }

    Timer::Status Timer::getStatus() const {
        return d_status;
    }

    Timer::~Timer(){
        d_status = Status::DEFAULT;
        if(p_timerThread && p_timerThread->joinable())
        {
            p_timerThread->join();
        }
    }
}