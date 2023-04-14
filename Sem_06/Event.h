#pragma once
#include "Time.h"
#include "Date.h"


class Event
{
private:
	char name[50];
	Date date;
	Time startTime;

	void setName(const char* name);


public:
	Event(const char* name, const Date& date, const Time& startTime);

	

	int dayOfWeekEvent() const ;

	void print() const;

	const char* getName() const;
	const Date& getDate() const;
	const Time& getStartTime() const;
};

