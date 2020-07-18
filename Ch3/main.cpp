//
//  main.cpp
//  Ch3
//
//  Created by zz on 7/18/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 3.1 1D Histograms
void computeHistogramForGreyScalImage(Mat& gray_image, MatND gray_histogram) {
    Mat display_image;
    MatND historgram;
    const int* channel_numbers = {0};
    float channel_range[] = {0.0, 255.0};
    const float* channel_ranges = channel_range;
    int number_bins = 64;
    calcHist(&gray_image, 1, channel_numbers, Mat(), historgram, 1, &number_bins, &channel_ranges);
    OneDHistogram::Draw1DHistogram(&gray_histogram, 1, display_image);
}

// 3.1.1 Histogram Smoothing
void histogramSmoothing(MatND& histogram, int channel) {
    MatND smoothed_histogram = histogram[channel].clone();
    for (int i = 1; i < histogram[channel].rows; i++) {
        smoothed_histogram[channel].at<float>(i) = (histogram.at<float>(i - 1) + histogram.at<float>(i) + histogram.at<float>(i + 1)) / 3;
    }
}

// 3.1.2 Color Histograms
void colorHistogram(Mat& image, Mat& display_image) {
    MatND* histogram = new MatND[image.channels()];
    vector<Mat> channels(image.channels());
    split(image, channels);
    const int* channel_numbers = {0};
    float channel_range[] = {0.0, 255.0};
    const float* channel_ranges = channel_range;
    int number_bins = 64;
    for (int chan = 0; chan < image.channels(); chan++) {
        calcHist(&(channels[chan]), 1, channel_numbers, Mat(), histogram[chan], 1, &number_bins, &channel_ranges);
    }
    OneDHistogram::Draw1DHistogram(histogram, image.channels(), display_iamge);
}

// 3.2 3D Historgrams
void compute3DHistogram(Mat& image) {
    MatND histogram;
    int channel_numbers[] = {0, 1, 2};
    int* number_bins = new int[image.channels()];
    for (int ch = 0; ch < image.channels(); ch++) {
        number_bins[ch] = 4;
    }
    float ch_range[] = {0.0, 255.0};
    const float* channel_ranges[] = {ch_range, ch_range, ch_range};
    calcHist(&image, 1, channel_numbers, Mat(), histogram, image.channels(), number_bins, channel_ranges);
}

// 3.3 Histogram / Image Equalisation
void histogramEqualisation(Mat& hls_image, int channel) {
    split(hls_image, channel);
    vector<Mat> channels(hls_image.channels());
    equalizeHist(channels[1], channels[1]);
    merge(channels, hls_image);
}

// 3.4 Histogram Comparison
void compareHistograms(MatND &histogram1, MatND& histogram2) {
    normalize(histogram1, histogram1, 1.0);
    normalize(histogram2, histogram2, 1.0);
    double matching_score = compareHist(histogram1, histogram2, CV_COMP_CORREL);
}

// 3.5 Back-projection
void backProjection() {
    calcHist(&hsl_samples_image, 1, channel_numbers, Mat(), histogram, image.channels(), number_bins, channel_ranges);
    normalize(histogram, histogram, 1.0);
    Mat probabilities = histogram.BackProject(hls_image);
}

// 3.6 k-means Clustering
void kMeansClustering(Mat& image, int channel) {
    // code
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
