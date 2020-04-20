#pragma once

#include "Entity.hpp"
#include <set>

class System
{
public:
	std::set<Entity*> mEntities;
	virtual void Update() = 0;
	virtual void Init() = 0;
};