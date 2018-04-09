#include <iostream>

#include "lite3.hpp"

void test()
{
	lite3::connection db(":memory:"); // or a file path to sqlite file

	// fire and forget query where nothing needs to be bound and no results are expected
	db.execute("create table people (id integer primary key autoincrement, name text not null, age int not null, fav_number double not null);");

	// more complex query with parameters
	lite3::statement stmt(db, "insert into people (name, age, fav_number) values (?, ?, ?);");
	stmt.bind(1, "joe biden");
	stmt.bind(2, 69);
	stmt.bind(3, 7.435);
	stmt.execute(); // only need to call this once (here)

	// query where results are expected
	lite3::statement query(db, "select * from people where age=?;");
	query.bind(1, 69);
	while(query.execute())
		std::cout << "id: " << query.integer(0) << ", name: " << query.str(1) << ", age: " << query.integer(2) << ", fave number: " << query.real(3) << std::endl;
}

int main()
{
	try
	{
		test();
	}
	catch(const lite3::statement_exception &se)
	{
		std::cerr << se.what() << " | query: \"" << se.query() << "\"" << std::endl;
	}
	catch(const lite3::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
