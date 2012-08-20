#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <vector>
#include "notemodel.h"

class Presenter;    // forward declaration

/*
Abstract class allowing the View to be accessed from the Presenter
*/
class AbstractView
{
public:
    virtual void setPresenter(Presenter *presenter) = 0;
    virtual void showWindow() = 0;
    virtual void setSearchFilter(const std::string &text) = 0;
    virtual std::string getSearchFilter() = 0;
    virtual void updateNotes(const std::vector<NoteModel> &notes) = 0;
    virtual void updateNote(const NoteModel &note) = 0;
    virtual void deleteNote(const NoteModel &note) = 0;
    virtual void addNewNote(NoteModel &newNote) = 0;
    virtual void showInfoMessageBox(std::string info) = 0;
};

#endif // ABSTRACTVIEW_H
