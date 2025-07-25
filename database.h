#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <string>
#include <ctime> // For currentDateTime()

using namespace std;
namespace fs = filesystem;

class Database
{
private:
    string name; // Database name

    vector<string> tables; // List of tables
    string currentDateTime(); // Helper function for timestamps

public:
    Database(string dbName = "baseDb");
    bool tableExists(const string &tableName);
};

#endif // DATABASE_H
