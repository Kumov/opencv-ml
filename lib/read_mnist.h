#ifndef READMNIST_H
#define READMNIST_H

// Functions for read in Mnist dataset

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;


int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}


void read_mnist(string filename, vector<cv::Mat> &vec){
    ifstream file (filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
        for(int i = 0; i < number_of_images; ++i)
        {
            cv::Mat tp = Mat::zeros(n_rows, n_cols, CV_32FC1);
            for(int r = 0; r < n_rows; ++r)
            {
                for(int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    tp.at<uchar>(r, c) = (int) temp;
                }
            }
            vec.push_back(tp);
        }
    }
}


void read_mnist_label(string filename, vector<double> &vec)
{
    ifstream file (filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        for(int i = 0; i < number_of_images; ++i)
        {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vec[i]= (double)temp;
        }
    }
}


cv::Mat concatenateMat(vector<Mat> &vec)
{

    int height = vec[0].rows;
    int width = vec[0].cols;
    Mat res = Mat::zeros(height * width, vec.size(), CV_32FC1);
    for(int i=0; i<vec.size(); i++){
        Mat img(height, width, CV_32FC1);

        vec[i].convertTo(img, CV_32FC1);
        // reshape(int cn, int rows=0), cn is num of channels.
        Mat ptmat = img.reshape(0, height * width);
        Rect roi = cv::Rect(i, 0, ptmat.cols, ptmat.rows);
        Mat subView = res(roi);
        ptmat.copyTo(subView);
    }
    divide(res, 255.0, res);
    return res;
}


void readData(Mat &x, Mat &y, string xpath, string ypath, int number_of_images)
{

    //read mnist images into OpenCV Mat vector
    int image_size = 28 * 28;
    vector<Mat> vec;
    //vec.resize(number_of_images, cv::Mat(28, 28, CV_8UC1));
    read_mnist(xpath, vec);
    x = concatenateMat(vec);

    //read MNIST label into double vector
    vector<double> y_tmp(number_of_images);
    read_mnist_label(ypath, y_tmp);
    y = Mat::zeros(1, number_of_images, CV_32FC1);
    for (int i=0; i < number_of_images; i++)
        y.at<float>(1, i) = y_tmp.at(i);
}


#endif
