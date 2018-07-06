#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <propvarutil.h>
#include <InitGuid.h>
#include <propkey.h>
#include <ShObjIdl.h>
#include <Propsys.h>

#include <map>

#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;
using namespace boost::filesystem;

bool fileExists(const char * fileName);

void saveFile(string& file, string name);

void getCorrectCVSFile(string& file);

void getCorrectTXTFile(string&file);

long long int getAverageFileSize(vector<string>& files);

unsigned int getEpisodeLenght(string file);


vector<string> listall(path p, bool mode_, string extension);
bool checkDirectoryExistance(const char* file);
long long int getFileSize(string path);

bool getVideoFiles(string path, map<int, string>& exts, vector<string>& files, string& ext);