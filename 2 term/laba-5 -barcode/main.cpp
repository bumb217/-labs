//
//  main.cpp
//  barcode
//
//  Created by Андрей Пригода on 07.06.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//


#include <string>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "barcode_detection.hpp"

using namespace cv;
using namespace std;

Mat downloadImage(string fileName) {
    auto image = imread(fileName.c_str());
    if (image.empty()) {
        throw runtime_error("Image cannot be loaded!");
    }
    return image;
}

//void saveImage(Mat image, string fileName) {
//    imwrite(fileName.c_str(), image);
//}

int main (int argc, const char **argv) {
    
    BarcodeDetector D;
    
    vector<string> names = {"1.jpg","4.jpg","3.jpg","2.jpg","5.jpg"};
    
    for (auto name : names) {
        
        Mat input = downloadImage(name);
        
        D.getBarcodeLocation(input);
        
        namedWindow("img", WINDOW_AUTOSIZE);
        imshow("img", input);
        waitKey(0);
    }
    
    return 0;
}
