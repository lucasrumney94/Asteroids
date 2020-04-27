#pragma once

#include "Utils.h"

#include "System.hpp"
#include "Renderable.hpp"
#include "BoxCollider.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"
#include "Event.hpp"

#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>

typedef void (*CollisionEventListener) (Entity*, Entity*);

class BoxCollisionEvent
{
protected:
	std::list<CollisionEventListener> Subscribers;

public:
	void RaiseBoxCollisionEvent(Entity* owner, Entity* other);

	void Subscribe(CollisionEventListener listener)
	{
		Subscribers.push_back(listener);
	}
};

class BoxColliderSystem : public System
{
public:
	BoxCollisionEvent* boxCollisionEvent;

	bool DrawBoundingBox; //maybe for debug purposes.

	void Init() override;
	void Update() override;
	bool checkOverlap(Entity*, Entity*);
};

