#ifndef CNN_PRACTICE_EXCEPTIONS
#define CNN_PRACTICE_EXCEPTIONS
namespace cnn_practice {
    namespace error_handling {
        //Hello:
        class NotImplementedException : std::logic_error {
            //Hello:
            public:
            NotImplementedException() : std::logic_error("Logic has yet to be implemented"){}
        };
    };
};
#endif