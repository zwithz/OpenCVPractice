//
//  main.cpp
//  Ch5
//
//  Created by zz on 7/26/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 5.2 Affine Transformations
void affineTransformations() {
    Mat affine_matrix(2, 3, CV_32FC1);
    wrapAffine(image, result, affine_matrix, image.size());
}

// 5.2.1.4 Skewing
void skewing() {
    // Initialize to the identity matrix
    Mat affine_matrix = Mat::eye(2, 3, CV_32FC1);
    // affine_matrix[0][1] Skewing
    *(((float*)(affine_matrix.data)) + 1) = 0.37;
    // affine_matrix[0][2] Translate to the left
    *(((float*)(affine_matrix.data)) + 2) = -30.0;
    // Apply transformation
    wrapAffine(image, result, affine_matrix, image.size());
}

// 5.2.2 Unknown Affine Transformations
void unknownAffineTransformations() {
    Point2f source[3], destination[3];
    // Assign values to source and destination points
    affine_matrix = getAffineTransform(source, destination);
}

// 5.3 Perspective Transformations
void perspectiveTransformations() {
    Point2f source[4], destination[4];
    // Assign values to source and destination points
    perspective_matrix = getPerspectiveTransform(source, destination);
    wrapPerspective(image, result, perspective_matrix, result.size());
}

// 5.5.1 Nearest Neighbor Interpolation
void nearestNeighborInterpolation() {
    int interpolation_scheme = INTER_NEAREST;
    wrapAffine(image, result, affine_matrix, result_size, interpolation_scheme);
    wrapPerspective(image, result, perspective_matrix, result_size, interpolation_scheme);
}

// 5.6.1 Camera Distortions
void cameraDistortions() {
    calibrateCamera(object_points, image_points, image_size, camera_matrix, distortion_coefficients, rotation_vectors, translation_vectors);
}

// 5.6.2 Camera Calibration and Removing Distortion
void cameraCalibrationAndRemovingDistortion() {
    undistort(camera_image, corrected_image, camera_matrix, distortion_coefficients);
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
