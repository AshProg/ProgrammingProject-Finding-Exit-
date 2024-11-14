#pragma once
#include <string>
using namespace std;

class Entity
{
protected:
	string fName;
	bool fDeathOrAlive;

public:
	Entity();
	Entity(string name, bool liveordeath);
	virtual ~Entity() = default;

	string get_Name() { return fName; }
	void set_Name(string name)
	{
		fName = name;
	}
};