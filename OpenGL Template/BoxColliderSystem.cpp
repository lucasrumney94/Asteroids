#include "BoxColliderSystem.hpp"

extern Coordinator gCoordinator;

void BoxCollisionEvent::RaiseBoxCollisionEvent(Entity* owner, Entity* other) {
	for (BoxCollisionEventListener listener : Subscribers) {
		listener(owner, other);
	}
}

void BoxColliderSystem::Init() {
	boxCollisionEvent = new BoxCollisionEvent();
	for (auto const& firstEntity : mEntities)
	{

	}
}


void BoxColliderSystem::Update() {

	for (auto const& firstEntity : mEntities)
	{
		for (auto const& secondEntity : mEntities)
		{
			// do not collide with self
			if (firstEntity->id == secondEntity->id) {
				continue;
			}

			if (checkOverlap(firstEntity, secondEntity)) {
				// Raise event
				boxCollisionEvent->RaiseBoxCollisionEvent(firstEntity, secondEntity);
			}
		}
	}
	//std::cout << "collisions: " << collisions << std::endl;
}

bool BoxColliderSystem::checkOverlap(Entity* firstEntity, Entity* secondEntity) {
	auto& firstTransform = gCoordinator.GetComponent<Transform>(firstEntity);
	BoxCollider& firstCollider = gCoordinator.GetComponent<BoxCollider>(firstEntity);

	auto& secondTransform = gCoordinator.GetComponent<Transform>(secondEntity);
	BoxCollider& secondCollider = gCoordinator.GetComponent<BoxCollider>(secondEntity);

	float firstMinX = firstTransform.GetPosition().x - (firstCollider.boundingBox.x) / 2.0f;
	float firstMaxX = firstTransform.GetPosition().x + (firstCollider.boundingBox.x) / 2.0f;
	float firstMinY = firstTransform.GetPosition().y - (firstCollider.boundingBox.y) / 2.0f;
	float firstMaxY = firstTransform.GetPosition().y + (firstCollider.boundingBox.y) / 2.0f;
	float firstMinZ = firstTransform.GetPosition().z - (firstCollider.boundingBox.z) / 2.0f;
	float firstMaxZ = firstTransform.GetPosition().z + (firstCollider.boundingBox.z) / 2.0f;

	float secondMinX = secondTransform.GetPosition().x - (secondCollider.boundingBox.x) / 2.0f;
	float secondMaxX = secondTransform.GetPosition().x + (secondCollider.boundingBox.x) / 2.0f;
	float secondMinY = secondTransform.GetPosition().y - (secondCollider.boundingBox.y) / 2.0f;
	float secondMaxY = secondTransform.GetPosition().y + (secondCollider.boundingBox.y) / 2.0f;
	float secondMinZ = secondTransform.GetPosition().z - (secondCollider.boundingBox.z) / 2.0f;
	float secondMaxZ = secondTransform.GetPosition().z + (secondCollider.boundingBox.z) / 2.0f;

	return ((firstMinX <= secondMaxX) && (firstMaxX >= secondMinX)) && 
		((firstMinY <= secondMaxY) && (firstMaxY >= secondMinY)) &&
		((firstMinZ <= secondMaxZ) && (firstMaxZ >= secondMinZ));
}