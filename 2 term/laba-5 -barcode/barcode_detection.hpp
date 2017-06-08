//
//  barcode_detection.hpp
//  barcode
//
//  Created by Андрей Пригода on 08.06.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#ifndef barcode_detection_hpp
#define barcode_detection_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class BarcodeDetector {
public:
    BarcodeDetector();
    Mat getBarcodeLocation(Mat);
    
private:
    
    Mat image;
    Mat grayImage;
    Mat imageSmooth;
    
    Rect crop(Mat, Point);
    Mat gradDifference();
    Mat getImageWithRectangle(Mat);
    
    const int ddepth;
};


#endif /* barcode_detection_hpp */
