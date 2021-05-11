#include <iostream>
#include "String.h"
#include "Book.h"
#include "User.h"
#include "Commands.h"

int main()
{
	Commands c;
	c.help();
	
    c.open();
	for (size_t i = 0;i < c.getAllLines().getSize();i++)
	{
		std::cout << c.getAllLines()[i] << "\n";
	}
	std::cout << "\n\n";
	c.booksAdd();
	c.saveas();
	std::cout << "\n\n";
	for (size_t i = 0;i < c.getAllLines().getSize();i++)
	{
		std::cout << c.getAllLines()[i] << "\n";
	}
	//std::cout << c.getAllBooks();
	//c.booksRemove();
	//c.booksFind();
	//c.addUser();

	//c.saveas();
	//c.login();
	/*User a;
	std::cin >> a; 
	std::cout << a;
	

	String toAdd, toCheck, two;
	std::cout << "enter 1:\n"; std::cin >> toAdd; std::cout << toAdd << std::endl;
	std::cout << "enter 2:\n"; std::cin >> toCheck; std::cout << toCheck << std::endl;
	std::cout << "enter 3:\n"; std::cin >> two; std::cout << two << std::endl;*/

	//c.logout();
	//c.save();
	//String str;
	//std::cin >> str;
	//Vector<String> newStr = book.separateString(str);
	//std::cout << newStr;
	//c.save();
	//std::cout << c.getAllUsers();
	//c.removeUser();
	///std::cout << c.getAllUsers();

	//c.login();
	//c.addUser();
	
	//std::cout << c.getAllLines().getSize() << std::endl;
	//std::cout << c.getAllLines();

	//c.save();
	//c.saveas();
	//c.exit();
	//c.close();
	//c.readUsers();

}