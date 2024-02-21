#include "stdafx.h"
#include "Level.h"
void Level::setLevelData(int enhanced1Freq_, int enhanced2Freq_, int enhanced3Freq_,  int UFOFreq_, int backgroundSpeed_,
	int normalEnemyHarm_, int ufoBallHarm_, int CollideHarm_, int enhancedBallHarm_, int missleHarm_,int fullScore_,int BOSSFreq_)
{
	enhanced1Freq = enhanced1Freq_;
	enhanced2Freq = enhanced2Freq_;
	enhanced3Freq = enhanced3Freq_;
	UFOFreq = UFOFreq_;
	backgroundSpeed = backgroundSpeed_;
	normalEnemyHarm = normalEnemyHarm_;
	ufoBallHarm = ufoBallHarm_;
	CollideHarm = CollideHarm_;
	enhancedBallHarm = enhancedBallHarm_;
	fullScore = fullScore_;
	missleHarm = missleHarm_;
	BOSSFreq = BOSSFreq_;
}
Level::Level()
{

}
Level::Level(int enhanced1Freq_, int enhanced2Freq_, int enhanced3Freq_, int UFOFreq_, int backgroundSpeed_,
	int normalEnemyHarm_, int ufoBallHarm_, int CollideHarm_, int enhancedBallHarm_,int missleHarm_,int fullScore_, int BOSSFreq_)
{
	enhanced1Freq = enhanced1Freq_;
	enhanced2Freq = enhanced2Freq_;
	enhanced3Freq = enhanced3Freq_;
	UFOFreq = UFOFreq_;
	backgroundSpeed = backgroundSpeed_;
	normalEnemyHarm = normalEnemyHarm_;
	ufoBallHarm = ufoBallHarm_;
	CollideHarm = CollideHarm_;
	enhancedBallHarm = enhancedBallHarm_;
	fullScore = fullScore_;
	missleHarm = missleHarm_;
	BOSSFreq = BOSSFreq_;
}
Level::~Level()
{

}