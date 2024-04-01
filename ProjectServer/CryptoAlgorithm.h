#pragma once
#include <string>
#include <iostream>

class CryptoAlgorithm
{
public:
	CryptoAlgorithm();
	~CryptoAlgorithm();
	virtual std::string encrypt(std::string message) = 0;
	virtual std::string decrypt(std::string cypher) = 0;
};