#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void maskset(){
    Mat src = imread("lena.bmp", IMREAD_COLOR);
    Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);
    Mat src2 = Mat::zeros(Size(800, 800), 0);
    src.copyTo(src2, mask);
    src.setTo(Scalar(255,0,0), mask);

    imshow("src", src);
    imshow("mask", mask);
    imshow("src2", src2);

    waitKey(0);
    destroyAllWindows();
}
void util_func(){
    Mat img = imread("lena.bmp", IMREAD_GRAYSCALE);
    //모든배율의 합과 평균([0]은 채널때문에)
    int sum = (int)cv::sum(img)[0];
    int mean1 = (int)mean(img)[0];
    cout << sum << " " << mean1 << endl;
    //최대최소와 그 좌표(grayscale에서만 됨)
    Point minPos, maxPos;
    double minval, maxval;
    minMaxLoc(img, &minval, &maxval, &minPos, &maxPos);
    cout << minval << " " << minPos;
    //normalize(보통 실수->grayscale)
    Mat normdst;
    normalize(img, normdst, 0, 255, NORM_MINMAX, CV_8UC1);
    // cout << normdst << endl;
    //round(반올림)
    cout << cvRound(2.5) << " " << cvCeil(2.1) << endl;

}
int main(){
//    maskset();
    util_func();
}