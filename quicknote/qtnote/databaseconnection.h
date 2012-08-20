#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <memory>
#include "sqlite.h"
#include "notetable.h"

/*
  Database-independent interface to any sql-database.
  Makes the *Table classes independent of current sqlite implementation.
*/
class DatabaseConnection
{
public:
    DatabaseConnection();
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;    // disallow copy/assignment
    DatabaseConnection(const DatabaseConnection&) = delete;    // disallow copy
    int execDML(const std::string sql);
    NoteTable &getNoteTable();
    std::unique_ptr<SqliteQuery> execQuery(const std::string &sql);
    std::unique_ptr<SqliteTable> getTable(const char *sql);
    long long int getLastInsertId();

private:
    void openOrCreateDatabase();
    void createDatabase();
    std::unique_ptr<Sqlite> sqlite_;
    NoteTable noteTable_;
};

#endif // DATABASECONNECTION_H
