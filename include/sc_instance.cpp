/*
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2010-2011 ScriptDev0 <http://github.com/scriptdev/scriptdevzero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "precompiled.h"

//Optional uiWithRestoreTime. If not defined, autoCloseTime will be used (if not 0 by default in *_template)
void ScriptedInstance::DoUseDoorOrButton(uint64 uiGuid, uint32 uiWithRestoreTime, bool bUseAlternativeState)
{
    if (!uiGuid)
        return;

    if (GameObject* pGo = instance->GetGameObject(uiGuid))
    {
        if (pGo->GetGoType() == GAMEOBJECT_TYPE_DOOR || pGo->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
        {
            if (pGo->getLootState() == GO_READY)
                pGo->UseDoorOrButton(uiWithRestoreTime, bUseAlternativeState);
            else if (pGo->getLootState() == GO_ACTIVATED)
                pGo->ResetDoorOrButton();
        }
        else
            error_log("SD0: Script call DoUseDoorOrButton, but gameobject entry %u is type %u.",pGo->GetEntry(),pGo->GetGoType());
    }
}

void ScriptedInstance::DoRespawnGameObject(uint64 uiGuid, uint32 uiTimeToDespawn)
{
    if (GameObject* pGo = instance->GetGameObject(uiGuid))
    {
        //not expect any of these should ever be handled
        if (pGo->GetGoType()==GAMEOBJECT_TYPE_FISHINGNODE || pGo->GetGoType()==GAMEOBJECT_TYPE_DOOR ||
            pGo->GetGoType()==GAMEOBJECT_TYPE_BUTTON || pGo->GetGoType()==GAMEOBJECT_TYPE_TRAP)
            return;

        if (pGo->isSpawned())
            return;

        pGo->SetRespawnTime(uiTimeToDespawn);
        pGo->Refresh();
    }
}

void ScriptedInstance::DoUpdateWorldState(uint32 uiStateId, uint32 uiStateData)
{
    Map::PlayerList const& lPlayers = instance->GetPlayers();

    if (!lPlayers.isEmpty())
    {
        for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
        {
            if (Player* pPlayer = itr->getSource())
                pPlayer->SendUpdateWorldState(uiStateId, uiStateData);
        }
    }
    else
        debug_log("SD0: DoUpdateWorldState attempt send data but no players in map.");
}

Player* ScriptedInstance::GetPlayerInMap(bool bOnlyAlive /*=false*/, bool bCanBeGamemaster /*=true*/)
{
    Map::PlayerList const& lPlayers = instance->GetPlayers();

    for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
    {
        Player* pPlayer = itr->getSource();
        if (pPlayer && (!bOnlyAlive || pPlayer->isAlive()) && (bCanBeGamemaster || !pPlayer->isGameMaster()))
            return pPlayer;
    }

    return NULL;
}

// Open door or Use button - Optional uiWithRestoreTime. If not defined, autoCloseTime will be used (if not 0 by default in *_template)
void ScriptedInstance::DoOpenDoorOrButton(uint64 uiGuid, uint32 uiWithRestoreTime, bool bUseAlternativeState)
{
    if (!uiGuid)
        return;

    if (GameObject* pGo = instance->GetGameObject(uiGuid))
    {
        if (pGo->GetGoType() == GAMEOBJECT_TYPE_DOOR || pGo->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
        {
            if (pGo->getLootState() == GO_READY)
                pGo->UseDoorOrButton(uiWithRestoreTime, bUseAlternativeState);
        }
        else
            error_log("SD0: Script call DoOpenDoorOrButton, but gameobject entry %u is type %u.",pGo->GetEntry(),pGo->GetGoType());
    }
}

// Close door or Reset button
void ScriptedInstance::DoCloseDoorOrButton(uint64 uiGuid)
{
    if (!uiGuid)
        return;

    if (GameObject* pGo = instance->GetGameObject(uiGuid))
    {
        if (pGo->GetGoType() == GAMEOBJECT_TYPE_DOOR || pGo->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
        {
            if (pGo->getLootState() == GO_ACTIVATED)
                pGo->ResetDoorOrButton();
        }
        else
            error_log("SD0: Script call DoCloseDoorOrButton, but gameobject entry %u is type %u.",pGo->GetEntry(),pGo->GetGoType());
    }
}
