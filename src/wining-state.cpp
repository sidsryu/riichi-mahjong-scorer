#include "wining-state.h"
#include <cassert>

void WiningState::setRiichi()
{
	assert(!is_double_riichi);
	is_riichi = true;
}

void WiningState::setDoubleRiichi()
{
	assert(!is_riichi);
	is_double_riichi = true;
}

void WiningState::setRon()
{
	assert(!is_tsumo);
	is_ron = true;
}

void WiningState::setTsumo()
{
	assert(!is_ron);	
	is_tsumo = true;
}

bool WiningState::isRiichi() const
{
	return is_riichi;
}

bool WiningState::isDoubleRiichi() const
{
	return is_double_riichi;
}

bool WiningState::isRon() const
{
	return is_ron;
}

bool WiningState::isTsumo() const
{
	return is_tsumo;
}
