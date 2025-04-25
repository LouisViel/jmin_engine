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
		\
		/* Prepare full check Variables */ \
		Collider* collider = object->collider; \
		int xposMin(int(collider->rx - collider->width - C::E_ADJUSTMENT_X + collider->cx)); \
		int xposMax(int(collider->rx + collider->width + collider->cx)); \
		float cry(collider->cy + collider->ry); \
		\
		/* Process full body check */ \
		for (float ypos = cry, ytarget = cry - collider->height; ypos > ytarget; --ypos) { \
			for (int xpos = xposMin; xpos <= xposMax; ++xpos) { \
				if (condition) return true;\
			} \
		} \
		\
		/* No collision */ \
		return false;


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