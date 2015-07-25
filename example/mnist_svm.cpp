// Test CvML functionality using mnist dataset
// usage: ./mnist_svm train_data train_label test_data test_label

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../src/iofunction.h"


using namespace cv;
using namespace std;


int main(int argc, char** argv){
    //Print help info
    if(argc != 5){
      cout << "Test CvML functionality using mnist dataset" << endl;
      cout << "usage: ./mnist_svm [train dir] [train label] [test dir] [test label]" << endl;
      cout << "\n# * dir: directory path for training data" << endl;
      cout << "# * label: training data label file" << endl;
      exit(1);
    }

	//Load in training and testing data
    cout << "Loading training data and testing data ..." << endl;
    string train_data_file = argv[1];
    string train_label_file = argv[2];
    string test_data_file = argv[3];
    string test_label_file = argv[4];
    cv::Mat train_data, train_label;
    cv::Mat test_data, test_label;
    readData(train_data, train_label, train_data_file, train_label_file, 60000);
    readData(test_data, test_label, test_data_file, test_label_file, 10000);

	//Train the SVM classifier and dump it
    cout << "Train and Save SVM model ..." << endl;
    CvSVM svm;
    string model_fname = "mnist_svm_model";
    svm_train(train_data, train_label, svm, model_fname.c_str());

	//Test the trained SVM
    cout << "Test the SVM on testing data ..." << endl;
    cv::Mat results;
    results = svm_predict(test_data, svm);

    //Evaluate the accuracy
    cout << "Evaluating Accuray ...(This function is not finish yet!)" << endl;
    
}
