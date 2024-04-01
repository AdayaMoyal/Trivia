#include "SqliteDatabase.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include "RequestsStructs.h"

std::string dbFileName = "TriviaDB.sqlite";

SqliteDatabase::SqliteDatabase()
{
    open();
}

SqliteDatabase::~SqliteDatabase()
{

}

bool SqliteDatabase::open()
{
    int file_exist = _access(dbFileName.c_str(), 0);
    int res = sqlite3_open(dbFileName.c_str(), &this->_db);
    if (res != SQLITE_OK) {
        this->_db = nullptr;
        std::cout << "Failed to open DB" << std::endl;
        return false;
    }
    if (file_exist != 0) {
        //building USERS table
        const char* sqlStatement = "CREATE TABLE USERS (ID INTEGER PRIMARY KEY, USER_NAME TEXT NOT NULL,PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL); ";
        const char* createQuestions = "CREATE TABLE QUESTIONS (ID INTEGER PRIMARY KEY, QUESTION TEXT NOT NULL,ANSWER1 TEXT NOT NULL, ANSWER2 TEXT NOT NULL, ANSWER3 TEXT NOT NULL, ANSWER4 TEXT NOT NULL, RIGHT_ANSWER TEXT NOT NULL); ";
        const char* createStatistics = "CREATE TABLE STATISTICS (USER_NAME TEXT PRIMARY KEY, TIME REAL NOT NULL,COUNT_RIGHTS INTEGER NOT NULL, COUNT_QUESTIONS INTEGER NOT NULL, COUNT_GAMES INTEGER NOT NULL); ";
        const char* createEncryption = "CREATE TABLE ENCRYPTION (KEY_ID INTEGER NOT NULL, KEY TEXT NOT NULL); ";
        char* errMessage = nullptr;
        res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
        res = sqlite3_exec(this->_db, createQuestions, nullptr, nullptr, &errMessage);
        res = sqlite3_exec(this->_db, createStatistics, nullptr, nullptr, &errMessage);
        res = sqlite3_exec(this->_db, createEncryption, nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cout << "false" << std::endl;
            return false;
        }
        insertQuestion();
    }
    return true;
}

bool SqliteDatabase::close()
{
    sqlite3_close(this->_db);
    this->_db = nullptr;
    return true;
}

int callbackId(void* data, int argc, char** argv, char** azColName)
{
    int* numId = (int*)data;
    *numId = atoi(argv[0]);
    return 0;
}

void SqliteDatabase::runQuery(std::string query)
{
    const char* sqlStatement = query.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}

void SqliteDatabase::insertQuestion()
{
    std::fstream file;
    file.open("C:/Users/test0/trivia_adaya_and_shai_2023/Trivia/ProjectServer/Questions.txt", std::ios::in);
    std::string question;
    while (std::getline(file, question))
    {
        runQuery(question);
    }
}

bool SqliteDatabase::doesUserExist(std::string user_name)
{
    int existOrNot = 0;
    std::string querydoesUserExist = "SELECT COUNT(ID) FROM USERS WHERE USER_NAME == \"" + user_name + "\";";
    const char* sqlStatement = querydoesUserExist.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, sqlStatement, callbackId, &existOrNot, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cout << "Error: " << errMessage << std::endl;
    }
    if (existOrNot == 0)
        return false;
    return true;
}

bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
    int existOrNot = 0;
    std::string request = "SELECT COUNT(ID) FROM USERS WHERE USER_NAME == \"" + username + "\" AND PASSWORD == \"" + password + "\"; ";
    const char* doesPasswordMatch = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, doesPasswordMatch, callbackId, &existOrNot, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cout << "Error: " << errMessage << std::endl;
    }
    if (existOrNot == 0)
    {
        return false;
    }
    return true;
}

void SqliteDatabase::addNewUser(std::string user_name, std::string password, std::string email)
{
    int lastId = 0;
    std::string request = "SELECT count(ID) FROM USERS; ";
    const char* createUser = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, createUser, callbackId, &lastId, &errMessage);
    if (lastId > 0)
    {
        request = "SELECT max(ID) FROM USERS; ";
        createUser = request.c_str();
        errMessage = nullptr;
        res = sqlite3_exec(this->_db, createUser, callbackId, &lastId, &errMessage);
    }
    lastId++;
    std::string queryaddNewUser = "INSERT INTO USERS VALUES("+std::to_string(lastId)+", \"" + user_name + "\" ,\"" + password + "\" ,\"" + email + "\");";
    const char* sqlStatement = queryaddNewUser.c_str();
    errMessage = nullptr;
    res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
    std::string queryAddStatistics = "INSERT INTO STATISTICS VALUES( \"" + user_name + "\" , 0.00, 0, 0, 0);";
    sqlStatement = queryAddStatistics.c_str();
    errMessage = nullptr;
    res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}

int callbackFloat(void* data, int argc, char** argv, char** azColName)
{
    float* numId = (float*)data;
    *numId = atoi(argv[0]);
    return 0;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
    float time = 0.00000;
    std::string request = "SELECT (TIME) FROM STATISTICS WHERE USER_NAME == \"" + username + "\"; ";
    const char* getTime = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, getTime, callbackFloat, &time, &errMessage);
    return time;
}

void SqliteDatabase::updatePlayer(std::string username, int correctAnswers, int countQuestion, float playerTotalTime)
{
    updatePlayersTotalAnswers(username, countQuestion);
    updateNumOfCorrectAnswers(username, correctAnswers);
    updatePlayersGame(username);
    updatePlayersTotalTime(username, playerTotalTime);
}

void SqliteDatabase::updatePlayersTotalTime(std::string username, float playerTotalTime)
{
    std::string queryUpdatePlayersTotalTime = "UPDATE STATISTICS SET TIME = " + std::to_string(playerTotalTime) + " WHERE USER_NAME == \"" + username + "\"; ";
    const char* sqlStatement = queryUpdatePlayersTotalTime.c_str();
    char* errMessage = nullptr;
    sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}

void SqliteDatabase::updatePlayersTotalAnswers(std::string username, int countQuestion)
{
    int numOfTotalAnswers = getNumOfTotalAnswers(username);
    std::string queryUpdatePlayersTotalQuestions = "UPDATE STATISTICS SET COUNT_QUESTIONS = " + std::to_string(numOfTotalAnswers + countQuestion)+ " WHERE USER_NAME == \"" + username + "\"; ";;
    const char* sqlStatement = queryUpdatePlayersTotalQuestions.c_str();
    char* errMessage = nullptr;
    sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
    int countRights = 0;
    std::string request = "SELECT (COUNT_RIGHTS) FROM STATISTICS WHERE USER_NAME == \"" + username + "\"; ";
    const char* getCountRights = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, getCountRights, callbackId, &countRights, &errMessage);
    return countRights;
}

void SqliteDatabase::updateNumOfCorrectAnswers(std::string username,int numOfCorrectAnswers)
{
    int correctAnswers = getNumOfCorrectAnswers(username);
    std::string queryUpdateNumOfCorrectAnswers = "UPDATE STATISTICS SET COUNT_RIGHTS = " + std::to_string(correctAnswers + numOfCorrectAnswers) + " WHERE USER_NAME == \"" + username + "\"; ";;
    const char* sqlStatement = queryUpdateNumOfCorrectAnswers.c_str();
    char* errMessage = nullptr;
    sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}


int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
    int totalAnswers = 0;
    std::string request = "SELECT (COUNT_QUESTIONS) FROM STATISTICS WHERE USER_NAME == \"" + username + "\"; ";
    const char* getTotalAnswers = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, getTotalAnswers, callbackId, &totalAnswers, &errMessage);
    return totalAnswers;
}

int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
    int playerGames = 0;
    std::string request = "SELECT (COUNT_GAMES) FROM STATISTICS WHERE USER_NAME == \"" + username + "\"; ";
    const char* getPlayerGames = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, getPlayerGames, callbackId, &playerGames, &errMessage);
    return playerGames;
}

void SqliteDatabase::updatePlayersGame(std::string username)
{
    int games = getNumOfPlayerGames(username);
    std::string queryUpdatePlayersGame = "UPDATE STATISTICS SET COUNT_GAMES = " + std::to_string(games + 1) + " WHERE USER_NAME == \"" + username + "\"; ";
    const char* sqlStatement = queryUpdatePlayersGame.c_str();
    char* errMessage = nullptr;
    sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}

float SqliteDatabase::getPlayerScore(std::string username)
{
    if (getNumOfTotalAnswers(username) == 0)
    {
        return 0;
    }
    float playerScore = (getNumOfCorrectAnswers(username) * 60 /100) + (getPlayerAverageAnswerTime(username) * 40/100);
    return playerScore;
}

int saveUsersNamesCallback(void* data, int argc, char** argv, char** azColName)
{
    std::list<std::string>* copyOfUsersNameLists = (std::list<std::string>*)data;
    for (int i = 0; i < argc; i++)
    {
        copyOfUsersNameLists->push_back(argv[i]);
    }
    return 0;
}

std::vector<std::string> SqliteDatabase::getHighScores()
{
    std::vector<std::string> vectorH;//vector of the five highest scores
    std::list<std::string> list;
    std::string request = "SELECT USER_NAME FROM USERS;";
    const char* getNames = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, getNames, saveUsersNamesCallback, &list, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cout << "Error" << std::endl;
    }
    int size = list.size();
    for (int i = 0; i < size; i++)
    {
        vectorH.push_back(getMaxScore(list));
        list.remove(getMaxScoreName(list));
    }
    return vectorH;
}

std::string SqliteDatabase::getMaxScore(std::list<std::string> list)
{
    float maxScore = -1;//score cannot be negative
    std::string maxScoreUser = "";
    for (auto it = list.begin(); it !=list.end(); it++)
    {
        if (getPlayerScore(*it) > maxScore)
        { 
            maxScore = getPlayerScore(*it);
            maxScoreUser = *it;
        }
    }
    maxScoreUser += " - " + std::to_string(maxScore);
    return maxScoreUser;
}

std::string SqliteDatabase::getMaxScoreName(std::list<std::string> list)
{
    float maxScore = -1;//score cannot be negative
    std::string maxScoreUser = "";
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (getPlayerScore(*it) > maxScore)
        {
            maxScore = getPlayerScore(*it);
            maxScoreUser = *it;
        }
    }
    return maxScoreUser;
}

int saveQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
    std::list<Question>* copyOfQuestionLists = (std::list<Question>*)data;
    std::string questionStr = argv[1];
    std::vector<std::string> possibleAnswers;
    possibleAnswers.push_back(argv[2]);
    possibleAnswers.push_back(argv[3]);
    possibleAnswers.push_back(argv[4]);
    possibleAnswers.push_back(argv[5]);
    std::string answer = argv[6];
    Question question(questionStr, possibleAnswers, answer);
    copyOfQuestionLists->push_back(question);
    return 0;
}

std::vector<Question> SqliteDatabase::getQuestions(int numOfQuestions)
{
    int count = 1;
    std::list<Question> list;
    std::vector<Question> questions;
    std::string request = "SELECT * FROM QUESTIONS;";
    const char* getQuestions = request.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, getQuestions, saveQuestionsCallback, &list, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cout << "Error" << std::endl;
    }
    std::vector<Question> allOfTheQuestions(list.begin(), list.end());
    std::random_device random;
    std::default_random_engine shuffleItems(random());
    shuffle(allOfTheQuestions.begin(), allOfTheQuestions.end(), shuffleItems);
    for (auto it = allOfTheQuestions.begin(); it != allOfTheQuestions.end(); it++)
    {
        questions.push_back(*it);
        if (count == numOfQuestions)
        {
            break;
        }
        count++;
    }
    return questions;
}


void SqliteDatabase::addNewKey(std::string key, int id_key)
{
    std::string queryUpdatePlayersGame = "INSERT INTO ENCRYPTION (KEY,KEY_ID) VALUES (‘"+key+"’"+", ‘" "+ id_key +" "’""""); ";
    const char* sqlStatement = queryUpdatePlayersGame.c_str();
    char* errMessage = nullptr;
    sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
}

void SqliteDatabase::addQuestion(AddQuestionRequest request)
{
    int lastId = 0;
    std::fstream file;
    std::string getId = "SELECT count(ID) FROM QUESTIONS; ";
    const char* createQuestion = getId.c_str();
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_db, createQuestion, callbackId, &lastId, &errMessage);
    if (lastId > 0)
    {
        getId = "SELECT max(ID) FROM QUESTIONS; ";
        createQuestion = getId.c_str();
        errMessage = nullptr;
        res = sqlite3_exec(this->_db, createQuestion, callbackId, &lastId, &errMessage);
    }
    lastId++;
    std::string addQuestionToDB = "INSERT INTO QUESTIONS VALUES(" + std::to_string(lastId) + ", \""+ request.question+"\", \""+ request.answer1+"\" ,\""+ request.answer2+"\",\"" + request.answer3 + "\" ,\"" + request.answer4 + "\", \"" + request.rightAnswer + "\");";
    createQuestion = addQuestionToDB.c_str();
    errMessage = nullptr;
    res = sqlite3_exec(this->_db, createQuestion, nullptr, nullptr, &errMessage);
}
