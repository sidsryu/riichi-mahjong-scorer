#include "dragons-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

void DragonsRecognizer::reset()
{
	dragon_count = 0;
	is_dragon_pair = false;
}

void DragonsRecognizer::check(const Pair& pair)
{
	if (pair.isDragons())
	{
		is_dragon_pair = true;
	}
}

void DragonsRecognizer::check(const Meld& meld)
{
	if (meld.isDragons())
	{
		dragon_count++;
	}
}

std::set<Pattern> DragonsRecognizer::recognize()
{
	if (is_dragon_pair && dragon_count == 2)
	{
		return { Pattern::LittleThreeDragons };
	}

	if (dragon_count == 3)
	{
		return { Pattern::BigThreeDragons };
	}

	return {};
}
