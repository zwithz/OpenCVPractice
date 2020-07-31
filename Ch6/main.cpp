//
//  main.cpp
//  Ch6
//
//  Created by zz on 7/28/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 6.1.1.2 Compass Edge Detectors
void compassEdgeDetectors() {
    Mat horizontal_derivative, vertical_derivative;
    Sobel(gray_image, horizontal_derivative, CV_32F, 1, 0);
    Sobel(gray_image, vertical_derivative, CV_32F, 0, 1);
}

// 6.1.1.3 Computing Gradient and Orientation
void computingGradientAndOrientation() {
    abs_gradient = abs(horizontal_derivative) + abs(vertical_derivative);
    cartToPolar(horizontal_derivative, vertical_derivative, l2norm_gradient, orientation);
}

// 6.1.1.5 Non-maxima Suppression
void nonMaximaSuppression() {
    nms_result = gradients.clone();
    for (int row = 1; row < gradients.rows - 1; row++) {
        for (int column = 1; column < gradients.cols - 1; column++) {
            float curr_gradient = gradients.at<float>(row, column);
            float curr_orientation = orientations.at<float>(row, column);
            // Determine which neighbors to check
            int direction = (((int)(16.0 * curr_gradient / (2.0 * PI)) + 15) % 8) / 2;
            float gradient1 = 0.0, gradient2 = 0.0;
            switch (direction) {
                case 0:
                    gradient1 = gradients.at<float>(row - 1, column - 1);
                    gradient2 = gradients.at<float>(row + 1, column + 1);
                    break;
                case 1:
                    gradient1 = gradients.at<float>(row - 1, column);
                    gradient2 = gradients.at<float>(row + 1, column);
                    break;
                case 2:
                    gradient1 = gradients.at<float>(row - 1, column + 1);
                    gradient2 = gradients.at<float>(row + 1, column - 1);
                    break;
                case 3:
                    gradient1 = gradients.at<float>(row, column + 1);
                    gradient2 = gradients.at<float>(row, column - 1);
                    break;
                default:
                    break;
            }
            if ((gradient1 > curr_gradient) || (gradient2 > curr_gradient))
                nms_result.at<float>(row, column) = 0.0;
        }
    }
}

// 6.1.2.1 Laplacian of Gaussian
void LaplacianofGaussian() {
    Mat laplacian;
    Mat blurred_image;
    GaussianBlur(gray_image, blurred_image, Size(5, 5), 1.5);
    Laplacian(blurred_image, laplacian, CV_32F, 3);
}

// 6.1.2.3 Canny Edge Detection
void CannyEdgeDetection() {
    Canny(gray_image, binary_edges, 100, 200);
}

// 6.1.4 Image Sharpening
void imageSharpening() {
    image.convertTo(image_32bit, CV_32F);
    Laplacian(image, laplacian, CV_32F, 3);
    Mat sharp_image_32bit = image_32bit - 0.3 * laplacian;
    sharp_image_32bit.converTo(sharp_image, CV_8U);
}

// 6.2.1.1 Boundary Chain Codes
void BCC() {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary_edge_image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
}

// 6.2.1.2 Directed Graphs
void directedGraphs() {
    for (int contour_number = 0; contour_number < contours.size(); contour_number++) {
        Scalar color(rand() & 0xFF, rand() & 0xFF, rand & 0xFF);
        drawContours(display_image, contours, contour_number, color, 1, 8, hierarchy);
    }
}

// 6.2.3.1 Recursive Boundary Splitting
void recursiveBoundarySplitting() {
    vector<vector<Point>> approx_contours(contours.sise());
    for (int contour_number = 0; contour_number < contours.size(); contour_number++) {
        approxPolyDP(Mat(contours[contour_number]), approx_contours[contour_number], 3, true);
    }
}

void approxPolyDPFunction() {
    vector<Vec4i> line_segments;
    for (int contour_number = 0; contour_number < contours.size(); contour_number++) {
        for (int segment_num = 0; segment_num < approx_contours[contour_number].size() - 1; segment_num++) {
            line_segments.push_back(Vec4i(approx_contours[contour_number][segment_num].x, approx_contours[contour_number][segment_num].y, approx_contours[contour_number][segment_num + 1].x, approx_contours[contour_number][segment_num + 1].y));
        }
    }
}

// 6.3.1 Hough for Lines
void HoughForLines() {
    vector<Vec2f> hough_lines;
    HoughLines(binary_edge_image, hough_lines, 1, PI / 200.0, 60);
}

void probabilisticHoughTransform() {
    vector<Vec4i> line_segments;
    HoughLinesP(binary_edge_image, line_segments, 1.0, PI / 200.0, 20, 20, 5);
}

// 6.3.2 Hough for Circles
void HoughForCircles() {
    vector<Vec3f> circles;
    HoughCircles(gray_image, circles, CV_HOUGH_GRADIENT, 2, 20, 300, 20, 5, 15);
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
