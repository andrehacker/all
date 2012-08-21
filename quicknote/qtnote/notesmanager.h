#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H
#include <vector>
#include <string>
#include "notetable.h"
#include "NoteDTO.h"

/*
  Logic to access any Notes.
  Currently this is only a wrapper around the table.
  Later this could be loading all notes into memory and serve as a buffer
*/
class NotesManager
{
public:
    NotesManager(DatabaseConnection &db);

    NotesManager& operator=(const NotesManager&) = delete;    // disallow copy assignment
    NotesManager(const NotesManager&) = delete;    // disallow copy

    bool createTable();

    std::vector<NoteDto> getNotes();
    std::vector<NoteDto> getNotes(const std::string searchText);
    std::vector<NoteDto> getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter);
    bool add(NoteDto &newNote);
    bool update(const NoteDto &changedNote);
    bool remove(const NoteDto &note);

private:
    NoteTable noteTable_;
};

#endif // NOTESMANAGER_H
