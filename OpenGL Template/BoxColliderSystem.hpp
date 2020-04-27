#pragma once

#include "Utils.h"

#include "Event.hpp"
#include "System.hpp"
#include "Renderable.hpp"
#include "BoxCollider.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"

#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>

typedef void (*CollisionEventListener) (Entity*, Entity*);

class BoxCollisionEvent : public Event<CollisionEventListener>
{

public:
	void RaiseBoxCollisionEvent(Entity* owner, Entity* other);

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
