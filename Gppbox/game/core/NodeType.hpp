#pragma once

enum NodeType
{
	None = 0,
	Wood = 1,
	Stone = 2,
	Coal = 4,
	Iron = 8,
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