#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "Types.hpp"

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
	Entity* CreateEntity(std::string name)
	{
		return mEntityManager->CreateEntity(name);
	}

	void DestroyEntity(Entity* entity)
	{
		mEntityManager->DestroyEntity(entity->id);

		mComponentManager->EntityDestroyed(entity->id);

		mSystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity* entity, T component)
	{
		mComponentManager->AddComponent<T>(entity->id, component);

		auto signature = mEntityManager->GetSignature(entity->id);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity->id, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity* entity)
	{
		mComponentManager->RemoveComponent<T>(entity->id);

		auto signature = mEntityManager->GetSignature(entity->id);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity->id, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	void EnableEntity(Entity* entity)
	{
		auto signature = mEntityManager->GetSignature(entity->id);
		mSystemManager->EntityEnabled(entity, signature);
	}

	void DisableEntity(Entity* entity)
	{
		auto signature = mEntityManager->GetSignature(entity->id);
		mSystemManager->EntityDisabled(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity* entity)
	{
		return mComponentManager->GetComponent<T>(entity->id);
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