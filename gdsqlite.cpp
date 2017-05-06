/* gdsqlite.cpp */

#include "gdsqlite.h"
#include "globals.h"
#include "os/os.h"

SQLite::SQLite() {
}

int SQLite::open(String path) {
	if (path.begins_with("res://")) {
		if (GlobalConfig::get_singleton()) {
			String resource_path = GlobalConfig::get_singleton()->get_resource_path();
			if (resource_path != "") path = path.replace("res:/",resource_path);
			else path = path.replace("res://", "");
		}
	}
	else if (path.begins_with("user://")) {
		String data_dir=OS::get_singleton()->get_data_dir();
		if (data_dir != "") path = path.replace("user:/",data_dir);
		else path = path.replace("user://", "");
	}
	
	return sqlite3_open(path.utf8().get_data(), &db);
}

void SQLite::prepare(String query) {
	sqlite3_prepare_v2(db, query.utf8().get_data(), -1, &stmt, NULL);
}

int SQLite::step() {
	return sqlite3_step(stmt);
}

int SQLite::step_assoc() {
	int ret = sqlite3_step(stmt);
	if (_row_names.size() == 0) {
		for(unsigned int i = 0; i < sqlite3_column_count(stmt); ++i)
			_row_names[sqlite3_column_name(stmt,i)] = i;
	}
	return ret;
}

Array SQLite::fetch_assoc() {
	Array result;
	while (1) {
		int ret = sqlite3_step(stmt);
		if (ret == SQLITE_ROW) {
			Dictionary row;
			for(unsigned int i = 0; i < sqlite3_column_count(stmt); ++i) {
				int type = sqlite3_column_type(stmt, i);
				switch (type) {
					case SQLITE_INTEGER: row[sqlite3_column_name(stmt,i)] = sqlite3_column_int(stmt, i); break;
					case SQLITE_FLOAT: row[sqlite3_column_name(stmt,i)] = sqlite3_column_double(stmt, i); break;
					case SQLITE_TEXT: row[sqlite3_column_name(stmt,i)] = String::utf8((char *)sqlite3_column_text(stmt, i)); break;
					default: break;
				}
			}
			result.push_back(row);
		}
		else if (ret == SQLITE_DONE) {
			break;
		}
		else {
			break;
		}
	}
	return result;
}

Array SQLite::fetch_one() {
	Array result = fetch_assoc();
	if (result.size() <= 0) { return NULL; }
	return result[0];
}

Array SQLite::fetch_array(String query) {
	prepare(query);
	Array result = fetch_assoc();
	finalize();
	return result;
}

int SQLite::query(String query) {
	prepare(query);
	int ret = step();
	finalize();
	return ret;
}

int SQLite::get_data_count() {
	return sqlite3_data_count(stmt);
}

int SQLite::get_column_count() {
	return sqlite3_column_count(stmt);
}

int SQLite::get_column_int(int col) {
	return sqlite3_column_int(stmt, col);
}

double SQLite::get_column_double(int col) {
	return sqlite3_column_double(stmt, col);
}

String SQLite::get_column_text(int col) {
	return String::utf8((char *)sqlite3_column_text(stmt, col));
}

int SQLite::get_column_int_assoc(String col) {
	return sqlite3_column_int(stmt, _row_names[col]);
}

double SQLite::get_column_double_assoc(String col) {
	return sqlite3_column_double(stmt, _row_names[col]);
}

String SQLite::get_column_text_assoc(String col) {
	return String::utf8((char *)sqlite3_column_text(stmt, _row_names[col]));
}

void SQLite::finalize() {
	sqlite3_finalize(stmt);
	_row_names.clear();
}

String SQLite::get_errormsg() {
	return sqlite3_errmsg(db);
}

void SQLite::close() {
	sqlite3_close(db);
}

void SQLite::_bind_methods() {
	ClassDB::bind_method("open", &SQLite::open);
	ClassDB::bind_method("prepare", &SQLite::prepare);
	ClassDB::bind_method("step", &SQLite::step);
	ClassDB::bind_method("step_assoc", &SQLite::step_assoc);
	ClassDB::bind_method("fetch_assoc", &SQLite::fetch_assoc);
	ClassDB::bind_method("fetch_one", &SQLite::fetch_one);
	ClassDB::bind_method("fetch_array", &SQLite::fetch_array);
	ClassDB::bind_method("query", &SQLite::query);

	ClassDB::bind_method("get_data_count", &SQLite::get_data_count);
	ClassDB::bind_method("get_column_count", &SQLite::get_column_count);
	ClassDB::bind_method("get_column_int", &SQLite::get_column_int);
	ClassDB::bind_method("get_column_double", &SQLite::get_column_double);
	ClassDB::bind_method("get_column_text", &SQLite::get_column_text);
	ClassDB::bind_method("finalize", &SQLite::finalize);
	ClassDB::bind_method("get_errormsg", &SQLite::get_errormsg);
	ClassDB::bind_method("close", &SQLite::close);

	ClassDB::bind_method("get_column_int_assoc", &SQLite::get_column_int_assoc);
	ClassDB::bind_method("get_column_double_assoc", &SQLite::get_column_double_assoc);
	ClassDB::bind_method("get_column_text_assoc", &SQLite::get_column_text_assoc);
	
	BIND_CONSTANT(SQLITE_OK);
	BIND_CONSTANT(SQLITE_ERROR);
	BIND_CONSTANT(SQLITE_INTERNAL);
	BIND_CONSTANT(SQLITE_PERM);
	BIND_CONSTANT(SQLITE_ABORT);
	BIND_CONSTANT(SQLITE_BUSY);
	BIND_CONSTANT(SQLITE_LOCKED);
	BIND_CONSTANT(SQLITE_NOMEM);
	BIND_CONSTANT(SQLITE_READONLY);
	BIND_CONSTANT(SQLITE_INTERRUPT);
	BIND_CONSTANT(SQLITE_IOERR);
	BIND_CONSTANT(SQLITE_CORRUPT);
	BIND_CONSTANT(SQLITE_NOTFOUND);
	BIND_CONSTANT(SQLITE_FULL);
	BIND_CONSTANT(SQLITE_CANTOPEN);
	BIND_CONSTANT(SQLITE_PROTOCOL);
	BIND_CONSTANT(SQLITE_EMPTY);
	BIND_CONSTANT(SQLITE_SCHEMA);
	BIND_CONSTANT(SQLITE_TOOBIG);
	BIND_CONSTANT(SQLITE_CONSTRAINT);
	BIND_CONSTANT(SQLITE_MISMATCH);
	BIND_CONSTANT(SQLITE_MISUSE);
	BIND_CONSTANT(SQLITE_NOLFS);
	BIND_CONSTANT(SQLITE_AUTH);
	BIND_CONSTANT(SQLITE_FORMAT);
	BIND_CONSTANT(SQLITE_RANGE);
	BIND_CONSTANT(SQLITE_NOTADB);
	BIND_CONSTANT(SQLITE_NOTICE);
	BIND_CONSTANT(SQLITE_WARNING);
	BIND_CONSTANT(SQLITE_ROW);
	BIND_CONSTANT(SQLITE_DONE);
}

