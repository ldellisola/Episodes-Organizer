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
	int sss = pos.end - pos.start;
	if (sss == 0)
		sss = 1;
	string retValue = ep.substr(pos.start, pos.end- pos.start);
	return retValue;
}

CutPos getEpisodePlace(string ep, CursesClass& curses)
{
	clear();
	move(0, 0);
	curses << "Select where it says the episode. use the keys, space  to select and enter finish. press esc to restart";
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
			if (pos.start == -1)
				pos.start = index;
			else
				pos.end = index;
			pos.start = index;
			color_set(2, nullptr);
			mvprintw(1,index,"%c", ep[index]);
			index++;
			move(1, index);
			color_set(1, nullptr);
			break;
		case 27:
			pos.start = -1;
			pos.end = -1;
			move(0, 0);
			curses << ep;
			leave = true;
			break;
		case '\n':
			if (pos.end == -1)
				pos.end = index;
			pos.end = ++index;
			color_set(2, nullptr);
			printw("%c", ep[index]);
			color_set(1, nullptr);
			leave = true;
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
	curses << tempCurs << "We couldn't find the TV show, did you mean any of these ones?. esc if none was found, enter to confuirm and arrows to select";
	int index = 0;

	for (ShowData& data_ : posibleShows) {
		tempCurs = { 1 + ((unsigned int)index++),0 };
		curses << tempCurs << data_.name;
	}
	index = 0;
	bool leave = false;
	while (!leave) {
		switch (getch()) {
		case '\n':
			leave = true;
			break;
		case 27:
			index = -1;
			leave = true;
		case KEY_DOWN:
			if (index < posibleShows.size() - 1) {
				index++;

				color_set(1, nullptr);
				mvdeleteln(index - 1 + 1, 0);
				tempCurs = { 1 + ((unsigned int)index - 1),0 };
				curses << tempCurs << posibleShows[index - 1].name;

				color_set(2, nullptr);
				mvdeleteln(index + 1, 0);
				tempCurs = { 1 + ((unsigned int)index),0 };
				curses << tempCurs << posibleShows[index].name;
				color_set(1, nullptr);
			}



			break;
		case KEY_UP:
			if (index > 0) {
				index--;

				color_set(1, nullptr);
				mvdeleteln((unsigned int)index + 1 + 1, 0);
				tempCurs = { 1 + ((unsigned int)index + 1),0 };
				curses << tempCurs << posibleShows[index + 1].name;

				color_set(2, nullptr);
				mvdeleteln(index + 1, 0);
				tempCurs = { 1 + ((unsigned int)index),0 };
				curses << tempCurs << posibleShows[index].name;

				color_set(1, nullptr);
			}
		}
	}
	if (index >= 0) {
		data = posibleShows[index];
		return true;
	}
	else return false;
	
}


