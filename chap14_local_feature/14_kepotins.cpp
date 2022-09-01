#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void detect_keypoints();

void keypoint_matching(){
    Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
    Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);
    if(src1.empty() || src2.empty()) return;
    Ptr<Feature2D> feature = ORB::create();

    vector<KeyPoint> kp1, kp2;
    Mat desc1, desc2 ;
    feature->detectAndCompute(src1, Mat(), kp1, desc1);
    feature->detectAndCompute(src2, Mat(), kp2, desc2);

    Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

    vector<DMatch> matches;
    matcher->match(desc1, desc2, matches);

    sort(matches.begin(), matches.end());
    vector<DMatch> good_matches(matches.begin(), matches.begin() +50);

    Mat dst;
    drawMatches(src1, kp1, src2, kp2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(),
    DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("ds", dst);

	waitKey();
	destroyAllWindows();

}
void find_homography(){
    Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
    Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);
    if(src1.empty() || src2.empty()) return;
    Ptr<Feature2D> feature = ORB::create();

    vector<KeyPoint> kp1, kp2;
    Mat desc1, desc2 ;
    feature->detectAndCompute(src1, Mat(), kp1, desc1);
    feature->detectAndCompute(src2, Mat(), kp2, desc2);

    Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

    vector<DMatch> matches;
    matcher->match(desc1, desc2, matches);

    sort(matches.begin(), matches.end());
    vector<DMatch> good_matches(matches.begin(), matches.begin() +50);

    Mat dst;
    drawMatches(src1, kp1, src2, kp2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(),
    DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


    vector<Point2f> pts1, pts2;
    for(size_t i=0; i<good_matches.size(); i++){
        pts1.push_back(kp1[good_matches[i].queryIdx].pt);
        pts2.push_back(kp2[good_matches[i].trainIdx].pt);
    }
    Mat H = findHomography(pts1, pts2, RANSAC);
    vector<Point2f> cn1, cn2;
    cn1.push_back(Point2f(0,0));
    cn1.push_back(Point2f(src1.cols-1.f, 0));
    cn1.push_back(Point2f(src1.cols-1.f, src1.rows-1.f));
    cn1.push_back(Point2f(0, src1.rows-1.f));
    perspectiveTransform(cn1, cn2, H);


    vector<Point> cndst;
    for(Point2f pt: cn2){
        cndst.push_back(Point(cvRound(pt.x+src1.cols),cvRound(pt.y)));
    }
    polylines(dst, cndst, true, Scalar(0,255,0),2, LINE_AA);
    imshow("ds", dst);

	waitKey();
	destroyAllWindows();

}
int main(void)
{
	find_homography();

	return 0;
}
void detect_keypoints()
{
	Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();

	vector<KeyPoint> keypoints;
	feature->detect(src, keypoints);

	Mat desc;
	feature->compute(src, keypoints, desc);

	cout << "keypoints.size(): " << keypoints.size() << endl;
	cout << "desc.size(): " << desc.size() << endl;

	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}