#ifndef PRESENTER_H
#define PRESENTER_H

#include <memory>
#include "databaseconnection.h"

class AbstractView;

class Presenter
{
public:
    Presenter(DatabaseConnection &db, AbstractView &view);
    Presenter& operator=(const Presenter&) = delete;    // disallow copy/assignment
    Presenter(const Presenter&) = delete;    // disallow copy

    void optionsClicked();
    void newNoteClicked();

    void searchTextChanged(std::string text);

    void titleEditingFinished(NoteModel &changedNote);
    void contentEditingFinished(NoteModel &changedNote);

    void deleteNote(NoteModel &note);

    void resultSelectionChanged();
    void tagSelectionChanged();

private:
    AbstractView &view_; // dependency, not in our ownership
    DatabaseConnection &db_; // dependency, not in our ownership
};

#endif // PRESENTER_H
