#include "notemodel.h"

NoteModel::NoteModel() :
    id_(-1), title_(""), content_("") {
}

// TODO: Extend!
NoteModel::NoteModel(int id, std::string title, std::string content) :
    id_(id), title_(title), content_(content) {
}

int NoteModel::getId() const {
    return id_;
}

std::string NoteModel::getTitle() const {
    return title_;
}

std::string NoteModel::getContent() const {
    return content_;
}

void NoteModel::setId(const long long int id) {
    id_ = id;
}

void NoteModel::setTitle(const std::string& title) {
    title_ = title;
}

void NoteModel::setContent(const std::string& content) {
    content_ = content;
}
