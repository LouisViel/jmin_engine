#pragma once

enum NodeType
{
	None = 0,
	Wall = 1,
	Wood = 2,
	Stone = 4,
	Coal = 8,
	Iron = 16,
};

constexpr inline NodeType operator|(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline NodeType operator&(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) & static_cast<int>(b));
}

constexpr inline NodeType operator==(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) == static_cast<int>(b));
}

constexpr inline NodeType operator!=(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) != static_cast<int>(b));
}

class NodeTypeHelper
{
public:
	static const NodeType Resources = NodeType::Wood | NodeType::Stone | NodeType::Coal | NodeType::Iron;
	static const NodeType All = NodeType::Wall | Resources;

	static const NodeType Buildable = static_cast<NodeType>(All - NodeType::Wall);
	static const NodeType NonBuildable = static_cast<NodeType>(All - Buildable);

	static bool has(NodeType a, NodeType b)
	{
		return (a & b) != NodeType::None;
	}
};