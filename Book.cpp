#include "Book.h"

Book::Book()
{
	this->author.setString("No author");
	this->title.setString("No title");
	this->title.setString("No genre");
	this->title.setString("No description");
	this->year = 2000;
	this->keyWords.setString("No key words");
	this->rate = 0;
	this->libraryID = 0;
}

Book::Book(String newAuthor, String newTitle, String newGenre, String newDescription, size_t newYear,
	String newKeyWords, double newRate, size_t newLibraryId)
{
	setAuthor(newAuthor);
	setTitle(newTitle);
	setGengre(newGenre);
	setDescription(newDescription);
	setYear(newYear);
	setKeyWords(newKeyWords);
	setRate(newRate);
	setLibraryID(newLibraryId);
}

void Book::setAuthor(String newAuthor)
{
	this->author = newAuthor;
}
String Book::getAuthor()const
{
	return this->author;
}
void Book::setTitle(String newTitle)
{
	this->title = newTitle;
}
String Book::getTitle()const
{
	return this->title;
}
void Book::setGengre(String newGenre)
{
	this->genre = newGenre;
}
String Book::getGenre()const
{
	return this->genre;
}
void Book::setDescription(String newDescription)
{
	this->description = newDescription;
}
String Book::getDescription()const
{
	return this->description;
}
void Book::setYear(size_t newYear)
{
	this->year = newYear;
}
size_t Book::getYear()const
{
	return this->year;
}
void Book::setKeyWords(String newKeyWords)
{
	this->keyWords = newKeyWords;
}
String Book::getKeyWords()const
{
	return this->keyWords;
}
void Book::setRate(double newRate)
{
	this->rate = newRate;
}
double Book::getRate()const
{
	return this->rate;
}
void Book::setLibraryID(size_t newLibraryID)
{
	this->libraryID = newLibraryID;
}
size_t Book::getLibraryID()const
{
	return this->libraryID;
}

Vector<String> Book::separateString(const String& str)
{
	size_t length = str.getLength();
	String currentWord;
	currentWord.setString("");
	Vector<String> separated;
	for (size_t i = 0;i < length;i++)
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			currentWord.add(str[i]);
		}
		else
		{
			separated.push_back(currentWord);
			currentWord.setString("");
		}
	}
	separated.push_back(currentWord);
	return separated;
}

bool Book::hasKeyWord(String& word, String& all)
{
	Vector<String> separated = separateString(all);
	size_t size = separated.getSize();
	for (size_t i = 0; i < size;i++)
	{
		if (separated[i] == word)
		{
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const Book& other)
{
	out << other.author.getString() << std::endl;
	out << other.title.getString() << std::endl;
	out << other.genre.getString() << std::endl;
	out << other.description.getString() << std::endl;
	out << other.year << std::endl;
	out << other.keyWords << std::endl;
	out << other.rate << std::endl;
	out << other.libraryID << std::endl;
	return out;
}
std::istream& operator>>(std::istream& in, Book& other)
{
	in >> other.author;
	in >> other.title;
	in >> other.genre;
	in >> other.description;
	in >> other.year;
	in.ignore();
	in >> other.keyWords;
	in >> other.rate;
	in >> other.libraryID;
	in.ignore();
	return in;
}