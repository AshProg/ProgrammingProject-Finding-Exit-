#include "Objects.h"

Objects::Objects()
{
	fEffects = "", fEffects = "";
}

Objects::Objects(string effects, string name) 
{ 
	fEffects = effects;
	fObjName = name; 
}

string Objects::get_ObjName()
{
	return fObjName;
}

string Objects::get_ObjEffects()
{
	return fEffects;
}