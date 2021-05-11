#pragma once
#include <iostream>
#include <cstring>

class String
{
private:
	char* string;

	void copy(const String& other);
	void erase();


public:
	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	void print() const;
	void setString(const char* newString);
	const char* getString()const;

	String& add(char symbol);
	size_t getLength() const;
	String& insertAt(size_t index, char symbol);
	String& removeAt(size_t index);
	void trimStart();
	void trimEnd();
	void trimStart(size_t numberOfElementsToRemove);
	void trimEnd(size_t numberOfElementsToRemove);
	String operator+(const String& other);
	String operator+(const char* other);
	String& operator+=(const String& other);
	String& operator+=(const char* other);
	bool operator==(const String& other) const;
	bool operator==(const char* other) const;
	bool operator!=(const String& other) const;
	bool operator!=(const char* other) const;
	char& operator[](size_t index) const;
	friend std::ostream& operator<<(std::ostream& out, const String& string);
	friend std::istream& operator>>(std::istream& in, String& string);
};


