#include <iostream>
#include <memory>
#include <vector>

#include <opencv4/opencv2/opencv.hpp>

#include <config>
int main (){
    std::string temp;
    std::shared_ptr<cnn_practice::config::Config> config = cnn_practice::config::get_config(); 

    if(! config -> have_monitor){
        std::cout << "We don't have a monitor. So, we are skipping visual display code.\n\n";
    }


    std::cout << config -> image_path -> string() << "\n";

    std::vector<cv::Mat> images = config -> get_images();
    
    std::cout << "******************************************\n";
    
    for(auto elem : images){
        temp = elem.generic_string();
        std::cout << temp << "\n";

        if(config -> have_monitor){
            cv::namedWindow(temp, cv::WINDOW_NORMAL);
            cv::imshow(temp, image);
            cv::resizeWindow(temp, 800, 600); //VGA
            cv::waitKey(0);
        }
    }

    std::cout << "\n";
    return 0;
}