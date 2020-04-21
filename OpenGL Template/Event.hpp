#pragma once
#include <list>
#include "BoxCollider.hpp"

//these could maybe go into their own file?
typedef void (*BasicEventListener) (void);
typedef void (*CollisionEventListener) (BoxCollider, BoxCollider);

class Event 
{

protected:
	std::list<BasicEventListener> Subscribers;

public:

	void RaiseEvent() {
		for (BasicEventListener listener : Subscribers) {
			listener();
		}
	}

	void Subscribe(BasicEventListener listener) {
		Subscribers.push_back(listener);
	}
};