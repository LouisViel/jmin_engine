#pragma once

enum class NodeType : int
{
	None = 0,
	Wall = 1 << 1,
	Wood = 1 << 2,
	Stone = 1 << 3,
	Coal = 1 << 4,
	Iron = 1 << 5,
};

constexpr inline NodeType operator|(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline NodeType operator&(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) & static_cast<int>(b));
}

constexpr inline NodeType operator+(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline NodeType operator-(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) & ~static_cast<int>(b));
}

constexpr inline bool operator==(NodeType a, NodeType b)
{
	return static_cast<int>(a) == static_cast<int>(b);
}

constexpr inline bool operator!=(NodeType a, NodeType b)
{
	return static_cast<int>(a) != static_cast<int>(b);
}

class NodeTypeHelper
{
public:
	static const NodeType Resources = NodeType::Wood | NodeType::Stone | NodeType::Coal | NodeType::Iron;
	static const NodeType All = NodeType::Wall | Resources;

	static const NodeType Buildable = All - NodeType::Wall;
	static const NodeType NonBuildable = All - Buildable;

	static bool has(NodeType a, NodeType b)
	{
		return (a & b) != NodeType::None;
	}
};