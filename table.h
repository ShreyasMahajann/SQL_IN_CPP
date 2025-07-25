#ifndef TABLE_H
#define TABLE_H

#include "database.h"

class Table : public Database
{
private:
    string tableName;                              // Table name
    unordered_map<string, pair<int, int>> columns; // column name -> (index, datatype ID)
    vector<vector<string>> table;                  // 2D vector to store table data

public:
    Table();
    Table(string tableName, vector<string> &columnName, vector<string> &type);
    void addRow(string tableName,const vector<string> &rowData);
    void displayTable(string tableName);
};

#endif // TABLE_H
