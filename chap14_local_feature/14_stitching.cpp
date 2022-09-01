#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	vector<Mat> imgs;
	for (int i = 1; i <=3; i++) {
		Mat img = imread(format("img%d.jpeg", i));

		if (img.empty()) {
			cerr << "Image load failed!" << endl;
			return -1;
		}

		imgs.push_back(img);
	}

	Ptr<Stitcher> stitcher = Stitcher::create();

	Mat dst;
	Stitcher::Status status = stitcher->stitch(imgs, dst);

	if (status != Stitcher::Status::OK) {
		cerr << "Error on stitching!" << endl;
		return -1;
	}

	imwrite("result.jpg", dst);

	imshow("dst", dst);

	waitKey();
	return 0;
}