#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main(){
    //file save
    String name = "Jane";
    int age = 10;
    Point pt1(100,200);
    vector<int> scores = {1,2,3,4,5};
    Mat mat1 = (Mat_<float>(2,2) << 1.0f, 1.5f, 2.0f, 3.2f);

    FileStorage fs("fileiotest.json", FileStorage::WRITE);

    fs << "name" << name;
    fs << "age" << age;
    fs << "point"<< pt1;
    fs << "scores" << scores;
    fs << "data" << mat1;

    fs.release();

    //file read
    FileStorage rfs("fileiotest.json", FileStorage::READ);
    int year;
    rfs["age"] >> year;
    rfs.release();

    cout << year << endl;

}