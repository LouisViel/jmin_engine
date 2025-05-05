#pragma once
#include "C.hpp"

namespace M
{
	// NO_UPDATE(dt)
	#define NO_UPDATE(dt) if (dt <= 0.0) { return; }


	// FULL_CHECK(object, (xpos == targetX && int(ypos) == targetY))
	#define FULL_CHECK(object, condition) \
		/* Verify object */ \
		if (!object || !object->collider) return false; \
		Collider* collider = object->collider; \
		if (collider->width * collider->height <= 0.0f) return false; \
		\
		/* Prepare full check Variables */ \
		int xposMin(int(collider->rx + collider->cx)); \
		int xposMax(int(xposMin + collider->width)); \
		float yposMin(collider->cy + collider->ry); \
		float yposMax(yposMin + collider->height); \
		\
		/* Process full body check */ \
		for (float ypos = yposMin; ypos < yposMax; ++ypos) { \
			for (int xpos = xposMin; xpos < xposMax; ++xpos) { \
				if (condition) return true;\
			} \
		} \
		\
		/* No collision */ \
		return false;

	// FULL_COLLISION(object, vector.emplace_back(xpos, ypos))
	#define FULL_COLLISION(object, output, action) \
		/* Verify object */ \
		if (!object || !object->collider) output; \
		Collider* collider = object->collider; \
		if (collider->width * collider->height <= 0.0f) output; \
		\
		/* Prepare full check Variables */ \
		int xposMin(int(collider->rx + collider->cx)); \
		int xposMax(int(xposMin + collider->width)); \
		float yposMin(collider->cy + collider->ry); \
		float yposMax(yposMin + collider->height); \
		\
		/* Process full body check */ \
		for (float ypos = yposMin; ypos < yposMax; ++ypos) { \
			for (int xpos = xposMin; xpos < xposMax; ++xpos) { \
				action; \
			} \
		}



	// REMOVE_ITEM(Object*, gameobjects, target)
	#define REMOVE_ITEM(objType, vector, obj) \
		for (int i = 0; i < (int)vector->size(); ++i) { \
			objType iobj = vector->operator[](i); \
			if (iobj == obj) vector->erase(vector->begin() + i); \
		}


	// GET_AXIS_MULTIPLE(result.x, < 0.0f, ({ -1, 2 }))
	#define GET_AXIS_MULTIPLE(output, operation, values) \
		/* Initialize dynamic containers */ \
		std::vector<float> vals = std::vector<float>values; \
		std::vector<float> results = std::vector<float>(); \
		\
		/* Get & Format all valid values */ \
		for (int i = 0; i < (int)vals.size(); ++i) { \
			if (vals[i] operation) { \
				results.push_back(std::abs(vals[i])); \
			} \
		} \
		\
		/* Output final result */ \
		if (results.size() > 0) { \
			output = *std::max_element(results.begin(), results.end()); \
		}


	// Loop Forward on vector
	// LOOPF_PTR(gameobjects, Object*)
	#define LOOPF(vector, obj) \
		for (int i = 0; i < (int)vector.size(); ++i) { \
			obj = vector[i];

	// Loop Backward on vector
	// LOOPF_PTR(gameobjects, Object*)
	#define LOOPB(vector, obj) \
		for (int i = (int)vector.size() - 1; i >= 0; --i) { \
			obj = vector[i];

	// Loop Forward on pointer vector
	// LOOPF_PTR(gameobjects, Object*)
	#define LOOPF_PTR(vector, obj) \
		for (int i = 0; i < (int)vector->size(); ++i) { \
			obj = vector->operator[](i);

	// Loop Backward on pointer vector
	// LOOPF_PTR(gameobjects, Object*)
	#define LOOPB_PTR(vector, obj) \
		for (int i = (int)vector->size() - 1; i >= 0; --i) { \
			obj = vector->operator[](i);

	// LOOP_END;
	#define LOOP_END }
}