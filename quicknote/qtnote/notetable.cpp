#include <QDebug>
#include <sstream>
#include "notetable.h"
#include "databaseconnection.h"

NoteTable::NoteTable(DatabaseConnection &db)
    : db_(db)
{

}

bool NoteTable::createTable()
{
    // Column id will be an alias for sqlites internal rowid.
    // See http://www.sqlite.org/lang_createtable.html#rowid
    db_.execDML("CREATE TABLE notes (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, title TEXT NOT NULL, content TEXT NOT NULL, deleted INTEGER DEFAULT 0 NOT NULL, tags TEXT NOT NULL)");
    db_.execDML("INSERT INTO notes (title, content, tags) values ('Welcome to Quicknote', 'Delete this note and create your own!', '');");
    db_.execDML("INSERT INTO notes (title, content, tags) values ('This is a second note', 'not so important this one', '');");
    return true;    //TODO: separate method execDDL needed
}

std::vector<NoteModel> NoteTable::getAll()
{
    std::vector<NoteModel> notes;
    std::unique_ptr<SqliteQuery> query = db_.execQuery("SELECT id, title, content FROM notes WHERE deleted=0");
    if (query) {
        while (query->hasNext()) {
            notes.push_back(NoteModel(
                                query->getIntField("id"),
                                query->getStringField("title"),
                                query->getStringField("content")
                                ));
            query->nextRow();
        }
    }
    return notes;
}

std::vector<NoteModel> NoteTable::getNotesByText(const std::string text) {
    std::vector<NoteModel> notes;
    std::unique_ptr<SqliteQuery> query = db_.execQuery("SELECT id, title, content FROM notes where deleted=0 AND (title like '%" + text + "%' OR content like '%" + text + "%')");
    if (query) {
        while (query->hasNext()) {
            notes.push_back(NoteModel(
                                query->getIntField("id"),
                                query->getStringField("title"),
                                query->getStringField("content")
                                ));
            query->nextRow();
        }
    }
    return notes;
}

bool NoteTable::addNote(NoteModel &newNote) {
    std::string sql = "INSERT INTO notes (title, content, tags) VALUES ('"
            + newNote.getTitle() + "', '"
            + newNote.getContent() + "', '');";

    if (db_.execDML(sql) > 0) {
        // Update note id!
        // notes.id is an alias for sqlites rowid, so no problem to use the returned rowid as id
        newNote.setId(db_.getLastInsertId());

        return true;
    }
    return false;
}

bool NoteTable::updateNote(const NoteModel &changedNote) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << changedNote.getId();
    std::string sql = "UPDATE notes SET title='" + changedNote.getTitle()
            + "', content='" + changedNote.getContent() + "' WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}


bool NoteTable::deleteNote(const NoteModel &note) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << note.getId();
    std::string sql = "UPDATE notes SET deleted=1 WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}


