#include "timerdisplay.h"
#include <iostream>
#include <fstream>
#include <string>

namespace ose4g{
    void TimeDisplay::initialize(){

        std::ifstream file("ui/numbers.txt");
        int readLines = 0;
        std::string line;

        if(!file.good())
        {
            throw std::runtime_error("Unable to load numbers file");
        
        }

        while(std::getline(file, line))
        {
            line = line.length() < NUMBER_WIDTH ? line + std::string(NUMBER_WIDTH-line.length(),' ') : line.substr(0,NUMBER_WIDTH);
            numbers[readLines/NUMBER_HEIGHT].push_back(line);
            readLines++;
        }


        std::ifstream file2("ui/colons.txt");

        if(!file2.good())
        {
            throw std::runtime_error("Unable to load  colons file");
        
        }

        while(std::getline(file2, line))
        {
            line = line.length() < COLON_WIDTH ? line + std::string(COLON_WIDTH-line.length(),' ') : line.substr(0,COLON_WIDTH);
            colon.push_back(line);
        }


    }

    TimeDisplay::TimeDisplay():numbers(10),allowed("\\d\\d:\\d\\d:\\d\\d"){
        initialize();
    }

    void TimeDisplay::display(const std::string& s){
        if(!std::regex_match(s,allowed))
        {
            throw std::invalid_argument("Invalid argument for time provided");
        }

        for(int i = 0; i < NUMBER_HEIGHT; i++)
        {
            for(char c: s)
            {
                std::string f = "";
                if(c==':')
                {   
                    f = colon[i];
                }
                else
                {
                    f = numbers[c-'0'][i];
                }
                std::cout<<f<<" ";
            }
            std::cout<<std::endl;
        }

    }

}