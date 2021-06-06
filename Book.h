#pragma once
#include "String.h"
#include "Vector.h"

class Book
{
private:
	String author;
	String title;
	String genre;
	String description;
	size_t year;
	String keyWords;
	double rate;
	size_t libraryID;

public:
	Book();
	Book(String newAuthor, String newTitle, String newGenre, String newDescription, size_t newYear,
		String newKeyWords, double newRate, size_t newLibraryId);

	void setAuthor(String newAuthor);
	String getAuthor()const;
	void setTitle(String newTitle);
	String getTitle()const;
	void setGengre(String newGenre);
	String getGenre()const;
	void setDescription(String newDescription);
	String getDescription()const;
	void setYear(size_t newYear);
	size_t getYear()const;
	void setKeyWords(String newKeyWords);
	String getKeyWords()const;
	void setRate(double newRate);
	double getRate()const;
	void setLibraryID(size_t newLibraryID);
	size_t getLibraryID()const;

	Vector<String> separateString(const String& str);
	bool hasKeyWord(String& word, String& all);

	friend std::ostream& operator<<(std::ostream& out, const Book& other);
	friend std::istream& operator>>(std::istream& in, Book& other);
};

