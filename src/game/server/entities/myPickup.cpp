/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "myPickup.h"
#include "character.h"

#include <game/generated/protocol.h>
#include <game/mapitems.h>
#include <game/teamscore.h>

#include <game/server/gamecontext.h>
#include <game/server/player.h>

static constexpr int gs_PickupPhysSize = 14;

MyPickup::MyPickup(CGameWorld *pGameWorld, int Type, CCharacter *pOwner) :
	CEntity(pGameWorld, CGameWorld::ENTTYPE_PICKUP, vec2(0, 0), gs_PickupPhysSize)
{
	m_Core = vec2(0.0f, 0.0f);
	m_Type = Type;

    m_pOwner = pOwner;

	GameWorld()->InsertEntity(this);
}

void MyPickup::Reset()
{
	m_MarkedForDestroy = true;
}

void MyPickup::Tick()
{
	Move();
}

void MyPickup::TickPaused()
{
}

void MyPickup::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient))
		return;

    CNetObj_Pickup *pPickup = Server()->SnapNewItem<CNetObj_Pickup>(GetId());

    pPickup->m_X = (int)m_Pos.x;
    pPickup->m_Y = (int)m_Pos.y;
    pPickup->m_Type = m_Type;
}

void MyPickup::Move()
{
    vec2 Offset = vec2(0.0f, 40.0f);
    float Speed = 15;

    if(m_pOwner){
        vec2 Direction = normalize(m_pOwner->m_Pos - Offset - m_Pos);
        float Distance = distance(m_Pos, m_pOwner->m_Pos - Offset); 

        m_Core = Direction * Speed * Distance / 100.0f;
        m_Pos += m_Core;
	}
}
