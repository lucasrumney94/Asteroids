#pragma once

#include "Types.hpp"
#include "Entity.hpp"
#include "Coordinator.hpp"
#include <array>
#include <cassert>
#include <unordered_map>
#include <exception>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(EntityID entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{

private:
	std::array<T, MAX_ENTITIES> mComponentArray{};
	std::unordered_map<EntityID, size_t> mEntityToIndexMap{};
	std::unordered_map<size_t, EntityID> mIndexToEntityMap{};
	size_t mSize{};

public:
	void InsertData(EntityID entity, T component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end
		size_t newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentArray[newIndex] = component;
		++mSize;
	}

	void RemoveData(EntityID entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1;
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		EntityID entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		--mSize;
	}

	bool HasData(EntityID entity)
	{
		return mEntityToIndexMap.find(entity) != mEntityToIndexMap.end();
	}

	T& GetData(EntityID entity)
	{
		// Check if entity does not exist in entity to index map (find will return an iterator past the bounds of the list if not found)
		if (mEntityToIndexMap.find(entity) == mEntityToIndexMap.end())
		{
			throw std::runtime_error("dont work");
		}

		return mComponentArray[mEntityToIndexMap[entity]];
	}

	void EntityDestroyed(EntityID entity) override
	{
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

};