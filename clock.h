#ifndef CLOCK_H
#define CLOCK_H

#include <map>
#include "timer.h"

namespace ose4g{
    const int MAX_TIMERS = 10;
    class Clock{
        /// @brief maps timer id to seconds left in that timer.
        std::map<int,std::unique_ptr<Timer>> d_timers;
        int d_counter  = 1;

        private:
            void validateIndex(int index);
        public: 
            void addTimer(int seconds);
            void startTimer(int index);
            void pauseTimer(int index);
            void showTimers();
            void showTimer(int index);
            void removeTimer(int index);
    };
}

#endif