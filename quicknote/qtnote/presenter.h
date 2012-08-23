#ifndef PRESENTER_H
#define PRESENTER_H

#include <memory>
#include "databaseconnection.h"
#include "notesmanager.h"
#include "tagsmanager.h"

class AbstractView;

class Presenter
{
public:
    Presenter();
    Presenter& operator=(const Presenter&) = delete;    // disallow copy/assignment
    Presenter(const Presenter&) = delete;    // disallow copy
    ~Presenter();

    void optionsClicked();
    void newNoteClicked();

    void searchTextChanged(const std::string &text);

    void titleEditingFinished(NoteDto &changedNote);
    void tagsEditingFinished(NoteDto &changedNote);
    void contentEditingFinished(NoteDto &changedNote);

    void deleteNote(const NoteDto &note);

    void resultSelectionChanged();
    void tagSelectionChanged();

private:
    //std::unique_ptr<AbstractView> view_;
    AbstractView *view_;
    DatabaseConnection db_;
    NotesManager notesManager_;
    TagsManager tagsManager_;

    template <typename Derived>
    static void customDeleterForDerived(void *p) {
        delete static_cast<Derived>(p);
    }
};

#endif // PRESENTER_H
