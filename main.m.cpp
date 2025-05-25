#include <iostream>
#include "command-processor.h"
#include "timerdisplay.h"
#include <thread>
#include <chrono>
#include "timer.h"
#include "clock.h"
#include "util.h"


int main(){
    /**
     * add-timer seconds, min:second, hour:minute:second
     * show-timers
     * show-timer number
     * pause-timer number
     * resume-timer number
     * stop-timer number
     */
    ose4g::CommandProcessor cp("MyTimer");
    ose4g::Clock clock;

    ose4g::ArgCountRule<1,1> minOneArgumentRule;
    ose4g::UserRule validTimeRule([&clock](const ose4g::Args& args){
        if(!ose4g::validateTime(args[0]))
        {
            return std::pair{false, "Time should either be number of seconds, MM:SS or HH:MM:SS"};
        }
        return std::pair{true, ""};
    });
    ose4g::UserRule firstArgumentInteger([&clock](const ose4g::Args& args){
        try {
            std::stoi(args[0]); 
        } catch (const std::invalid_argument& e) {
            return std::pair{false, "numeric value expected"};
        } catch (const std::out_of_range& e) {
            return std::pair{false, "integer out of range"};
        }
        return std::pair{true, ""};
    });


    cp.add("add-timer",[&clock](const ose4g::Args& args){
        int seconds = ose4g::getSeconds(args[0]);
        clock.addTimer(seconds);
    }, {&minOneArgumentRule, &validTimeRule});

    cp.add("show-timers",[&clock](const ose4g::Args& args){
        clock.showTimers();
    });

    cp.add("show-timer",[&clock](const ose4g::Args& args){
        int index = std::stoi(args[0]);
        clock.showTimer(index);
    },{&minOneArgumentRule, &firstArgumentInteger});

    cp.add("pause-timer",[&clock](const ose4g::Args& args){
        int index = std::stoi(args[0]);
        clock.pauseTimer(index);
    },{&minOneArgumentRule, &firstArgumentInteger});

    cp.add("remove-timer",[&clock](const ose4g::Args& args){
        int index = std::stoi(args[0]);
        clock.removeTimer(index);
    },{&minOneArgumentRule, &firstArgumentInteger});

    cp.add("resume-timer",[&clock](const ose4g::Args& args){
        int index = std::stoi(args[0]);
        clock.startTimer(index);
    },{&minOneArgumentRule, &firstArgumentInteger});

   
    cp.run();
    // ose4g::showWhile([](){
    //     std::cout<<"I am running"<<std::endl;
    // });    
    
}