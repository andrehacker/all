#include <QDebug>
#include "databaseconnection.h"

DatabaseConnection::DatabaseConnection()
    : sqlite_(std::unique_ptr<Sqlite>(new Sqlite())),
      noteTable_(*this) {
    openOrCreateDatabase();
}

void DatabaseConnection::openOrCreateDatabase() {
    bool dbExists = sqlite_->openExisting("notes.db");
    if (!dbExists) {
        createDatabase();
    }
}

int DatabaseConnection::execDML(const std::string sql) {
    return sqlite_->execDML(sql);
}

NoteTable &DatabaseConnection::getNoteTable() {
    return noteTable_;
}

std::unique_ptr<SqliteQuery> DatabaseConnection::execQuery(const std::string &sql) {
    return sqlite_->execQuery(sql);
}

std::unique_ptr<SqliteTable> DatabaseConnection::getTable(const char *sql) {
    return sqlite_->getTable(sql);
}

void DatabaseConnection::createDatabase() {
    sqlite_->openOrCreate("notes.db");

    noteTable_.createTable();
}

long long int DatabaseConnection::getLastInsertId() {
    return sqlite_->getLastInsertId();
}
