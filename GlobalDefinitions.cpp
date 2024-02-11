#include "GlobalDefinitions.h"

bool IsValueInBounds(short value, short bottomBorder, short topBorder)
{
	return value >= bottomBorder && value < topBorder;
}
