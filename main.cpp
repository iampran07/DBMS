#include <iostream>
#include "dbms.h"

void printMenu() {
    std::cout << "1. Create Table\n";
    std::cout << "2. Insert Row\n";
    std::cout << "3. Update Row\n";
    std::cout << "4. Remove Row\n";
    std::cout << "5. Select Table\n";
    std::cout << "6. Exit\n";
}

int main() {
    DBMS db;
    int choice;
    std::string tableName;
    std::vector<std::string> columns;
    std::unordered_map<std::string, std::string> row;
    std::string keyColumn, keyValue;
    std::unordered_map<std::string, std::string> newRow;

    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::cout << "Enter table name: ";
                std::getline(std::cin, tableName);
                std::cout << "Enter column names separated by space (end with enter): ";
                std::string column;
                while (std::cin >> column) {
                    columns.push_back(column);
                    if (std::cin.peek() == '\n')
                        break;
                }
                db.createTable(tableName, columns);
                break;
            }
            case 2: {
                std::cout << "Enter table name: ";
                std::getline(std::cin, tableName);
                std::cout << "Enter row data in format 'column=value' separated by space: ";
                std::string entry;
                while (std::getline(std::cin, entry, ' ')) {
                    size_t pos = entry.find('=');
                    if (pos != std::string::npos) {
                        row[entry.substr(0, pos)] = entry.substr(pos + 1);
                    }
                }
                db.insert(tableName, row);
                break;
            }
            case 3: {
                std::cout << "Enter table name: ";
                std::getline(std::cin, tableName);
                std::cout << "Enter key column: ";
                std::getline(std::cin, keyColumn);
                std::cout << "Enter key value: ";
                std::getline(std::cin, keyValue);
                std::cout << "Enter new row data in format 'column=value' separated by space: ";
                std::string entry;
                while (std::getline(std::cin, entry, ' ')) {
                    size_t pos = entry.find('=');
                    if (pos != std::string::npos) {
                        newRow[entry.substr(0, pos)] = entry.substr(pos + 1);
                    }
                }
                db.update(tableName, keyColumn, keyValue, newRow);
                break;
            }
            case 4: {
                std::cout << "Enter table name: ";
                std::getline(std::cin, tableName);
                std::cout << "Enter key column: ";
                std::getline(std::cin, keyColumn);
                std::cout << "Enter key value: ";
                std::getline(std::cin, keyValue);
                db.remove(tableName, keyColumn, keyValue);
                break;
            }
            case 5: {
                std::cout << "Enter table name: ";
                std::getline(std::cin, tableName);
                db.select(tableName);
                break;
            }
            case 6:
                return 0;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}
