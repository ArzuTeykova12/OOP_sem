#include "Event.h"
#pragma warning(disable : 4996)


void Event::setName(const char* name)
{
	if (strlen(name) > 50)
	{
		return;
	}
	else
	{
		strcpy(this->name, name);
	}

}


Event::Event(const char* name,const Date& date, const Time& startTime) : date(date), startTime(startTime)
{
	setName(name);
}

int Event::dayOfWeekEvent() const
{
	date.getDayOfWeek();
}

void Event::print() const
{
	std::cout << std::setw(2) << std::setfill('0') << name << '.' << std::setw(2) << std::setfill('0') << date << '.';
	std::cout << std::setw(3) << std::setfill('0') << startTime;
}

const char* Event::getName() const
{
	return name;

}
const Date& Event::getDate() const
{
	return date;

}
const Time& Event::getStartTime() const
{
	return startTime;

}
