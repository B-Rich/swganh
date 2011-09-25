/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef SWGANH_OBJECT_CREATURE_H_
#define SWGANH_OBJECT_CREATURE_H_

#include <list>

#include "swganh/object/object.h"

namespace swganh {
namespace object {
namespace creature {

class Creature : public swganh::object::Object
{
public:
    Creature();
    Creature(uint32_t bank_credits, uint32_t cash_credits, std::list<std::string> skill_list);
    ~Creature();

    enum POSTURE
    {
        STANDING = 0,
        SNEAKING,
        WALKING,
        RUNNING,
        KNEELING,
        CROUCH_SNEAKING,
        CROUCH_WALKING,
        PRONE,
        CRAWLING,
        CLIMBING_STATIONARY,
        CLIMBING,
        HOVERING,
        FLING,
        LYING_DOWN,
        SITTING,
        SKILL_ANIMATING,
        DRIVING_VEHICLE,
        RIDING_CREATURE,
        KNOCKED_DOWN,
        INCAPACITATED,
        DEAD,
        BLOCKING
    };

    enum STATE
    {
        COVER = 0,
        COMBAT,
        PEACE,
        AIMING,
        ALERT,
        BERSERK,
        FEIGN_DEATH,
        COMBAT_ATTITUDE_EVASIVE,
        COMBAT_ATTITUDE_NORMAL,
        COMBAT_ATTITUDE_AGGRESSIVE,
        TUMBLING,
        RALLIED,
        STUNNED,
        BLINDED,
        DIZZY,
        INTIMIDATED,
        IMMOBILIZED,
        FROZEN,
        SWIMMING,
        SITTING_ON_CHAIR,
        CRAFTING,
        GLOWING_JEDI,
        MASK_SCENT,
        POISONED,
        BLEEDING,
        DISEASED,
        ON_FIRE,
        RIDING_MOUNT,
        MOUNTED_CREATURE,
        PILOTING_SHIP,
        SHIP_OPERATIONS,
        SHIP_GUNNER,
        SHIP_INTERIOR,
        PILOTING_POB_SHIP
    };

    // CREO
    uint32_t GetType() const;
    const static uint32_t type = 0x4352454F;

    /**
     *
     */
    void SetBankCredits(uint32_t bank_credits);

    /**
     *
     */
    void SetCashCredits(uint32_t cash_credits);

    /**
     *
     */
    void AddSkill(std::string skill);

    /**
     *
     */
    void RemoveSkill(std::string skill);

    /**
     *
     */
    void SetPosture(POSTURE posture);

    /**
     *
     */
    void SetFactionRank(uint8_t faction_rank);

    /**
     *
     */
    void SetOwnerId(uint64_t owner_id);

    /**
     *
     */
    void SetScale(float scale);

    /**
     *
     */
    void SetBattleFatigue(uint32_t battle_fatigue);

    /**
     *
     */
    void SetStateBitmask(uint64_t state_bitmask);

private:
    uint32_t    bank_credits_;              // update 1 variable 0
    uint32_t    cash_credits_;              // update 1 variable 1
    uint32_t    skill_list_counter_;        // update 1 variable 3
    std::list<std::string> skill_list_;     // update 1 variable 3
    uint32_t    posture_;                   // update 3 variable 11
    uint8_t     faction_rank_;              // update 3 variable 12
    uint64_t    owner_id_;                  // update 3 variable 13
    float       scale_;                     // update 3 variable 14
    uint32_t    battle_fatigue_;            // update 3 variable 15
    uint64_t    state_bitmask_;             // update 3 variable 16

};

}}}  // namespace swganh::object::creature

#endif // SWGANH_OBJECT_CREATURE_CREATURE_H_
