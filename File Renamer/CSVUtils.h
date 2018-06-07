#pragma once

#include "CSV Parser/csvparser.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;


typedef struct ShowData {
	string name;
	unsigned int season = 0, map = 0,episodes = 0;
	vector<string> episodeList;
};

void parsePosibleShows(ShowData& data, vector<ShowData>& posibleShows, string file);

void parseIndex(string file, ShowData& data);

void parseEpisodeList(string file, ShowData& data);