#include "SQLManager.h"

SQLManager* SQLManager::instance = nullptr;

SQLManager::SQLManager()
{
    cout << "SQL Manager up and running." << endl;
}

SQLManager* SQLManager::getInstance()
{
     if (instance == nullptr)
        instance = new SQLManager;
    return instance;
}

string SQLManager::makeCustomQuery(const wchar_t* query, int column)
{
    Query* temp_query = new Query;

    return temp_query->makeCustomQuery(query, column);
}

void SQLManager::destroyInstance()
{
    if (instance != nullptr){
        delete instance;
        instance = nullptr;
    }
}

string SQLManager::getAllUserNames()
{
    Query* temp_query = new Query;

    return temp_query->getAllUserNames();
}

int SQLManager::getUserRole(string uEmail)
{
    Query* temp_query = new Query;
    string query;

    query = "select UserRole from Users where Email = '" + uEmail + "'";
    return atoi(temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1).c_str());
}

int SQLManager::getUserID(string uEmail)
{
    Query* temp_query = new Query;
    string query;

    query = "select UserID from Users where Email = '" + uEmail + "'";
    return atoi(temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1).c_str());
}

string SQLManager::makeRangedQuery(const wchar_t* query, int column_start, int column_finish)
{
    Query* temp_query = new Query;
    return temp_query->makeRangedQuery(query, column_start, column_finish);
}

string SQLManager::getFullUserName(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select LastName + FirstName from Users where UserID = " + to_string(userID);
    return temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1);
}

string SQLManager::getUserFirstName(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select FirstName from Users where UserID = " + to_string(userID);
    return temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1);
}

string SQLManager::getUserLastName(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select LastName from Users where UserID = " + to_string(userID);
    return temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1);
}

string SQLManager::getUserEmail(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select Email from Users where UserID = " + to_string(userID);
    return temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1);
}

string SQLManager::getUserJoinedDate(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select JoinDate from Users where UserID = " + to_string(userID);
    return temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1);
}

int SQLManager::getUserStudyYear(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select StudyYear from Users where UserID = " + to_string(userID);
    return atoi(temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1).c_str());
}

string SQLManager::getUserStudyGroup(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select StudyGroup from Users where UserID = " + to_string(userID);
    return temp_query->makeCustomQuery(STR_TO_WSTR(query).c_str(), 1);
}

string SQLManager::getAllUserData(int userID)
{
    Query* temp_query = new Query;
    string query;

    query = "select * from Users where UserID = " + to_string(userID);
    return temp_query->makeRangedQuery(STR_TO_WSTR(query).c_str(), 1, 9);
}

bool SQLManager::authentifyUser(string mail_string, string password_string)
{
    Query* temp_query = new Query;
    wstring query_wstring;

    query_wstring = L"select Email + PasswordHash from Users where Email = '"  +
        STR_TO_WSTR(mail_string) +
        L"' and PasswordHash = '" +
        STR_TO_WSTR(password_string) +
        L"'";

    string return_string = temp_query->makeCustomQuery(query_wstring.c_str(), 1);

    if (return_string.length() != mail_string.length() + password_string.length() + 1) // +1 accounts for the space after the query ends
        return false;
    return true;
  
}

void SQLManager::insertNewStudent(string queryBuffer)
{
    Query* temp_query = new Query;
    string query;
    
    query = "USE Noodle INSERT INTO Users(LastName, FirstName, Email, PasswordHash, JoinDate, UserRole, StudyGroup, StudyYear) VALUES " +
        queryBuffer;

    temp_query->insertData(STR_TO_WSTR(query));
}

SQLManager::~SQLManager()
{
    destroyInstance();
    cout << "SQL Manager shutting down." << endl;
}