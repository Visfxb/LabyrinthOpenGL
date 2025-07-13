#include "Profile.h"

Profile::Profile()
{
    nickname = "";
    password = "";
}

Profile::Profile(string nickname, string password)
{
    thisId = id++;
    this->nickname = nickname;
    this->password = password;
    record = 0;
}

void Profile::setId(int id)
{
    thisId = id;
}

int Profile::getId()
{
    return thisId;
}

void Profile::loadFromFile(ifstream& file)
{
    file >> thisId >> nickname >> password >> record;
}

void Profile::saveToFile(ofstream& file)
{
    file << thisId << " " << nickname << " " << password << " " << record << endl; 
}