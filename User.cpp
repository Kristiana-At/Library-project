#include "User.h"

User::User()
{
	this->username.setString("defaultUser");
	this->password.setString("defaultPassword");
	this->isAdmin = true;
}

User::User(String newUsername, String newPassword, bool newIsAdmin)
{
	setUsername(newUsername);
	setPassword(newPassword);
	setIsAdmin(newIsAdmin);
}

void User::setUsername(String newUsername)
{
	this->username = newUsername;
}
String User::getUsername()const
{
	return this->username;
}
void User::setPassword(String newPassword)
{
	this->password = newPassword;
}
String User::getPassword()const
{
	return this->password;
}

void User::setIsAdmin(bool newIsAdmin)
{
	this->isAdmin = newIsAdmin;
}

bool User::getIsAdmin()const
{
	return this->isAdmin;
}

bool User::doesExist(Vector<User>& allUsers, String searchedName, String searchedPassword, bool& isAdmin)
{
	size_t sizeVec = allUsers.getSize();
	for (size_t i = 0; i < sizeVec; i++)
	{
		if (allUsers[i].getUsername() == searchedName && allUsers[i].getPassword() == searchedPassword)
		{
			isAdmin = allUsers[i].getIsAdmin();
			return true;
		}
	}
	return false;
}

bool User::operator==(const User& other)const
{
	return this->username == other.username && this->password == other.password && this->isAdmin == other.isAdmin;
}

bool User::operator!=(const User& other)const
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const User& other)
{
	out << other.username << std::endl
		<< other.password << std::endl
		<< other.isAdmin << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, User& other)
{
	in >> other.username;
	in >> other.password;
	in >> other.isAdmin;
	in.ignore();//???защо работи
	return in;
	/*char newUsername[32];
	in >> newUsername;
	other.username.setString(newUsername);

	char newPassword[32];
	in >> newPassword;
	other.password.setString(newPassword);
	
	in >> other.isAdmin;
	in.ignore();*/

	return in;
}