#pragma once

enum ResourceType
{
	// Specials
	Unknown = 0,

	// Wood
	Wood = 2,
	Planks = 4,

	// Stone
	Stone = 64,
	Brick = 128,

	// Coal
	Coal = 2048,

	// Iron
	IronOre = 65'536,
	IronIngot = 131'072,
	Nails = 262'144
};

constexpr inline ResourceType operator|(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline ResourceType operator&(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) & static_cast<int>(b));
}

constexpr inline ResourceType operator==(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) == static_cast<int>(b));
}

constexpr inline ResourceType operator!=(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) != static_cast<int>(b));
}

class ResourceTypeHelper
{
public:
	static const ResourceType Wood = ResourceType::Wood | ResourceType::Planks;
	static const ResourceType Stone = ResourceType::Stone | ResourceType::Brick;
	static const ResourceType Coal = ResourceType::Coal;
	static const ResourceType Iron = ResourceType::IronOre | ResourceType::IronIngot | ResourceType::Nails;
	static const ResourceType All = Wood | Stone | Coal | Iron;

	static bool has(ResourceType a, ResourceType b)
	{
		return (a & b) != ResourceType::Unknown;
	}
};