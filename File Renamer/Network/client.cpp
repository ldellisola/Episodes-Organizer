#include "client.h"


const string CLIENT_PORT = "80";

client::client() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	failure = 0;
}

client::~client() {
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

void client::startConnection(const char* host) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, CLIENT_PORT));
	cout << "Trying to connect to " << host << " on port " << CLIENT_PORT << endl;
	try {
		boost::asio::connect(*socket_forClient, endpoint);
	}
	catch (exception const&  ex) {
		cout << "could not connect" << '\n';
		failure = 1;
	}
}

bool client::success() {
	return !failure;
}

std::string client::receiveMessage() {
	boost::system::error_code error;
	char buf[PKGSIZE]; //El buffer debe ser del tamaño del paquete. 
	size_t len = 0;

	for (int i = 0; i < PKGSIZE; i++)
		buf[i] = 0;

	std::string auxString = "";
	do {
		len += this->socket_forClient->read_some(boost::asio::buffer(buf,PKGSIZE), error);
	} while (error.value() == WSAEWOULDBLOCK);

	if (error) {
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		failure = 1;
		return ERR_STR;
	}
	int a = 0;
	while (buf[a] != -52 && a < PKGSIZE) {
		auxString += buf[a++];
	}
	//auxString = buf;
	/*int lenght = (strlen(buf) >= PKGSIZE ? PKGSIZE : strlen(buf));
	for (int i = 0; (i < lenght); i++)
		auxString += buf[i];*/

	return auxString;
}

void client::nonblock(void)
{
	this->socket_forClient->non_blocking(true);
}
void client::send_message(const char *msg, int size) {
	size_t len;
	boost::system::error_code error;
	len = socket_forClient->write_some(boost::asio::buffer(msg, size), error);
}