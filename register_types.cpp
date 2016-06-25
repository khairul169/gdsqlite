/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"

#include "gdsqlite.h"

void register_gdsqlite_types() {

        ObjectTypeDB::register_type<SQLite>();
}

void unregister_gdsqlite_types() {
   //nothing to do here
}
