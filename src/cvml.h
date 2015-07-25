#ifndef CVML_H
#define CVML_H

// Implement ML functions for Frame classification

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;


// Functions list
void svm_train(cv::Mat& train_data, cv::Mat& train_label, CvSVM &svm, char* svm_filename);
cv::Mat svm_batch_predict(cv::Mat& test_data, CvSVM &svm);
float evaluate(cv::Mat& predicted, cv::Mat& actual);


// Train and dump a SVM model
void svm_train(cv::Mat& train_data, cv::Mat& train_label, CvSVM &svm, char* svm_filename)
{
	//Set up SVM parameters
    CvSVMParams param = CvSVMParams();

	param.svm_type = CvSVM::C_SVC;
	param.kernel_type = CvSVM::RBF; //CvSVM::RBF, CvSVM::LINEAR ...
	param.degree = 0; // for poly
	param.gamma = 20; // for poly/rbf/sigmoid
	param.coef0 = 0; //for poly/sigmoid

	param.C = 7;
	param.nu = 0.0;
	param.p = 0.0;

	param.class_weights = NULL;
	param.term_crit.type = CV_TERMCRIT_ITER + CV_TERMCRIT_EPS;
	param.term_crit.max_iter = 1000;
	param.term_crit.epsilon = 1e-6;

	//Train SVM
	svm.train(train_data, train_label, cv::Mat(), cv::Mat(), param);

	//Store the SVM model
	svm.save(svm_filename);
}


// Predict by svm and return the results
cv::Mat svm_batch_predict(cv::Mat& test_data, CvSVM &svm)
{
	//Test the data by SVM
    cv::Mat results(test_data.rows, 1, CV_32FC1);
    for(int i=0; i < test_data.rows; i++){
        cv::Mat sample = test_data.row(i);
	    float result = svm.predict(sample);
        results.at<float>(i,0) = result;
    }
    return results;
}


// Calculate accuracy
float evaluate(cv::Mat& predicted, cv::Mat& actual) {
	assert(predicted.rows == actual.rows);
	int t = 0;
	int f = 0;
	for(int i = 0; i < actual.rows; i++) {
		float p = predicted.at<float>(i,0);
		float a = actual.at<float>(i,0);
		if((p >= 0.0 && a >= 0.0) || (p <= 0.0 &&  a <= 0.0))
	        t++;
		else
		    f++;
	}
	return (t * 1.0) / (t + f);
}


#endif
