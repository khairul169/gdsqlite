# GDSQLite

A [SQLite](https://www.sqlite.org/) wrapper for Godot Engine.

## Installation

To install, clone latest source of Godot Engine, drop the `gdsqlite` directory in the `godot/modules` directory and compile it.


Command line:
```
git clone https://github.com/godotengine/godot.git
cd godot/modules
git clone https://github.com/khairul169/gdsqlite.git
cd ../../
compile~
```

## Example

```python
extends Node

var db = SQLite.new();

func _ready():
	# Open SQL
	if db.open("user://data.sql") != db.SQLITE_OK:
		print("ERR: ", db.get_errormsg());
		return;
	
	# Create database if not exists
	db.prepare("CREATE TABLE IF NOT EXISTS players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, playcount INTEGER);");
	if db.step() != db.SQLITE_DONE:
		print("ERR: ", db.get_errormsg());
	db.finalize();
	
	# Select Operation
	db.prepare(str("SELECT * FROM players WHERE name = 'khairul' LIMIT 1;"));
	var rows = 0;
	var uid = -1;
	var playcount = 0;
	
	while true:
		var step = db.step_assoc();
		
		if step == db.SQLITE_ROW:
			print("ID: ", db.get_column_int_assoc("id"), " | Name: ", db.get_column_text_assoc("name"), " | Email: ", db.get_column_text_assoc("email"), " | Play Count: ", db.get_column_int_assoc("playcount"));
			
			uid = db.get_column_int_assoc("id");
			playcount = db.get_column_int_assoc("playcount");
			rows += 1;
		
		elif step == db.SQLITE_DONE:
			print("Fetch data completed.");
			print("Total result: ", rows);
			break;
		
		else:
			print("Fetch data failed.");
			print("ERR: ", db.get_errormsg());
			break;
	
	db.finalize();
	
	playcount += 1;
	
	if rows <= 0:
		# Insert Operation
		db.prepare(str("INSERT INTO players (name, email) VALUES ('khairul', '", escape_string("' \" \\n khairul169x@gmail.com"), "');"));
		if db.step() != db.SQLITE_DONE:
			print("ERR: ", db.get_errormsg());
		db.finalize();
	else:
		# Update Operation
		db.prepare(str("UPDATE players SET playcount='", playcount, "' WHERE id='", uid, "';"));
		if db.step() != db.SQLITE_DONE:
			print("ERR: ", db.get_errormsg());
		db.finalize();
	
	# Close SQL
	db.close();

func escape_string(string):
	return string.replace("'","''");
```

### Sample Output:

```
ID: 1 | Name: khairul | Email: ' " \n khairul169x@gmail.com | Play Count: 7
Fetch data completed.
Total result: 1
```

## Public Methods:
```
int open( String path )
void prepare( String query )
int step()
int step_assoc()
int get_data_count()
int get_column_count()
int get_column_int( int col )
int get_column_int_assoc( String col )
float get_column_double( int col )
float get_column_double_assoc( String col )
String get_column_text( int col )
String get_column_text_assoc( String col )
void finalize()
String get_errormsg()
void close()
```
## Constants:
```
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
```
