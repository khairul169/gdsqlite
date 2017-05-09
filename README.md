# GDSQLite

A [SQLite](https://www.sqlite.org/) wrapper for Godot Engine.

### For Godot 3.0, you don't need to recompile the whole engine, just use https://github.com/khairul169/gdsqlite-native for easy usage.

## Installation

To install, clone latest stable version of Godot Engine, drop the `gdsqlite` directory in the `godot/modules` directory and compile it.


Command line:
```
git clone -b 2.2 https://github.com/godotengine/godot.git
cd godot/modules
git clone https://github.com/khairul169/gdsqlite.git
cd ../../
scons
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

## Functions:
```
int open( String path )
String get_errormsg()

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
void close()
```
