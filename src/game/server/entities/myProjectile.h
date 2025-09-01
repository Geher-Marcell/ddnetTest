/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_MYPROJECTILE_H
#define GAME_SERVER_ENTITIES_MYPROJECTILE_H

#include <game/server/entity.h>

class MyProjectile : public CEntity
{
public:
	MyProjectile(CGameWorld *pGameWorld, int Type, int LifeSpan, vec2 Pos);

	void Reset() override;
	void Tick() override;
	void TickPaused() override;
	void Snap(int SnappingClient) override;

private:
	vec2 m_Direction;
	int m_LifeSpan;
	int m_Owner;
	int m_Type;
	int m_StartTick;
};

#endif
