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
	db.query("CREATE TABLE IF NOT EXISTS players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, playcount INTEGER);");
	
	# Select Operation
	for i in db.fetch_array("SELECT * FROM players LIMIT 100;"):
		print(i);
		
		# Update Operation
		db.query("UPDATE players SET playcount='"+str(i["playcount"]+1)+"' WHERE id='"+str(i["id"])+"';");
	
	# Insert Operation
	db.query("INSERT INTO players (name, email, playcount) VALUES ('khairul', 'my@mail.com', '0');");
	
	# Remove Operation
	db.query("DELETE FROM players WHERE playcount > '5';");
	
	db.close();
```

### Sample Output:

```
(email:my@mail.com), (id:14), (name:khairul), (playcount:5)
(email:my@mail.com), (id:15), (name:khairul), (playcount:4)
(email:my@mail.com), (id:16), (name:khairul), (playcount:3)
(email:my@mail.com), (id:17), (name:khairul), (playcount:2)
(email:my@mail.com), (id:18), (name:khairul), (playcount:1)
(email:my@mail.com), (id:19), (name:khairul), (playcount:0)
```

## Functions:
```
int open( String path )
void prepare( String query )
int step()
int step_assoc()
Array fetch_array( String query )
Array fetch_assoc()
Array fetch_one()
int query( String query )
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
