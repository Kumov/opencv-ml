#include <iostream>
#include <string>
#include <vector>
#include "../src/iofunction.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
  vector<Mat> images;
  vector<int> labels;

  // load in images
  string dir_path = argv[1];
  if( dir_path[dir_path.size()-1] != '/' )
    dir_path = dir_path + "/";
  load_images_and_labels(dir_path, argv[2], images, labels);

  // Output images and labels
  for(int i = 0; i < images.size(); i++){
    string name = to_string(labels[i]);
    namedWindow( name );
    imshow(name, images[i]);
    waitKey(500);
    destroyWindow(name);
  }

  return 0;
}
