#ifndef CNN_PRACTICE_MEMORY
#define CNN_PRACTICE_MEMORY

namespace cnn_practice {
    namespace memory {
        template <typename T> struct EmptyDeleter {
            EmptyDeleter(){}
            template <typename U> EmptyDeleter(
                const EmptyDeleter<U>&,
                typename std::enable_if<
                std::is_convertible<U*, T*>::value>::type* = nullptr
            ){
            }

            //Does nothing and that is the point. 
            void operator()(T* const) const {}
        };
    };
};

#endif