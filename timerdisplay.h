#include <vector>
#include <regex>

namespace ose4g{
    
    class TimeDisplay{
        private:
            const int NUMBER_WIDTH=9;
            const int NUMBER_HEIGHT=7;
            const int COLON_WIDTH=4;
            const std::regex allowed;
            std::vector<std::vector<std::string>> numbers;
            std::vector<std::string> colon;;

            void initialize();
        public:
            TimeDisplay();
            void display(const std::string& s);
    };
}