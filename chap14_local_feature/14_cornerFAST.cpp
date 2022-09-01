#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void corner_fast(){
    Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

    vector<KeyPoint> keypoints;
    FAST(src, keypoints, 60, true);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for(KeyPoint kp: keypoints){
        Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
        circle(dst, pt, 5, Scalar(0,0,255),2);
    }
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}
int main(){
    corner_fast();
}