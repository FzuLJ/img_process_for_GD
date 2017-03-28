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
	WIN32_FIND_DATA p; //指向一个用于保存文件信息的结构体

	//这一部分为将char类型转换为wchar_t
	char road[1024] = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\images\\*.jpg";
	int num1 = MultiByteToWideChar(0, 0, road, -1, NULL, 0);
	wchar_t *road_f = new wchar_t[num1];
	MultiByteToWideChar(0, 0, road, -1, road_f, num1);

	HANDLE h = FindFirstFile(road_f, &p); //FindFirstFile的返回值是一个句柄，第二个参数p是采用引用的方式，也就是说当这句话执行完毕后p就指向该文件*.jpg
	//由于p的成员变量只有文件名，而无文件路径，所以必须加上路径头
	string src_route_head = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\images\\"; //源图像的路径头
	string dst_route_head = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\images_32\\";//目标图像的路径头

	//这一部分将wchar_t类型转换为char
	int num2 = WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num2];
	WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, pchar, num2, NULL, FALSE);

	string SourceRoute = src_route_head + pchar; //包含了路径头和文件名的全路径
	string DestRoute = dst_route_head + pchar;

	src = cvLoadImage(SourceRoute.c_str(), 4);//载入源图像，第二个参数用于指定读入图片的颜色和深度，0为灰度图，>0为三信道即彩色，4为保持不变
	dst = cvCreateImage(cvSize(32, 32), src->depth, src->nChannels);//分配一个32*32的目标图像，resize后的结果将放在这里

	cvResize(src, dst);
	cvSaveImage(DestRoute.c_str(), dst);//保存dst

	//到目前为止，我们就已经完成了对目标文件夹中第一幅图像的resize处理与保存，接下来让该文件夹中其余图像也被处理

	while (FindNextFile(h, &p)) //p指针不断后移，寻找下一个、下下一个*.jpg
	{
		//这一部分将wchar_t类型转换为char
		int num3 = WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, NULL, 0, NULL, FALSE);
		char *pchar = new char[num3];
		WideCharToMultiByte(CP_OEMCP, NULL, p.cFileName, -1, pchar, num2, NULL, FALSE);

		SourceRoute = src_route_head + pchar; //route是路径头，imageroute是包含了路径头和文件名的全路径
		src = cvLoadImage(SourceRoute.c_str(), 4);//载入源图像，第二个参数用于指定读入图片的颜色和深度，0为灰度图，>0为三信道即彩色，4为保持不变

		cvResize(src, dst);

		DestRoute = dst_route_head + pchar;
		cvSaveImage(DestRoute.c_str(), dst);//保存dst
	}
}