
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat img = imread(argv[1], 0);

	if(img.empty()){
		cout << "Error : Image cannot be loaded..!!" << endl;
      system("pause"); //wait for a key press
      return -1;
	}

	namedWindow("MyWindow", WINDOW_AUTOSIZE);
	imshow("MyWindow", img);
	waitKey(0);
	destroyWindow("MyWindow");

	return 0;
}