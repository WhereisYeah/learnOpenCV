//L2:在指定图像上，把图像转化为灰度图，二值图，在灰度图的基础上，把图像转化为矩阵显示并输出，计算整个矩阵的平均值，中位数，分别把
//平均值，中位数设为阈值 T，把整个矩阵中小于 T 的数改为0，大于等于 T 的改为255
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    // 读取图像
    Mat img = imread("lena.jpg");
    if (img.empty())
    {
        cout << "请确认图像文件名称是否正确" << endl;
        return -1;
    }
    // 转换为灰度图
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // 显示原始图像和灰度图像
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Gray Image", WINDOW_AUTOSIZE);
    imshow("Original Image", img);
    imshow("Gray Image", gray);
    // 获取矩阵尺寸
    int rows = gray.rows;
    int cols = gray.cols;
    cout << "Image dimensions: " << rows << "x" << cols << endl;

    //  将图像转化为矩阵并输出
    cout << "Mat: " <<endl << gray << endl;
    //计算整个矩阵的平均值
    Scalar myMean;
    myMean = mean(gray);
    cout << "gray均值=" << myMean << endl;
    cout << "gray第一个通道的均值=" << myMean[0] << "    "
        << "gray第二个通道的均值=" << myMean[1] << endl << endl;
    Mat gray_B;
    // 设置阈值为平均值，大于平均值的像素点设置为255，小于平均值的像素点设置为0
    cv::threshold(gray, gray_B, myMean[0], 255, THRESH_BINARY);
    imshow("gray_B", gray_B);

    //计算这个矩阵的中位数，把中位数设为阈值 T，把数据中小于 T 的数改为0，大于等于 T 的改为255
    //将gray转换为一行，再使用cv::sort函数排序
    Mat rgray = gray.reshape(1, 1);
    Mat s;
    Mat rgray_B2;
    cv::sort(rgray, s, SORT_EVERY_ROW);

    //计算中位数，如果列数为奇数，则中位数为中间的数，若列数为偶数，中位数为中间两个数的平均数
    float median;
    if (s.cols % 2 != 0) {
        median = s.at<uchar>(0, (s.cols - 1) / 2);
    }
    else  median = (s.at<uchar>(0, (s.cols) / 2) + s.at<uchar>(0, ((s.cols) / 2) - 1)) / 2;
    cout << "中位数为" << median << endl;
    // 设置阈值为平均值，大于平均值的像素点设置为255，小于平均值的像素点设置为0
   threshold(gray, rgray_B2, median, 255, THRESH_BINARY); 
    imshow("rgray_B2", rgray_B2);

    waitKey(0);
    return 0;
}