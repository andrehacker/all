#ifndef NOTETABLE_H
#define NOTETABLE_H

#include <vector>
#include <string>
#include "notemodel.h"

class DatabaseConnection;   // forward declaration

class NoteTable
{
public:
    NoteTable(DatabaseConnection &);
    NoteTable& operator=(const NoteTable&) = delete;    // disallow copy/assignment
    NoteTable(const NoteTable&) = delete;    // disallow copy
    bool createTable();
    std::vector<NoteModel> getAll();
    NoteModel getNodeByGuid();
    std::vector<NoteModel> getNotesByText(const std::string);
    bool addNote(NoteModel &newNote);
    bool updateNote(const NoteModel &changedNote);
    bool deleteNote(const NoteModel &note);

private:
    DatabaseConnection &db_;    // this is a dependency, not in our ownership, and may never be null (because it is a reference)
};

#endif // NOTETABLE_H
