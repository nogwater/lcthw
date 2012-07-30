#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Address {
	int id;
	int set;
	int age;
	char *name;
	char *email;
};

struct Database {
	int max_data;
	int max_rows;
	struct Address **rows;
};

struct Connection {
	FILE *file;
	struct Database *db;
};


void Connection_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	Connection_close(conn);

	exit(1);
}

struct Address *Address_create(int id, int max_data)
{
	struct Address *addr;

	addr = malloc(sizeof(struct Address));
	if (!addr) die("Memory error", NULL);

	addr->id = id;
	addr->set = 0;
	addr->age = 0;

	addr->name = malloc(sizeof(char) * max_data);
	if (!addr->name) die("Memory error", NULL);

	addr->email = malloc(sizeof(char) * max_data);
	if (!addr->email) die("Memory error", NULL);

	return addr;
}

struct Address *Address_load(FILE *file, int max_data)
{
	struct Address *addr;
	int rc = 0;

	addr = malloc(sizeof(struct Address));
	if (!addr) die("Memory error", NULL);

	rc = fread(addr, sizeof(struct Address), 1, file);
	if (rc != 1) die("Failed to load Address", NULL);

	addr->name = malloc(sizeof(char) * max_data);
	rc = fread(addr->name, sizeof(char), max_data, file);
	if (rc != max_data) die("Failed to load name", NULL);

	addr->email = malloc(sizeof(char) * max_data);
	rc = fread(addr->email, sizeof(char), max_data, file);
	if (rc != max_data) die("Failed to load email", NULL);

	return addr;
}

void Address_destroy(struct Address *addr)
{
	free(addr->name);
	free(addr->email);
	free(addr);
}

void Address_write(struct Address *addr, FILE *file, int max_data)
{
	int rc = fwrite(addr, sizeof(struct Address), 1, file);
	if (rc != 1) die("Failed to write address.", NULL);

	rc = fwrite(addr->name, sizeof(char), max_data, file);
	if (rc != max_data) die("Failed to write name.", NULL);

	rc = fwrite(addr->email, sizeof(char), max_data, file);
	if (rc != max_data) die("Failed to write name.", NULL);

	rc = fflush(file);
	if (rc == -1) die("Cannot flush address.", NULL);
}

void Address_set(struct Address *addr, int age, char *name, char *email, int max_data)
{
	if (addr->set) die("Address already set.", NULL);

	addr->set = 1;
	addr->age = age;

	char *res = strncpy(addr->name, name, max_data);
	addr->name[max_data - 1] = '\0';
	if (!res) die("Name copy failed", NULL);

	res = strncpy(addr->email, email, max_data);
	addr->email[max_data - 1] = '\0';
	if (!res) die("Email copy failed", NULL);
}

void Address_clear(struct Address *addr, int max_data)
{
	int i = 0;

	addr->set = 0;
	addr->age = 0;

	for (i = 0; i < max_data; i++) {
		addr->name[i] = '\0';
		addr->email[i] = '\0';
	}
}

void Address_print(struct Address *addr)
{
	if (addr->set) {
		printf("Address: %d %d %s %s\n",
				addr->id, addr->age, addr->name, addr->email);
	} else {
		printf("Address %d is not set\n", addr->id);
	} 
}

struct Database *Database_create(int max_data, int max_rows)
{
	struct Database *db;
	int i = 0;

	db = malloc(sizeof(struct Database));
	if(!db) die("Memory error", NULL);

	db->max_data = max_data;
	db->max_rows = max_rows;

	db->rows = malloc(sizeof(struct Address *) * max_rows);

	for (i = 0; i < max_rows; i++) {
		db->rows[i] = Address_create(i, max_data);
	}

	return db;
}

void Database_load(struct Connection *conn)
{
	int i = 0;

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error", conn);
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) die("Failed to load database", conn);

	conn->db->rows = malloc(sizeof(struct Address *) * conn->db->max_rows);

	for (i = 0; i < conn->db->max_rows; i++) {
		conn->db->rows[i] = Address_load(conn->file, conn->db->max_data);
	}
}

void Database_destroy(struct Connection *conn)
{
	int i = 0;
	for (i = 0; i < conn->db->max_rows; i++) {
		Address_destroy(conn->db->rows[i]);
	}
	free(conn->db->rows);
	free(conn->db);
}

void Database_write(struct Connection *conn)
{
	int i = 0;
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) die("Failed to write database", conn);

	for (i = 0; i < conn->db->max_rows; i++) {
		Address_write(conn->db->rows[i], conn->file, conn->db->max_data);
	}

	rc = fflush(conn->file);
	if (rc == -1) die("Cannot flush database", conn);
}

void Database_get(struct Connection *conn, int id)
{
	Address_print(conn->db->rows[id]);
}

void Database_set(struct Connection *conn, int id, int age, const char *name, const char *email)
{
	struct Address *addr = conn->db->rows[id];
	if(addr->set) die("Already set, delete it first", conn);

	addr->set = 1;

	addr->age = age;

	char *res = strncpy(addr->name, name, conn->db->max_data);
	addr->name[conn->db->max_data - 1] = '\0';
	if (!res) die("Name copy failed", conn);

	res = strncpy(addr->email, email, conn->db->max_data);
	addr->email[conn->db->max_data - 1] = '\0';
	if (!res) die("Email copy failed", conn);
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for (i = 0; i < db->max_rows; i++) {
		struct Address *cur = db->rows[i];

		if (cur->set) {
			Address_print(cur);
		}
	}
}

void Database_find(struct Connection *conn, const char *term)
{
	int i = 0;

	for (i = 0; i < conn->db->max_rows; i++) {
		struct Address *addr = conn->db->rows[i];

		if (addr->set && 
			(addr->age == atoi(term)
			|| strcmp(addr->name, term) == 0
			|| strcmp(addr->email, term) == 0)) {
			Address_print(addr);
		}
	}
}

void Database_delete(struct Connection *conn, int id)
{
	Address_clear(conn->db->rows[id], conn->db->max_data);
}

struct Connection *Connection_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn) die("Memory error", conn);

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
		if(!conn->file) die("Failed to open the file", conn);
		conn->db = NULL;
	} else {
		conn->file = fopen(filename, "r+");
		if(!conn->file) die("Failed to open the file", conn);
		Database_load(conn);
	}

	return conn;
}

void Connection_close(struct Connection *conn)
{
	if(conn) {
		if(conn->file) fclose(conn->file);
		if(conn->db) Database_destroy(conn);
		free(conn);
	}
}


int main(int argc, char *argv[])
{
	int id = 0;
	struct Connection *conn = NULL;

	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", conn);

	char *filename = argv[1];
	char action = argv[2][0];
	conn = Connection_open(filename, action);


	if (action == 'c') {
		if (argc != 5) die("Need max_data max_rows", conn);

		int max_data = atoi(argv[3]);
		if (max_data < 0) die("Don't be silly", conn);
		int max_rows = atoi(argv[4]);
		if (max_rows < 0) die("Don't be silly", conn);

		conn->db = Database_create(max_data, max_rows);
		Database_write(conn);
	} else {

		if (argc > 3) id = atoi(argv[3]);
		if (id < 0) die("Don't be silly", conn);
		if (id >= conn->db->max_rows) die("There's not that many records.", conn);

		switch(action) {
			
			case 'g':
				if (argc != 4) die("Need an id to get", conn);

				Database_get(conn, id);
				break;
			
			case 's':
				if (argc != 7) die("Need id, age, name, email to set", conn);

				Database_set(conn, id, atoi(argv[4]), argv[5], argv[6]);
				Database_write(conn);
				break;

			case 'd':
				if (argc != 4) die("Need id to delete", conn);

				Database_delete(conn, id);
				Database_write(conn);
				break;
			
			case 'l':
				Database_list(conn);
				break;
			
			case 'f':
				if (argc != 4) die("Need something to find", conn);

				Database_find(conn, argv[3]);
				break;

			default:
				die("Invalid action, only: c=create, g=get, s=set, d=set, d=del, l=list", conn);
		}
	}

	Connection_close(conn);
	
	return 0;
}
