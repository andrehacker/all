#ifndef NOTETABLE_H
#define NOTETABLE_H

#include <vector>
#include <string>
#include "NoteDTO.h"

class DatabaseConnection;   // forward declaration

class NoteTable
{
public:
    NoteTable(DatabaseConnection &);

    NoteTable& operator=(const NoteTable&) = delete;    // disallow copy/assignment
    NoteTable(const NoteTable&) = delete;    // disallow copy

    bool createTable();

    std::vector<NoteDto> getNotes();
    std::vector<NoteDto> getNotes(const std::string &searchText);
    std::vector<NoteDto> getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter);

    bool add(NoteDto &newNote);
    bool update(const NoteDto &changedNote);
    bool remove(const NoteDto &note);

    bool removeTagFromNotes(const std::string &tagName);

private:
    DatabaseConnection &db_;    // this is a dependency, not in our ownership, and may never be null (because it is a reference)
};

#endif // NOTETABLE_H
