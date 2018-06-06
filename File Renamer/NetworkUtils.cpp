#include "NetworkUtils.h"


bool webOK(string str);
bool getFileSize(string& str, size_t& size);
string getHTTPCode(string str);
bool end(string file);
bool endTXT(string& str, int size);

string getHTTPFile(string host_)
{
	client client;
	string tempWeb;

	if (host_.find("//") == string::npos)
		tempWeb = host_;
	else
		tempWeb = host_.substr(host_.find("//") + 2);

	string host = tempWeb.substr(0, tempWeb.find_first_of('/'));
	string instrGet = "GET " + tempWeb.substr(tempWeb.find_first_of('/')) + " HTTP/1.1" + "\r\n";
	string instrHost = "Host: " + host + "\r\n";
	string instrBlank = "\r\n";
	string auxString = "";

	client.startConnection(host.c_str());

	if (client.success()) {
		client.send_message(instrGet.c_str(), instrGet.size());
		client.send_message(instrHost.c_str(), instrHost.size());
		client.send_message(instrBlank.c_str(), instrBlank.size());

		bool getSize = true;
		bool leave = false;
		size_t len = 0;
		size_t totalSize;

		do {
			auxString += client.receiveMessage();
			len = auxString.size();
			if (webOK(auxString)) {

				if (getSize) {
					getSize = getFileSize(auxString, totalSize);
				}
			}
			else {
				cout << "ERROR";
				break;
			}


		} while (!leave && !end(auxString));
	}
	else
		cout << "Error: Client was never initialized";

	auxString = auxString.substr(0, auxString.find_last_of("</pre>"));
	return auxString;
	
}

string getTXTFile(string host_)
{
	client client;
	string tempWeb;

	if (host_.find("//") == string::npos)
		tempWeb = host_;
	else
		tempWeb = host_.substr(host_.find("//") + 2);

	string host = tempWeb.substr(0, tempWeb.find_first_of('/'));
	string instrGet = "GET " + tempWeb.substr(tempWeb.find_first_of('/')) + " HTTP/1.1" + "\r\n";
	string instrHost = "Host: " + host + "\r\n";
	string instrBlank = "\r\n";
	string auxString = "";

	client.startConnection(host.c_str());

	if (client.success()) {
		client.send_message(instrGet.c_str(), instrGet.size());
		client.send_message(instrHost.c_str(), instrHost.size());
		client.send_message(instrBlank.c_str(), instrBlank.size());

		bool getSize = true;
		bool leave = false;
		size_t len = 0;
		size_t totalSize;

		do {
			auxString += client.receiveMessage();
			len = auxString.size();
			if (webOK(auxString)) {

				if (getSize) {
					getSize = getFileSize(auxString, totalSize);
				}
			}
			else {
				cout << "ERROR";
				break;
			}


		} while (!leave && !endTXT(auxString,totalSize));
	}
	else
		cout << "Error: Client was never initialized";

	auxString = auxString.substr(0, auxString.find_last_of('\n'));
	return auxString;

}

bool endTXT(string& str, int size) {
	size_t init = str.find_first_of("\n\n") + strlen("\n\n");
	size_t end = str.find_last_of('\n');

	if (end - init >= size)
		return true;
	else
		return false;
}

bool webOK(string str)
{
	string temp = getHTTPCode(str);
	return (!temp.compare("200"));
}

bool getFileSize(string& str, size_t& size) {
	bool retValue;
	size_t place = str.find("Content-Length: ");
	if (place == string::npos)
		retValue = true;
	else {
		retValue = false;
		string num = str.c_str() + place + strlen("Content-Length: ");
		num = num.substr(0, num.find('\r'));
		size = atoi(num.c_str());
		string garbage = num.substr(0, num.find("<rss"));
		size += garbage.size();
	}

	return retValue;
}

string getHTTPCode(string str)
{
	string code, temp;

	temp = str.substr(str.find_first_of("HTTP/1.1 ") + strlen("HTTP/1.1 "));
	code = temp.substr(0, temp.find_first_of(' '));

	return code;
}

bool end(string file)
{
	bool retValue = false;

	if (file.find("</pre>") != string::npos)
		retValue = true;
	return retValue;
}
