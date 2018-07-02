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
#include "fileSys.h"
using namespace std;

bool fileExists(const char * fileName);


void saveFile(string& file, string name);

void getCorrectCVSFile(string& file);

void getCorrectTXTFile(string&file);

long long int getAverageFileSize(vector<string>& files);

unsigned int getEpisodeLenght(string file);
