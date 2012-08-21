#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include <vector>
#include <string>
#include "tagtable.h"
#include "tagdto.h"

class TagsManager
{
public:
    TagsManager(DatabaseConnection &db);

    TagsManager& operator=(const TagsManager&) = delete;    // disallow copy assignment
    TagsManager(const TagsManager&) = delete;    // disallow copy

    bool createTable();

    std::vector<TagDto> getAll();

    bool add(TagDto &newTag);
    bool update(const TagDto &changedTag);
    bool remove(const TagDto &tag);

private:
    TagTable tagTable_;
};

#endif // TAGSMANAGER_H
