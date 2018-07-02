#include "FileUtils.h"

bool fileExists(const char * fileName)
{
	bool retValue = false;
	std::ifstream src;
	src.open(fileName);

	if (src.good())
		retValue = true;
	src.close();
	return retValue;
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
