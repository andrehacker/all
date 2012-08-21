#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <vector>
#include "NoteDTO.h"

class Presenter;    // forward declaration

/*
Abstract class allowing the View to be accessed from the Presenter
*/
class AbstractView
{
public:
    virtual void showWindow() = 0;
    virtual void setSearchFilter(const std::string &text) = 0;
    virtual std::string getSearchFilter() = 0;
    virtual std::vector<TagDto> getSelectedTags() = 0;
    virtual void updateNotes(const std::vector<NoteDto> &notes) = 0;
    virtual void updateTags(const std::vector<TagDto> &tags) = 0;
    virtual void updateNote(const NoteDto &note) = 0;
    virtual void deleteNote(const NoteDto &note) = 0;
    virtual void addNewNote(NoteDto &newNote) = 0;
    virtual void showInfoMessageBox(std::string info) = 0;
};

#endif // ABSTRACTVIEW_H
