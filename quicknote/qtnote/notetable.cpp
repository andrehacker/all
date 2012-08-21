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
    db_.execDML("INSERT INTO notes (title, content, tags) values ('Welcome to Quicknote', 'Delete this note and create your own!', ',DEV,');");
    db_.execDML("INSERT INTO notes (title, content, tags) values ('This is a second note', 'not so important this one', ',Personal,');");
    return true;    //TODO: separate method execDDL needed
}

std::vector<NoteDto> NoteTable::getNotes() {
    return getNotes("", std::vector<TagDto>());
}

std::vector<NoteDto> NoteTable::getNotes(const std::string &searchText) {
    return getNotes(searchText, std::vector<TagDto>());
}

std::vector<NoteDto> NoteTable::getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter) {

    std::string sql = "SELECT id, title, content, tags FROM notes where deleted=0";

    for (auto it = tagFilter.begin(); it != tagFilter.end(); ++it) {
        sql += " AND tags like '%," + it->getName() + ",%'";
    }
    if (searchText != "") {
        sql += " AND (title like '%" + searchText
            + "%' OR content like '%" + searchText + "%')";
    }

    std::vector<NoteDto> notes;
    std::unique_ptr<SqliteQuery> query = db_.execQuery(sql);
    if (query) {
        while (query->hasNext()) {
            notes.push_back(NoteDto(
                                query->getIntField("id"),
                                query->getStringField("title"),
                                query->getStringField("content"),
                                query->getStringField("tags")
                                ));
            query->nextRow();
        }
    }
    return notes;
}

bool NoteTable::add(NoteDto &newNote) {
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

bool NoteTable::update(const NoteDto &changedNote) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << changedNote.getId();
    std::string sql = "UPDATE notes SET title='" + changedNote.getTitle()
            + "', content='" + changedNote.getContent()
            + "', tags='" + changedNote.getTags() + "' WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}


bool NoteTable::remove(const NoteDto &note) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << note.getId();
    std::string sql = "UPDATE notes SET deleted=1 WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}

bool NoteTable::removeTagFromNotes(const std::string &tagName) {
    // TODO: This function must be called whenever a tag (with notes assigned) is deleted
    return false;
}


