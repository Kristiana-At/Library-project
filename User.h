#pragma once
#include "String.h"
#include "Vector.h"

class User
{
private:
	String username;
	String password;
	bool isAdmin;

public:
	User();
	User(String newUsername, String newPassword, bool newIsAdmin);

	void setUsername(String newUsername);
	String getUsername()const;
	void setPassword(String newPassword);
	String getPassword()const;
	void setIsAdmin(bool newIsAdmin);
	bool getIsAdmin()const;

	bool doesExist(Vector<User>& allUsers, String searchedName, String searchedPassword, bool& isAdmin);
	bool operator==(const User& other)const;
	bool operator!=(const User& other)const;

	friend std::ostream& operator<<(std::ostream& out, const User& other);
	friend std::istream& operator>>(std::istream& in, User& other);
};

