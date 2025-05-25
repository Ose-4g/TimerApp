#include "util.h"
#include <sstream>
#include <iomanip>
#include <regex>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <iostream>

namespace ose4g{
    const std::regex SECONDS("[0-9]+");
    const std::regex MINUTES_SECONDS("[012345][0-9]:[012345][0-9]");
    const std::regex HOUR_MINUTES_SECONDS("[0-9]{2}:[012345][0-9]:[012345][0-9]");
    
    bool validateTime(const std::string& s){
        return std::regex_match(s, SECONDS) || std::regex_match(s, MINUTES_SECONDS) || std::regex_match(s, HOUR_MINUTES_SECONDS);
    }

    int getSeconds(const std::string& s){
        if(std::regex_match(s, SECONDS))
        {
            return std::stoi(s);
        }
        if(std::regex_match(s, MINUTES_SECONDS))
        {
            return std::stoi(s.substr(0,2)) * 60 + std::stoi(s.substr(3,2));
        }
        if(std::regex_match(s, HOUR_MINUTES_SECONDS))
        {
            return std::stoi(s.substr(0,2)) * 3600 + std::stoi(s.substr(3,2)) * 60 + std::stoi(s.substr(6,2));
        }
        return 0;
    }

    std::string secondsToTimeString(int totalSeconds)
    {
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int seconds = totalSeconds % 60;
    
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;
    
        return oss.str();
    }


    void waitForChar(char breakChar = 'q'){
        termios original;

        //retrieves the current terminal settings standard input
        tcgetattr(STDIN_FILENO, &original);  

        // create copy of terminal.
        auto raw = original;
        // disables line buffereing for input and echoing to terminal when you input.
        raw.c_lflag &= ~(ICANON | ECHO); 
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

        while (true)
        {
            char c;
            if (read(STDIN_FILENO, &c, 1) == 1)
            {
                if (c == breakChar)
                {
                    return;
                }
            }
        }

    }
    void showWhile(std::function<void()> func){
        bool isRunning = true;
        std::thread t([&isRunning,&func](){
            while(isRunning){
                std::cout << "\033[2J\033[H";
                func();
                std::cout<<"\nPress q to quit\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
        waitForChar();
        isRunning = false;
        t.join();
    }
}