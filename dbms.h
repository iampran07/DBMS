#ifndef DBMS_H
#define DBMS_H

#include <vector>
#include <string>
#include <unordered_map>

class Table {
public:
    std::vector<std::string> columns;
    std::vector<std::unordered_map<std::string, std::string>> rows;

    void addRow(const std::unordered_map<std::string, std::string>& row);
    void updateRow(int index, const std::unordered_map<std::string, std::string>& row);
    void removeRow(int index);
};

class DBMS {
private:
    std::unordered_map<std::string, Table> tables;

public:
    void createTable(const std::string& tableName, const std::vector<std::string>& columns);
    void insert(const std::string& tableName, const std::unordered_map<std::string, std::string>& row);
    void update(const std::string& tableName, const std::string& keyColumn, const std::string& keyValue, const std::unordered_map<std::string, std::string>& newRow);
    void remove(const std::string& tableName, const std::string& keyColumn, const std::string& keyValue);
    void select(const std::string& tableName);
};

#endif // DBMS_H
