#ifndef SQLITETABLE_H
#define SQLITETABLE_H

class SqliteTable
{
public:
    SqliteTable(char **result, int numberRows, int numberCols);
    SqliteTable& operator=(const SqliteTable&) = delete;    // disallow copy
    SqliteTable(const SqliteTable&) = delete;    // disallow copy
    ~SqliteTable();

    const char* getField(int row, int column);
    const char* getColumnName(int column);
    const int numberRows();
    const int numberCols();

private:
    char **result_;
    int numberRows_;
    int numberCols_;
    int currentRow_;
};

#endif // SQLITETABLE_H
