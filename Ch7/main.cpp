//
//  main.cpp
//  Ch7
//
//  Created by zz on 8/4/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 7.2 Harris Corner Detection
void HarrisCornerDetection() {
    GoodFeaturesToTrackDetector harris_detector(1000, 0.01, 10, 3, true);
    vector<KeyPoint> keypoints;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    harris_detector.detect(gray_image, keypoints);

    Mat display_image;
    drawKeypoints(image, keypoints, display_image, Scalar(0, 0, 255));
}

// 7.3 FAST Corner Detection
void FASTCornerDetection() {
    Ptr<FeatureDetector> feature_detector = FeatureDetector::create("FAST");
    vector<KeyPoint> keypoints;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    feature_detector->detect(gray_image, keypoints);

    // An implementation which is 5x faster
    FASTX(gray_image, keypoints, 50, true, FastFeatureDetector::TYPE_9_16);
}

// 7.4.1 SIFT Scale Space Extrema Detection
void SIFT1() {
    Ptr<FeatureDetector> feature_detector = FeatureDetector::create("SIFT");
    vector<KeyPoint> keypoints;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    feature_detector->detect(gray_image, keypoints);
}

// 7.4 SIFT
void SIFT() {
    SiftFeatureDetector sift_detector;
    vector<KeyPoint> keypoints1, keypoints2;
    sift_detector.detect(gray_image1, keypoints1);
    sift_detector.detect(gray_image2, keypoints2);
    // Extract feature descriptors
    SiftDescriptorExtractor sift_extractor;
    Mat descriptors1, descriptors2;
    sift_extractor.compute(gray_image1, keypoints1, descriptors1);
    sift_extractor.compute(gray_image2, keypoints2, descriptors2);
    // Match descriptors
    BFMatcher sift_matcher(NORM_L2);
    vector<DMatch> matches;
    sift_matcher.match(descriptors1, descriptors2, matches);
    // Display SIFT matches
    Mat display_image;
    drawMatches(gray_image1, keypoints1, gray_image2, keypoints2, matches, display_image);
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
