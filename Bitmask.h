#pragma once

#include <stdint.h>

//Вспомогательный класс
//Удобная обертка для побитовой маски
class Bitmask
{
public:
	Bitmask();

	void SetMask(Bitmask& other);
	uint64_t GetMask() const;

	bool GetBit(int pos) const;
	void SetBit(int pos, bool on);

	void SetBit(int pos);
	void ClearBit(int pos);

	void Clear();

	bool operator < (const Bitmask& right) const
	{
		return this->bits < right.bits;
	}
	bool operator > (const Bitmask& right) const
	{
		return this->bits > right.bits;
	}

private:
	uint64_t bits;
};
