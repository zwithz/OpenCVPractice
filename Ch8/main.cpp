//
//  main.cpp
//  Ch8
//
//  Created by zz on 8/7/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 8.1.3 Matching Metrics
void matchingMetrics() {
    Mat matching_space;
    matching_space.create(search_image.rows - template_image.rows + 1, search_image.cols - template_image.cols + 1, CV_32FC1);
    matchingTemplate(search_image, template_image, matching_space, CV_TM_CCORR_NORMED);
}

// 8.1.4 Finding Local Maxima or Minima
void findLocalMaximaOrMinima() {
    Mat dilated, thresholded_matching_space, local_maxima, thresholded_8bit;
    dilate(matching_space, dilated, Mat());
    compare(matching_space, dilated, local_maxima, CMP_EQ);
    threshold(matching_space, thresholded_matching_space, 5, 255, THRESH_BINARY);
    thresholded_matching_space.convertTo(thresholded_8bit, CV_8U);
    bitwise_and(local_maxima, thresholded_8bit, local_maxima);
}

// 8.2.1 Chamfering Algorithm
void chamferingAlgorithm() {
    Canny(gray_image, edge_image, 100, 200, 3);
    threshold(edge_image, edge_image, 127, 255, THRESH_BINARY);
    distanceTransform(edge_image, chamfer_image, CV_DIST_L2, 3);
}

// 8.2.2 Chamfer Matching Algorithm
void chamferMatchingAlgorithm(Mat& chamfer_image, Mat& model, Mat& matching_image) {
    // Extract the model points (as they are sparse)
    vector<Point> model_points;
    int image_channels = model.channels();
    for (int model_row = 0; model_row < model.rows; model_row++) {
        uchar* curr_point = model.ptr<uchar>(model_row);
        for (int model_column = 0; model_column < model.cols; model_column++) {
            if (*curr_point > 0) {
                Point& new_point = Point(model_column, model_row);
                model_points.push_back(new_point);
            }
            curr_point += image_channels;
        }
    }
    int num_model_points = model_points.size();
    image_channels = chamfer_image.channels();
    // Try the model in every possible position
    matching_image = Mat(chamfer_image.rows - model.rows + 1, chamfer_image.cols - model.cols + 1, CV_32FC1);
    for (int search_row = 0; search_row <= chamfer_image.rows - model.rows; search_row++) {
        float* output_point = matching_image.ptr<float>(search_row);
        for (int search_col = 0; search_col <= chamfer_image.cols - model.cols; search_col++) {
            float matching_score = 0.0;
            for (int point_count = 0; point_count < num_model_points; point_count++) {
                matching_score += (float)*(chamfer_image.ptr<float>(model_points[point_count].y + search_row) + search_col + model_points[point_count].x * image_channels);
            }
            *output_point = matching_score;
            output_point++;
        }
    }
}

// 8.3.2.1 Area
void area() {
    vector < vector<Point> contours;
    vector<Vec4i> hierarchy;
    findContours(binary_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
    for (int contour_number = 0; contour_number >= 0; contour_number = hierarchy[contour_number][0]) {
        double area = contourArea(contours[contour_number]) + contours[contour_number].size() / 2 + 1;
        for (int hole_number = hierarchy[contour_number][2]; hole_number >= 0; hole_number = hierarchy[hole_number][0]) {
            area -= (contourArea(contours[hole_number]) - contours[hole_number].size() / 2 + 1);
        }
    }
}

// 8.3.2.3 Length to Width Ratio for the Minimum Bounding Rectangle
void minimumBoundingRectangle() {
    RotatedRect min_bounding_rectangle = minAreaRect(contours[coutour_number]);
}

// 8.3.2.4 Convex Hull Area/Minimum Bounding Rectangle Area Ratio
void convexHullArea() {
    vector<vector<Point>> hulls(contours.size());
    for (int contour_number = 0; contour_number < contours.size(); contour_number++) {
        convexHull(contours[contour_number], hulls[contour_number]);
    }
}

// 8.3.2.5 Concavities and Holes
void concavitiesAndHoles() {
    vector<vector<int>> hull_indices(contours.size());
    vector<vector<Vec4i>> convexity_defects(contours.size());
    for (int contour_number = 0; contour_number < contours.size(); contour_number++) {
        convexHull(contours[contour_number], hull_indices[contour_number]);
        convexityDefects(contours[contour_number], hull_indices[contour_number], convexity_defects[contour_number]);
    }
}

// 8.3.2.8 Moments and Moment Invariants
void momentsAndMomentInvariants() {
    Moments contour_moments;
    double hu_moments[7];
    contour_moments = moments(contours[contour_number]);
    HuMoments(contour_moments, hu_moments);
}

// 8.4 Cascade of Haar Classifiers
void cascadeOfHaarClassifiers() {
    CascadeClassifier cascade;
    if (cascade.load("haarcascades/haarcascade_frontalface_alt.xml")) {
        vector<Rect> faces;
        equalizeHist(gray_image, gray_image);
        cascade.detectMultiScale(gray_image, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));
    }
}

// 8.5.2 Histogram of Oriented Gradients (HoG)
void HoG() {
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> people;
    hog.detectMultiScale(search_image, people);
}

// 8.6 Performance
void performance() {
    double before_tick_count = static_cast<double>(getTickCount());
    // Put methods to be timed here...
    double after_tick_count = static_cast<double>(getTickCount());
    double duration_in_ms = 1000.0 * (after_tick_count - before_tick_count) / getTickFrequency();
}

// 8.6.3 Metrics for Assessing Classification Performance
void metricsForAssessingClassificationPerformance() {
    CV_Assert(results.type() == CV_8UC1);
    CV_Assert(ground_truth.type() == CV_8UC1);
    int FP = 0;
    int FN = 0;
    int TP = 0;
    int TN = 0;
    for (int row = 0; row < ground_truth.rows; row++) {
        for (int col = 0; col < ground_truth.cols; col++) {
            uchar result = results.at<uchar>(row, col);
            uchar gt = ground_truth.at<uchar>(row, col);
            if (gt > 0) {
                if (result > 0)
                    TP++;
                else
                    FN++;
            } else if (result > 0)
                FP++;
            else
                TN++;
        }
    }
    double precision = ((double)TP) / ((double)(TP + FP));
    double recall = ((double)TP) / ((double)(TP + FN));
    double accuracy = ((double)(TP + TN)) / ((double)(TP + FP + TN + FN));
    double specificity = ((double)TN) / ((double)(FP + TN));
    double f1 = 2.0 * precision * recall / (precision + recall);
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
