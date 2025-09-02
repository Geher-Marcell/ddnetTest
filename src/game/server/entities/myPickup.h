/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_MYPICKUP_H
#define GAME_SERVER_ENTITIES_MYPICKUP_H

#include <game/server/entity.h>

class MyPickup : public CEntity
{
public:
	static const int ms_CollisionExtraSize = 6;

	MyPickup(CGameWorld *pGameWorld, int Type, CCharacter *pOwner);

	void Reset() override;
	void Tick() override;
	void TickPaused() override;
	void Snap(int SnappingClient) override;

	int Type() const { return m_Type; }

private:
	int m_Type;
	CCharacter *m_pOwner;

	// DDRace

	void Move();
	vec2 m_Core;
};

#endif
