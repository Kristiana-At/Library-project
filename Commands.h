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
	void createFile();

	void close();
	void save();
	void saveas();
	void saveHelp(String fileNameSave);
	String convertPath(String& path);
	void help()const;
	bool exit()const;

	void readLines();
	void readUsers();
	void readBooks();

	void login();
	void logout();

	void booksAll();
	void booksInfo();
	void booksFind();

	int booksFindHelp(String& searchBy);

	void convertToLower(String& str);

	void booksAdd();
	void booksRemove();

	//SORT functions with helpers
	void booksSort();// title, author, year, rating
	void sortByTitleOrAuthor(int by);
	void sortByYearOrRate(int by);
	String helperSortTitleAuthor(int get, const Book& book);
	double helperSortYearOrRate(int get, const Book& book);
	int booksSortHelp(String& searchBy);

	void addUser();
	void removeUser();

	bool isBooksLoaded();
	bool isUsersLoaded();

	//print function to show the sort
	void printBooks()const;

	void setFileName(String newFileName);
	User getUser()const;
	Vector<String> getAllLines()const;
	Vector<User> getAllUsers()const;
	Vector<Book> getAllBooks()const;
};

