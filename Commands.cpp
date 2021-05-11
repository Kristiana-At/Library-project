#include "Commands.h"

void Commands::open()
{
	this->fileName.setString("");
	std::cout << "enter name of file you want to open: ";
	std::cin >> this->fileName;

	this->readFile.open(this->fileName.getString());
	if (!(this->readFile.is_open()))
	{
		this->writeFile.open(this->fileName.getString());
		std::cout << this->fileName.getString() << " was created!\n";

		if (strcmp(convertPath(this->fileName).getString(), "Users.txt") == 0)
		{
			User newUser, newUser2;
			String username, username2; username.setString("admin"); 
			String password; password.setString("i<3c++");
			newUser.setUsername(username); newUser.setPassword(password); newUser.setIsAdmin(1);

			this->writeFile << newUser;
		}
		this->writeFile.close();
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

void Commands::save()
{
	this->writeFile.open(this->fileName.getString());
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

void Commands::saveas()
{
	this->readFile.close();
	this->writeFile.close();
	this->fileName.setString("");

	std::cout << "enter name of new file you want to save: ";
	std::cin >> this->fileName;

	this->writeFile.open(fileName.getString());
	if (writeFile.is_open())
	{
		size_t size = allLines.getSize();
		for (size_t i = 0; i < size;i++)
		{
			this->writeFile << this->allLines[i] << std::endl;
		}
		std::cout << "new file created: " << convertPath(this->fileName) << std::endl;
	}
	else
	{
		std::cout << "Error saving file!";
	}
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

void Commands::help()
{
	std::cout << "LIST OF COMMANDS:" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "open      opens <file>" << std::endl;
	std::cout << "close     closes currently opened file" << std::endl;
	std::cout << "save      saves the currently opened file" << std::endl;
	std::cout << "saveas    saves the currently opened file as <file>" << std::endl;
	std::cout << "help      prints this information" << std::endl;
	std::cout << "exit      exits the program" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}

int Commands::exit()
{
	std::cout << "Exiting the program..." << std::endl;
	return 0;
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
				//currentLine.add('\n');
				this->allLines.push_back(currentLine);
				currentLine.setString("");
			}
		}
		//this->allLines.push_back(currentLine); // for the last line
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
	
	/*
	size_t length = this->allLines.getSize();
	User currentUser;
	for (size_t indexUsername = 0, indexPassword = 1, indexAdmin = 2; indexAdmin < length; indexUsername += 3, indexPassword += 3, indexAdmin += 3)
	{
		currentUser.setUsername(allLines[indexUsername]);
		currentUser.setPassword(allLines[indexPassword]);
		currentUser.setIsAdmin((bool)(atoi(allLines[indexAdmin].getString())));
		this->allUsers.push_back(currentUser);
	}
	*/
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
	std::cout << "Goodbye " << this->user.getUsername() << "!" << std::endl;
	this->user = User();
}

void Commands::addUser()
{
	this->fileName.setString("Users.txt");
	User newUser;
	std::cout << "Enter username, password, admin rights:\n";
	std::cin >> newUser;

	this->allUsers.push_back(newUser);
	/*
	allLines.push_back(newUser.getUsername());
	allLines.push_back(newUser.getPassword());
	if (newUser.getIsAdmin())
	{
		String isAdmin; isAdmin.setString("1");
		allLines.push_back(isAdmin);
	}
	else
	{
		String isNotAdmin; isNotAdmin.setString("0");
		allLines.push_back(isNotAdmin);
	}*/
	save();
	this->allLines = {};
	readLines();
}

void Commands::removeUser()
{
	String username;
	std::cout << "Which user you want to remove: ";
	std::cin >> username;
	size_t size = this->allUsers.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (this->allUsers[i].getUsername() == username)
		{
			//removeUserFromAllLines(allUsers[i]);
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

void Commands::removeUserFromAllLines(User& user)
{
	size_t sizeLines = this->allLines.getSize();
	for (size_t i = 0; i < sizeLines; i++)
	{
		if (this->allLines[i] == user.getUsername())
		{
			this->allLines.pop_at(i);
			this->allLines.pop_at(i);
			this->allLines.pop_at(i);
		}
	}
}

void Commands::booksAdd()
{
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

void Commands::booksAll() const
{
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

void Commands::booksInfo() const
{
	std::cout << "Enter ID: ";
	size_t id;
	std::cin >> id;
	size_t size = this->allBooks.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (allBooks[i].getLibraryID() == id)
		{
			std::cout << allBooks[i];
			return;
		}
	}
}

void Commands::booksFind()
{
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
		for (size_t i = 0; i < size; i++)
		{
			String toLower = allBooks[i].getTitle();
			convertToLower(toLower);
			if (toLower == name)
			{
				std::cout << "\nBOOK FOUND!\n";
				std::cout << allBooks[i];
				return;
			}
		}
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
		for (size_t i = 0; i < size; i++)
		{
			String toLower = allBooks[i].getAuthor();
			convertToLower(toLower);
			if (toLower == name)
			{
				std::cout << "\nBOOK FOUND!\n";
				std::cout << allBooks[i];
				return;
			}
		}
		std::cout << "\nBOOK NOT FOUND!\n";
		break;
	}
	case 3:
	{
		int name;
		std::cout << "Enter ID: ";
		std::cin >> name;
		size_t size = this->allBooks.getSize();
		for (size_t i = 0; i < size; i++)
		{
			if (allBooks[i].getLibraryID() == name)
			{
				std::cout << "\nBOOK FOUND!\n";
				std::cout << allBooks[i];
				return;
			}
		}
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

int Commands::booksFindHelp(String searchBy)
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

void Commands::convertToLower(String& str)
{
	size_t length = str.getLength();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] < 'a')
		{
			str[i] += 32;
		}
	}
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