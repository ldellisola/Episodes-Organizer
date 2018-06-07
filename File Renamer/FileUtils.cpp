#include "FileUtils.h"

bool fileExists(const char * fileName)
{
	bool retValue = false;
	ifstream src;
	src.open(fileName);

	if (src.good())
		retValue = true;
	src.close();
	return retValue;
}


void saveFile(string & file, string name)
{
	ofstream out(name.c_str(), ofstream::out);
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
