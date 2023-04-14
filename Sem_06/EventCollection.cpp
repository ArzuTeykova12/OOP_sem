#include "EventCollection.h"


void EventCollection::addEvent(const Event& event)
{
	if (eventNum == MAX_EVENTS)
	{
		return false;
	}
	
	event[eventNum] = event; 
	eventNum++;

	return true;
}
void EventCollection::removeEvent(char* name)
{
	
	int index = -1;
	for (int i = 0; i < eventNum; i++) {
		if (strcmp(event[i].name(), name) == 0) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		return; 
	}
	for (int i = index; i < eventNum - 1; i++) {
		std::swap(event[i], event[i + 1]);
	}
	eventNum--;
}
Event* EventCollection::theLongestEvent() const
{

	const Event* longest = event[0];
	for (int i = 1; i < eventNum; i++)
	{
		unsigned int longestE = longest->getStartTime();
		unsigned int currentE = event[i].getStartTime();


		if (currentE > longestE) {
			longest = event[i];
		}
	}
	return longest;
}
int EventCollection::maxEvent(const Date& date) const
{
	int numEvents = 0;
	for (int i = 0; i < eventNum; i++) {
		if (event[i].getDate().isEqualTo(date)) { 
			numEvents++;
		}
	}
	return numEvents;
}
