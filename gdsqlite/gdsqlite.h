/* gdsqlite.h */
#ifndef GDSQLITE_H
#define GDSQLITE_H

#include "reference.h"
#include "ustring.h"

#include "map.h"
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
	int step_assoc();
	int get_data_count();
	int get_column_count();
	int get_column_int(int col);
	double get_column_double(int col);
	String get_column_text(int col);
	int get_column_int_assoc(String col);
	double get_column_double_assoc(String col);
	String get_column_text_assoc(String col);

	void finalize();
	String get_errormsg();
	void close();

private:
	sqlite3 *db;
	sqlite3_stmt *stmt;

	Map<String, unsigned int> _row_names;
};

#endif
