#include <iostream>
#include <vector>

int main(int argc, char** argv){
    std::vector<unsigned char> trial_vec{ 'a', 'a', 'a', 0x00, 0x00, 0x00, 0x04, 'a', 'a', 'a'};
    for (auto elem : trial_vec){
        std::cout << "trial_vec: " << elem << "\n";
    }
    unsigned char* trial_char_add = trial_vec.data()+3;
    for(int i = 0; i < 4; i++){
	    std::cout << "char: " << (int)trial_vec.data()[i] << "\n";
    }

    int trial =  *(reinterpret_cast<int*>(trial_char_add));
    /*unsigned trial = 0;
    int start = 3;
    for (int i = 0; i < sizeof(int); i++){
        //Hello:
	trial = trial << 8;
	trial = trial | (unsigned int)trial_vec[start];
        std::cout << "trial: " << trial << "\n";
	start++;
    }*/
    
    std::cout << "final trial: " << trial << "\n";
}
