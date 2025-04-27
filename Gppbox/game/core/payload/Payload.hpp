#pragma once

class PayloadPool;
class PayloadBase;
typedef PayloadBase Payload;

class PayloadBase
{
private:
	friend class PayloadPool;
	bool pool = false;
	PayloadBase() : pool(true) { }

public:
	int quantity = -1;
	PayloadBase(int qty) : quantity(qty) { }
};
