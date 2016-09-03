#pragma once

class WiningHandCounter;

class MinipointCounter
{
public:
	MinipointCounter(const WiningHandCounter& hands);
	int total() const;

private:
	const WiningHandCounter& hands;
};
