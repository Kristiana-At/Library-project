#include "Commands.h"

void Commands::open()
{
	this->fileName.setString("");
	this->allLines = {};
	std::cout << "enter name of file you want to open: ";
	std::cin >> this->fileName;

	this->readFile.open(this->fileName.getString());
	if (!(this->readFile.is_open()))
	{
		createFile();
	}
	else
	{
		std::cout << "Successfuly opened " << convertPath(this->fileName) << std::endl;
	}
	this->readFile.close();

	readLines();

	if (this->fileName == "Users.txt")
	{
		readUsers();
	}

	if (this->fileName == "Books.txt")
	{
		readBooks();
	}
}

void Commands::createFile()
{
	this->writeFile.open(this->fileName.getString());
	std::cout << this->fileName.getString() << " was created!\n";

	if (strcmp(convertPath(this->fileName).getString(), "Users.txt") == 0)
	{
		User newUser;
		String username; 
		username.setString("admin");

		String password; 
		password.setString("i<3c++");
		newUser.setUsername(username); newUser.setPassword(password); newUser.setIsAdmin(1);

		this->writeFile << newUser;
	}
	this->writeFile.close();
}

void Commands::close()
{
	if (readFile.is_open())
	{
		this->readFile.close();
		std::cout << "Successfully closed " << convertPath(this->fileName) << std::endl;
	}

	if (writeFile.is_open())
	{
		this->writeFile.close();
		std::cout << "Successfully closed " << convertPath(this->fileName) << std::endl;
	}
	this->fileName.setString("");
	this->allLines = {};
	this->allUsers = {};
	this->allBooks = {};
}
void Commands::saveHelp(String fileNameSave)
{
	this->writeFile.open(fileNameSave.getString());
	if (writeFile.is_open())
	{
		if (this->fileName == "Users.txt")
		{
			size_t length = this->allUsers.getSize();
			for (size_t i = 0; i < length; i++)
			{
				this->writeFile << this->allUsers[i];
			}
			this->writeFile.close();
			return;
		}

		if (this->fileName == "Books.txt")
		{
			size_t length = this->allBooks.getSize();
			for (size_t i = 0; i < length; i++)
			{
				this->writeFile << this->allBooks[i];
			}
			this->writeFile.close();
			return;
		}

		size_t length = this->allLines.getSize();
		for (size_t i = 0; i < length;i++)
		{
			this->writeFile << this->allLines[i] << std::endl;
		}
		this->writeFile.close();
	}
	else
	{
		std::cout << "Error saving file!";
	}
}

void Commands::save()
{
	saveHelp(this->fileName);
}

void Commands::saveas()
{
	this->readFile.close();
	this->writeFile.close();

	String newFileName;
	std::cout << "enter name of new file you want to save: ";
	std::cin >> newFileName;

	saveHelp(newFileName);
	this->fileName.setString(newFileName.getString());
	std::cout << "new file created: " << convertPath(this->fileName) << std::endl;
}

String Commands::convertPath(String& path)
{
	String nameNewFile;
	nameNewFile.setString("");
	size_t length = path.getLength();
	size_t counter = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (path.getString()[i] == '\\')
		{
			counter = i; //this will take the index of the last \ sign
		}
	}
	if (counter != 0)
	{
		counter++;
	}
	for (size_t i = counter; i < length; i++)
	{
		nameNewFile.add(path.getString()[i]);		
	}
	return nameNewFile;
}

void Commands::help()const
{
	std::cout << "LIST OF COMMANDS:" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "1.open		 opens <file>" << std::endl;
	std::cout << "2.close		 closes currently opened file" << std::endl;
	std::cout << "3.save		 saves the currently opened file" << std::endl;
	std::cout << "4.saveas	 saves the currently opened file as <file>" << std::endl;
	std::cout << "5.help		 prints this information" << std::endl;
	std::cout << "6.exit		 exits the program" << std::endl;
	std::cout << "7.login		 login to the system" << std::endl;
	std::cout << "8.logout	 current user logs out" << std::endl;
	std::cout << "9.books all	 prints information for all books" << std::endl;
	std::cout << "10.books find	 shows information about a book by certain criteria" << std::endl;
	std::cout << "11.books sort	 sorts books" << std::endl;
	std::cout << "12.books view	 search book by id" << std::endl;
	std::cout << "13.books add	 adds book" << std::endl;
	std::cout << "14.books remove	 removes book" << std::endl;
	std::cout << "15.users add	 adds user" << std::endl;
	std::cout << "16.users remove	 removes user" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}

bool Commands::exit()const
{
	std::cout << "Exiting the program..." << std::endl;
	return true;
}

void Commands::readLines()
{
	this->readFile.open(this->fileName.getString());
	if (this->readFile.is_open())
	{
		String currentLine;
		currentLine.setString("");
		char c; //each symbol of the text file
		while (this->readFile.get(c))
		{
			if (c != '\n')
			{
				currentLine.add(c);
			}
			else
			{
				this->allLines.push_back(currentLine);
				currentLine.setString("");
			}
		}
		this->readFile.close();
	}
	else
	{
		std::cout << "Unable to open file!\n";
	}
}

void Commands::readUsers()
{	
	this->readFile.open("Users.txt");
	if (this->readFile.is_open())
	{
		User currentUser;
		while (this->readFile >> currentUser)
		{
			this->allUsers.push_back(currentUser);
		}
		this->readFile.close();
	}
	else
	{
		std::cout << "Unable to open file!\n";
	}
}

void Commands::readBooks()
{
	this->readFile.open("Books.txt");
	if (this->readFile.is_open())
	{
		Book currentBook;
		while (this->readFile >> currentBook)
		{
			this->allBooks.push_back(currentBook);
		}
		this->readFile.close();
	}
	else
	{
		std::cout << "Unable to open file!\n";
	}
}

void Commands::login()
{
	if (!isUsersLoaded())
	{
		return;
	}
	bool isAdmin = false;
	String defaultName;
	defaultName.setString("defaultUser");
	while (this->user.getUsername() == defaultName)
	{
		String enteredUsername;
		String enteredPassword;
		std::cout << "enter username:"; 
		std::cin >> enteredUsername;

		std::cout << "enter password:";
		std::cin >> enteredPassword;

		if (this->user.doesExist(this->allUsers, enteredUsername, enteredPassword, isAdmin))
		{
			this->user.setUsername(enteredUsername);
			this->user.setPassword(enteredPassword);
			this->user.setIsAdmin(isAdmin);

			std::cout << "Welcome " << enteredUsername << "!" << std::endl;
			return;
		}
		"Wrong username or password!\n";
	}
	std::cout << "You are already logged in!\n";
}

void Commands::logout()
{
	if (this->user != User())
	{
		std::cout << "Goodbye " << this->user.getUsername() << "!" << std::endl;
		this->user = User();
	}
	else
	{
		std::cout << "No currently logged user! Choose option 7 to log in!\n";
	}
}

void Commands::addUser()
{
	this->fileName.setString("Users.txt");
	if (!isUsersLoaded())
	{
		return;
	}

	this->fileName.setString("Users.txt");
	User newUser;
	std::cout << "Enter username, password, admin rights:\n";
	std::cin >> newUser;

	this->allUsers.push_back(newUser);
	save();
	this->allLines = {};
	readLines();
}

void Commands::removeUser()
{
	this->fileName.setString("Users.txt");
	if (!isUsersLoaded())
	{
		return;
	}

	String username;
	std::cout << "Which user you want to remove: ";
	std::cin >> username;
	size_t size = this->allUsers.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (this->allUsers[i].getUsername() == username)
		{
			this->allUsers.pop_at(i);
			std::cout << "User removed\n";
			save();
			this->allLines = {};
			readLines();
			return;
		}
	}

	std::cout << "No such user!\n";
}

void Commands::booksAdd()
{
	this->fileName.setString("Books.txt");
	if (!isBooksLoaded())
	{
		return;
	}
	this->fileName.setString("Books.txt");
	Book newBook;
	std::cout << "Enter autho, title, genre, description, year, keyWords, rate, libraryID:\n";
	std::cin >> newBook;

	this->allBooks.push_back(newBook);
	
	save();
	this->allLines = {};
	readLines();
}

void Commands::booksRemove()
{
	this->fileName.setString("Books.txt");
	if (!isBooksLoaded())
	{
		return;
	}
	String bookName;
	std::cout << "Which book you want to remove: ";
	std::cin >> bookName;
	size_t size = this->allBooks.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (this->allBooks[i].getTitle() == bookName)
		{
			this->allBooks.pop_at(i);
			std::cout << "Book removed\n";
			save();
			this->allLines = {};
			readLines();
			return;
		}
	}

	std::cout << "No such book!\n";
}

void Commands::booksAll() 
{
	if (!isBooksLoaded())
	{
		return;
	}
	size_t size = this->allBooks.getSize();
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "BOOK " << i + 1 << std::endl;
		std::cout << "Title: "<<allBooks[i].getTitle() << std::endl;
		std::cout << "Author: " << allBooks[i].getAuthor() << std::endl;
		std::cout << "Genre: " << allBooks[i].getGenre() << std::endl;
		std::cout << "Book ID: " << allBooks[i].getLibraryID() << std::endl;
	}
}

void Commands::booksInfo() 
{
	if (!isBooksLoaded())
	{
		return;
	}
	int id;
	std::cout << "Enter ID: ";
	std::cin >> id;
	std::cin.ignore();
	size_t size = this->allBooks.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (this->allBooks[i].getLibraryID() == id)
		{

			std::cout << "\nBOOK FOUND!\n";

			std::cout << this->allBooks[i];
			return;
		}
	}
	std::cout << "\nBOOK NOT FOUND!\n";
}

void Commands::booksFind()
{
	if (!isBooksLoaded())
	{
		return;
	}
	std::cout << "books find by(title/author/tag) ";
	String searchBy;
	std::cin >> searchBy;
	int chosen = booksFindHelp(searchBy);
	switch (chosen)
	{
	case 1:
	{
		String name;
		std::cout << "Enter title: ";
		std::cin >> name;
		convertToLower(name);
		size_t size = this->allBooks.getSize();
		bool isFound = false;
		for (size_t i = 0; i < size; i++)
		{
			String toLower = allBooks[i].getTitle();
			convertToLower(toLower);
			if (toLower == name)
			{
				if (!isFound)
				{
					std::cout << "\nBOOK FOUND!\n";
				}
				std::cout << allBooks[i] << std::endl;
				isFound = true;
				//return;
			}
		}
		if (isFound)return;
		std::cout << "\nBOOK NOT FOUND!\n";
		break;
	}
	case 2:
	{
		String name;
		std::cout << "Enter author name: ";
		std::cin >> name;
		convertToLower(name);
		size_t size = this->allBooks.getSize();
		bool isFound = false;
		for (size_t i = 0; i < size; i++)
		{
			String toLower = allBooks[i].getAuthor();
			convertToLower(toLower);
			if (toLower == name)
			{
				if (!isFound)
				{
					std::cout << "\nBOOK FOUND!\n" << std::endl;
				}
				std::cout << allBooks[i];
				isFound = true;
			}
		}
		if (isFound)return;
		std::cout << "\nBOOK NOT FOUND!\n";
		break;
	}
	case 3:
	{
		String keyWord;
		std::cout << "Enter key word: ";
		std::cin >> keyWord;
		convertToLower(keyWord);
		bool isFound = false;
		size_t size = this->allBooks.getSize();
		for (size_t i = 0; i < size; i++)
		{
			String toLower = this->allBooks[i].getKeyWords();
			convertToLower(toLower);
			if (allBooks[i].hasKeyWord(keyWord,toLower))
			{
				if (!isFound)
				{
					std::cout << "\nBOOK FOUND!\n" << std::endl;
				}
				std::cout << allBooks[i];
				isFound = true;
			}
		}
		if (isFound)return;
		std::cout << "\nBOOK NOT FOUND!\n";
		break;
	}
	default:
	{
		std::cout << "No such criteria for searching!\n";
		break;
	}
	}
}

int Commands::booksFindHelp(String& searchBy)
{
	convertToLower(searchBy);
	if (searchBy == "title")
	{
		return 1;
	}
	if (searchBy == "author")
	{
		return 2;
	}
	if (searchBy == "tag")
	{
		return 3;
	}
	return 0;
}

int Commands::booksSortHelp(String& searchBy)// title, author, year, rating
{
	convertToLower(searchBy);
	if (searchBy == "title")
	{
		return 1;
	}
	if (searchBy == "author")
	{
		return 2;
	}
	if (searchBy == "year")
	{
		return 3;
	}
	if (searchBy == "rating")
	{
		return 4;
	}
	return 0;
}

void Commands::booksSort()
{
	this->fileName.setString("Books.txt");
	if (!isBooksLoaded())
	{
		return;
	}
	std::cout << "books sort by(title/author/year/rating) ";
	String sortBy;
	std::cin >> sortBy;
	int chosen = booksSortHelp(sortBy);

	std::cout << "\nChoose:\n1.Ascending\n2.Descending\nEnter(1/2): ";
	String checkOrder;
	std::cin >> checkOrder;
	bool isDescending = (checkOrder == "2" || checkOrder == "desc" || checkOrder == "Descending");
	switch (chosen)
	{
	case 1:
	{
		sortByTitleOrAuthor(1);
		break;
	}
	case 2:
	{
		sortByTitleOrAuthor(2);
		break;
	}
	case 3:
	{
		sortByYearOrRate(3);
		break;
	}
	case 4:
	{
		sortByYearOrRate(4);
		break;
	}
	default:
	{
		std::cout << "No such criteria for sorting!\n";
		break;
	}
	}	
	if (isDescending)
	{
		this->allBooks.reverse();
	}
	printBooks();
}


void Commands::sortByTitleOrAuthor(int by)
{
	size_t size = this->allBooks.getSize();
	for (size_t i = 0;i < size - 1;i++)
	{
		for (size_t j = 0;j < size - i - 1;j++)
		{
			String iGetName;
			iGetName = helperSortTitleAuthor(by, this->allBooks[j]);
			String jGetName;
			jGetName = helperSortTitleAuthor(by, this->allBooks[j + 1]);
			if (strcmp(iGetName.getString(), jGetName.getString()) > 0)
			{
				this->allBooks.swap(j, j + 1);
			}
		}
	}
}

void Commands::sortByYearOrRate(int by)
{
	size_t size = this->allBooks.getSize();
	for (size_t i = 0;i < size - 1;i++)
	{
		for (size_t j = 0;j < size - i - 1;j++)
		{
			double firstGetNum;
			firstGetNum = helperSortYearOrRate(by, this->allBooks[j]);
			double secondGetNum;
			secondGetNum = helperSortYearOrRate(by, this->allBooks[j + 1]);
			if (firstGetNum > secondGetNum)
			{
				this->allBooks.swap(j, j + 1);
			}
		}
	}
}

String Commands::helperSortTitleAuthor(int get, const Book& book)
{
	String str;
	if (get == 1)
	{
		str.setString(book.getTitle().getString());
	}
	if (get == 2)
	{
		str.setString(book.getAuthor().getString());
	}
	convertToLower(str);
	return str;
}

double Commands::helperSortYearOrRate(int get, const Book& book)
{
	double num = 0;
	if (get == 3)
	{
		num = (double)(book.getYear());
	}
	if (get == 4)
	{
		num = book.getRate();
	}
	return num;
}

void Commands::convertToLower(String& str)
{
	size_t length = str.getLength();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
}

void Commands::printBooks()const
{
	size_t size = this->allBooks.getSize();
	for (size_t i = 0; i < size;i++)
	{
		std::cout << this->allBooks[i] << std::endl;
	}
}

bool Commands::isBooksLoaded()
{
	if (this->allBooks.isEmpty())
	{
		std::cout << "No file loaded...choose option 1 to open Books.txt\n";
		return false; 
	}
	return true;
}

bool Commands::isUsersLoaded()
{
	if (this->allUsers.isEmpty())
	{
		std::cout << "No file loaded...choose option 1 to open Users.txt\n";
		return false;
	}
	return true;
}

void Commands::setFileName(String newFileName)
{
	this->fileName = newFileName;
}

User Commands::getUser()const
{
	return this->user;
}

Vector<String> Commands::getAllLines()const
{
	return this->allLines;
}

Vector<User> Commands::getAllUsers()const
{
	return this->allUsers;
}
Vector<Book> Commands::getAllBooks()const
{
	return this->allBooks;
}