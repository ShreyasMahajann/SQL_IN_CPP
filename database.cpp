#include "database.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
using namespace std;

string Database::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return string(buf);
}

Database::Database(string dbName)
{
    name = dbName;

    // Load information_schema from information_schema.csv
    ifstream file("./Databases/information_schema.csv");
    if (!file.is_open())
    {
        cerr << "Failed to open information_schema.csv" << endl;
        return;
    }

    string line;
    bool databaseExists = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string database_name, date_created;
        getline(ss, database_name, ',');
        getline(ss, date_created, ',');

        if (database_name == name)
        {
            databaseExists = true;
            break;
        }
    }
    file.close();

    if (databaseExists)
    {
        cout << "Loading existing database: " << name << endl;

        ifstream dbFile("./Database/" + name + "/tables.csv");
        if (!dbFile.is_open())
        {
            cerr << "Failed to open " << name << "/tables.csv" << endl;
            return;
        }

        // Read existing table names from file
        while (getline(dbFile, line))
        {
            stringstream ss(line);
            string table_name;
            getline(ss, table_name, ','); // Read only table name
            if (!table_name.empty() && table_name != "table_name")
            {
                tables.push_back(table_name);
            }
        }
        dbFile.close();
    }
    else
    {
        // Create new database directory
        filesystem::create_directories("./Database/" + name);
        cout << "Creating new database: " << name << endl;

        ofstream infoFile("./Databases/information_schema.csv", ios::app);
        infoFile << name << "," << currentDateTime() << endl;
        infoFile.close();

        ofstream tableFile("./Database/" + name + "/tables.csv");
        tableFile << "table_name,date_created" << endl;
        tableFile.close();
    }
}

bool Database::tableExists(const string &tableName)
{
    return find(tables.begin(), tables.end(), tableName) != tables.end();
}
