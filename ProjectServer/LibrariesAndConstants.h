#pragma once
#include "Communicator.h"
#include "Helper.h"
#include "IRequestHandler.h"
#include "json.hpp"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"
#include "MagshChat.h"
#include "RequestsStructs.h"
#include "ResponsesStructs.h"
#include "Server.h"
#include "WSAInitializer.h"


#include <WinSock2.h>
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <thread>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <map>
#include <mutex>
#include <ctime>
#include <Windows.h>

#define LENGTH_OF_FIRST_MESSAGE 5
#define BYTES_TO_RECV 1024
#define LENGTH_OF_ID 1
#define LENGTH_OF_CONTENT 4
#define CURRENT_TIME 0
#define LOGIN_REQUEST 200
#define SIGNUP_REQUEST 201
#define ERROR_MESSAGE 404
#define LOGIN_MESSAGE 100
#define SIGNUP_MESSAGE 101


// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

