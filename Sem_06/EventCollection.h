#pragma once
#include "Event.h"

const int MAX_EVENTS = 30;

class EventCollection
{
private:

	Event event[MAX_EVENTS];
	unsigned int eventNum = 0;

public:

	void addEvent(const Event& event);
	void removeEvent(char* name);
	Event* theLongestEvent() const;
	int maxEvent(const Date& date) const;

};

