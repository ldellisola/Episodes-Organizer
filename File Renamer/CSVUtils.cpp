#include "CSVUtils.h"

enum { titleIX, directoryIX, tvrageIX, TVmazeIX, starDateIX, endDateIX, numberOfEpisodesIX, runTimeIX, networkIX, countryIX};

enum { numberEP, seasonEP, episodeEP, airdateEP, titleEP, tvmazeLinkEP};

bool compareNames(string name, string realName);

void saveCSV(string & file, string name)
{
	ofstream out((name + ".csv").c_str(), ofstream::out);
	for (char& ch : file) {
		out.put(ch);
	}
	out.close();
}

void getCorrectCVSFile(string & file)
{
	file = file.substr(file.find("<pre>")+ strlen("<pre>\n")+1);
	file = file.substr(0, file.find("</pre>"));
}

void getCorrectTXTFile(string&file) {
	file = file.substr(file.find("title"));
}

void parseIndex(string fileName, ShowData& data)
{
	CsvParser * parser = CsvParser_new(fileName.c_str(), ",", 1);
	CsvRow * row;
	const CsvRow * header = CsvParser_getHeader(parser);
	bool rightTitle = false;

	if (header != NULL) {
		while (row = CsvParser_getRow(parser)) {
			const char **rowFields = CsvParser_getFields(row);

			if (compareNames(rowFields[titleIX], data.name)) {
				data.map = atoi(rowFields[TVmazeIX]);
				data.episodes = atoi(rowFields[numberOfEpisodesIX]);
				CsvParser_destroy_row(row);
				break;
			}
			else	CsvParser_destroy_row(row);
		}
		CsvParser_destroy(parser);
	}
	
}

void parseEpisodeList(string file, ShowData & data)
{
	CsvParser * parser = CsvParser_new(file.c_str(), ",", 1);
	CsvRow * row;
	const CsvRow * header = CsvParser_getHeader(parser);
	bool rightTitle = false;
	int a = 0;
	if (header != NULL) {
		while (row = CsvParser_getRow(parser)) {
			const char **rowFields = CsvParser_getFields(row);
			a++;
			if (data.season == atoi(rowFields[seasonEP])) {
				data.episodeList.push_back(rowFields[titleEP]);
			}
			
			if (data.season < atoi(rowFields[seasonEP])) {
				CsvParser_destroy_row(row);
				break;
			}
			CsvParser_destroy_row(row);
		}
		CsvParser_destroy(parser);
	}

}

bool compareNames(string name, string realName) {
	
	for (char& ch : name)
		ch = tolower(ch);
	for (char& ch : realName)
		ch = tolower(ch);

	if (!name.compare(realName))
		return true;
	else return false;
	
}
