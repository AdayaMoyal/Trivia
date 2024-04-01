#include "OTPCryptoAlgorithm.h"

OTPCryptoAlgorithm::OTPCryptoAlgorithm()
{
	m_key = 0;
}

OTPCryptoAlgorithm::~OTPCryptoAlgorithm()
{
}

std::string OTPCryptoAlgorithm::encrypt(std::string message)
{
	std::string ecnryptedMsg = "";
	int key_id = rand();//i am going to assume the key_id does not exists
	std::string key = createKey(message,key_id);
	int indexKey = 0;
	for (char c : message)
	{
		std::bitset<8> bits(c);
		for (int i = 0; i < 8; i++)
		{
			ecnryptedMsg += xorFunction(bits[i], key[indexKey]);
			indexKey++;
		}
	}
	return ecnryptedMsg;
}

//does not matter for the project
std::string OTPCryptoAlgorithm::decrypt(std::string cypher)
{
	return std::string();
}


int OTPCryptoAlgorithm::getRandomNumber(int num1, int num2)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(num1, num2);
	return distribution(generator);
}

std::string OTPCryptoAlgorithm::createKey(std::string message,int key_id)
{
	std::string key = "";
	for (int i = 0; i < message.length() * 8; i++)
	{
		key += getRandomNumber(0, 1);
	}
	this->m_db->addNewKey(key, key_id);
	return key;
}

bool OTPCryptoAlgorithm::xorFunction(char ch1, char ch2)
{
	return ch1 != ch2;
}
