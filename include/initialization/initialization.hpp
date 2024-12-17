#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_INITIALIZATION_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_INITIALIZATION_HPP

#include <memory>

#include <config.hpp>

namespace cnn_practice {
    namespace initialization {

        int initialize(int argc, char*[] argv);
 
        //Performs initialization and sets up the error-handlng wrappers.
        int main(std::shared_ptr<cnn_practice::config::Config> config);

    };
};
#endif