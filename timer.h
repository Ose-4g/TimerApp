#ifndef TIMER_H
#define TIMER_H

#include <unordered_map>
#include <thread>

namespace ose4g{
    
    class Timer{
        public: 
            enum class Status{
                RUNNING,
                PAUSED,
                DEFAULT
            };
        private:
            int d_seconds;
            Status d_status = Status::DEFAULT;
            std::unique_ptr<std::thread> p_timerThread;
        public:
            Timer(int seconds):d_seconds(seconds){}
            void start();
            void pause();
            int getSeconds() const;
            Status getStatus() const;
            ~Timer();

    };
}

#endif