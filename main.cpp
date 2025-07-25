#include "database.h"
#include "table.h"
#include <filesystem>
#include <fstream>
#include <iostream>

// Global unordered map for datatype mapping
unordered_map<string, int> datatype = {
    {"INT32_t", 1},
    {"FLOAT", 2},
    {"STRING", 3},
    {"BOOL", 4},
    {"TIMESTAMP", 5},
};

void initializeDatabaseSystem() {
    std::filesystem::path dbFolder = "Databases";
    std::filesystem::path schemaFile = dbFolder / "information_schema.csv";
    std::filesystem::path baseDb = dbFolder / "baseDb";

    // Check if the Databases folder exists, if not, create it
    if (!std::filesystem::exists(dbFolder)) {
        std::filesystem::create_directory(dbFolder);
    }

    // Check if the information_schema.csv file exists, if not, create it with default headings
    if (!std::filesystem::exists(schemaFile)) {
        std::ofstream schema(schemaFile);
        if (schema.is_open()) {
            schema << "databases_name,data_created\n";
            schema.close();
        } else {
            std::cerr << "Failed to create information_schema.csv file." << std::endl;
        }
    }

    // Check if the baseDb folder exists, if not, create it
    if (!std::filesystem::exists(baseDb)) {
        std::filesystem::create_directory(baseDb);
    }
    if(!std::filesystem::exists(baseDb / "tables.csv")) {
        std::ofstream tables(baseDb / "tables.csv");
        if (tables.is_open()) {
            tables << "table_name,date_created\n";
            tables.close();
        } else {
            std::cerr << "Failed to create tables.csv file." << std::endl;
        }
    }
}

int main()
{
    // Initialize the database system
    initializeDatabaseSystem();
    cout << "Database system initialized." << std::endl;
    // Example usage
    Database db("exampleDB");
    // vector<string> columnNames = {"id", "name", "age"};
    // vector<string> columnTypes = {"INT32_t", "STRING", "INT32_t"};
    // Table table("exampleTable", columnNames, columnTypes);

    // table.addRow({"1", "Alice", "30"});
    // table.addRow({"2", "Bob", "25"});

    // table.displayTable();

    return 0;
}
