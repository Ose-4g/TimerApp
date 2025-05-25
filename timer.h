#ifndef TIMER_H
#define TIMER_H

#include <unordered_map>
#include <thread>
#include <mutex>

namespace ose4g{
    
    class Timer{
        public: 
            enum class Status{
                RUNNING,
                PAUSED,
                DEFAULT
            };
        private:
            std::atomic<int> d_seconds;
            std::atomic<Status> d_status = Status::DEFAULT;
            std::unique_ptr<std::thread> p_timerThread;
            std::condition_variable d_cv;
            std::mutex d_mtx;
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