#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;
using namespace boost::filesystem;

vector<string> listall(path p, bool mode_, string extension);
int check_existance(const char* file);
long long int getFileSize(string path);