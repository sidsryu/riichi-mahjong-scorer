#pragma once

#include <set>
#include <map>

enum class Pattern;
class PlayerHand;
class WiningState;

class DoublingFactorTable
{
public:
	DoublingFactorTable(const PlayerHand& hand, const WiningState& state);
	int total(const std::set<Pattern>& patterns) const;

private:
	int factor(Pattern pattern) const;

private:
	const PlayerHand& hand;
	const WiningState& state;
	std::map<Pattern, int> factor_table;
};
