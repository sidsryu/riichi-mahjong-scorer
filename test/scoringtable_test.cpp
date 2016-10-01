#include "CppUTest/TestHarness.h"
#include "scoring-table.h"

using namespace std;
using namespace mahjong;

TEST_GROUP(ScoringTableTest)
{
	ScoringTable t;
};

TEST(ScoringTableTest, DealerWinByDiscard)
{
	CHECK_EQUAL(1500, t.dealerWinByDiscard(1, 30));
	CHECK_EQUAL(2000, t.dealerWinByDiscard(1, 40));
	CHECK_EQUAL(2400, t.dealerWinByDiscard(1, 50));
	CHECK_EQUAL(2900, t.dealerWinByDiscard(1, 60));
	CHECK_EQUAL(3400, t.dealerWinByDiscard(1, 70));

	CHECK_EQUAL(2000, t.dealerWinByDiscard(2, 20));
	CHECK_EQUAL(2900, t.dealerWinByDiscard(2, 30));
	CHECK_EQUAL(3900, t.dealerWinByDiscard(2, 40));
	CHECK_EQUAL(4800, t.dealerWinByDiscard(2, 50));
	CHECK_EQUAL(5800, t.dealerWinByDiscard(2, 60));
	CHECK_EQUAL(6800, t.dealerWinByDiscard(2, 70));

	CHECK_EQUAL(3900, t.dealerWinByDiscard(3, 20));
	CHECK_EQUAL(5800, t.dealerWinByDiscard(3, 30));
	CHECK_EQUAL(7700, t.dealerWinByDiscard(3, 40));
	CHECK_EQUAL(9600, t.dealerWinByDiscard(3, 50));
	CHECK_EQUAL(11600, t.dealerWinByDiscard(3, 60));

	CHECK_EQUAL(7700, t.dealerWinByDiscard(4, 20));
	CHECK_EQUAL(11600, t.dealerWinByDiscard(4, 30));
}

TEST(ScoringTableTest, DealerSelfDrawn)
{
	CHECK_EQUAL(500, t.dealerSelfDrawn(1, 30));
	CHECK_EQUAL(700, t.dealerSelfDrawn(1, 40));
	CHECK_EQUAL(800, t.dealerSelfDrawn(1, 50));
	CHECK_EQUAL(1000, t.dealerSelfDrawn(1, 60));
	CHECK_EQUAL(1200, t.dealerSelfDrawn(1, 70));

	CHECK_EQUAL(700, t.dealerSelfDrawn(2, 20));
	CHECK_EQUAL(1000, t.dealerSelfDrawn(2, 30));
	CHECK_EQUAL(1300, t.dealerSelfDrawn(2, 40));
	CHECK_EQUAL(1600, t.dealerSelfDrawn(2, 50));
	CHECK_EQUAL(2000, t.dealerSelfDrawn(2, 60));
	CHECK_EQUAL(2300, t.dealerSelfDrawn(2, 70));

	CHECK_EQUAL(1300, t.dealerSelfDrawn(3, 20));
	CHECK_EQUAL(2000, t.dealerSelfDrawn(3, 30));
	CHECK_EQUAL(2600, t.dealerSelfDrawn(3, 40));
	CHECK_EQUAL(3200, t.dealerSelfDrawn(3, 50));
	CHECK_EQUAL(3900, t.dealerSelfDrawn(3, 60));

	CHECK_EQUAL(2600, t.dealerSelfDrawn(4, 20));
	CHECK_EQUAL(3900, t.dealerSelfDrawn(4, 30));
}

TEST(ScoringTableTest, NonDealerWinByDiscard)
{
	CHECK_EQUAL(1000, t.nonDealerWinByDiscard(1, 30));
	CHECK_EQUAL(1300, t.nonDealerWinByDiscard(1, 40));
	CHECK_EQUAL(1600, t.nonDealerWinByDiscard(1, 50));
	CHECK_EQUAL(2000, t.nonDealerWinByDiscard(1, 60));
	CHECK_EQUAL(2300, t.nonDealerWinByDiscard(1, 70));

	CHECK_EQUAL(1300, t.nonDealerWinByDiscard(2, 20));
	CHECK_EQUAL(2000, t.nonDealerWinByDiscard(2, 30));
	CHECK_EQUAL(2600, t.nonDealerWinByDiscard(2, 40));
	CHECK_EQUAL(3200, t.nonDealerWinByDiscard(2, 50));
	CHECK_EQUAL(3900, t.nonDealerWinByDiscard(2, 60));
	CHECK_EQUAL(4500, t.nonDealerWinByDiscard(2, 70));

	CHECK_EQUAL(2600, t.nonDealerWinByDiscard(3, 20));
	CHECK_EQUAL(3900, t.nonDealerWinByDiscard(3, 30));
	CHECK_EQUAL(5200, t.nonDealerWinByDiscard(3, 40));
	CHECK_EQUAL(6400, t.nonDealerWinByDiscard(3, 50));
	CHECK_EQUAL(7700, t.nonDealerWinByDiscard(3, 60));

	CHECK_EQUAL(5200, t.nonDealerWinByDiscard(4, 20));
	CHECK_EQUAL(7700, t.nonDealerWinByDiscard(4, 30));
}

TEST(ScoringTableTest, NonDealerSelfDrawn)
{
	CHECK_EQUAL(300, t.nonDealerSelfDrawn(1, 30).first);
	CHECK_EQUAL(500, t.nonDealerSelfDrawn(1, 30).second);
	CHECK_EQUAL(400, t.nonDealerSelfDrawn(1, 40).first);
	CHECK_EQUAL(700, t.nonDealerSelfDrawn(1, 40).second);
	CHECK_EQUAL(400, t.nonDealerSelfDrawn(1, 50).first);
	CHECK_EQUAL(800, t.nonDealerSelfDrawn(1, 50).second);
	CHECK_EQUAL(500, t.nonDealerSelfDrawn(1, 60).first);
	CHECK_EQUAL(1000, t.nonDealerSelfDrawn(1, 60).second);
	CHECK_EQUAL(600, t.nonDealerSelfDrawn(1, 70).first);
	CHECK_EQUAL(1200, t.nonDealerSelfDrawn(1, 70).second);

	CHECK_EQUAL(400, t.nonDealerSelfDrawn(2, 20).first);
	CHECK_EQUAL(700, t.nonDealerSelfDrawn(2, 20).second);
	CHECK_EQUAL(500, t.nonDealerSelfDrawn(2, 30).first);
	CHECK_EQUAL(1000, t.nonDealerSelfDrawn(2, 30).second);
	CHECK_EQUAL(700, t.nonDealerSelfDrawn(2, 40).first);
	CHECK_EQUAL(1300, t.nonDealerSelfDrawn(2, 40).second);
	CHECK_EQUAL(800, t.nonDealerSelfDrawn(2, 50).first);
	CHECK_EQUAL(1600, t.nonDealerSelfDrawn(2, 50).second);
	CHECK_EQUAL(1000, t.nonDealerSelfDrawn(2, 60).first);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(2, 60).second);
	CHECK_EQUAL(1200, t.nonDealerSelfDrawn(2, 70).first);
	CHECK_EQUAL(2300, t.nonDealerSelfDrawn(2, 70).second);

	CHECK_EQUAL(700, t.nonDealerSelfDrawn(3, 20).first);
	CHECK_EQUAL(1300, t.nonDealerSelfDrawn(3, 20).second);
	CHECK_EQUAL(1000, t.nonDealerSelfDrawn(3, 30).first);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(3, 30).second);
	CHECK_EQUAL(1300, t.nonDealerSelfDrawn(3, 40).first);
	CHECK_EQUAL(2600, t.nonDealerSelfDrawn(3, 40).second);
	CHECK_EQUAL(1600, t.nonDealerSelfDrawn(3, 50).first);
	CHECK_EQUAL(3200, t.nonDealerSelfDrawn(3, 50).second);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(3, 60).first);
	CHECK_EQUAL(3900, t.nonDealerSelfDrawn(3, 60).second);

	CHECK_EQUAL(1300, t.nonDealerSelfDrawn(4, 20).first);
	CHECK_EQUAL(2600, t.nonDealerSelfDrawn(4, 20).second);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(4, 30).first);
	CHECK_EQUAL(3900, t.nonDealerSelfDrawn(4, 30).second);
}

TEST(ScoringTableTest, DealerWinByDiscard_ManganOrMore)
{
	CHECK_EQUAL(12000, t.dealerWinByDiscard(3, 70));
	CHECK_EQUAL(12000, t.dealerWinByDiscard(4, 40));
	CHECK_EQUAL(12000, t.dealerWinByDiscard(4, 70));
	CHECK_EQUAL(12000, t.dealerWinByDiscard(5, 0));

	CHECK_EQUAL(18000, t.dealerWinByDiscard(6, 0));
	CHECK_EQUAL(18000, t.dealerWinByDiscard(7, 0));

	CHECK_EQUAL(24000, t.dealerWinByDiscard(8, 0));
	CHECK_EQUAL(24000, t.dealerWinByDiscard(9, 0));
	CHECK_EQUAL(24000, t.dealerWinByDiscard(10, 0));

	CHECK_EQUAL(36000, t.dealerWinByDiscard(11, 0));
	CHECK_EQUAL(36000, t.dealerWinByDiscard(12, 0));

	CHECK_EQUAL(48000, t.dealerWinByDiscard(13, 0));
}

TEST(ScoringTableTest, DealerSelfDrawn_ManganOrMore)
{
	CHECK_EQUAL(4000, t.dealerSelfDrawn(3, 70));
	CHECK_EQUAL(4000, t.dealerSelfDrawn(4, 40));
	CHECK_EQUAL(4000, t.dealerSelfDrawn(4, 70));
	CHECK_EQUAL(4000, t.dealerSelfDrawn(5, 0));

	CHECK_EQUAL(6000, t.dealerSelfDrawn(6, 0));
	CHECK_EQUAL(6000, t.dealerSelfDrawn(7, 0));

	CHECK_EQUAL(8000, t.dealerSelfDrawn(8, 0));
	CHECK_EQUAL(8000, t.dealerSelfDrawn(9, 0));
	CHECK_EQUAL(8000, t.dealerSelfDrawn(10, 0));

	CHECK_EQUAL(12000, t.dealerSelfDrawn(11, 0));
	CHECK_EQUAL(12000, t.dealerSelfDrawn(12, 0));

	CHECK_EQUAL(16000, t.dealerSelfDrawn(13, 0));
}

TEST(ScoringTableTest, NonDealerWinByDiscard_ManganOrMore)
{
	CHECK_EQUAL(8000, t.nonDealerWinByDiscard(3, 70));
	CHECK_EQUAL(8000, t.nonDealerWinByDiscard(4, 40));
	CHECK_EQUAL(8000, t.nonDealerWinByDiscard(4, 70));
	CHECK_EQUAL(8000, t.nonDealerWinByDiscard(5, 0));

	CHECK_EQUAL(12000, t.nonDealerWinByDiscard(6, 0));
	CHECK_EQUAL(12000, t.nonDealerWinByDiscard(7, 0));

	CHECK_EQUAL(16000, t.nonDealerWinByDiscard(8, 0));
	CHECK_EQUAL(16000, t.nonDealerWinByDiscard(9, 0));
	CHECK_EQUAL(16000, t.nonDealerWinByDiscard(10, 0));

	CHECK_EQUAL(24000, t.nonDealerWinByDiscard(11, 0));
	CHECK_EQUAL(24000, t.nonDealerWinByDiscard(12, 0));

	CHECK_EQUAL(32000, t.nonDealerWinByDiscard(13, 0));
}

TEST(ScoringTableTest, NonDealerSelfDrawn_ManganOrMore)
{
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(3, 70).first);
	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(3, 70).second);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(4, 40).first);
	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(4, 40).second);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(4, 70).first);
	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(4, 70).second);
	CHECK_EQUAL(2000, t.nonDealerSelfDrawn(5, 0).first);
	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(5, 0).second);

	CHECK_EQUAL(3000, t.nonDealerSelfDrawn(6, 0).first);
	CHECK_EQUAL(6000, t.nonDealerSelfDrawn(6, 0).second);
	CHECK_EQUAL(3000, t.nonDealerSelfDrawn(7, 0).first);
	CHECK_EQUAL(6000, t.nonDealerSelfDrawn(7, 0).second);

	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(8, 0).first);
	CHECK_EQUAL(8000, t.nonDealerSelfDrawn(8, 0).second);
	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(9, 0).first);
	CHECK_EQUAL(8000, t.nonDealerSelfDrawn(9, 0).second);
	CHECK_EQUAL(4000, t.nonDealerSelfDrawn(10, 0).first);
	CHECK_EQUAL(8000, t.nonDealerSelfDrawn(10, 0).second);

	CHECK_EQUAL(6000, t.nonDealerSelfDrawn(11, 0).first);
	CHECK_EQUAL(12000, t.nonDealerSelfDrawn(11, 0).second);
	CHECK_EQUAL(6000, t.nonDealerSelfDrawn(12, 0).first);
	CHECK_EQUAL(12000, t.nonDealerSelfDrawn(12, 0).second);

	CHECK_EQUAL(8000, t.nonDealerSelfDrawn(13, 0).first);
	CHECK_EQUAL(16000, t.nonDealerSelfDrawn(13, 0).second);
}
