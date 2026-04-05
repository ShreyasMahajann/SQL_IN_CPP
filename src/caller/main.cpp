#include "database.h"
#include "table.h"
#include "sqlparser.h"
#include <iostream>
#include <string>

using namespace std;

<<<<<<< Updated upstream
=======
#ifdef __EMSCRIPTEN__
EM_ASYNC_JS(char*, webReadLineRaw, (), {
  return Asyncify.handleSleep((wakeUp) => {
    if (typeof window.awaitInputLine !== "function") {
      wakeUp(0);
      return;
    }
    window.awaitInputLine().then((value) => {
      const text = String(value || "");
      const len = lengthBytesUTF8(text) + 1;
      const ptr = _malloc(len);
      stringToUTF8(text, ptr, len);
      wakeUp(ptr);
    });
  });
});
#endif

static string readLinePrompt(const string& prompt) {
    cout << prompt;
    cout.flush();
#ifdef __EMSCRIPTEN__
    char* raw = webReadLineRaw();
    if (raw == nullptr) {
        return "";
    }
    string line(raw);
    free(raw);
    return line;
#else
    string line;
    getline(cin, line);
    return line;
#endif
}

static int readIntPrompt(const string& prompt) {
    while (true) {
        string line = readLinePrompt(prompt);
        stringstream ss(line);
        int value;
        char extra;
        if ((ss >> value) && !(ss >> extra)) {
            return value;
        }
        cerr << "Invalid choice. Try again.\n";
    }
}

>>>>>>> Stashed changes
void sqlQueryMenu(Database& db) {
    while (true) {
        cout << "\nEnter SQL Query (or type EXIT to go back):\nSQL> ";
        string query;
        getline(cin, query);
        if (query == "EXIT") break;
        SQLParser::executeQuery(db, query);
    }
}

void tableOperationsMenu(Database& db) {
    int choice;
    while (true) {
        cout << "\nTable Operations Menu:\n";
        cout << "1. Create Table\n";
        cout << "2. Show Tables\n";
        cout << "3. Run SQL Query\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Prevent input buffer issues

        switch (choice) {
        case 1:
            cout << "Enter SQL CREATE TABLE query:\nSQL> ";
            {
                string query;
                getline(cin, query);
                SQLParser::executeQuery(db, query);
            }
            break;

        case 2:
            db.displayTables();
            break;

        case 3:
            sqlQueryMenu(db); // Call SQL Query Menu
            break;

        case 4:
            return; // Go back to Main Menu

        default:
            cerr << "Invalid choice. Try again.\n";
        }
    }
}

void mainMenu() {
    int choice;
    string dbName;
    Database db;

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Create Database\n";
        cout << "2. Select Database\n";
        cout << "3. Show Databases\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter database name: ";
            cin >> dbName;
            db = createDatabase(dbName);
            if (db.isValid()) {
                cout << "Database created successfully." << endl;
            } else {
                cerr << "Failed to create database." << endl;
            }
            break;

        case 2:
            cout << "Enter database name: ";
            cin >> dbName;
            db = selectDatabase(dbName);
            if (db.isValid()) {
                cout << "Database '" << dbName << "' selected successfully." << endl;
                tableOperationsMenu(db); // Enter Table Operations Menu
            } else {
                cerr << "Failed to select database '" << dbName << "'." << endl;
            }
            break;

        case 3:
            displayDatabases();
            break;

        case 4:
            cout << "Exiting...\n";
            return;

        default:
            cerr << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    initializeDatabaseSystem();
    cout << "Database system initialized." << endl;
    mainMenu();
    return 0;
}
