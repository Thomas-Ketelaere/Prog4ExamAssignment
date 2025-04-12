#pragma once
#include "Hash.h"

using EventId = unsigned int;

struct Event
{
	const EventId id;
	explicit Event(EventId _id) : id{ _id } {}
};