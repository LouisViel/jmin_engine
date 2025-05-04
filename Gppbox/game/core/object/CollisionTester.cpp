#include "CollisionTester.hpp"
#include "Collider.hpp"

CollisionTester::CollisionTester(int width, int height) : Object()
{
	this->collider = new Collider((float)width, (float)height);
}

void CollisionTester::sync()
{
	collider->sync(getPosition());
}