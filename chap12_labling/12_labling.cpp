#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void labeling_basic(){
    uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
    
    Mat src = Mat(8,8,CV_8UC1, data) * 255;
    Mat labels;

    cout << connectedComponents(src, labels);
}
void labling_stats(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat labels, stats, centorids;
    int cnt = connectedComponentsWithStats(bin, labels, stats, centorids);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for(int i=1; i<cnt; i++){
        int *p = stats.ptr<int>(i);

        if(p[4]<20) continue;
        rectangle(dst, Rect(p[0], p[1],p[2],p[3]), Scalar(0,255,255), 2);
    }
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}
void contours_basic(){
    Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);
    if(src.empty()) return;
    vector<vector<Point>> contours;
    findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for(int i=0; i<contours.size(); i++){
        Scalar c(rand()%255, rand()%255, rand()%255);
        drawContours(dst, contours, i, c, 2);
    }
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();

}
void contours_hier(){
    Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    findContours(src, contours, hierachy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for(int i=0; i>=0; i=hierachy[i][0]){
        Scalar c(rand()&255, rand()&255, rand()&255);
        drawContours(dst, contours, i, c, -1, LINE_8, hierachy);
    }

    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void setlabel(Mat& img, const vector<Point>& pts, const String& label){
    Rect rc = boundingRect(pts);
    rectangle(img, rc, Scalar(0,0,255), 1);
    putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0,0,255));
}
void polygons(){
    Mat img = imread("polygon.bmp", IMREAD_COLOR);

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for(vector<Point>& pts: contours){
        if(contourArea(pts) < 400)
            continue;
        vector<Point> approx;
        approxPolyDP(pts, approx, arcLength(pts, true)*0.02, true);
        int vtc = (int) approx.size();

        if(vtc == 3)
            setlabel(img, pts, "TRI");
        else if(vtc==4)
            setlabel(img, pts, "RECT");
        else if(vtc>4){
            double len = arcLength(pts, true);
            double area = contourArea(pts);
            double ratio =4. * CV_PI * area / (len*len);
            if(ratio > 0.8) setlabel(img, pts, "CIR");
        }
    }
    imshow("img", img);
    waitKey();
    destroyAllWindows();
}
int main(){
    polygons();
}
