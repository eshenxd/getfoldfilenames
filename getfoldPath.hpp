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
    @abstract         遍历文件夹目录，获取内部所有文件(目录)
    @discussion

*/


#include <iostream>
#include <string>
#include <vector>
#include <io.h> 


/*!
   @function
   @abstract 获取某一目录下的所有文件的全路径
   @discussion
   @param    path       目录名
   @param    files      所有文件的全路径
   @result   none
*/
void getFiles(std::string path, std::vector<std::string>& files)
{
	//文件句柄 
	long   hFile = 0;
	//文件信息 
	struct _finddata_t fileinfo;

	std::string p;

	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{

		do  {
			//如果是目录,迭代之
			//如果不是,加入列表
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
    @abstract 获取某一目录下的所有特定扩展名的文件的全路径
    @discussion
    @param    path       目录名
    @param    exd        扩展名
    @param    files      所有文件的全路径
    @result   none
*/
void getFiles(std::string path, std::string exd, std::vector<std::string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
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
			//如果是文件夹中仍有文件夹,迭代之
			//如果不是,加入列表
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
   @abstract 获取某一目录下的所有最底层子目录的全路径
   @discussion
   @param    path       目录名
   @param    files      所有子目录的全路径
   @result   none
*/
void getDirs(std::string path, std::vector<std::string>& files)
{
	//文件句柄 
	long   hFile = 0;
	//文件信息 
	struct _finddata_t fileinfo;

	std::string p;

	int flag = 0; // 标志是否为子目录 

	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{

		do  {
			//如果是目录,迭代之
			//如果不是,加入列表
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