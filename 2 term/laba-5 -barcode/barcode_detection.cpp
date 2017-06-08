//
//  barcode_detection.cpp
//  barcode
//
//  Created by Андрей Пригода on 08.06.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "barcode_detection.hpp"

BarcodeDetector::BarcodeDetector() : ddepth(CV_16S) {}

Mat BarcodeDetector::gradDifference() {
    
    Mat gradX, gradY;
    Mat absGradX, absGradY;
    
    // Get gray version f the image
    cvtColor(this->image, this->grayImage, CV_BGR2GRAY);
    
    // Gradient X
    Sobel(this->grayImage, gradX, ddepth, 1, 0);
    // Gradient Y
    Sobel(this->grayImage, gradY, ddepth, 0, 1);
    
    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);
    
    Mat gradDiff = absGradX - absGradY;
    
    return gradDiff;
}

Mat BarcodeDetector::getImageWithRectangle(Mat graddDiff) {
    
    // Bluring - region normalization
    blur(graddDiff,this->imageSmooth, Size(31, 31), Point(-1, -1));
    
    // Find the location of the max value
    double minValue, maxValue;
    Point minLocation, maxLocation;
    
    // Get top-left corner of the position for the best match
    minMaxLoc(this->imageSmooth, &minValue, &maxValue, &minLocation, &maxLocation);
    
    std::cout << "Max value : " << maxValue << std::endl;
    
    if(maxValue > 135.0){
        // thresholding by OTSU method
        Mat thres;
        
        // devide image into two colors -> white and black
        threshold(this->imageSmooth, thres, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        
        Point MaxPoint(maxLocation.x, maxLocation.y);
        
        // get the frame
        Rect rect = crop(thres, MaxPoint);
        
        int borderWidth = 3;
        
        Scalar borderColor(0, 255, 0);
        
        // Draw rectangle
        rectangle(this->image, rect, borderColor, borderWidth);
    }
    return this->image;
}

Mat BarcodeDetector::getBarcodeLocation(const Mat image) {
    this->image = image;
    Mat gradDiff = gradDifference();
    return getImageWithRectangle(gradDiff);
}

Rect BarcodeDetector::crop(Mat thresImage, Point MaxPoint){
    int x = MaxPoint.x;
    int y = MaxPoint.y;
    
    Rect Location;
    
    int leftLocation = -1 , rightLocation = -1, upLocation = -1 , downLocation = -1;
    
    // Find the barcode rectangle
    for (int i(x); thresImage.ptr<uchar>(y)[i] != 0; i--) {
        leftLocation = i;
    }
    for (int i(x); thresImage.ptr<uchar>(y)[i] != 0; i++) {
        rightLocation = i;
    }
    for (int i(y); thresImage.ptr<uchar>(i)[x] != 0; i++) {
        downLocation = i;
    }
    for (int i(y); thresImage.ptr<uchar>(i)[x] != 0; i--) {
        upLocation = i;
    }
    
    Location.x = leftLocation;
    Location.y = upLocation;
    Location.width = rightLocation - leftLocation;
    Location.height = downLocation - upLocation  ;
    
    return Location;
}
