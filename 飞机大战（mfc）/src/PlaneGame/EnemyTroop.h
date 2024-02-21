#pragma once
#include "gameobject.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"

class CEnemyTroop :public CGameObject
{
public:
	CEnemyTroop(void);
	CEnemyTroop(int type);
	~CEnemyTroop(void);

	//CEnemy  Enemyt [4];
	//CEnemy2 Enemyt2[4];
	//CEnemy3 Enemyt3[4];
	//CEnemy4 Enemyt4[4];
	int m_type;
};
