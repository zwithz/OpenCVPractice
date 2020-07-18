//
//  main.cpp
//  Ch2
//
//  Created by zz on 7/18/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 2.2 Images
void changeQuantisationGrey(Mat &image, int num_bits) {
    CV_Assert((image.type() == CV_8UC1) && (num_bits >= 1) && (num_bits <= 8));
    uchar mask = 0xFF << (8 - num_bits);
    for (int row = 0; row < image.rows; row++) {
         for (int col = 0; col < image.cols; col++) {
            image.at<uchar>(row, col) = image.at<uchar>(row, col) & mask;
        }
    }
}

// 2.2.1 Sampling
void resizeImage() {
    resize(image, smaller_image, Size(image1.cols / 2, image.rows / 2));
}

// 2.3.1 RGB Images
void invertColor(Mat &input_image, Mat &output_image) {
    CV_Assert(input_image.type() == CV_8UC3);
    output_image = input_image.clone();
    for (int row = 0; row < input_image.rows; row++) {
        for (int col = 0; col < input_image.cols; col++) {
            for (int channel = 0; channel < input_image.channels(); channel++) {
                output_image.at<Vec3b>(row, col)[channel] =
                    255 - input_image.at<Vec3b>(row, col)[channel];
            }
        }
    }
}

void splitColorImageIntoChannels(Mat &bgr_image, Mat &grey_image) {
    cvtColor(bgr_image, grey_image, CV_BGR2GRAY);
    vector<Mat> bgr_images(3);
    split(bgr_image, bgr_images);
    Mat &blue_image = bgr_images[0];
}

void usePointer(Mat &image, Mat &result_image) {
    int image_rows = image.rows;
    int image_columns = image.cols;
    for (int row = 0; row < image_rows; row++) {
        uchar *value = image.ptr<uchar>(row);
        uchar *result_value = result_image.ptr<uchar>(row);
        for (int column = 0; column < image_columns; column++) {
            *result_value++ = *value++ ^ 0xFF;
            *result_value++ = *value++ ^ 0xFF;
            *result_value++ = *value++ ^ 0xFF;
        }
    }
}

// 2.3.3 YUV Images
void converRGB2YUV(Mat &image, Mat &yuv_image) {
    cvtColor(image, yuv_image, CV_BGR2YUV);
}

// 2.3.4 HLS Images
void converRGB3HLS(Mat &image, Mat *hls_image) {
    cvtColor(image, hls_image, CV_BGR2HLS);
}

// 2.3.6.1 Skin Detection
void sKinDetection(Mat &hls_image) {
    uchar H = hls_image.at<Vec3b>(row, col)[0];
    uchar L = hls_image.at<Vec3b>(row, col)[1];
    uchar S = hls_image.at<Vec3b>(row, col)[2];
    double LS_ratio = ((double)L) / ((double)S);
    bool skin_pixel = (S >= 50) && (LS_ratio > 0.5) && (LS_ratio < 3.0) && ((H <= 14) || (H >= 165));
}

// 2.3.6.2 Red Eye Detection
void redEyeDetection(Mat &hls_image) {
    uchar H = hls_image.at<Vec3b>(row, col)[0];
    uchar L = hls_image.at<Vec3b>(row, col)[1];
    uchar S = hls_image.at<Vec3b>(row, col)[2];
    double LS_ratio = ((double)L) / ((double)S);
    bool red_eye_pixel = (L >= 64) && (S >= 100) &&
                         (LS_ratio > 0.5) && (LS_ratio < 1.5) &&
                         ((H <= 7) || (H >= 162));
}

// 2.4.1.1 Gaussian Noise
void addGaussianNoise (Mat& image, double average=0.0,double standard_deviation=10.0) {
    // We need to work with signed images (as noise can be
    // negative as well as positive). We use 16 bit signed
    // images as otherwise we would lose precision.
    Mat noise_image(image.size(), CV_16SC3);
    randn(noise_image, Scalar::all(average), Scalar::all(standard_deviation));
    Mat temp_image;
    image.convertTo(temp_image, CV_16SC3);
    addWeighted(temp_image, 1.0, noise_image, 1.0, 0.0, temp_image);
    temp_image.convertTo(image, image.type());
}

// 2.4.1.2 Salt and Pepper Noise
void addSaltAndPepperNoise(Mat& image, double noise_percentage) {
    int image_rows = image.rows;
    int image_columns = image.cols;
    int image_channels = image.channels();
    int noise_points = (int) (((double) image_rows * image_columns * image_channels) * noise_percentage / 100.0);
    for (int count = 0; count < noise_points; count++) {
        int row = rand() % image_rows;
        int column = rand() % image_columns;
        int channel = rand() % image_channels;
        uchar* pixel = image.ptr<uchar>(row) + (column * image_channels) + channel;
        *pixel = (rand() % 2 == 1) ? 255 : 0;
    }
}

// 2.5.1 Image Averaging
void imageAverage(Mat& image1, Mat& image2, Mat& average_image) {
    addWeighted(image1, 0.5, image2, 0.5, 0.0, average_image);
}

// 2.5.2 Local Averaging and Gaussian Smoothing
void localAverage(Mat& image, Mat& smoothed_image) {
    blur(image, smoothed_image, Size(3,3));
}

void gaussianSmoothing (Mat& image, Mat& smoothed_image) {
    GaussianBlur(image, smoothed_image, Size(5,5), 1.5);
}

// 2.5.4 Median Filter
void medianFilter(Mat& image, Mat& smoothed_image) {
    medianBlur(image, smoothed_image, 5);
}

int main(int argc, const char *argv[]) {
    return 0;
}
