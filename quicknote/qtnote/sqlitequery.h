#ifndef SQLITEQUERY_H
#define SQLITEQUERY_H

#include "sqlite3.h"

class SqliteQuery
{
public:
    /*SqliteQuery();*/
    SqliteQuery(sqlite3_stmt *preparedStatement, bool hasNext, sqlite3 *db);

    SqliteQuery& operator=(const SqliteQuery&) = delete;    // disallow copy
    SqliteQuery(const SqliteQuery&) = delete;    // disallow copy

    ~SqliteQuery();

    const std::string getStringField(int index, const std::string nullValue="");
    const std::string getStringField(const std::string name, const std::string nullValue="");
    int getIntField(int index, const int nullValue=0);
    int getIntField(const std::string name, const int nullValue=0);
    long long int getInt64Field(int index, long long int nullValue=0);
    long long int getInt64Field(const std::string name, long long int nullValue=0);
    double getDoubleField(int index, double nullValue=0.0);
    double getDoubleField(const std::string name, double nullValue=0.0);
    const unsigned char* getBlobField(int index, int& nLen);
    const unsigned char* getBlobField(const std::string name, int& nLen);

    bool fieldIsNull(int index);
    bool fieldIsNull(const std::string name);

    bool hasNext();
    void nextRow();


private:
    int getFieldIndexByName(const std::string &);
    int getFieldDataType(int col);

    sqlite3_stmt *preparedStatement_;

    bool hasNext_;
    int cols_;

    sqlite3 *db_;        // This is a dependency, not our ownership

};

#endif // SQLITEQUERY_H
