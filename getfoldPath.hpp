/*******************************************************
*
* Author: Ethan
*
*         xdshen@mail.ustc.edu.cn
*
* Version: 2.0 
* Date:  2016-04-08
*
*******************************************************/


#ifndef _GET_FOLD_PATH_
#define _GET_FOLD_PATH_

/*!

    @header 
    @abstract         �����ļ���Ŀ¼����ȡ�ڲ������ļ�(Ŀ¼)
    @discussion

*/


#include <iostream>
#include <string>
#include <vector>
#include <io.h> 


/*!
   @function
   @abstract ��ȡĳһĿ¼�µ������ļ���ȫ·��
   @discussion
   @param    path       Ŀ¼��
   @param    files      �����ļ���ȫ·��
   @result   none
*/
void getFiles(std::string path, std::vector<std::string>& files)
{
	//�ļ���� 
	long   hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo;

	std::string p;

	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{

		do  {
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib   &   _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}


/*!
    @function
    @abstract ��ȡĳһĿ¼�µ������ض���չ�����ļ���ȫ·��
    @discussion
    @param    path       Ŀ¼��
    @param    exd        ��չ��
    @param    files      �����ļ���ȫ·��
    @result   none
*/
void getFiles(std::string path, std::string exd, std::vector<std::string>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	std::string pathName, exdName;

	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}
	else
	{
		exdName = "\\*";
	}

	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//������ļ����������ļ���,����֮
			//�������,�����б�
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
			}
			else
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
/*!
   @function
   @abstract ��ȡĳһĿ¼�µ�������ײ���Ŀ¼��ȫ·��
   @discussion
   @param    path       Ŀ¼��
   @param    files      ������Ŀ¼��ȫ·��
   @result   none
*/
void getDirs(std::string path, std::vector<std::string>& files)
{
	//�ļ���� 
	long   hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo;

	std::string p;

	int flag = 0; // ��־�Ƿ�Ϊ��Ŀ¼ 

	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{

		do  {
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib   &   _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getDirs(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else
			{
				if (flag == 0)
				{
					files.push_back(p.assign(path));
					flag = 1;
				}

			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}




#endif