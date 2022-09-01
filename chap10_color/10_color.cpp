#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void color_inverse(){
    Mat src = imread("lena.bmp", IMREAD_COLOR);

    Mat dst(src.rows, src.cols, src.type());

    for(int i=0; i<src.rows; i++){
        for(int j=0; j<src.cols; j++){
            Vec3b& p1 = src.at<Vec3b>(j,i);
            Vec3b& p2 = dst.at<Vec3b>(j,i);

            p2[0] = 255-p1[0];
            p2[1] = 255-p1[1];
            p2[2] = 255-p1[2];
        }
    }

    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}
void color_split(){
    Mat src = imread("lena.bmp");

    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    imshow("src", src);
    imshow("B", bgr_planes[0]);
    imshow("G", bgr_planes[1]);
    imshow("R", bgr_planes[2]);

    waitKey();
    destroyAllWindows();
}
void coloreq(){
    Mat src = imread("lena.bmp");

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    vector<Mat> ycrcb_planes;
    split(src_ycrcb, ycrcb_planes);

    equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);

    Mat dst_ycrcb;
    merge(ycrcb_planes, dst_ycrcb);
    
    Mat dst;
    cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
    

}
void hue_inrange(){
    Mat src = imread("lena.bmp");
    Mat src_hsv, mask;
    cvtColor(src, src_hsv, COLOR_BGR2HSV);

    Scalar lowerb(40, 100, 0);
    Scalar upperb(80, 255, 255);

    inRange(src_hsv, lowerb, upperb, mask);
    imshow("mask", mask);

    waitKey();
    destroyAllWindows();
}
void backhist(){
    Mat ref, ref_ycrcb, mask;
    ref = imread("ref.png", IMREAD_COLOR);
    mask = imread("mask.bmp", IMREAD_GRAYSCALE);
    cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

    Mat hist;
    int channels[] ={1,2};
    int cr_bins = 128; int cb_bins = 128;
    int histsize[] = {cr_bins, cb_bins};
    float cr_range[] = {0,256};
    float cb_range[] = {0,256};
    const float* ranges[] = {cr_range, cb_range};

    calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histsize, ranges);

    Mat src, src_ycrcb;
    src = imread("ref.png", IMREAD_COLOR);
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    Mat backproj;
    calcBackProject(&src_ycrcb, 1,channels, hist, backproj, ranges, 1, true);

    imshow("src", src);
    imshow("baackproj", backproj);
    waitKey();
    destroyAllWindows();

}
int main(){
    backhist();
}