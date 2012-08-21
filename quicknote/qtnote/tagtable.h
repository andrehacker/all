#ifndef TAGTABLE_H
#define TAGTABLE_H

#include <vector>
#include "tagdto.h"

class DatabaseConnection;   // forward decl.

class TagTable
{
public:
    TagTable(DatabaseConnection &);

    TagTable& operator=(const TagTable&) = delete;    // disallow copy/assignment
    TagTable(const TagTable&) = delete;    // disallow copy

    bool createTable();

    std::vector<TagDto> getAll();

    bool add(TagDto &newTag);
    bool update(const TagDto &changedTag);
    bool remove(const TagDto &tag);

private:
    DatabaseConnection &db_;    // this is a dependency, not in our ownership, and may never be null (because it is a reference)
};

#endif // TAGTABLE_H
