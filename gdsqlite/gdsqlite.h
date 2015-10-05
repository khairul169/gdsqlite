/* gdsqlite.h */
#ifndef GDSQLITE_H
#define GDSQLITE_H

#include "reference.h"
#include "ustring.h"

#include "sqlite/sqlite3.h"

class SQLite : public Reference {
	OBJ_TYPE(SQLite,Reference);

protected:
	static void _bind_methods();

public:
	SQLite();
	
	int open(String path);
	
	void prepare(String query);
	int step();
	int get_data_count();
	int get_column_count();
	int get_column_int(int col);
	double get_column_double(int col);
	String get_column_text(int col);

	void finalize();
	String get_errormsg();
	void close();

private:
	sqlite3 *db;
	sqlite3_stmt *stmt;
};

#endif
