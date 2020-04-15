#pragma once

#include "Types.hpp"
#include "Entity.hpp"
#include <queue>
#include <array>
#include <cassert>

class EntityManager
{
private:
	std::queue<EntityID> mAvailableEntities{};
	std::array<Entity*, MAX_ENTITIES> mEntities{};
	std::array<Signature, MAX_ENTITIES> mSignatures{};
	uint32_t mLivingEntityCount{};

public:
	EntityManager() {
		for (EntityID entityid = 0; entityid < MAX_ENTITIES; ++entityid)
		{
			mAvailableEntities.push(entityid);
		}
	}

	Entity* CreateEntity(std::string name)
	{
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		EntityID id = mAvailableEntities.front();
		Entity* newEntity = new Entity{ true, name, id };
		mEntities[id] = newEntity;
		mAvailableEntities.pop();
		++mLivingEntityCount;

		return newEntity;
	}

	void DestroyEntity(EntityID id)
	{
		assert(id < MAX_ENTITIES && "Entity out of range.");

		delete(mEntities[id]);
		mSignatures[id].reset();
		mAvailableEntities.push(id);
		--mLivingEntityCount;
	}

	void SetSignature(EntityID id, Signature signature)
	{
		assert(id < MAX_ENTITIES && "Entity out of range.");

		mSignatures[id] = signature;
	}

	Signature GetSignature(EntityID id)
	{
		assert(id < MAX_ENTITIES && "Entity out of range.");

		return mSignatures[id];
	}
};