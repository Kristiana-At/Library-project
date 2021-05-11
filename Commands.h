#pragma once
#include<fstream>
#include "Book.h"
#include "User.h"

class Commands
{
private:
	User user;
	String fileName;
	Vector<String> allLines;
	Vector<User> allUsers;
	Vector<Book> allBooks;
	std::ofstream writeFile;
	std::ifstream readFile;

public:
	void open();
	void close();
	void save();
	void saveas();
	String convertPath(String& path);
	void help();
	int exit();

	void readLines();
	void readUsers();
	void readBooks();

	void login();
	void logout();
	void booksAll()const;
	void booksInfo()const;

	void booksFind();
	int booksFindHelp(String searchBy);
	void convertToLower(String& str);

	void booksAdd();
	void booksRemove();
	void booksSort(String option);
	void addUser();

	void removeUser();
	void removeUserFromAllLines(User& user);

	void setFileName(String newFileName);
	User getUser()const;
	Vector<String> getAllLines()const;
	Vector<User> getAllUsers()const;
	Vector<Book> getAllBooks()const;
};

