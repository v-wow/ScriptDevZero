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

#ifndef DEF_BRD_H
#define DEF_BRD_H

enum
{
    MAX_ENCOUNTER           = 10,
    MAX_RELIC_DOORS         = 12,

    TYPE_RING_OF_LAW        = 1,
    TYPE_VAULT              = 2,
    TYPE_BAR                = 3,
    TYPE_TOMB_OF_SEVEN      = 4,
    TYPE_LYCEUM             = 5,
    TYPE_IRON_HALL          = 6,
    TYPE_QUEST_JAIL_BREAK   = 7,
    TYPE_JAIL_DUGHAL        = 8,
    TYPE_JAIL_SUPPLY_ROOM   = 9,
    TYPE_JAIL_TOBIAS        = 10,

    NPC_EMPEROR             = 9019,
    NPC_PRINCESS            = 8929,
    NPC_PHALANX             = 9502,
    NPC_HATEREL             = 9034,
    NPC_ANGERREL            = 9035,
    NPC_VILEREL             = 9036,
    NPC_GLOOMREL            = 9037,
    NPC_SEETHREL            = 9038,
    NPC_DOOMREL             = 9039,
    NPC_DOPEREL             = 9040,
    NPC_WATCHER_DOOMGRIP    = 9476,
    NPC_WARBRINGER_CONST    = 8905,         // activated when watcher doomgrip is summoned

    NPC_OGRABISI            = 9677,
    NPC_SHILL               = 9678,
    NPC_CREST               = 9680,
    NPC_JAZ                 = 9681,

    GO_ARENA_1              = 161525,
    GO_ARENA_2              = 161522,
    GO_ARENA_3              = 161524,
    GO_ARENA_4              = 161523,

    GO_JAIL_DOOR_SUPPLY     = 170561,
    GO_JAIL_SUPPLY_CRATE    = 166872,
    GO_JAIL_DOOR_DUGHAL     = 170562,
    GO_JAIL_DOOR_TOBIAS     = 170566,
    GO_JAIL_DOOR_CREST      = 170567,
    GO_JAIL_DOOR_JAZ        = 170568,
    GO_JAIL_DOOR_SHILL      = 170569,

    GO_SHADOW_LOCK          = 161460,
    GO_SHADOW_MECHANISM     = 161461,
    GO_SHADOW_GIANT_DOOR    = 157923,
    GO_SHADOW_DUMMY         = 161516,
    GO_BAR_KEG_SHOT         = 170607,
    GO_BAR_KEG_TRAP         = 171941,
    GO_BAR_DOOR             = 170571,
    GO_TOMB_ENTER           = 170576,
    GO_TOMB_EXIT            = 170577,
    GO_LYCEUM               = 170558,
    GO_GOLEM_ROOM_N         = 170573,
    GO_GOLEM_ROOM_S         = 170574,
    GO_THRONE_ROOM          = 170575,

    GO_SPECTRAL_CHALICE     = 164869,
    GO_CHEST_SEVEN          = 169243,
    GO_ARENA_SPOILS         = 181074,
    GO_SECRET_DOOR          = 174553,

    SPELL_STONED            = 10255,        // removed from the warbringer constructs

    QUEST_JAIL_BREAK        = 4322
};

enum ArenaNPCs
{
    // Gladiators
    NPC_LEFTY               = 16049,
    NPC_ROTFANG             = 16050,
    NPC_SNOKH               = 16051,
    NPC_MALGEN              = 16052,
    NPC_KORV                = 16053,
    NPC_REZZNIK             = 16054,
    NPC_VAJASHNI            = 16055,
    NPC_VOLIDA              = 16058,
    NPC_THELDREN            = 16059,
    // Ring mobs
    NPC_WORM                = 8925,
    NPC_STINGER             = 8926,
    NPC_SCREECHER           = 8927,
    NPC_THUNDERSNOUT        = 8928,
    NPC_CREEPER             = 8933,
    NPC_BEETLE              = 8932,
    // Ring bosses
    NPC_GOROSH              = 9027,
    NPC_GRIZZLE             = 9028,
    NPC_EVISCERATOR         = 9029,
    NPC_OKTHOR              = 9030,
    NPC_ANUBSHIAH           = 9031,
    NPC_HEDRUM              = 9032
};

static const uint32 aArenaNPCs[] =
{
    // Gladiators
    NPC_LEFTY, NPC_ROTFANG, NPC_SNOKH, NPC_MALGEN, NPC_KORV, NPC_REZZNIK, NPC_VAJASHNI, NPC_VOLIDA, NPC_THELDREN,
    // Ring mobs
    NPC_WORM, NPC_STINGER, NPC_SCREECHER, NPC_THUNDERSNOUT, NPC_CREEPER, NPC_BEETLE,
    // Ring bosses
    NPC_GOROSH, NPC_GRIZZLE, NPC_EVISCERATOR, NPC_OKTHOR, NPC_ANUBSHIAH, NPC_HEDRUM
};

// Used to summon Watcher Doomgrip
static const float aVaultPositions[1][4] =
{
    {821.905f,-338.382f,-50.134f,3.78736f}
};

class MANGOS_DLL_DECL instance_blackrock_depths : public ScriptedInstance
{
    public:
        instance_blackrock_depths(Map* pMap);
        ~instance_blackrock_depths() {}

        void Initialize();

        void SetOpenedDoor(uint64 m_uiGoEntry, bool opened);
        bool GetOpenedDoor(uint64 m_uiGoEntry);

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);
        void OnCreatureEvade(Creature* pCreature);
        void OnCreatureDeath(Creature* pCreature);

        // Arena Event
        void SetArenaCenterCoords(float fX, float fY, float fZ) { m_fArenaCenterX = fX; m_fArenaCenterY = fY; m_fArenaCenterZ = fZ; }
        void GetArenaCenterCoords(float &fX, float &fY, float &fZ) { fX = m_fArenaCenterX; fY = m_fArenaCenterY; fZ = m_fArenaCenterZ; }

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        uint32 m_uiBarAleCount;
        uint32 m_uiCofferDoorsOpened;

        GUIDSet m_suiVaultNpcGUIDs;

        float m_fArenaCenterX, m_fArenaCenterY, m_fArenaCenterZ;

        bool m_bDoorDughalOpened;
        bool m_bDoorTobiasOpened;
        bool m_bDoorCrestOpened;
        bool m_bDoorJazOpened;
        bool m_bDoorShillOpened;
        bool m_bDoorSupplyOpened;
};

#endif
