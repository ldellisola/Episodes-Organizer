#include "utils.h"

string getExtension(CursesClass & curses)
{
	string ext;

	clear();

	curses << "Extension is :\n";
	move(1, 0);
	ext = curses.getString(1,0,5);

	return ext;
}

string getName(CursesClass & curses)
{
	clear();
	curses << "Name is :\n";
	move(1, 0);
	return curses.getString(1,0,100);
}

int getSeason(CursesClass & curses)
{
	clear();
	echo();
	curses << "Season is:\n";
	move(1, 0);
	return curses.getNumberString(1, 0, "Tonto, solo numeros");
}


string getPath(CursesClass& curses) {
	clear();
	curses << "Path is:\n";
	return curses.getString(1, 0, 100);
}

vector<string> getNameFromFile()
{
	vector<string> names;
	ifstream file;

	file.open("a.txt");
	char buffer[1000];
	while (file.good()) {
		for (char& a : buffer)
			a = 0;
		file.getline(buffer, 1000);
		string line = buffer;
		string temp = line.substr(line.find(','));
		names.push_back(buffer);
	}
	return names;
}

string getEpisode(string ep, CutPos pos)
{

	string retValue = ep.substr(pos.start, pos.end- pos.start);

	char a = retValue[1];
	char b = retValue[0];
	bool dig = isdigit(a);

	if (!dig) {				
		retValue[0] = '0';
		retValue[1] = b;
	}


	return retValue;
}

CutPos getEpisodePlace(string ep, CursesClass& curses)
{
	clear();
	move(0, 0);
	curses << "Select where it says the episode. Use the space key to select where the number starts. (This program is optimized for series with up to 99 episodes per season)";
	move(1, 0);
	curses << ep;
	int index = 0;
	bool leave = false;
	CutPos pos;
	pos.start = -1;
	pos.end = -1;

	while (!leave) {
		switch (getch()) {
		case KEY_LEFT:
			if (index > 0) {
				--index;
				move(1, index);
			}
			break;
		case KEY_RIGHT:
			if (index < ep.size() - 1) {
				++index;
				move(1, index);
			}
			break;
		case ' ':
			pos.start = index;
			pos.end = index+2;
			leave = true;
			break;
		//case 27:
		//	pos.start = -1;
		//	pos.end = -1;
		//	move(0, 0);
		//	curses << ep;
		//	leave = true;
		//	break;
		//case '\n':
		//	if (pos.end == -1)
		//		pos.end = index;
		//	pos.end = ++index;
		//	color_set(2, nullptr);
		//	printw("%c", ep[index]);
		//	color_set(1, nullptr);
		//	leave = true;
		}
	}

	

	return pos;
}

void removeForbbidenChars(vector<string>& arr)
{
	for (string& str : arr) {
		size_t pos;
		while ((pos = str.find('\\')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('/')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('?')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('|')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('*')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find(':')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('<')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('>')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find('"')) != string::npos) {
			str.erase(pos);
		}
		while ((pos = str.find("&quot;")) != string::npos) {
			str.erase(pos,strlen("&quot;"));
		}
		while ((pos = str.find("&amp;")) != string::npos) {
			str.erase(pos, strlen("&quot;"));
			str.insert(pos, "and ");
		}
	}
}


bool askForIntendedShow(vector<ShowData>& posibleShows, ShowData& data, CursesClass& curses) {
	Cursor tempCurs;
	clear();
	tempCurs = { 0,0 };
	curses << tempCurs << "We couldn't find the TV show, did you mean any of these ones?. Press 'enter' to confirm and arrows to select";
	int index = 0;

	for (ShowData& data_ : posibleShows) {
		tempCurs = { 1 + ((unsigned int)index++),0 };
		curses << tempCurs << data_.name;
	}
	index = 0;
	noecho();
	nodelay(curses.getDispay(), true);


	color_set(1, nullptr);
	for (int i = 0; i < posibleShows.size(); i++) 
		mvprintw(i + 1, 0, posibleShows[i].name.c_str());

	color_set(2, nullptr);
	tempCurs = { 1 + ((unsigned int)index),0 };
	mvprintw(index + 1, 0, posibleShows[index].name.c_str());

	bool leave = false;
	while (!leave) {
		switch (getch()) {
		case '\n':
			leave = true;
			break;
		case KEY_DOWN:
			if (index < posibleShows.size() - 1) {
				index++;

				color_set(1, nullptr);
				for (int a = 0; a < posibleShows.size(); a++)
					mvprintw(a + 1, 0, posibleShows[a].name.c_str());

				color_set(2, nullptr);
				tempCurs = { 1 + ((unsigned int)index),0 };
				curses << tempCurs << posibleShows[index].name;
			}
			break;
		case KEY_UP:
			if (index > 0) {
				index--;

				color_set(1, nullptr);
				for (int a = 0; a < posibleShows.size(); a++)
					mvprintw(a + 1, 0, posibleShows[a].name.c_str());

				color_set(2, nullptr);
				tempCurs = { 1 + ((unsigned int)index),0 };
				curses << tempCurs << posibleShows[index].name;
			}
			break;
		}
	}
	if (index >= 0 && index < posibleShows.size()) {
		color_set(1, nullptr);
		data = posibleShows[index];
		return true;
	}
	else return false;
	
}


map<int, string> getVideoFormatDictionary()
{
	map<int, string> a;
	a[0] = ".mp4";
	a[1] = ".avi";
	a[2] = ".mkv";
	a[3] = ".mpeg";
	a[4] = ".m4v";

	return a;
}


