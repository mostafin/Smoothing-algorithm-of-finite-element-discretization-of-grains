#include "vertex.h"


vertex::vertex()
{
}

vertex::vertex(const vertex & other)
{
	this->loc = other.loc;
	this->id = other.id;
}

bool vertex::operator==(const vertex & other)
{
	return loc == other.loc;
}


vertex::~vertex()
{
}
