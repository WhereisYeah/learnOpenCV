//L3:�ڻҶ�ͼ�Ļ����ϣ��ѻҶ�ͼ���ϰ벿�������������ƽ��ֵΪ��ֵת��Ϊ��ֵͼ���ѻҶ�ͼ���°벿���ԻҶ�ͼ��ʾ�����������������
//������ʾ���

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    // ��ȡͼ��
    Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);//��־����IMREAD_GRAYSCALE��ͼ��ת�ɵ�ͨ���Ҷ�ͼ����ȡ
    if (img.empty())
    {
        cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
        return -1;
    }

    //ʹ��mean()�����������������ƽ��ֵ
    Scalar myMean;
    myMean = mean(img);
    cout << "matrix��ֵ=" << myMean << endl;
    cout << "imgs��һ��ͨ���ľ�ֵ=" << myMean[0] << "    "
        << "imgs�ڶ���ͨ���ľ�ֵ=" << myMean[1] << endl << endl;
    Mat img_B;
    // ������ֵΪƽ��ֵ������ƽ��ֵ�����ص�����Ϊ255��С��ƽ��ֵ�����ص�����Ϊ0
    threshold(img, img_B, myMean[0], 255, THRESH_BINARY);
    imshow("img_B", img_B);
    

    //ʹ�������ǳ����ʵ�ְѻҶ�ͼ���ϰ벿�������������ƽ��ֵΪ��ֵת��Ϊ��ֵͼ���ѻҶ�ͼ���°벿���ԻҶ�ͼ��ʾ
    Mat ROI1, mask, gray_copy;
    img.copyTo(gray_copy);//�������img�����gray_copy
    // ��ȡͼ��ĸ߶ȺͿ��
    int height = img.rows;
    int width = img.cols;
    //��ͼ����img���Ҷ�ͼ���Ͻ�ȡ�ϰ벿��ͼ��ROI1����img_B����ֵͼ���Ͻ�ȡ�ϰ벿��ͼ��mask
    //��ͼ�൱ǳ����
    ROI1 = img(Range(0, height / 2), Range(0, width));
   mask= img_B(Range(0, height / 2), Range(0, width));
    mask.copyTo(ROI1);//��mask���Ƹ�ROI1
    imshow("img", img);//img��ı䣬��ΪROI1Ϊǳ������ROI1��Ϊ��ֵͼmask,��img�ϰ벿��Ҳ��ı�Ϊ��ֵͼ
    imshow("gray_copy", gray_copy);//gray_copy����ı䣬��Ϊgray_copyΪ���
    imshow("ROI1", ROI1);
    imshow("mask", mask);
  
    waitKey(0);
    return 0;
}