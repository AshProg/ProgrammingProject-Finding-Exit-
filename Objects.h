#pragma once
#include <string>
using namespace std;

class Objects
{
protected:
	string fEffects;
	string fObjName;

public:
	Objects();
	Objects(string effects, string name);
	virtual ~Objects() = default;

	string get_ObjName();
	string get_ObjEffects();
};
