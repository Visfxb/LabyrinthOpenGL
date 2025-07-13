#pragma once
#include "../Include.h"

class Profile
{
	friend class SignUpScene;
	friend class LogInScene;
protected:
	static int id;
	int thisId;
	string nickname;
	int record;
	string password;
public:
	Profile();
	Profile(string nickname, string password);
	void setId(int id);
	int getId();
	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file);
};