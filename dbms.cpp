#include "dbms.h"
#include <iostream>

void Table::addRow(const std::unordered_map<std::string, std::string>& row) {
    rows.push_back(row);
}

void Table::updateRow(int index, const std::unordered_map<std::string, std::string>& row) {
    for (const auto& [key, value] : row) {
        rows[index][key] = value;
    }
}

void Table::removeRow(int index) {
    rows.erase(rows.begin() + index);
}

void DBMS::createTable(const std::string& tableName, const std::vector<std::string>& columns) {
    tables[tableName] = Table{columns, {}};
}

void DBMS::insert(const std::string& tableName, const std::unordered_map<std::string, std::string>& row) {
    tables[tableName].addRow(row);
}

void DBMS::update(const std::string& tableName, const std::string& key, const std::string& newValue, const std::unordered_map<std::string, std::string>& row) {
    for (std::vector<std::unordered_map<std::string, std::string>>::size_type i = 0; i < tables[tableName].rows.size(); ++i) {
        if (tables[tableName].rows[i].find(key) != tables[tableName].rows[i].end()) {
            tables[tableName].rows[i][key] = newValue;
        }
    }
}

void DBMS::remove(const std::string& tableName, const std::string& key, const std::string& value) {
    for (std::vector<std::unordered_map<std::string, std::string>>::size_type i = 0; i < tables[tableName].rows.size(); ++i) {
        if (tables[tableName].rows[i].find(key) != tables[tableName].rows[i].end() && tables[tableName].rows[i][key] == value) {
            tables[tableName].rows.erase(tables[tableName].rows.begin() + i);
            --i; // Decrement i to stay at the same position after the erase
        }
    }
}  

void DBMS::select(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table not found." << std::endl;
        return;
    }

    for (const auto& column : tables[tableName].columns) {
        std::cout << column << "\t";
    }
    std::cout << std::endl;

    for (const auto& row : tables[tableName].rows) {
        for (const auto& column : tables[tableName].columns) {
            std::cout << row.at(column) << "\t";
        }
        std::cout << std::endl;
    }
}
