#pragma once
#include "Object.hpp"

class CollisionTester : public Object
{
public:
	CollisionTester(int width, int height);
	virtual ~CollisionTester() { }
	void sync();
};