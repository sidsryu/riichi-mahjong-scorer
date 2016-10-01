#pragma once

namespace mahjong {
enum class Pattern;

struct IsLimitHand
{
	bool operator()(const Pattern& pattern) const;
};
}
