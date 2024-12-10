#include <cstdlib>

#include <utilities.hpp>
namespace cnn_practice{
    namespace utilities {

        std::string convert_to_lowercase(std::string input){
            std::transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c){ return std::tolower(c); });    
            return input;
        }
        
        bool do_we_have_a_monitor(){
            bool retval = false;
            #ifdef __linux__
            //Check "DISPLAY" environment variable.
            const char* temp;
        
            //Try X11:
            temp = std::getenv("DISPLAY");
        
            //Try Wayland:
            if(temp == NULL) {
                temp = std::getenv("WAYLAND_DISPLAY");
            }
        
            retval = (temp != NULL);
        
            #else
                #error "For now, this executable only compiles on Linux systems."
            #endif
        
            return retval;
        }

    };
};