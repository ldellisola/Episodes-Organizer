// File Renamer.cpp : Defines the entry point for the console application.
//


#include "NetworkUtils.h"
#include "FileUtils.h"
#include "CSVUtils.h"
#include <cstdio>
#include "utils.h"

#define INDEX ("index.csv")
#define ALLSHOWS ("http://epguides.com/common/allshows.txt")
#define SHOWADRESS ("epguides.com/common/exportToCSVmaze.asp?maze=")



int main()
{
	CursesClass curses;
	/////////// Descargo el indice de la pagina

	if (!fileExists(INDEX)) {
		string indexFile = getTXTFile(ALLSHOWS);
		if (indexFile.size() == 0) {
			curses << "Error";
			return -1;
		}

		getCorrectTXTFile(indexFile);
		saveFile(indexFile, INDEX);
	}
		

	///////////

	
	ShowData data;
	data.name = getName(curses);
	/////////// Parseo el indice para  verificar si existe la serie

	parseIndex(INDEX, data);

	if (data.map == 0) {
		vector<ShowData> posibleShows;
		parsePosibleShows(data, posibleShows, INDEX);

		if (!askForIntendedShow(posibleShows, data, curses)) {
			clear();
			curses << "Ok, that show doesn't exist";
			cin.get();
			return -1;
		}
	}

	
	data.season = getSeason(curses);
	

	//////////// Busco los episodios de la serie

	if (!fileExists((data.name + ".csv").c_str())) {
		string allEpisodes = getHTTPFile(SHOWADRESS + to_string(data.map));
		if (allEpisodes.size() == 0) {
			curses << "Error getting Episodes. Press enter to exit";
			cin.get();
			return -1;
		}
		getCorrectCVSFile(allEpisodes);
		saveFile(allEpisodes, data.name + ".csv");
	}

	
	parseEpisodeList(data.name + ".csv",data);
	removeForbbidenChars(data.episodeList);


	string path = getPath(curses);

	map<int, string> videoFormat = getVideoFormatDictionary();


	if (checkDirectoryExistance(path.c_str())){
		vector<string> files;
		string ext;
		if (!getVideoFiles(path, videoFormat, files, ext)) {
			ext = getExtension(curses);
			files = listall(path, true, ext);
		}
		bool leave = false;

		if (files.size() != 0) {

			if (files.size() != data.episodeList.size()) {
				curses.clearDisplay();
				curses << "It seems that EpGuides has a different number of episodes for this TV show.\n";
				curses << "If you only want to rename a few episodes, its ok, but there is an issue when you want to rename 2 in 1 episodes that we haven't figured out how to solve and could lead to renaming errors.\n";
				curses << "If this is the case, pres 'Q' to cancel, otherwise press any key to continue.";
				char b;
				do { b = getch(); } while (b == ERR);
				if (b == 'q')
					leave = true;
			}

			if (!leave) {
				string season = (data.season >= 10 ? to_string(data.season) : "0" + to_string(data.season));
				CutPos pos = getEpisodePlace(files[0], curses);

				if (pos.start < pos.end) {
					for (int i = 0; i < files.size(); i++) {
						string newName = path + "\\S" + season + 'E' + getEpisode(files[i], pos) + " - " + data.episodeList[-1 + atoi(getEpisode(files[i], pos).c_str())] + ext;
						rename((files[i]).c_str(), newName.c_str());
					}
				}
				else{
					curses.clearDisplay();
					curses << "Error: Sos tonto o te haces? Ponelo bien";
					cin.get();
				}
			}

			
		}
		else {
			curses.clearDisplay();
			curses << "There were no files with that extension";
			cin.get();
		}


	}

	
    return 0;
}

