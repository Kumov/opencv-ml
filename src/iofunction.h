#ifndef IOFUNCTION_H
#define IOFUNCTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

// #define CV_LOAD_IMAGE_GRAYSCALE 0


void load_images(string dir_path, vector<Mat> &images);
void read_labels(string fname, vector<int> &label);
void tokenize_line(const string s, char delim, vector<string> &token_list);


void load_images(string dir_path, vector<Mat> &images)
{
  images.clear();

  // Set up file name list
  vector<string> fname_list;
  DIR *dp;
  struct dirent *ep;
  dp = opendir( dir_path.c_str() );

  if( dp != NULL ){
    while( (ep = readdir(dp)) ){
      string fname = ep->d_name;
      if( fname == "." || fname == ".." )
        continue;
      fname_list.push_back( dir_path + fname );
    }
  }
  else
    perror("Could not open the directory");

  // Read in images
  for( int i = 0; i < fname_list.size(); i++ ){
    Mat img = imread(fname_list[i], CV_LOAD_IMAGE_GRAYSCALE); // Read in gray scale
    if( img.empty() ){
      cout << "Error: Image cannot be loaded" << endl;
      system("pause"); // wait for a key press
    }
    else
      images.push_back(img);
  }
}


void read_labels(string fname, vector<int> &label)
{
  ifstream f;
  f.open(fname, ios::in);
  if( f.is_open() ){
    string line;
    while( getline(f, line) ){
      vector<string> name_label_pair;
      tokenize_line(line, ' ', name_label_pair);
      label.push_back( stoi(name_label_pair[1]) );
    }
  }
  f.close();
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
