// File Renamer.cpp : Defines the entry point for the console application.
//


#include "fileSys.h"
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
	/////////// Descargo el indice de la pagina




	
	if (!fileExists(INDEX)) {
		string indexFile = getTXTFile(ALLSHOWS);
		if (indexFile.size() == 0) {
			cout << "Error";
			return -1;
		}

		getCorrectTXTFile(indexFile);
		saveFile(indexFile, INDEX);
	}
		

	///////////

	CursesClass curses;
	ShowData data;
	data.name = getName(curses);
	string ext = getExtension(curses);
	data.season= getSeason(curses);
	string path = getPath(curses);

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

	//////////// Busco los episodios de la serie

	if (!fileExists((data.name + ".csv").c_str())) {
		string allEpisodes = getHTTPFile(SHOWADRESS + to_string(data.map));
		if (allEpisodes.size() == 0) {
			cout << "Error getting Episodes. Press enter to exit" << endl;
			cin.get();
			return -1;
		}
		getCorrectCVSFile(allEpisodes);
		saveFile(allEpisodes, data.name + ".csv");
	}


	parseEpisodeList(data.name + ".csv",data);
	removeForbbidenChars(data.episodeList);




	if (check_existance(path.c_str())){
		vector<string> files = listall(path.c_str(), true, ext);
		string season = (data.season >= 10 ? to_string(data.season) : "0" + to_string(data.season));
		CutPos pos = getEpisodePlace(files[0], curses);
		
		if (pos.start < pos.end) {
			for (int i = 0; i < files.size(); i++) {
				string newName = path + "\\S" + season + 'E' + getEpisode(files[i], pos) + " - " + data.episodeList[-1+atoi(getEpisode(files[i], pos).c_str())]+ext;
				rename((files[i]).c_str(), newName.c_str());

			}
		}
		else
		{
			clear();
			curses << "Error: Sos tonto o te haces? Ponelo bien";
			getchar();
		}


	}

	
    return 0;
}

