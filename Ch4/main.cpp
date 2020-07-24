//
//  main.cpp
//  Ch4
//
//  Created by zz on 7/21/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 4.1 Thresholding
void thresholding(Mat& gray_image, Mat& binary_image, double thres) {
    threshold(gray_image, binary_image, thres, 255, THRESH_BINARY);
}

// 4.2.3 Otsu Thresholding

void otsu(Mat& gray_image, Mat& binary_image, double threshold) {
    threshold(gray_image, binary_image, threshold, 255, THRESH_BINARY | THRESH_OTSU);
}

// 4.3.1 Adaptive Thresholding
void adaptiveThresholding(Mat& gray_image, Mat& binary_image) {
    adaptiveThreshold(gray_image, binary_image, output_value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, block_size, offset);
}

// 4.3.2 Band Thresholding
void bandThresholding() {
    threshold(image, binary_image1, low_threshold, 255, THRESH_BINARY);
    threshold(image, binary_image2, high_threshold, 255, THRESH_BINARY_INV);
    bitwise_and(binary_image1, binary_image2, band_thresholded_image);
}

// 4.3.3 Semi-Thresholding
void semiThresholding() {
    threshold(gray_image, binary_image, threshold, 255, THRESH_BINARY);
    bitwise_and(gray_image, binary_image, semi_thresholded_image);
}

// 4.4.1 Dilation
void dilation1() {
    dilate(binary_image, dilated_image, Mat());
}

void dilation2() {
    Mat structuring_element(5, 5, CV_8U, Scalar(1));
    dilate(binary_image, dilated_image, structuring_element);
}

// 4.4.3 Opening and Closing
void openingAndClosing() {
    Mat five_by_five_element(5, 5, CV_8U, Scalar(1));
    morphologyEx(binary_image, opened_image, MORPH_OPEN, five_by_five_element);
    morphologyEx(binary_image, closed_image, MORPH_CLOSE, five_by_five_element);
}

// 4.5.2 Connected Components Analysis
void connectedComponentsAnalysis() {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
