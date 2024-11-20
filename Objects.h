#pragma once
#include <string>
using namespace std;

class Objects
{
protected:
	string fEffects;
	string fObjName;

public:
	Objects() { fEffects = "", fEffects = "";  }
	Objects(string effects, string name) { fEffects = effects, fObjName = name; }
	virtual ~Objects() = default;

	virtual string get_ObjName() { return fObjName; }
	virtual string get_ObjEffects() { return fEffects; }

};
