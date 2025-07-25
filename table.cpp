#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <string>
#include <ctime>      // For currentDateTime()
#include "database.h" // Include the header for the Database class

using namespace std;
namespace fs = filesystem;

// table class will inherit the database class
class Table : public Database
{
private:
    string tableName;                              // Table name
    unordered_map<string, pair<int, int>> columns; // column name -> (index, datatype ID)
    // vector<vector<string>> table;                  // 2D vector to store table data  // not need as it might overflow the memory


public:
    // Constructor to initialize columns
    Table()
    {
    }
    Table(string dbName = "baseDb", string tableName, vector<string> &columnName, vector<string> &type)
        : Database(dbName)
    {
        this->tableName = tableName;
        // checking if the table already exists
        if (tableExists(tableName))
        {
            cout << "Table already exists! Loading columns..." << endl;
            ifstream columnFile("./Database/" + name + "/" + tableName + "/columnNames.csv");
            
            string line, colName, dataType;
            int index, type;
            while (getline(columnFile, line))
                // column_name,data_type
            {
                stringstream ss(line);
                getline(ss, colName, ','); // column_name
                getline(ss, dataType, ','); // data_type
                getline(ss, index, ','); // index
                columns[colName] = {index, datatype[dataType]};
            }
            columnFile.close();
            
            return;
        }
        else
        {

            if (columnName.size() != type.size())
            {
                cout << "Column names and types size mismatch!" << endl;
                return;
            }
            bool valid = true;
            // Check if the column names are unique
            for (std::size_t i = 0; i < columnName.size(); i++)
            {
                if (columns.find(columnName[i]) != columns.end())
                {
                    valid = false;
                    break;
                }
            }
            // Initialize columns
            if (!valid)
            {
                cout << "Invalid column name" << endl;
                return;
            }
            ofstream columnFile("./Database/" + name + "/" + tableName + "/columnNames.csv");
            for (std::size_t i = 0; i < columnName.size(); i++)
            {
                columns[columnName[i]] = {i, datatype[type[i]]};
                columnFile << columnName[i] << "," << i << "," << datatype[type[i]] << endl;
            }
            columnFile.close();

            // Create table folder
            std::filesystem::create_directories("./Database/" + name + "/" + tableName);
            // Create default files
            ofstream dataFile("./Database/" + name + "/" + tableName + "/data.csv");
            dataFile.close();
        }
    }

    // Function to add a row of data
    void addRow(const vector<string> &rowData)
    {
        if (rowData.size() != columns.size())
        {
            cout << "Row size mismatch!" << endl;
            return;
        }
        table.push_back(rowData);
    }

    // Function to display table data
    void displayTable()
    {
        cout << "Table Structure:\n";
        for (const auto &col : columns)
        {
            cout << col.first << " (Index: " << col.second.first
                 << ", Datatype ID: " << col.second.second << ")\n";
        }
        cout << "\nTable Data:\n";
        for (const auto &row : table)
        {
            for (const auto &cell : row)
            {
                cout << cell << "\t";
            }
            cout << endl;
        }
    }
};
