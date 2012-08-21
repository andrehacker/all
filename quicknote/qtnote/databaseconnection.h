#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <memory>
#include "sqlite.h"
#include "notetable.h"

/*
  Database-independent interface to any sql-database.
  Makes the *Table classes independent of the underlying database
*/
class DatabaseConnection
{
public:
    DatabaseConnection();
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;    // disallow copy/assignment
    DatabaseConnection(const DatabaseConnection&) = delete;    // disallow copy
    bool openExisting();
    void createDatabaseAndOpen();
    int execDML(const std::string &sql);
    std::unique_ptr<SqliteQuery> execQuery(const std::string &sql);
    std::unique_ptr<SqliteTable> getTable(const std::string &sql);
    long long int getLastInsertId();

private:
    std::unique_ptr<Sqlite> sqlite_;
    const std::string kDatabaseFileName_;
};

#endif // DATABASECONNECTION_H
