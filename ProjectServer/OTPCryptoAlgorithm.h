#pragma once
#include "CryptoAlgorithm.h"
#include "IDatabase.h"
#include <bitset>
#include <random>

class OTPCryptoAlgorithm :public CryptoAlgorithm
{
public:
	OTPCryptoAlgorithm();
	~OTPCryptoAlgorithm();
	std::string encrypt(std::string message);
	std::string decrypt(std::string cypher);
	int getRandomNumber(int num1, int num2);
	std::string createKey(std::string message,int);
	bool xorFunction(char, char);
private:
	IDatabase* m_db;
	int m_key;
};