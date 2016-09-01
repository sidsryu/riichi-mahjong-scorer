#include "CppUTest/TestHarness.h"
#include "scoring-table.h"

using namespace std;

TEST_GROUP(ScoringTableTest)
{
	ScoringTable t;
};

TEST(ScoringTableTest, DealerRon)
{
	CHECK_EQUAL(1500, t.dealerRon(1, 30));
	CHECK_EQUAL(2000, t.dealerRon(1, 40));
	CHECK_EQUAL(2400, t.dealerRon(1, 50));
	CHECK_EQUAL(2900, t.dealerRon(1, 60));
	CHECK_EQUAL(3400, t.dealerRon(1, 70));

	CHECK_EQUAL(2000, t.dealerRon(2, 20));
	CHECK_EQUAL(2900, t.dealerRon(2, 30));
	CHECK_EQUAL(3900, t.dealerRon(2, 40));
	CHECK_EQUAL(4800, t.dealerRon(2, 50));
	CHECK_EQUAL(5800, t.dealerRon(2, 60));
	CHECK_EQUAL(6800, t.dealerRon(2, 70));

	CHECK_EQUAL(3900, t.dealerRon(3, 20));
	CHECK_EQUAL(5800, t.dealerRon(3, 30));
	CHECK_EQUAL(7700, t.dealerRon(3, 40));
	CHECK_EQUAL(9600, t.dealerRon(3, 50));
	CHECK_EQUAL(11600, t.dealerRon(3, 60));

	CHECK_EQUAL(7700, t.dealerRon(4, 20));
	CHECK_EQUAL(11600, t.dealerRon(4, 30));
}

TEST(ScoringTableTest, DealerTsumo)
{
	CHECK_EQUAL(500, t.dealerTsumo(1, 30));
	CHECK_EQUAL(700, t.dealerTsumo(1, 40));
	CHECK_EQUAL(800, t.dealerTsumo(1, 50));
	CHECK_EQUAL(1000, t.dealerTsumo(1, 60));
	CHECK_EQUAL(1200, t.dealerTsumo(1, 70));

	CHECK_EQUAL(700, t.dealerTsumo(2, 20));
	CHECK_EQUAL(1000, t.dealerTsumo(2, 30));
	CHECK_EQUAL(1300, t.dealerTsumo(2, 40));
	CHECK_EQUAL(1600, t.dealerTsumo(2, 50));
	CHECK_EQUAL(2000, t.dealerTsumo(2, 60));
	CHECK_EQUAL(2300, t.dealerTsumo(2, 70));

	CHECK_EQUAL(1300, t.dealerTsumo(3, 20));
	CHECK_EQUAL(2000, t.dealerTsumo(3, 30));
	CHECK_EQUAL(2600, t.dealerTsumo(3, 40));
	CHECK_EQUAL(3200, t.dealerTsumo(3, 50));
	CHECK_EQUAL(3900, t.dealerTsumo(3, 60));

	CHECK_EQUAL(2600, t.dealerTsumo(4, 20));
	CHECK_EQUAL(3900, t.dealerTsumo(4, 30));
}

TEST(ScoringTableTest, NonDealerRon)
{
	CHECK_EQUAL(1000, t.nonDealerRon(1, 30));
	CHECK_EQUAL(1300, t.nonDealerRon(1, 40));
	CHECK_EQUAL(1600, t.nonDealerRon(1, 50));
	CHECK_EQUAL(2000, t.nonDealerRon(1, 60));
	CHECK_EQUAL(2300, t.nonDealerRon(1, 70));

	CHECK_EQUAL(1300, t.nonDealerRon(2, 20));
	CHECK_EQUAL(2000, t.nonDealerRon(2, 30));
	CHECK_EQUAL(2600, t.nonDealerRon(2, 40));
	CHECK_EQUAL(3200, t.nonDealerRon(2, 50));
	CHECK_EQUAL(3900, t.nonDealerRon(2, 60));
	CHECK_EQUAL(4500, t.nonDealerRon(2, 70));

	CHECK_EQUAL(2600, t.nonDealerRon(3, 20));
	CHECK_EQUAL(3900, t.nonDealerRon(3, 30));
	CHECK_EQUAL(5200, t.nonDealerRon(3, 40));
	CHECK_EQUAL(6400, t.nonDealerRon(3, 50));
	CHECK_EQUAL(7700, t.nonDealerRon(3, 60));

	CHECK_EQUAL(5200, t.nonDealerRon(4, 20));
	CHECK_EQUAL(7700, t.nonDealerRon(4, 30));
}

TEST(ScoringTableTest, NonDealerTsumo)
{
	CHECK_EQUAL(300, t.nonDealerTsumo(1, 30).first);
	CHECK_EQUAL(500, t.nonDealerTsumo(1, 30).second);
	CHECK_EQUAL(400, t.nonDealerTsumo(1, 40).first);
	CHECK_EQUAL(700, t.nonDealerTsumo(1, 40).second);
	CHECK_EQUAL(400, t.nonDealerTsumo(1, 50).first);
	CHECK_EQUAL(800, t.nonDealerTsumo(1, 50).second);
	CHECK_EQUAL(500, t.nonDealerTsumo(1, 60).first);
	CHECK_EQUAL(1000, t.nonDealerTsumo(1, 60).second);
	CHECK_EQUAL(600, t.nonDealerTsumo(1, 70).first);
	CHECK_EQUAL(1200, t.nonDealerTsumo(1, 70).second);

	CHECK_EQUAL(400, t.nonDealerTsumo(2, 20).first);
	CHECK_EQUAL(700, t.nonDealerTsumo(2, 20).second);
	CHECK_EQUAL(500, t.nonDealerTsumo(2, 30).first);
	CHECK_EQUAL(1000, t.nonDealerTsumo(2, 30).second);
	CHECK_EQUAL(700, t.nonDealerTsumo(2, 40).first);
	CHECK_EQUAL(1300, t.nonDealerTsumo(2, 40).second);
	CHECK_EQUAL(800, t.nonDealerTsumo(2, 50).first);
	CHECK_EQUAL(1600, t.nonDealerTsumo(2, 50).second);
	CHECK_EQUAL(1000, t.nonDealerTsumo(2, 60).first);
	CHECK_EQUAL(2000, t.nonDealerTsumo(2, 60).second);
	CHECK_EQUAL(1200, t.nonDealerTsumo(2, 70).first);
	CHECK_EQUAL(2300, t.nonDealerTsumo(2, 70).second);

	CHECK_EQUAL(700, t.nonDealerTsumo(3, 20).first);
	CHECK_EQUAL(1300, t.nonDealerTsumo(3, 20).second);
	CHECK_EQUAL(1000, t.nonDealerTsumo(3, 30).first);
	CHECK_EQUAL(2000, t.nonDealerTsumo(3, 30).second);
	CHECK_EQUAL(1300, t.nonDealerTsumo(3, 40).first);
	CHECK_EQUAL(2600, t.nonDealerTsumo(3, 40).second);
	CHECK_EQUAL(1600, t.nonDealerTsumo(3, 50).first);
	CHECK_EQUAL(3200, t.nonDealerTsumo(3, 50).second);
	CHECK_EQUAL(2000, t.nonDealerTsumo(3, 60).first);
	CHECK_EQUAL(3900, t.nonDealerTsumo(3, 60).second);

	CHECK_EQUAL(1300, t.nonDealerTsumo(4, 20).first);
	CHECK_EQUAL(2600, t.nonDealerTsumo(4, 20).second);
	CHECK_EQUAL(2000, t.nonDealerTsumo(4, 30).first);
	CHECK_EQUAL(3900, t.nonDealerTsumo(4, 30).second);
}

TEST(ScoringTableTest, DealerRonManganOrMore)
{
	CHECK_EQUAL(12000, t.dealerRon(3, 70));
	CHECK_EQUAL(12000, t.dealerRon(4, 40));
	CHECK_EQUAL(12000, t.dealerRon(4, 70));
	CHECK_EQUAL(12000, t.dealerRon(5, 0));

	CHECK_EQUAL(18000, t.dealerRon(6, 0));
	CHECK_EQUAL(18000, t.dealerRon(7, 0));

	CHECK_EQUAL(24000, t.dealerRon(8, 0));
	CHECK_EQUAL(24000, t.dealerRon(9, 0));
	CHECK_EQUAL(24000, t.dealerRon(10, 0));

	CHECK_EQUAL(36000, t.dealerRon(11, 0));
	CHECK_EQUAL(36000, t.dealerRon(12, 0));

	CHECK_EQUAL(48000, t.dealerRon(13, 0));
}

TEST(ScoringTableTest, DealerTsumoManganOrMore)
{
	CHECK_EQUAL(4000, t.dealerTsumo(3, 70));
	CHECK_EQUAL(4000, t.dealerTsumo(4, 40));
	CHECK_EQUAL(4000, t.dealerTsumo(4, 70));
	CHECK_EQUAL(4000, t.dealerTsumo(5, 0));

	CHECK_EQUAL(6000, t.dealerTsumo(6, 0));
	CHECK_EQUAL(6000, t.dealerTsumo(7, 0));

	CHECK_EQUAL(8000, t.dealerTsumo(8, 0));
	CHECK_EQUAL(8000, t.dealerTsumo(9, 0));
	CHECK_EQUAL(8000, t.dealerTsumo(10, 0));

	CHECK_EQUAL(12000, t.dealerTsumo(11, 0));
	CHECK_EQUAL(12000, t.dealerTsumo(12, 0));

	CHECK_EQUAL(16000, t.dealerTsumo(13, 0));
}

TEST(ScoringTableTest, NonDealerRonManganOrMore)
{
	CHECK_EQUAL(8000, t.nonDealerRon(3, 70));
	CHECK_EQUAL(8000, t.nonDealerRon(4, 40));
	CHECK_EQUAL(8000, t.nonDealerRon(4, 70));
	CHECK_EQUAL(8000, t.nonDealerRon(5, 0));

	CHECK_EQUAL(12000, t.nonDealerRon(6, 0));
	CHECK_EQUAL(12000, t.nonDealerRon(7, 0));

	CHECK_EQUAL(16000, t.nonDealerRon(8, 0));
	CHECK_EQUAL(16000, t.nonDealerRon(9, 0));
	CHECK_EQUAL(16000, t.nonDealerRon(10, 0));

	CHECK_EQUAL(24000, t.nonDealerRon(11, 0));
	CHECK_EQUAL(24000, t.nonDealerRon(12, 0));

	CHECK_EQUAL(32000, t.nonDealerRon(13, 0));
}

TEST(ScoringTableTest, NonDealerTsumoManganOrMore)
{
	CHECK_EQUAL(2000, t.nonDealerTsumo(3, 70).first);
	CHECK_EQUAL(4000, t.nonDealerTsumo(3, 70).second);
	CHECK_EQUAL(2000, t.nonDealerTsumo(4, 40).first);
	CHECK_EQUAL(4000, t.nonDealerTsumo(4, 40).second);
	CHECK_EQUAL(2000, t.nonDealerTsumo(4, 70).first);
	CHECK_EQUAL(4000, t.nonDealerTsumo(4, 70).second);
	CHECK_EQUAL(2000, t.nonDealerTsumo(5, 0).first);
	CHECK_EQUAL(4000, t.nonDealerTsumo(5, 0).second);

	CHECK_EQUAL(3000, t.nonDealerTsumo(6, 0).first);
	CHECK_EQUAL(6000, t.nonDealerTsumo(6, 0).second);
	CHECK_EQUAL(3000, t.nonDealerTsumo(7, 0).first);
	CHECK_EQUAL(6000, t.nonDealerTsumo(7, 0).second);

	CHECK_EQUAL(4000, t.nonDealerTsumo(8, 0).first);
	CHECK_EQUAL(8000, t.nonDealerTsumo(8, 0).second);
	CHECK_EQUAL(4000, t.nonDealerTsumo(9, 0).first);
	CHECK_EQUAL(8000, t.nonDealerTsumo(9, 0).second);
	CHECK_EQUAL(4000, t.nonDealerTsumo(10, 0).first);
	CHECK_EQUAL(8000, t.nonDealerTsumo(10, 0).second);

	CHECK_EQUAL(6000, t.nonDealerTsumo(11, 0).first);
	CHECK_EQUAL(12000, t.nonDealerTsumo(11, 0).second);
	CHECK_EQUAL(6000, t.nonDealerTsumo(12, 0).first);
	CHECK_EQUAL(12000, t.nonDealerTsumo(12, 0).second);

	CHECK_EQUAL(8000, t.nonDealerTsumo(13, 0).first);
	CHECK_EQUAL(16000, t.nonDealerTsumo(13, 0).second);
}
