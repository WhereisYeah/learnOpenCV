//L3:在灰度图的基础上，把灰度图的上半部分用整个矩阵的平均值为阈值转化为二值图，把灰度图的下半部分以灰度图显示（即不做处理），输出
//最后的显示结果

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    // 读取图像
    Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);//标志参数IMREAD_GRAYSCALE将图像转成单通道灰度图像后读取
    if (img.empty())
    {
        cout << "请确认图像文件名称是否正确" << endl;
        return -1;
    }

    //使用mean()函数计算整个矩阵的平均值
    Scalar myMean;
    myMean = mean(img);
    cout << "matrix均值=" << myMean << endl;
    cout << "imgs第一个通道的均值=" << myMean[0] << "    "
        << "imgs第二个通道的均值=" << myMean[1] << endl << endl;
    Mat img_B;
    // 设置阈值为平均值，大于平均值的像素点设置为255，小于平均值的像素点设置为0
    threshold(img, img_B, myMean[0], 255, THRESH_BINARY);
    imshow("img_B", img_B);
    
    //使用深拷贝，浅拷贝实现把灰度图的上半部分用整个矩阵的平均值为阈值转化为二值图，把灰度图的下半部分以灰度图显示
    Mat ROI1, mask, gray_copy;
    img.copyTo(gray_copy);//深拷贝，将img深拷贝给gray_copy
    // 获取图像的高度和宽度
    int height = img.rows;
    int width = img.cols;
    //截图，从img（灰度图）上截取上半部分图像ROI1，从img_B（二值图）上截取上半部分图像mask
    //截图相当浅拷贝
    ROI1 = img(Range(0, height / 2), Range(0, width));
    mask= img_B(Range(0, height / 2), Range(0, width));
    mask.copyTo(ROI1);//将mask复制给ROI1
    imshow("img", img);//img会改变，因为ROI1为浅拷贝，ROI1变为二值图mask,则img上半部分也会改变为二值图
    imshow("gray_copy", gray_copy);//gray_copy不会改变，因为gray_copy为深拷贝
    imshow("ROI1", ROI1);
    imshow("mask", mask);
    imwrite("pray.jpg", img);
    imwrite("gray_copy.jpg", gray_copy);
    waitKey(0);
    return 0;
}
