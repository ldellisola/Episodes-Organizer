// File Renamer.cpp : Defines the entry point for the console application.
//

#include "utils.h"
#include "fileSys.h"
#include "NetworkUtils.h"
#include "CSVUtils.h"
#include <cstdio>

int main()
{
	/////////// Descargo el indice de la pagina
	string indexFile = getTXTFile("http://epguides.com/common/allshows.txt");
	if (indexFile.size() == 0) {
		cout << "Error";
		return -1;
	}

	getCorrectTXTFile(indexFile);
	saveCSV(indexFile, "index");

	///////////

	CursesClass curses;
	ShowData data;
	data.name = getName(curses);
	string ext = getExtension(curses);
	data.season= getSeason(curses);
	string path = getPath(curses);

	/////////// Parseo el indice para  verificar si existe la serie

	parseIndex("index.csv", data);

	if (data.map == 0) {
		cout << "TV Show not found. Press enter to exit" << endl;
		cin.get();
		return -1;
	}

	//////////// Busco los episodios de la serie

	string allEpisodes = getHTTPFile("epguides.com/common/exportToCSVmaze.asp?maze=" + to_string(data.map));
	if (allEpisodes.size() == 0) {
		cout << "Error getting Episodes. Press enter to exit" << endl;
		cin.get();
		return -1;
	}
	getCorrectCVSFile(allEpisodes);
	saveCSV(allEpisodes, "episodes");

	parseEpisodeList("episodes.csv",data);
	removeForbbidenChars(data.episodeList);




	if (check_existance(path.c_str())){
		vector<string> files = listall(path.c_str(), true, ext);
		string season = (data.season >= 10 ? to_string(data.season) : "0" + to_string(data.season));
		// Seria correcto asumir que me agarra las cosas en orden alfabetico?
		CutPos pos = getEpisodePlace(files[0], curses);
		if (files.size() != data.episodeList.size()) {
			cout << "We still do not support Shows that have 2 in 1 episodes, sorry" << endl << "Press enter to exit" << endl;
			cin.get();
			return -1;
		}
		if (pos.start < pos.end) {
			for (int i = 0; i < files.size(); i++) {
				string newName = path + "\\S" + season + 'E' + getEpisode(files[i], pos) + " - " + data.episodeList[i]+ext;
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

