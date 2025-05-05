#pragma once
#include <map>
#include <vector>
#include <string>

enum class ResourceType;
class ContainerBase;

class ContainerManager
{
private:
	static inline std::map<ResourceType, std::vector<ContainerBase*>*> containersMap;
	static std::string getTitle(ResourceType type);

public:
	static void clear();
	static void add(ResourceType type, ContainerBase* container);
	static void remove(ResourceType type, ContainerBase* container);
	static void imgui();
};
