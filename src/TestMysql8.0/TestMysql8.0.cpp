//Experimenting some one's work trying to undertand and how to use it
#include <iostream>
#include <mysqlx/xdevapi.h>

using ::std::cout;
using ::std::endl;

int main()
try {
	using namespace ::mysqlx;

	Session sess("user:password@host/schema"); //

	Collection coll = sess.getDefaultSchema().createCollection("myCollection", true);

	coll.add(R"({ "name": "foo"; "age": 7 })").execute();

	CollectionFind query = coll.find("age < :age").fields("name", "age");

	DocResult res = query.bind("age", 18).execute();

	for (DbDoc doc : res)
	{
		cout << "name: " << doc["name"]	<< ", age: " << doc["age"]	<< endl;
	}
}
catch (const mysqlx::Error &err)
{
	cout << "ERROR: " << err << endl;
}