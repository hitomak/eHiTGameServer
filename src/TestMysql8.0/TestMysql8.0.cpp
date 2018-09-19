/*
//It Should Be Mysql connector c++ v8.0
//Which is here is for connector c++ v1.**
#include "stdafx.h"
#include <mysql.h>
#include <iostream>
#include <mysqlx/xdevapi.h>

using namespace std;
int qstate;

int main()
{
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES *res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "testdb", 3306, NULL, 0);

	if (conn) {
		puts("Successful connection to database!");

		string query = "SELECT * FROM test";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}

	return 0;
}
*/