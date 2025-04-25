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

inline NodeType operator|(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) | static_cast<int>(b));
}

inline NodeType operator&(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) & static_cast<int>(b));
}

inline NodeType operator==(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) == static_cast<int>(b));
}

inline NodeType operator!=(NodeType a, NodeType b)
{
	return static_cast<NodeType>(static_cast<int>(a) != static_cast<int>(b));
}

class NodeTypeHelper
{
public:
	const NodeType Resources = NodeType::Wood | NodeType::Stone | NodeType::Coal | NodeType::Iron;
	const NodeType All = NodeType::Wall | Resources;

	const NodeType Buildable = static_cast<NodeType>(All - NodeType::Wall);
	const NodeType NonBuildable = static_cast<NodeType>(All - Buildable);

	bool has(NodeType a, NodeType b)
	{
		return (a & b) != NodeType::None;
	}
};