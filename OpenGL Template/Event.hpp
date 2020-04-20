#pragma once
#include "BoxCollider.hpp"
#include <list>

//these could maybe go into their own file?
typedef void (*BasicEventListener) (void);
typedef void (*CollisionEventListener) (BoxCollider); //maybe typedef specific types of events that will require specific parameters?

class Event 
{

private:
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

/*

Were going to need event listeners that can accept different kinds of parameters.

--We could either make an extension class for every kind of event listener or we 

*/