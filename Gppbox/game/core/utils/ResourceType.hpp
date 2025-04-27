#pragma once

enum class ResourceType : int
{
	// Specials
	Unknown = 0,

	// Wood
	Wood = 1 << 1,
	Planks = 1 << 2,

	// Stone
	Stone = 1 << 6,
	Brick = 1 << 7,

	// Coal
	Coal = 1 << 11,

	// Iron
	IronOre = 1 << 16,
	IronIngot = 1 << 17,
	Nails = 1 << 18
};

constexpr inline ResourceType operator|(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline ResourceType operator&(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) & static_cast<int>(b));
}

constexpr inline ResourceType operator+(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline ResourceType operator-(ResourceType a, ResourceType b)
{
	return static_cast<ResourceType>(static_cast<int>(a) & ~static_cast<int>(b));
}

constexpr inline bool operator==(ResourceType a, ResourceType b)
{
	return static_cast<int>(a) == static_cast<int>(b);
}

constexpr inline bool operator!=(ResourceType a, ResourceType b)
{
	return static_cast<int>(a) != static_cast<int>(b);
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