#pragma once

enum class Hand
{
	ReadyHand,
	DoubleReady,
	SelfPick,
	OneSetOfIdenticalSequences,
	NoPointsHand,
	WhiteDragon,
	GreenDragon,
	RedDragon,
	EastWind,
	SouthWind,
	WestWind,
	NorthWind,
	DoubleEastWind,
	DoubleSouthWind,
	DoubleWestWind,
	DoubleNorthWind,
	AllSimples,
	ThreeColourStraights,
	Straight,
	TerminalOrHonorInEachSet,
	SevenPairs,
	AllTriplets,
	ThreeClosedTriplets,
	ThreeColourTriplets,
	ThreeQuads,
	LittleThreeDragons,
	AllTerminalsAndHornors,
	HalfFlush,
	TwoSetsOfIdenticalSequences,
	TerminalInEachSet,
	Flush,
};
