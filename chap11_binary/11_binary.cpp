#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void thresholdtest(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    Mat dst;

    threshold(src, dst, 122, 255, THRESH_BINARY);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}
void adaptivethresh(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);

    int bsize = 11;
    Mat dst;
    adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();


}
void erode_dilate(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat dst1,dst2;
    erode(bin, dst1, Mat());
    dilate(bin, dst2, Mat());
    
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    waitKey();
    destroyAllWindows();
}
void open_close(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);

    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY|THRESH_OTSU);

    Mat dst1, dst2;
    morphologyEx(src, dst1, MORPH_OPEN, Mat());
    morphologyEx(src, dst2, MORPH_OPEN, Mat());

    imshow("bin", bin);
    imshow("dst1", dst1);
    imshow("dst2", dst2);
    waitKey();
    destroyAllWindows();

}
int main(){
    open_close();
}