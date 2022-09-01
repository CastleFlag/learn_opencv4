#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void cont(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);

    Mat dst = 2.f * src;
    imshow("src", src);
    imshow("dst", dst);

    //효과적인 명암비(약간 normalize?)
    Mat dst2 = 1.f * (src-128) + src;

    imshow("dst2", dst2);


    waitKey();
    destroyAllWindows();
}

int main(){
    cont();
}