#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "Types.hpp"
#include <iostream>
#include <typeinfo>

class Coordinator
{
private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<SystemManager> mSystemManager;

	// TODO: Queues for enable/disable, add/destroy entities

public:
	void Init()
	{
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}

	// TODO: Update function, goes through entity queues


	// Entity methods
	Entity CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	void EnableEntity(Entity entity)
	{
		auto signature = mEntityManager->GetSignature(entity);
		mSystemManager->EntityEnabled(entity, signature);
	}

	void DisableEntity(Entity entity)
	{
		auto signature = mEntityManager->GetSignature(entity);
		mSystemManager->EntityDisabled(entity, signature);
	}

	template<typename T>
	bool HasComponent(Entity entity)
	{
		return mComponentManager->HasComponent<T>(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		try
		{
			return mComponentManager->GetComponent<T>(entity);
		}
		catch (...)
		{
			std::cout << "Tried to retrieve non-existent component " << typeid(T).name() << " on entity " << entity << std::endl;
			throw;
		}
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}

	void InitSystems() {
		mSystemManager->InitSystems();
	}

	void UpdateSystems() {
		mSystemManager->UpdateSystems();
	}
};