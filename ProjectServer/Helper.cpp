#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;
#define BYTES_TO_RECV 1024

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(const SOCKET sc)
{
	std::string msg = getPartFromSocket(sc, 3, 0);

	if (msg == "")
		return 0;

	int res = std::atoi(msg.c_str());
	return  res;
}


void Helper::send_update_message_to_client(const SOCKET sc, const string& file_content, const string& second_username, const string &all_users)
{
	//TRACE("all users: %s\n", all_users.c_str())
	const string code = std::to_string(MT_SERVER_UPDATE);
	const string current_file_size = getPaddedNumber(file_content.size(), 5);
	const string username_size = getPaddedNumber(second_username.size(), 2);
	const string all_users_size = getPaddedNumber(all_users.size(), 5);
	const string res = code + current_file_size + file_content + username_size + second_username + all_users_size + all_users;
	//TRACE("message: %s\n", res.c_str());
	sendData(sc, res);
}

// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return atoi(getPartFromSocket(sc, bytesNum, 0).c_str());
}

// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

// return string after padding zeros if necessary
string Helper::getPaddedNumber(const int num, const int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

// recieve data from socket according byteSize
// this is private function
std::string Helper::getPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

// send data to socket
// this is private function
void Helper::sendData(const SOCKET sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string Helper::getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);
	delete[] data;
	return received;
}

int Helper::convert4BytesToInt(char* bytes)
{
	int number = int((unsigned char)(bytes[1]) << 24 |
		(unsigned char)(bytes[2]) << 16 |
		(unsigned char)(bytes[3]) << 8 |
		(unsigned char)(bytes[4]));
	return number;
}

int Helper::getMessageCode(char* message)
{
	int number = message[0];
	return number;
}

std::string Helper::getDataFromMessage(char* message)
{
	std::string str = "";
	char data[BYTES_TO_RECV] = { 0 };
	int i = 0;
	int startFrom5 = 5;
	while (message[startFrom5] != NULL)
	{
		str += message[startFrom5];
		startFrom5++;
	}
	return str;
}

char* Helper::vectorToCharArray(std::vector<unsigned char> vector)
{
	char array[BYTES_TO_RECV] = { 0 };
	int i = 0;
	for (auto it = vector.begin(); it != vector.end(); it++)
	{
		array[i] = *it;
		i++;
	}
	return array;
}

std::vector<unsigned char> Helper::stringToVector(std::string str)
{
	std::vector<unsigned char> vector;
	vector.insert(vector.begin(), str.begin(), str.end());
	return vector;
}

std::string Helper::CharArrayToString(char* arr)
{
	int i = 0;
	std::string str = "";
	while (arr[i] != NULL)
	{
		str += arr[i];
		i++;
	}
	std::cout << str << std::endl;
	return str;
}

int Helper::lengthOfArray(char* arr)
{
	int i = 0;
	int length = 0;
	while (arr[i] != NULL)
	{
		length++;
		i++;
	}
	return length;
}