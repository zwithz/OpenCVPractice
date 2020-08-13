//
//  main.cpp
//  Ch9
//
//  Created by zz on 8/13/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 9.1.3 Difference Images
void differenceImages() {
    absdiff(frame, background, difference);
}

// 9.1.4.1 Static Background Image
void staticBackgroundImage() {
    absdiff(current_frame, first_frame, difference);
    cvtColor(difference, moving_points, CV_BGR2GRAY);
    threshold(moving_points, moving_points, 30, 255, THRESH_BINARY);
    Mat display_image = Mat::zeros(moving_points.size(), CV_8UC3);
    current_frame.copyTo(display_image, moving_points);
}

// 9.1.4.3 Running Average
void runningAverage() {
    accumulateWeighted(current_frame_gray, running_average_background, 0.01);
}

// 9.1.4.4 Selectivity
void selectivity() {
    accumulateWeighted(current_frame_gray, running_average_background, 0.01, foreground_mask);
}

// 9.1.4.7 Gaussian Mixture Model
void GaussianMixtureModel() {
    BackgroundSubtractorMOG2 gmm;
    gmm(current_frame, foreground_mask);
    threshold(foreground_mask, moving_points, 150, 255, THRESH_BINARY);

    // Shadow points
    threshold(foreground_mask, changing_points, 50, 255, THRESH_BINARY);
    absdiff(moving_points, changing_points, shadow_points);
    Mat mean_background_image;
    gmm.getBackgroundImage(mean_background_image);
}

// 9.2.2 Mean Shift
void meanShift() {
    Rect position(starting_position);
    TermCriteria criteria(cv::TermCriteria::MAX_ITER, 5, 0.01);
    meanShift(back_projection_probabilities, position, criteria)
}

// 9.2.3 Dense Optical Flow
void denseOpticalFlow() {
    calcOpticalFlowFarneback(previous_gray_frame, gray_frame, optical_flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    cvtColor(previous_gray_frame, display, CV_GRAY2BGR);
    for (int row = 4; row < display.rows; row += 8) {
        for (int col = 4; col < display.cols; col += 8) {
            Point2f& flow = optical_flow.at<Point2f>(row, col);
            line(display, Point(col, row), Point(cvRound(col + flow.x), cvRound(row + flow.y)), passed_color);
        }
    }
}

// 9.2.4 Feature Based Optical Flow
void featureBasedOpticalFlow() {
    vector<Point2f> previous_features, current_features;
    const int MAX_CORNERS = 500;
    int win_size = 10;
    goodFeaturesToTrack(previous_gray_frame, previous_features, MAX_CORNERS, 0.05, 5, noArray(), 3, false, 0.04);
    cornerSubPix(previous_gray_frame, previous_features, Size(win_size, win_size), Size(-1, -1), TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
    vector<uchar> features_found;
    calcOpticalFlowPyrLK(previous_gray_image, gray_frame, previous_features, current_features, features_found, noArray(), Size(win_size * 4 + 1, win_size * 4 + 1), 5, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3));
    for (int i = 0; i < (int)previous_features.size(); i++) {
        if (features_found[i]) {
            line(display_image, previous_features[i], current_features[i], passed_color);
        }
    }
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
