#include "Entity.h"

Entity::Entity()
{
	fName = "";
	fDeathOrAlive = true;
}

Entity::Entity(string name, bool liveordeath)
{
	fName = name;
	fDeathOrAlive = liveordeath;
}





