#include <vector>
#include <algorithm>
#include "presenter.h"
#include "abstractview.h"

Presenter::Presenter(DatabaseConnection &db, AbstractView &view) :
    view_(view),
    db_(db)
{
    view_.setPresenter(this);
    view_.showWindow();

    // Populate GUI with initial data
    std::vector<NoteModel> notes = db_.getNoteTable().getAll();
    view_.updateNotes(notes);

    // TODO: Subscribe to model for changes (e.g. after sync). Update UI afterwards
}


void Presenter::optionsClicked() {
    view_.showInfoMessageBox("Not yet implemented");
}

void Presenter::newNoteClicked() {
    // Remove search filter (if existing)
    view_.setSearchFilter("");

    // Add (empty) new note to model.
    // Passed note will be populated with new id
    NoteModel newNote(-1, "", "");
    db_.getNoteTable().addNote(newNote);

    // Update the UI-Mode (add new node at beginning and select)
    view_.addNewNote(newNote);
}

void Presenter::searchTextChanged(std::string text) {
    std::vector<NoteModel> notes = db_.getNoteTable().getNotesByText(text);
    view_.updateNotes(notes);
}

void Presenter::titleEditingFinished(NoteModel &changedNote) {
    // Update Title in Model
    db_.getNoteTable().updateNote(changedNote);

    // Update UI-Model (new title)
    view_.updateNote(changedNote);
}

void Presenter::contentEditingFinished(NoteModel &changedNote) {
    // Update Content in Model
    db_.getNoteTable().updateNote(changedNote);

    // Update UI-Model (new content)
    view_.updateNote(changedNote);
}

void Presenter::deleteNote(NoteModel &note) {
    // Mark as deleted in Model
    db_.getNoteTable().deleteNote(note);

    // Update UI
    view_.deleteNote(note);
}

void Presenter::resultSelectionChanged() {
    // Handled in view
}

void Presenter::tagSelectionChanged() {
    // TODO
}



