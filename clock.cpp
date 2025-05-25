#include "clock.h"
#include <string>
#include "util.h"
#include <iostream>
#include "timerdisplay.h"

namespace ose4g{
    void Clock::validateIndex(int index){
        if(!d_timers.count(index))
        {
            throw std::runtime_error("No timer with index "+std::to_string(index));
        }
    }

    void Clock::addTimer(int seconds){
        if(d_timers.size() >= MAX_TIMERS)
        {
            throw std::invalid_argument("Maximum number of timers reached");
        }
        d_timers[d_counter] = std::make_unique<Timer>(seconds);
        startTimer(d_counter);
        d_counter++;
    }

    void Clock::startTimer(int index){
        validateIndex(index);
        if(d_timers[index]->getSeconds() == 0)
        {
            throw std::runtime_error("timer already completed");
        }
        if(d_timers[index]->getStatus() == Timer::Status::RUNNING)
        {
            throw std::runtime_error("timer already started");
        }

        d_timers[index]->start();
    }

    void Clock::pauseTimer(int index){
        validateIndex(index);
        if(d_timers[index]->getStatus() != Timer::Status::RUNNING)
        {
            throw std::runtime_error("timer is not running");
        }
        d_timers[index]->pause();
    }
    void Clock::showTimer(int index){
        validateIndex(index);
        TimeDisplay td;
        showWhile([this,&index,&td](){
            int seconds = d_timers[index]->getSeconds();
            td.display(secondsToTimeString(seconds));
        });
    }

    void Clock::removeTimer(int index){
        validateIndex(index);
        if(d_timers[index]->getStatus() == Timer::Status::RUNNING)
        {
            throw std::runtime_error("Cannot remove running timer");
        }
        d_timers.erase(index);
    }

    void Clock::showTimers()
    {
        showWhile([this](){
            for(auto &k: d_timers)
            {
                std::cout<<k.first<<") "<<secondsToTimeString(k.second->getSeconds())<<std::endl;
            }
        });
        
    }
}
