# DBMS in C++ - Simple Database Management System

A simple database management system implementation in C++ that provides basic database and table operations with file-based storage.

## Project Structure

```
SQL_IN_CPP/
├── database.cpp           # Database class implementation
├── database.h             # Database class header
├── main.cpp              # Main application entry point
├── table.cpp             # Table class implementation
├── table.h               # Table class header
├── Makefile              # Build configuration
├── README.md             # Project documentation
├── Databases/            # Database storage directory
│   ├── information_schema.csv    # Database registry
│   ├── baseDb/           # Default database
│   │   ├── tables.csv    # Table registry for baseDb
│   │   └── table1/       # Example table
│   │       ├── columns.csv       # Column definitions
│   │       └── data.csv          # Table data
│   └── db1/              # Example user database
│       ├── tables.csv    # Table registry for db1
│       └── table2/       # Example table
└── output/               # Build output directory
```

## Features

- **Database Management**: Create and manage multiple databases
- **Table Operations**: Create tables with custom column definitions
- **Data Types Support**: Support for INT32_t, FLOAT, STRING, BOOL, and TIMESTAMP
- **File-based Storage**: Persistent storage using CSV files
- **Automatic Initialization**: Creates necessary directories and files on startup

## Supported Data Types

The system supports the following data types mapped to integer IDs:

| Data Type | ID |
|-----------|----| 
| INT32_t   | 1  |
| FLOAT     | 2  |
| STRING    | 3  |
| BOOL      | 4  |
| TIMESTAMP | 5  |

## Core Classes

### Database Class (database.h / database.cpp)

- **Constructor**: `Database(string dbName)` - Creates or loads a database
- **Methods**:
  - `tableExists(const string &tableName)` - Check if a table exists
  - `currentDateTime()` - Generate timestamp strings

### Table Class (table.h / table.cpp)

Inherits from Database class and provides table-specific functionality:

- **Constructor**: `Table(string dbName, string tableName, vector<string> &columnName, vector<string> &type)`
- **Methods**:
  - `addRow(const vector<string> &rowData)` - Add data rows
  - `displayTable()` - Display table structure and data

## Building the Project

Use the provided `Makefile` to build the project:

```bash
# Build the project
make

# Clean build files
make clean
```

## Usage

The main application (main.cpp) demonstrates basic usage:

1. **System Initialization**: The `initializeDatabaseSystem()` function sets up the required directory structure and files
2. **Database Creation**: Create database instances using the Database constructor
3. **Table Creation**: Create tables with defined columns and data types

### Example Usage

```cpp
// Initialize the database system
initializeDatabaseSystem();

// Create a database
Database db("exampleDB");

// Create a table
vector<string> columnNames = {"id", "name", "age"};
vector<string> columnTypes = {"INT32_t", "STRING", "INT32_t"};
Table table("exampleDB", "exampleTable", columnNames, columnTypes);

// Add data
table.addRow({"1", "Alice", "30"});
table.addRow({"2", "Bob", "25"});

// Display table
table.displayTable();
```

## File Storage Structure

- **`Databases/information_schema.csv`**: Tracks all databases in the system
- **Database directories**: Each database has its own folder under `Databases/`
- **`tables.csv`**: Each database contains a registry of its tables
- **Table directories**: Each table has its own folder with:
  - `columns.csv`: Column definitions and metadata
  - `data.csv`: Actual table data

## Getting Started

1. Clone or download the project
2. Run `make` to build the executable
3. Execute the generated executable to start the application
4. The system will automatically create the necessary directory structure

## Dependencies

- C++11 or higher
- Standard C++ libraries (filesystem, iostream, fstream, etc.)
- Compatible with g++ compiler

This project provides a foundation for understanding database management concepts and file-based storage systems in C++.

