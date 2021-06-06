#include "Session.h"

void Session::session()
{
	std::cout << "			WELCOME TO OUR LIBRARY APP!\n";
	this->command.help();
	do 
	{
		std::cout << "\nEnter command: ";
		std::cin >> this->current;
		std::cout << "\n";
		int choice = 0;
		if (isNumber())
		{
			choice = atoi(this->current.getString());
		}
		switch(choice)
		{
		case 1:
		{
			this->command.open();
			break;
		}
		case 2:
		{
			this->command.close();
			break;
		}
		case 3:
		{
			this->command.save();
			break;
		}
		case 4:
		{
			this->command.saveas();
			break;
		}
		case 5:
		{
			this->command.help();
			break;
		}
		case 6:
		{
			this->doesEnd = this->command.exit();
			return;
			break;
		}
		case 7:
		{
			this->command.login();
			break;
		}
		case 8:
		{
			if (this->command.getUser() != User())
			{
				this->command.logout();
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 9:
		{
			if (this->command.getUser() != User())
			{
				this->command.booksAll();
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 10:
		{
			if (this->command.getUser() != User())
			{
				this->command.booksFind();
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 11:
		{
			if (this->command.getUser() != User())
			{
				this->command.booksSort();
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 12:
		{
			if (this->command.getUser() != User())
			{
				this->command.booksInfo();
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 13:
		{
			if (this->command.getUser() != User())
			{
				if (this->command.getUser().getIsAdmin())
				{
					this->command.booksAdd();
				}
				else
				{
					std::cout << "Only admins have rights for the following command!";
				}
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 14:
		{
			if (this->command.getUser() != User())
			{
				if (this->command.getUser().getIsAdmin())
				{
					this->command.booksRemove();
				}
				else
				{
					std::cout << "Only admins have rights for the following command!";
				}
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 15:
		{
			if (this->command.getUser() != User())
			{
				if (this->command.getUser().getIsAdmin())
				{
					this->command.addUser();
				}
				else
				{
					std::cout << "Only admins have rights for the following command!";
				}
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		case 16:
		{
			if (this->command.getUser() != User())
			{
				if (this->command.getUser().getIsAdmin())
				{
					this->command.removeUser();
				}
				else
				{
					std::cout << "Only admins have rights for the following command!";
				}
			}
			else
			{
				std::cout << "No current user!\n";
			}
			break;
		}
		default:
		{
			std::cout << "Invalid command!\n";
			break;
		}
		}
	} while (!this->doesEnd);

}

bool Session::isNumber()const
{
	if (this->current == "1" || this->current == "2" || this->current == "3" || this->current == "4" || this->current == "5" ||
		this->current == "6" || this->current == "7" || this->current == "8" || this->current == "9" || this->current == "10" ||
		this->current == "11" || this->current == "12" || this->current == "13" || this->current == "14" || this->current == "15" ||
		this->current == "16")
	{
		return true;
	}
	return false;
}