#pragma once
#include "Windows.h"
#include "stdafx.h"
class Picture
{
public:
	struct Point
	{
		int x, y;
	};
	struct bitmap
	{
		int width, height;
		bool array[250 * 50];//����ƣ���ά������tm��ƫ�ƣ����ŵĻ��Լ�����ȥ
	};
	//��ֵ��
	void Binaryzation(const char* sourcePath, const char* destPath, bitmap &bm);
	//��ͼ ��һλ��������άbitmap
	Point FindPicture(bitmap source, bitmap pic);
	void ReadBMP(const char* picPath, bitmap &bm);
	Picture();
	~Picture();

};

