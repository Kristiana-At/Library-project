#include "String.h"

void String::copy(const String& other)
{
	this->string = new char[strlen(other.string) + 1];
	strcpy_s(this->string, strlen(other.string) + 1, other.string);
}

void String::erase()
{
	delete[] this->string;
}


String::String()
{
	this->string = new char[1];
	strcpy_s(this->string, 1, "");
}

String::String(const String& other)
{
	this->copy(other);
}
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

String::~String()
{
	this->erase();
}

void String::print() const
{
	std::cout << this->string << std::endl;
}

void String::setString(const char* newString)
{
	if (newString != nullptr)
	{
		delete[] this->string;
		this->string = new char[strlen(newString) + 1];
		strcpy_s(this->string, strlen(newString) + 1, newString);
	}
}
const char* String::getString()const
{
	return this->string;
}

String& String::add(char symbol)
{
	size_t lengthOfString = getLength();
	String newString;
	newString.string = new char[lengthOfString + 2]; // +2 because one for the new element and 1 for the \0 as lengthOfString does not count \0
	strcpy_s(newString.string, lengthOfString + 2, string);
	newString.string[lengthOfString] = symbol;
	newString.string[lengthOfString + 1] = '\0';
	*this = newString;
	return *this;
}

size_t String::getLength() const
{
	return strlen(string);
}

String& String::insertAt(size_t index, char symbol)
{
	if (index < getLength() + 1)
	{
		String newString;
		newString.string = new char[getLength() + 2];
		for (size_t i = 0, j = 0;i < getLength() + 1;i++)
		{
			if (i != index)
			{
				newString.string[i] = this->string[j];
				j++; //if i == index I dont increase j and that is how I do not miss the symbol on the index position
			}
			else
			{
				newString.string[i] = symbol;
			}
		}
		newString.string[getLength() + 1] = '\0';
		*this = newString;
	}
	return *this;

}

String& String::removeAt(size_t index)
{
	if (index < getLength())
	{
		String newString;
		newString.string = new char[getLength() + 1];
		for (size_t i = 0, j = 0;i < getLength();i++)
		{
			if (i != index)
			{
				if (j < getLength() - 1)
				{
					newString.string[j] = this->string[i];
					j++;
				}
			}
		}
		newString.string[getLength() - 1] = '\0';
		*this = newString;
	}
	return *this;
}

String String::operator+(const String& other)
{
	String result;
	result.string = new char[strlen(string) + strlen(other.string) + 1];

	strcpy_s(result.string, strlen(this->string) + strlen(other.string) + 1, this->string);
	strcat_s(result.string, strlen(this->string) + strlen(other.string) + 1, other.string);

	return result;
}

String String::operator+(const char* other) // when we want to combine a variable of type String with char array: s1 + "Something";
{
	String result;
	result.string = new char[strlen(string) + strlen(other) + 1];

	strcpy_s(result.string, strlen(this->string) + strlen(other) + 1, this->string);
	strcat_s(result.string, strlen(this->string) + strlen(other) + 1, other);

	return result;
}

String& String::operator+=(const String& other)
{
	*this = *this + other;
	return *this;
}

String& String::operator+=(const char* other)
{
	*this = *this + other;
	return *this;
}

void String::trimStart()
{
	*this = removeAt(0);
}

void String::trimEnd()
{
	*this = removeAt(getLength() - 1);
}

void String::trimStart(size_t numberOfElementsToRemove)
{
	if (numberOfElementsToRemove < getLength() - 1)
	{
		for (size_t i = 0;i < numberOfElementsToRemove;i++)
		{
			trimStart();
		}
	}
}

void String::trimEnd(size_t numberOfElementsToRemove)
{
	if (numberOfElementsToRemove < getLength() - 1)
	{
		for (size_t i = 0;i < numberOfElementsToRemove;i++)
		{
			trimEnd();
		}
	}
}

bool String::operator==(const String& other) const
{
	return strcmp(this->string, other.string) == 0;
}

bool String::operator==(const char* other) const
{
	return strcmp(this->string, other) == 0;
}

bool String::operator!=(const String& other) const
{
	return !(this->string == other.string);
}

bool String::operator!=(const char* other) const
{
	return !(this->string == other);
}

char& String::operator[] (size_t i) const
{
	return this->string[i];
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str.string;
	return out ;
}
std::istream& operator>>(std::istream& in, String& str)
{	
	char fixed[70];
	//in.sync();
	in.getline(fixed, 64);
	//in >> fixed;
	str.setString(fixed);
	return in;
}



