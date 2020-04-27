#pragma once
#include <list>
#include "BoxCollider.hpp"

//these could maybe go into their own file?
typedef void (*BasicEventListener) (void);
typedef void (*CollisionEventListener) (BoxCollider, BoxCollider);

class Event 
{
protected:
	std::list<T> Subscribers;

public:

	void RaiseEvent(...);

	void Subscribe(T listener);
};

class CollisionEvent {

protected:
	std::list<CollisionEventListener> Subscribers;

public:

	void RaiseEvent(BoxCollider owner, BoxCollider other) {
		for (CollisionEventListener listener : Subscribers) {
			listener(owner, other);
		}
	}

	void Subscribe(CollisionEventListener listener) {
		Subscribers.push_back(listener);
	}
};