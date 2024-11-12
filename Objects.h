#pragma once
#include <string>
using namespace std;

class Objects
{
protected:
	string fEffects;
	string fObjName;
	int fAmount;

public:
	Objects() { fEffects = "", fEffects = "", fAmount = 0; }
	Objects(string effects, string name, int amount) { fEffects = effects, fObjName = name, fAmount = amount;; }
	virtual ~Objects() = default;

	virtual string get_ObjName() { return fObjName; }
	virtual string get_ObjEffects() { return fEffects; }

};
