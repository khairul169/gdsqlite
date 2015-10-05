# GDSQLite

A [SQLite](https://www.sqlite.org/) wrapper for Godot Engine.

## Installation

To install, clone latest source of Godot Engine, drop the `gdsqlite` directory in the `godot/modules` directory and compile it.

## Example

```python
extends Node

var db = SQLite.new();

func _ready():
	# Open SQL
	if db.open("user://data.sql") != db.SQLITE_OK:
		print(db.get_errormsg());
		return;
	
	# Create database if not exists
	db.prepare("CREATE TABLE IF NOT EXISTS demo (name TEXT, age INTEGER);");
	if db.step() != db.SQLITE_DONE:
		print(db.get_errormsg());
	db.finalize();
	
	# Insert Operation
	randomize();
	var query = str("INSERT INTO demo (name, age) VALUES ('khairul_", int(rand_range(99,999)) ,"', '", int(rand_range(17,25)) ,"');");
	db.prepare(query);
	if db.step() != db.SQLITE_DONE:
		print(db.get_errormsg());
	db.finalize();
	
	# Select Operation
	db.prepare(str("SELECT name, age FROM demo WHERE age > 16;"));
	
	while db.step() == db.SQLITE_ROW:
		print(db.get_column_text(0), " is ", db.get_column_int(1), " years old");
	
	db.finalize();
	
	# Delete all data
	db.prepare("DELETE FROM demo;");
	if db.step() != db.SQLITE_DONE:
		print(db.get_errormsg());
	db.finalize();
	
	# Close SQL
	db.close();
```

### Sample Output:

```
khairul_898 is 20 years old
```

## Public Methods:

int open( String path )
void prepare( String query )
int step()
int get_data_count()
int get_column_count()
int get_column_int( int col )
float get_column_double( int col )
String get_column_text( int col )
void finalize()
String get_errormsg()
void close()

## Constants:

SQLITE_OK = 0
SQLITE_ERROR = 1
SQLITE_INTERNAL = 2
SQLITE_PERM = 3
SQLITE_ABORT = 4
SQLITE_BUSY = 5
SQLITE_LOCKED = 6
SQLITE_NOMEM = 7
SQLITE_READONLY = 8
SQLITE_INTERRUPT = 9
SQLITE_IOERR = 10
SQLITE_CORRUPT = 11
SQLITE_NOTFOUND = 12
SQLITE_FULL = 13
SQLITE_CANTOPEN = 14
SQLITE_PROTOCOL = 15
SQLITE_EMPTY = 16
SQLITE_SCHEMA = 17
SQLITE_TOOBIG = 18
SQLITE_CONSTRAINT = 19
SQLITE_MISMATCH = 20
SQLITE_MISUSE = 21
SQLITE_NOLFS = 22
SQLITE_AUTH = 23
SQLITE_FORMAT = 24
SQLITE_RANGE = 25
SQLITE_NOTADB = 26
SQLITE_NOTICE = 27
SQLITE_WARNING = 28
SQLITE_ROW = 100
SQLITE_DONE = 101
