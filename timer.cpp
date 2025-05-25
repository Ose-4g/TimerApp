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

        if(d_status == Status::PAUSED)
        {
            d_status = Status::RUNNING;
            d_cv.notify_all();
            return;
        }

        d_status =  Status::RUNNING;
        if(p_timerThread && p_timerThread->joinable())
        {
            p_timerThread->join();
        }
        p_timerThread = std::make_unique<std::thread>([this](){
            while(d_seconds > 0 && d_status != Status::DEFAULT)
            {
                std::unique_lock<std::mutex> lock(d_mtx);
                if(d_status == Status::PAUSED)
                {
                    d_cv.wait(lock, [this]() {
                        return d_status != Status::PAUSED;
                    });
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
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
        d_cv.notify_all();
        if(p_timerThread && p_timerThread->joinable())
        {
            p_timerThread->join();
        }
    }
}