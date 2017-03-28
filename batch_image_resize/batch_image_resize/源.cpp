#include "cv.h"
#include "highgui.h"
#include "math.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;


void main()
{
	IplImage *src;
	IplImage *dst;
	WIN32_FIND_DATA p; //ָ��һ�����ڱ����ļ���Ϣ�Ľṹ��

	//��һ����Ϊ��char����ת��Ϊwchar_t
	char road[1024] = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\images\\*.jpg";
	int num1 = MultiByteToWideChar(0, 0, road, -1, NULL, 0);
	wchar_t *road_f = new wchar_t[num1];
	MultiByteToWideChar(0, 0, road, -1, road_f, num1);

	HANDLE h = FindFirstFile(road_f, &p); //FindFirstFile�ķ���ֵ��һ��������ڶ�������p�ǲ������õķ�ʽ��Ҳ����˵����仰ִ����Ϻ�p��ָ����ļ�*.jpg
	//����p�ĳ�Ա����ֻ���ļ����������ļ�·�������Ա������·��ͷ
	string src_route_head = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\images\\"; //Դͼ���·��ͷ
	string dst_route_head = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\images_32\\";//Ŀ��ͼ���·��ͷ

	//��һ���ֽ�wchar_t����ת��Ϊchar
	int num2 = WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num2];
	WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, pchar, num2, NULL, FALSE);

	string SourceRoute = src_route_head + pchar; //������·��ͷ���ļ�����ȫ·��
	string DestRoute = dst_route_head + pchar;

	src = cvLoadImage(SourceRoute.c_str(), 4);//����Դͼ�񣬵ڶ�����������ָ������ͼƬ����ɫ����ȣ�0Ϊ�Ҷ�ͼ��>0Ϊ���ŵ�����ɫ��4Ϊ���ֲ���
	dst = cvCreateImage(cvSize(32, 32), src->depth, src->nChannels);//����һ��32*32��Ŀ��ͼ��resize��Ľ������������

	cvResize(src, dst);
	cvSaveImage(DestRoute.c_str(), dst);//����dst

	//��ĿǰΪֹ�����Ǿ��Ѿ�����˶�Ŀ���ļ����е�һ��ͼ���resize�����뱣�棬�������ø��ļ���������ͼ��Ҳ������

	while (FindNextFile(h, &p)) //pָ�벻�Ϻ��ƣ�Ѱ����һ��������һ��*.jpg
	{
		//��һ���ֽ�wchar_t����ת��Ϊchar
		int num3 = WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, NULL, 0, NULL, FALSE);
		char *pchar = new char[num3];
		WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, pchar, num2, NULL, FALSE);

		SourceRoute = src_route_head + pchar; //route��·��ͷ��imageroute�ǰ�����·��ͷ���ļ�����ȫ·��
		src = cvLoadImage(SourceRoute.c_str(), 4);//����Դͼ�񣬵ڶ�����������ָ������ͼƬ����ɫ����ȣ�0Ϊ�Ҷ�ͼ��>0Ϊ���ŵ�����ɫ��4Ϊ���ֲ���

		cvResize(src, dst);

		DestRoute = dst_route_head + pchar;
		cvSaveImage(DestRoute.c_str(), dst);//����dst
	}
}