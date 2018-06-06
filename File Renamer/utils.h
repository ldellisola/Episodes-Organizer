#pragma once
#include "CursesClass.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef struct CutPos
{
	size_t start, end;
};
string getExtension(CursesClass& curses);

string getName(CursesClass& curses);

int getSeason(CursesClass & curses);

string getPath(CursesClass& curses);

vector<string> getNameFromFile();

string getEpisode(string ep, CutPos pos);

CutPos getEpisodePlace(string ep, CursesClass& curses);

void removeForbbidenChars(vector <string>& arr);