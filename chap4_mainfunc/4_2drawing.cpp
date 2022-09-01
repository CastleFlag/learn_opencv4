#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void draw_line_and_marker(){
    Mat img(800, 800, CV_8UC3, Scalar(255,255,255));
    //line 그리기
    line(img, Point(50, 50), Point(250, 50), Scalar(0, 0, 255));
    //arrow 그리기
    arrowedLine(img, Point(50, 300), Point(250, 300), Scalar(0, 0, 255), 1);
    //maerker 그리기
    drawMarker(img, Point(100, 100), Scalar(0,255,0), MARKER_STAR);
    imshow("img", img);
    waitKey(0);
    destroyAllWindows();
}
void draw_poly(){
    Mat img(800, 800, CV_8UC3, Scalar(255,255,255));
    Scalar red = Scalar(0, 0, 255);

    rectangle(img, Rect(50, 50, 100, 50), red, 2);
    circle(img, Point(200,200), 30, red, 3);
    ellipse(img, Point(100, 100), Size(60, 30), 20, 0, 120, red, -1);

    vector<Point> pts;
    pts.push_back(Point(250, 250));
    pts.push_back(Point(300, 250));
    pts.push_back(Point(350, 300));
    pts.push_back(Point(350, 350));
    pts.push_back(Point(250, 350));
    polylines(img, pts, true, red, 4);

    imshow("img", img);
    waitKey(0);
    destroyAllWindows();
}

void draw_text(){
    Mat img(800, 800, CV_8UC3, Scalar(255,255,255));
    Scalar red = Scalar(0, 0, 255);

    putText(img, "FOMT_HERSHEY_PLAIN", Point(20, 50), FONT_HERSHEY_PLAIN, 1, red);

    //적절한 위치에 그리기
    const String text = "hello opencv";
    int fontface = FONT_HERSHEY_TRIPLEX;
    double fontscale = 2.0;
    int thickness = 1;

    Size sizeText = getTextSize(text, fontface, fontscale, thickness, 0);
    Size sizeImg = img.size();
    Point org((sizeImg.width - sizeText.width)/2, (sizeImg.height+sizeText.height)/2);
    putText(img, text, org, fontface, fontscale, Scalar(255,255,0), thickness);
    rectangle(img, org, org+Point(sizeText.width, -sizeText.height), Scalar(255,0,255), 1);

    imshow("img", img);
    waitKey(0);
    destroyAllWindows();

}
int main(){
    draw_text();
}