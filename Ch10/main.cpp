//
//  main.cpp
//  Ch10
//
//  Created by zz on 8/26/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
 * Exercise 10.1 - Baby Food
 */
void ex1() {
    const double emptyThreshold = 10;
    const double oneThreshold = 30;
    string answer[18];
    const string imagesPath = "./BabyFood/";
    const string samplePrefix = "BabyFood-Sample";
    const string testPrefix = "BabyFood-Test";
    const string suffix = ".JPG";

    // Read smaple images
    Mat sampleImages[3];
    for (int i = 0; i < 3; i++) {
        string path = imagesPath + samplePrefix + to_string(i) + suffix;
        sampleImages[i] = imread(path);
        if (sampleImages[i].empty()) {
            cout << "Failed to read sample images!" << endl;
            return;
        }
    }

    // Read test images
    Mat testImages[18];
    for (int i = 0; i < 18; i++) {
        string path = imagesPath + testPrefix + to_string(i + 1) + suffix;
        testImages[i] = imread(path);
        if (testImages[i].empty()) {
            cout << "Failed to read test images!" << endl;
            return;
        }
    }

    Mat bgr[3];

    for (int i = 0; i < 18; i++) {
        split(testImages[i], bgr);
        cout << testPrefix << to_string(i + 1) << ": ";
        double t = mean(2 * bgr[2] - bgr[0] - bgr[1])[0];
        if (t < emptyThreshold) {
            cout << "0" << endl;
        } else if (t < oneThreshold) {
            cout << "1" << endl;
        } else {
            cout << "2" << endl;
        }
    }
}

int main(int argc, const char* argv[]) {
    ex1();
    return 0;
}
