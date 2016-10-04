#include "stdafx.h"
#include "Picture.h"
using namespace std;
// �����̬�����ά�ڴ�(ָ������)�ĺ���������˼
template<typename T>
void NewArr(T**& Array, int row, int line)
{
	Array = new T*[row];
	for (int i = 0; i != row; i++)
	{
		Array[i] = new T[line];
		memset(Array[i], 0, sizeof(T) * line);
	}
}
// �����̬�ͷŶ�ά�ڴ�ĺ���Ҳ������˼
template<typename T>
void DeleteArray(T**& Array, int line)
{
	for (int i = 0; i < line; i++)
	{
		delete[] Array[i];
		Array[i] = NULL;
	}
	delete[] Array;
	Array = NULL;
}
// path �ļ�ͼƬ�ľ��Ե�ַ
// bf, bi��Ϊ�����������, �����ڲ���ɳ�ʼ��
// lpBit, ͼ������, һ��������Ķ�ά����(һ��ָ������), ���Զ�һ����ָ���ȥ, �����ڲ���Ϊ�����ڴ�
void ReadBitmap(const char* path, BITMAPFILEHEADER& bf, BITMAPINFOHEADER& bi, unsigned char**& lpBit)
{
	FILE* fp = fopen(path, "rb");
	if (fp == NULL)
		exit(0);

	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp); // д���ļ�ͷ
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp); // д����Ϣͷ

	NewArr(lpBit, bi.biHeight, (bi.biWidth * 3 + 3) / 4 * 4);
	for (int i = 0; i < bi.biHeight; i++)
		for (int j = 0; j < (bi.biWidth * 3 + 3) / 4 * 4; j++)
			fread(&lpBit[i][j], sizeof(unsigned char), 1, fp); // ÿ�ζ���һ���ֽ�
			
	fclose(fp);
}
// path �ļ�ͼƬ�ľ��Ե�ַ
// bf, bi��Ϊ�����������,
// lpBit, ͼ������, ����ReadBitmap��ʼ������Ϊ�������
void WriteBitmap(const char* path, BITMAPFILEHEADER& bf, BITMAPINFOHEADER& bi, unsigned char**& lpBit, BYTE limit, Picture::bitmap &bm)
{
	FILE* fp;
	fp = fopen(path, "wb");
	if (fp == NULL)
		exit(0);

	BITMAPFILEHEADER newbf; // ��ʼ���ļ�ͷ
	memcpy(&newbf, &bf, sizeof(BITMAPFILEHEADER));
	int newbfWidth = (bi.biWidth + 3) / 4 * 4; // 4�ֽڲ���
	int newbfImageSize = newbfWidth * bi.biHeight; // λͼ����ʵ�ʴ�С
	newbf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	newbf.bfSize = newbfImageSize + newbf.bfOffBits; // λͼ�ļ�ʵ�ʴ�С

	BITMAPINFOHEADER newbi; // ��ʼ����Ϣͷ
	memcpy(&newbi, &bi, sizeof(BITMAPINFOHEADER));
	newbi.biSizeImage = newbfImageSize;
	newbi.biBitCount = 8;

	fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, fp); // д���ļ�ͷ
	fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, fp); // д����Ϣͷ

	RGBQUAD* pRGB = new RGBQUAD[256]; // ��ʼ����ɫ��
	for (int i = 0; i != 256; i++)
		pRGB[i].rgbRed = pRGB[i].rgbGreen = pRGB[i].rgbBlue = i;
	fwrite(pRGB, sizeof(RGBQUAD), 256, fp); // д���ɫ��

	unsigned char** Array;
	NewArr(Array, newbi.biHeight, newbfWidth);
	bm.height = newbi.biHeight;
	bm.width = newbfWidth;
	for (int i = 0; i < newbi.biHeight; i++)
	{
		for (int j = 0; j < newbfWidth; j++)
		{
			//                        newImagedata[Pos + j] = (ImageData[i][j * 3] + ImageData[i][j * 3 + 1] + ImageData[i][j * 3 + 2]) / 3; // һ��д��
			Array[i][j] = lpBit[i][j * 3] * 0.114 +
				lpBit[i][j * 3 + 1] * 0.587 +
				lpBit[i][j * 3 + 2] * 0.299; // ��������Ϊ B G R����ɫ���� ���лҶȻ�
			Array[i][j] > limit ? Array[i][j] = 255 : Array[i][j] = 0; // �˴����÷�ֵ
			if ((int)Array[i][j] == 255)
			{
				bm.array[i*bm.width + j] = false;
			}
			else
			{
				bm.array[i*bm.width + j] = true;
			}
			fwrite(&Array[i][j], sizeof(unsigned char), 1, fp); // ��ÿ��һ���ֽ�д��
		}
	}
	DeleteArray(Array, newbi.biHeight);
	fclose(fp);
}
//��ֵ��
void Picture::Binaryzation(const char* sourcePath, const char* destPath, Picture::bitmap &bm)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	memset(&bf, 0, sizeof(BITMAPFILEHEADER));
	memset(&bi, 0, sizeof(BITMAPINFOHEADER));
	unsigned char** lpBit = NULL;
	// �����ڲ���Ϊ�����ڴ�, ����Ϊ����ָ��, ���Ժ����ڲ���̬���ݳ��ڴ����β�Ϊ����ָ������û�����ָ��
	ReadBitmap(sourcePath, bf, bi, lpBit);
	WriteBitmap(destPath, bf, bi, lpBit, 128, bm);
	DeleteArray(lpBit, bi.biHeight);
}
//��ͼ ��һλ��������άbitmap
Picture::Point Picture::FindPicture(Picture::bitmap source, Picture::bitmap pic)
{
	Picture::Point p;
	bool flag = false;

	freopen("1.txt", "w", stdout);
	for (int i = 0; i < pic.height; i++)
	{
		for (int j = 0; j < pic.width-1; j++)
		{
			if (pic.array[i*pic.width + j])
			{
				cout << ".";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	
	for (int i = 0; i <= source.height - pic.height; i++)//ö����Ѱ��ͼƬ���Ͻ�����
	{
		for (int j = 0; j <= source.width - pic.width; j++)
		{
			flag = false;
			for (int k = 0; k < pic.height-1; k++)
			{
				for (int l = 0; l < pic.width-1; l++)
				{
					if (pic.array[k*pic.width + l] == source.array[(i + k)*source.width + (j + l)])
					{
						flag = true;
					}
					else
					{
						flag = false;
						break;
					}
				}
				if (!flag)
					break;
			}
			if (flag)
			{
				p.x = j;
				p.y = i;
				return p;
			}
		}
	}
	p.x = p.y = -1;
	return p;
}
void Picture::ReadBMP(const char* picPath, Picture::bitmap &bm)
{
	string dstPath(picPath); dstPath.append("_.bmp");
	Binaryzation(picPath, dstPath.c_str(), bm);
}
Picture::Picture()
{
}


Picture::~Picture()
{
}
