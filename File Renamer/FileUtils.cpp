#include "FileUtils.h"

bool fileExists(const char * fileName)
{
	path p(fileName);
	if (exists(p))
		if (is_regular_file(p))
			return true;
	return false;
}


void saveFile(string & file, string name)
{
	std::ofstream out(name.c_str(), std::ofstream::out);
	for (char& ch : file) {
		out.put(ch);
	}
	out.close();
}

void getCorrectCVSFile(string & file)
{
	file = file.substr(file.find("<pre>") + strlen("<pre>\n") + 1);
	file = file.substr(0, file.find("</pre>"));
}

void getCorrectTXTFile(string&file) {
	file = file.substr(file.find("title"));
}

long long int getAverageFileSize(vector<string>& files)
{ 
	long long int total = 0;
	for (string& file : files)
		total += getFileSize(file);

	return total/files.size();
}

unsigned int getEpisodeLenght(string file)
{
	CoInitialize(NULL);
	HRESULT hr = S_OK;
	IPropertyStore* store = NULL;
	wstring temp_ = wstring(file.begin(), file.end());
	PCWSTR file_ = temp_.c_str();
	hr = SHGetPropertyStoreFromParsingName(file_, NULL, GPS_READWRITE, __uuidof(IPropertyStore), (void**)&store);
	if (hr == S_OK) {
		PROPVARIANT variant;
		hr = store->GetValue(PKEY_Media_Duration, &variant);
		printf("duration: %d\n", variant.ulVal);
		//double temp = (double)variant.ulVal * 0.0001;
		//printf("Temp: %d\n", temp);
		// conver to seconds
		double seconds = (double)(variant.ulVal / 10000000);
		printf("Seconds: %f\n", seconds);
		store->Release();
		return seconds;
	}
	else
		printf("Premision denied: cant read properties\n");


	return 0;
}


bool checkDirectoryExistance(const char* file)
{
	path p(file); //Constructor de path. lleva un const char.
	if (exists(p))
		if (is_directory(p))
			return true;
	return false;
}

vector<string> listall(path p, bool mode_, string extension) {
	directory_iterator end_itr;
	vector<string> found;
	// cycle through the directory
	for (directory_iterator itr(p); itr != end_itr; ++itr) {
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if (is_regular_file(itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			string current_file = itr->path().string();
			if (current_file.size() >= 5) {
				if (!strcmp(&current_file[current_file.size() - 4], extension.c_str())) {
					found.push_back(current_file);
					path aux(current_file);
				}
			}
		}
	}
	return found;
}

long long int getFileSize(string path) {
	return boost::filesystem::file_size(path);
}

bool getVideoFiles(string path, map<int, string>& exts, vector<string>& files, string&ext)
{
	int i = -1;
	do {
		ext = exts[++i];
		files = listall(path, true, ext);
	} while (i < exts.size() && files.size() == 0);

	if (files.size() == 0)
		return false;
	else 
		return true;
}