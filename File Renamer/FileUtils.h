#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool fileExists(const char * fileName);


void saveFile(string& file, string name);

void getCorrectCVSFile(string& file);

void getCorrectTXTFile(string&file);
