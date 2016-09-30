#pragma once

#include <set>
#include <map>

enum class Pattern;
class WiningState;

class DoublingFactorTable
{
public:
	DoublingFactorTable(const WiningState& state);
	int total(const std::set<Pattern>& patterns) const;

private:
	int factor(Pattern pattern) const;

private:
	const WiningState& state;
	std::map<Pattern, int> factor_table;
};
