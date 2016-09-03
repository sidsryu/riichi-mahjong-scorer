#include "CppUTest/TestHarness.h"
#include "minipoint-counter.h"
#include "wining-hand-counter.h"
#include "hand-define.h"

using namespace std;

TEST_GROUP(MinipointCounterTest)
{	
	WiningHandCounter h;
	MinipointCounter p { h };
};

TEST(MinipointCounterTest, NoPointsHandTsumo)
{
	h.add(Hand::NoPointsHand);
	h.add(Hand::SelfPick);

	CHECK_EQUAL(20, p.total());
}

TEST(MinipointCounterTest, NoPointsHandRon)
{
	h.add(Hand::NoPointsHand);

	CHECK_EQUAL(30, p.total());
}

TEST(MinipointCounterTest, SevenPairs)
{
	h.add(Hand::SevenPairs);
	
	CHECK_EQUAL(25, p.total());

	h.add(Hand::SelfPick);

	CHECK_EQUAL(25, p.total());
}
