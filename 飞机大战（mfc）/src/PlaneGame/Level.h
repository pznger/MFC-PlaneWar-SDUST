#pragma once
class Level
{
public:
	int enhanced1Freq;
	int enhanced2Freq;
	int enhanced3Freq;
	int UFOFreq;
	int backgroundSpeed;
	int normalEnemyHarm;
	int ufoBallHarm;
	int CollideHarm;
	int enhancedBallHarm;
	int fullScore;
	int missleHarm;
	int BOSSFreq;
	wchar_t bg[50]= L"plane\\bg06.jpg";
public:
	void setLevelData(int enhanced1Freq_, int enhanced2Freq_, int enhanced3Freq_, int UFOFreq_, int backgroundSpeed_,
		int normalEnemyHarm_, int ufoBallHarm_, int CollideHarm_, int enhancedBallHarm_,int missleHarm_,int fullScore_, int BOSSFreq_);
	Level();
	~Level();
	Level(int enhanced1Freq_, int enhanced2Freq_, int enhanced3Freq_, int UFOFreq_, int backgroundSpeed_,
		int normalEnemyHarm_, int ufoBallHarm_, int CollideHarm_, int enhancedBallHarm_, int missleHarm_, int fullScore_, int BOSSFreq_);
	wchar_t getBg()
	{
		return bg[50];
	}
};

