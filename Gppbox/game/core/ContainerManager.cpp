#include "imgui.h"
#include <algorithm>
#include "ContainerManager.hpp"
#include "utils/ResourceType.hpp"
#include "game/object/containers/ContainerBase.hpp"
#include "engine/Utils.hpp"


void ContainerManager::clear()
{
	for (auto& itr : containersMap)
		delete itr.second;
	containersMap.clear();
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void ContainerManager::add(ResourceType type, ContainerBase* container)
{
	auto itr = containersMap.find(type);
	if (itr == containersMap.end()) {
		std::vector<ContainerBase*>* containers = new std::vector<ContainerBase*>();
		containers->emplace_back(container);
		containersMap.insert({ type, containers });
	} else itr->second->emplace_back(container);
}

void ContainerManager::remove(ResourceType type, ContainerBase* container)
{
	auto itr = containersMap.find(type);
	if (itr == containersMap.end()) return;
	auto id = std::find(itr->second->begin(), itr->second->end(), container);
	if (id != itr->second->end()) itr->second->erase(id);
	if (itr->second->size() <= 0) {
		delete itr->second;
		containersMap.erase(itr);
	}
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void ContainerManager::imgui()
{
	using namespace ImGui;
	if (CollapsingHeader("Resources", ImGuiTreeNodeFlags_DefaultOpen)) {

		if (containersMap.size() <= 0) {
			BulletText("No Ressources for now...");
		}

		for (auto& itr : containersMap) {

			// Calculate count for this resource
			int resourceCount = 0;
			for (ContainerBase* container : *itr.second)
				resourceCount = Utils::safeAdd(resourceCount, container->getCount());

			// Show Value
			std::string text = getTitle(itr.first);
			text += resourceCount > 10'000 ? " : %e" : " : %d";
			BulletText(text.c_str(), resourceCount);
		}
	}
}

std::string ContainerManager::getTitle(ResourceType type)
{
	switch (type) {
		// Wood
		case ResourceType::Wood: return "Wood";
		case ResourceType::Planks: return "Planks";

		// Stone
		case ResourceType::Stone: return "Stone";
		case ResourceType::Brick: return "Bricks";

		// Coal
		case ResourceType::Coal: return "Coal";

		// Iron
		case ResourceType::IronOre: return "Iron Ore";
		case ResourceType::IronIngot: return "Iron Ingot";
		case ResourceType::Nails: return "Nails";
	}
	return "ERROR";
}