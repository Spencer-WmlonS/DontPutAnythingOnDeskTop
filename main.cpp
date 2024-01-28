//#include "stdafx.h" 
#include <stdio.h> 
#include<iostream> 
#include<vector> 
#include <Windows.h> 
#include <fstream>  
#include <iterator> 
#include <string> 
using namespace std; 
 
#define MAX_PATH 1024 //最长路径长度 
 
/*---------------------------- 
 * 功能 : 递归遍历文件夹，找到其中包含的所有文件 
 *---------------------------- 
 * 函数 : find 
 * 访问 : public  
 * 
 * 参数 : lpPath [in]   需遍历的文件夹目录 
 * 参数 : fileList [in]  以文件名称的形式存储遍历后的文件 
 */ 
void find(char* lpPath,std::vector<const std::string> &fileList) 
{ 
  char szFind[MAX_PATH]; 
  WIN32_FIND_DATA FindFileData; 
   
  strcpy(szFind,lpPath); 
  strcat(szFind,"\\*.*"); 
 
  HANDLE hFind=::FindFirstFile(szFind,&FindFileData); 
  if(INVALID_HANDLE_VALUE == hFind)  return; 
 
  while(true) 
  { 
    if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
    { 
      if(FindFileData.cFileName[0]!='.') 
      { 
        char szFile[MAX_PATH]; 
        strcpy(szFile,lpPath); 
        strcat(szFile,"\\"); 
        strcat(szFile,(char* )(FindFileData.cFileName)); 
        find(szFile,fileList); 
      } 
    } 
    else 
    { 
      //std::cout << FindFileData.cFileName << std::endl; 
      fileList.push_back(FindFileData.cFileName); 
    } 
    if(!FindNextFile(hFind,&FindFileData))  break; 
  } 
  FindClose(hFind); 
} 
 
 
int main() 
{ 
  std::vector<const std::string> fileList;//定义一个存放结果文件名称的链表 
 
  //遍历一次结果的所有文件,获取文件名列表 
  find("D:\CloudMusic\VipSongsDownload",fileList);//之后可对文件列表中的文件进行相应的操作 
 
  //输出文件夹下所有文件的名称 
  for(int i = 0; i < fileList.size(); i++) 
  { 
    cout << fileList[i] << endl; 
  } 
  cout << "文件数目：" << fileList.size() << endl; 
  return 0; 
}
