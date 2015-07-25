#ifndef IOFUNCTION_H
#define IOFUNCTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

// #define CV_LOAD_IMAGE_GRAYSCALE 0

void load_images_and_labels(string dir_path, string fname, vector<Mat> &images, vector<int> &label);
void tokenize_line(const string s, char delim, vector<string> &token_list);


void load_images_and_labels(string dir_path, string fname, vector<Mat> &images, vector<int> &label)
{
  images.clear();
  label.clear();

  vector<string> fname_list;

  // Read in labels
  ifstream f;
  f.open(fname, ios::in);
  if( f.is_open() ){
    string line;
    int idx = 0;
    while( getline(f, line) ){
      vector<string> name_label_pair;
      tokenize_line(line, ' ', name_label_pair);
      fname_list.push_back( dir_path + name_label_pair[0] );
      label.push_back( stoi(name_label_pair[1]) );
      idx++;
    }
  }
  f.close();

  // Read in images
  for( int i = 0; i < fname_list.size(); i++ ){
    string fname = fname_list[i];
    Mat img = imread(fname, CV_LOAD_IMAGE_GRAYSCALE); // Read in gray scale
    if( img.empty() ){
      cout << "Error: Image cannot be loaded" << endl;
      system("pause"); // wait for a key press
    }
    else
      images.push_back(img);
  }
}


void tokenize_line(const string s, char delim, vector<string> &token_list)
{
  stringstream ss(s);
  string item;
  while( getline(ss, item, delim) ){
    token_list.push_back(item);
  }
}


#endif
