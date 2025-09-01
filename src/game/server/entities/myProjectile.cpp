/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "myProjectile.h"
#include "character.h"

#include <engine/shared/config.h>

#include <game/generated/protocol.h>
#include <game/mapitems.h>

#include <game/server/gamecontext.h>
#include <game/server/gamemodes/DDRace.h>

MyProjectile::MyProjectile(CGameWorld *pGameWorld, int Type, int LifeSpan,vec2 Pos) : CEntity(pGameWorld, CGameWorld::ENTTYPE_PROJECTILE)
{
	m_Type = Type;
	m_Pos = Pos;
	m_LifeSpan = LifeSpan;

	GameWorld()->InsertEntity(this);
}

void MyProjectile::Reset()
{
	m_MarkedForDestroy = true;
}

void MyProjectile::Tick()
{
	char aBuf[256];

	// str_format(aBuf, sizeof(aBuf), "PROJECTILE TICK LIFE %d", m_LifeSpan);
	// dbg_msg("projectile", aBuf);

	if(m_LifeSpan > 1) m_LifeSpan--;
	else m_MarkedForDestroy = true;
}

void MyProjectile::TickPaused()
{
	++m_StartTick;
}

void MyProjectile::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient))
		return;

	CNetObj_Projectile *pProj = Server()->SnapNewItem<CNetObj_Projectile>(GetId());
	// CNetObj_Projectile pProj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, GetId(), sizeof(CNetObj_Projectile)));

	pProj->m_X = (int)m_Pos.x;
	pProj->m_Y = (int)m_Pos.y;
	pProj->m_StartTick = Server()->Tick()-1;
	pProj->m_VelX = 0;
	pProj->m_VelY = -1;
	pProj->m_Type = m_Type;
}