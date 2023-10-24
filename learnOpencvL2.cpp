//L2:��ָ��ͼ���ϣ���ͼ��ת��Ϊ�Ҷ�ͼ����ֵͼ���ڻҶ�ͼ�Ļ����ϣ���ͼ��ת��Ϊ������ʾ��������������������ƽ��ֵ����λ�����ֱ��
//ƽ��ֵ����λ����Ϊ��ֵ T��������������С�� T ������Ϊ0�����ڵ��� T �ĸ�Ϊ255
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    // ��ȡͼ��
    Mat img = imread("lena.jpg");
    if (img.empty())
    {
        cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
        return -1;
    }
    // ת��Ϊ�Ҷ�ͼ
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // ��ʾԭʼͼ��ͻҶ�ͼ��
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Gray Image", WINDOW_AUTOSIZE);
    imshow("Original Image", img);
    imshow("Gray Image", gray);
    // ��ȡ����ߴ�
    int rows = gray.rows;
    int cols = gray.cols;
    cout << "Image dimensions: " << rows << "x" << cols << endl;

    //  ��ͼ��ת��Ϊ�������
    cout << "Mat: " <<endl << gray << endl;
    //�������������ƽ��ֵ
    Scalar myMean;
    myMean = mean(gray);
    cout << "gray��ֵ=" << myMean << endl;
    cout << "gray��һ��ͨ���ľ�ֵ=" << myMean[0] << "    "
        << "gray�ڶ���ͨ���ľ�ֵ=" << myMean[1] << endl << endl;
    Mat gray_B;
    // ������ֵΪƽ��ֵ������ƽ��ֵ�����ص�����Ϊ255��С��ƽ��ֵ�����ص�����Ϊ0
    cv::threshold(gray, gray_B, myMean[0], 255, THRESH_BINARY);
    imshow("gray_B", gray_B);

    //��������������λ��������λ����Ϊ��ֵ T����������С�� T ������Ϊ0�����ڵ��� T �ĸ�Ϊ255
    //��grayת��Ϊһ�У���ʹ��cv::sort��������
    Mat rgray = gray.reshape(1, 1);
    Mat s;
    Mat rgray_B2;
    cv::sort(rgray, s, SORT_EVERY_ROW);

    //������λ�����������Ϊ����������λ��Ϊ�м������������Ϊż������λ��Ϊ�м���������ƽ����
    float median;
    if (s.cols % 2 != 0) {
        median = s.at<uchar>(0, (s.cols - 1) / 2);
    }
    else  median = (s.at<uchar>(0, (s.cols) / 2) + s.at<uchar>(0, ((s.cols) / 2) - 1)) / 2;
    cout << "��λ��Ϊ" << median << endl;
    // ������ֵΪƽ��ֵ������ƽ��ֵ�����ص�����Ϊ255��С��ƽ��ֵ�����ص�����Ϊ0
   threshold(gray, rgray_B2, median, 255, THRESH_BINARY); 
    imshow("rgray_B2", rgray_B2);

    waitKey(0);
    return 0;
}