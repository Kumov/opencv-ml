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
#include "../lib/iofunction.h"
#include "../lib/operation.h"


using namespace cv;
using namespace std;


int main(int argc, char** argv){
  // Print help info
  if(argc != 6){
    cout << "Test CvML functionality using mnist dataset" << endl;
    cout << "usage: ./mnist_svm [train dir] [train label] [test dir] [test label] [output model]" << endl;
    cout << "\n# * dir: directory path for training data" << endl;
    cout << "# * label: training data label file" << endl;
    cout << "# output model: the output model file name" << endl;
    exit(1);
  }

  // Load in training and testing data
  cout << "Loading training data and testing data ..." << endl;
  vector<Mat> train, test;
  vector<int> train_label, test_label;
  load_images_and_labels(argv[1], argv[2], train, train_label);
  load_images_and_labels(argv[3], argv[4], test, test_label);

  // Reshape training and testing data
  Mat train_X, test_X;
  train_X = concatenateMat(train);
  test_X = concatenateMat(test);
  Mat train_y(train_label, false);
  Mat test_y(test_label, false);

  // Set up SVM parameters
  CvSVMParams params;
  params.svm_type = CvSVM::C_SVC;
  params.kernel_type = CvSVM::LINEAR;
  params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

  // Train a SVM classifier and dump it
  cout << "Train and Save SVM model ..." << endl;
  CvSVM svm;
  svm.train(train_X, train_y, Mat(), Mat(), params);
  svm.save(argv[5]);
  
  // Test the trained SVM
  cout << "Test the SVM on testing data ..." << endl;
  cv::Mat results;
  svm.predict(test_X, results);

  // Evaluate the accuracy
  cout << "Evaluating Accuray ..." << endl;
  float acc;
  acc = evaluate(results, test_y);
}
