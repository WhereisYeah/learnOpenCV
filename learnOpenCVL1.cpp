//L1����ָ��ͼ���ϣ���ͼ��ת��Ϊ�Ҷ�ͼ����ֵͼ���ڻҶ�ͼ�Ļ����ϣ���ͼ��ת��Ϊ������ʾ������������������ǰ��������ƽ��ֵ����λ
//�����ֱ��ƽ��ֵ����λ����Ϊ��ֵ T����������������С�� T ������Ϊ0�����ڵ��� T �ĸ�Ϊ255

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);//��־����IMREAD_GRAYSCALE��ͼ��ת�ɵ�ͨ���Ҷ�ͼ����ȡ
    ////ת��Ϊ�Ҷ�ͼ������ʹ��convertTo()����
    //Mat gray;
    //cvtColor(img, gray, COLOR_BGR2GRAY);
    if (img.empty())
    {
        cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
        return -1;
    }

    //��ʾԭʼͼ��ͻҶ�ͼ��
    namedWindow("Gray Image", WINDOW_AUTOSIZE);
    imshow("Gray Image", img);

    // ��ȡ����ߴ�
    int rows = img.rows;
    int cols = img.cols;
    cout << "Image dimensions: " << rows << "x" << cols << endl;

    // ��ͼ��ת��Ϊ�������
    cout << "Mat: " << endl << img << endl;

    //��img�н�ȡ��һ�������ݹ���newMatrix
    Mat newMatrix(img, Range(0, 2)); //Range���ݽṹ�������������ݣ�����������������

    //�����������ǰ��������ƽ��������ƽ������Ϊ��ֵ T����������������С�� T ������Ϊ0�����ڵ��� T �ĸ�Ϊ255
    //��mean()��������ƽ����
    Mat newMatrix_B;
    Scalar myMean2;
    myMean2 = mean(newMatrix);
    cout << "newMatrix��ֵ=" << myMean2 << endl;
    threshold(newMatrix, newMatrix_B, myMean2[0], 255, THRESH_BINARY); // ������ֵΪƽ��ֵ������ƽ��ֵ�����ص�����Ϊ255��С��ƽ��ֵ�����ص�����Ϊ0
    imshow("newMatrix_B", newMatrix_B);

    //�����������ǰ����������λ��������λ����Ϊ��ֵ T����������������С�� T ������Ϊ0�����ڵ��� T �ĸ�Ϊ255
    //��newMatrixת��Ϊһ�У���ʹ��cv::sort��������
    Mat rnewMatrix = newMatrix.reshape(1, 1);
    Mat s;
    Mat newMatrix_B2;
    cv::sort(rnewMatrix, s, SORT_EVERY_ROW);
    //int cols1 = s.cols;
    float median;
    //�������Ϊ����������λ��Ϊ�м������������Ϊż������λ��Ϊ�м���������ƽ����
    if (s.cols % 2 != 0) {
        median = s.at<uchar>(0, (s.cols - 1) / 2);
    }
    else  median = (s.at<uchar>(0, (s.cols) / 2) + s.at<uchar>(0, ((s.cols) / 2) - 1)) / 2;
    cout << "��λ��Ϊ"<<median << endl;
    // ������ֵΪƽ��ֵ������ƽ��ֵ�����ص�����Ϊ255��С��ƽ��ֵ�����ص�����Ϊ0
    threshold(newMatrix, newMatrix_B2, median, 255, THRESH_BINARY); 
    imshow("newMatrix_B2", newMatrix_B2);
    
    //��ͼ����img���Ѿ�Ϊ�Ҷ�ͼ����ͼ����ȡȥ����һ�������ݵ�ͼ��
    Mat img1;
    img1 = img(Range(2, rows), Range(0, cols));
    imshow("img1", img1);
    //ƴ�ӣ�ʹ��vconcat()��������ȡ���ͼ��img1�ֱ���newMatrix_B��newMatrix_B2��������
    Mat vc, vc1;
    vconcat(newMatrix_B, img1, vc);
    imshow("vc", vc);
    vconcat(newMatrix_B2, img1, vc1);
    imshow("vc1", vc1);

    waitKey(0);
    return 0;
}