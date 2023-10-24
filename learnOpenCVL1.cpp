//L1：在指定图像上，把图像转化为灰度图，二值图，在灰度图的基础上，把图像转化为矩阵显示并输出，计算这个矩阵前两行数的平均值，中位
//数，分别把平均值，中位数设为阈值 T，把这两行数据中小于 T 的数改为0，大于等于 T 的改为255

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);//标志参数IMREAD_GRAYSCALE将图像转成单通道灰度图像后读取
    ////转换为灰度图还可以使用convertTo()函数
    //Mat gray;
    //cvtColor(img, gray, COLOR_BGR2GRAY);
    if (img.empty())
    {
        cout << "请确认图像文件名称是否正确" << endl;
        return -1;
    }

    //显示原始图像和灰度图像
    namedWindow("Gray Image", WINDOW_AUTOSIZE);
    imshow("Gray Image", img);

    // 获取矩阵尺寸
    int rows = img.rows;
    int cols = img.cols;
    cout << "Image dimensions: " << rows << "x" << cols << endl;

    // 将图像转化为矩阵并输出
    cout << "Mat: " << endl << img << endl;

    //从img中截取第一二行数据构造newMatrix
    Mat newMatrix(img, Range(0, 2)); //Range数据结构包含左括号数据，不包含右括号数据

    //计算这个矩阵前两行数的平均数，把平均数设为阈值 T，把这两行数据中小于 T 的数改为0，大于等于 T 的改为255
    //用mean()函数计算平均数
    Mat newMatrix_B;
    Scalar myMean2;
    myMean2 = mean(newMatrix);
    cout << "newMatrix均值=" << myMean2 << endl;
    threshold(newMatrix, newMatrix_B, myMean2[0], 255, THRESH_BINARY); // 设置阈值为平均值，大于平均值的像素点设置为255，小于平均值的像素点设置为0
    imshow("newMatrix_B", newMatrix_B);

    //计算这个矩阵前两行数的中位数，把中位数设为阈值 T，把这两行数据中小于 T 的数改为0，大于等于 T 的改为255
    //将newMatrix转换为一行，再使用cv::sort函数排序
    Mat rnewMatrix = newMatrix.reshape(1, 1);
    Mat s;
    Mat newMatrix_B2;
    cv::sort(rnewMatrix, s, SORT_EVERY_ROW);
    //int cols1 = s.cols;
    float median;
    //如果列数为奇数，则中位数为中间的数，若列数为偶数，中位数为中间两个数的平均数
    if (s.cols % 2 != 0) {
        median = s.at<uchar>(0, (s.cols - 1) / 2);
    }
    else  median = (s.at<uchar>(0, (s.cols) / 2) + s.at<uchar>(0, ((s.cols) / 2) - 1)) / 2;
    cout << "中位数为"<<median << endl;
    // 设置阈值为平均值，大于平均值的像素点设置为255，小于平均值的像素点设置为0
    threshold(newMatrix, newMatrix_B2, median, 255, THRESH_BINARY); 
    imshow("newMatrix_B2", newMatrix_B2);
    
    //截图：将img（已经为灰度图）截图，截取去除第一二行数据的图像
    Mat img1;
    img1 = img(Range(2, rows), Range(0, cols));
    imshow("img1", img1);
    //拼接：使用vconcat()函数将截取后的图像img1分别与newMatrix_B，newMatrix_B2竖向连接
    Mat vc, vc1;
    vconcat(newMatrix_B, img1, vc);
    imshow("vc", vc);
    vconcat(newMatrix_B2, img1, vc1);
    imshow("vc1", vc1);

    waitKey(0);
    return 0;
}