#include "creature_message_builder.h"
#include "creature.h"

using namespace swganh::object::creature;
using namespace swganh::messages;

void CreatureMessageBuilder::BuildBankCreditsDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_1, 0);
        message.data.write<uint32_t>(creature->GetBankCredits());   // Bank Credits
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildCashCreditsDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_1, 1);
        message.data.write<uint32_t>(creature->GetCashCredits());   // Cash Credits
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildStatBaseDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_1, 2);
        creature->stat_base_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->stat_base_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildSkillDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_1, 3);
        creature->skills_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->skills_.ClearDeltas();
}

void CreatureMessageBuilder::BuildPostureDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 11);
        message.data.write<uint8_t>(creature->GetPosture());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildFactionRankDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 12);
        message.data.write<uint8_t>(creature->GetFactionRank());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildOwnerIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 13);
        message.data.write<uint64_t>(creature->GetOwnerId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildScaleDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 14);
        message.data.write<float>(creature->GetScale());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildBattleFatigueDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 15);
        message.data.write<uint32_t>(creature->GetBattleFatigue());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildStateBitmaskDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 16);
        message.data.write<uint64_t>(creature->GetStateBitmask());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildStatWoundDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_3, 17);
        creature->stat_wound_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->stat_wound_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildAccelerationMultiplierBaseDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 0);
        message.data.write<float>(creature->GetAccelerationMultiplierBase());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildAccelerationMultiplierModifierDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 1);
        message.data.write<float>(creature->GetAccelerationMultiplierModifier());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildStatEncumberanceDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 2);
        creature->stat_encumberance_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->stat_encumberance_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildSkillModDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 3);
        creature->skill_mod_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->skill_mod_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildSpeedMultiplierBaseDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 4);
        message.data.write<float>(creature->GetSpeedMultiplierBase());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildSpeedMultiplierModifierDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 5);
        message.data.write<float>(creature->GetSpeedMultiplierModifier());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildListenToIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 6);
        message.data.write<uint64_t>(creature->GetListenToId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildRunSpeedDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 7);
        message.data.write<float>(creature->GetRunSpeed());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildSlopeModifierAngleDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 8);
        message.data.write<float>(creature->GetSlopeModifierAngle());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildSlopeModifierPercentDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 9);
        message.data.write<float>(creature->GetSlopeModifierPercent());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildTurnRadiusDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 10);
        message.data.write<float>(creature->GetTurnRadius());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildWalkingSpeedDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 11);
        message.data.write<float>(creature->GetWalkingSpeed());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildWaterModifierPrecentDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 12);
        message.data.write<float>(creature->GetWaterModifierPercent());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildMissionCriticalObjectDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_4, 13);
        creature->mission_critical_object_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->mission_critical_object_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildCombatLevelDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 2);
        message.data.write<uint16_t>(creature->GetCombatLevel());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildAnimationDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 3);
        message.data.write<std::string>(creature->GetAnimation());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildMoodAnimationDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 4);
        message.data.write<std::string>(creature->GetMoodAnimation());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildWeaponIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 5);
        message.data.write<uint64_t>(creature->GetWeaponId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildGroupIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 6);
        message.data.write<uint64_t>(creature->GetGroupId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildInviteSenderIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 7);
        message.data.write<uint64_t>(creature->invite_counter_++);
        message.data.write<uint64_t>(creature->GetInviteSenderId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildGuildIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 8);
        message.data.write<uint32_t>(creature->GetGuildId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildTargetIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 9);
        message.data.write<uint64_t>(creature->GetTargetId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildMoodIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 10);
        message.data.write<uint8_t>(creature->GetMoodId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildPerformanceIdDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 12);
        message.data.write<uint32_t>(creature->GetPerformanceId());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildStatCurrentDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 13);
        creature->stat_current_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->stat_current_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildStatMaxDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 14);
        creature->stat_max_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->stat_max_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildEquipmentDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 15);
        creature->equipment_list_.Serialize(message);
        creature->AddDeltasUpdate(std::move(message));
    }
    else
        creature->equipment_list_.ClearDeltas();
}

void CreatureMessageBuilder::BuildDisguiseDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 16);
        message.data.write<std::string>(creature->GetDisguise());
        creature->AddDeltasUpdate(std::move(message));
    }
}

void CreatureMessageBuilder::BuildStationaryDelta(Creature* creature)
{
    if (creature->HasObservers())
    {
        DeltasMessage message = creature->CreateDeltasMessage(Object::VIEW_6, 17);
        message.data.write<uint8_t>(creature->IsStationary());
        creature->AddDeltasUpdate(std::move(message));
    }
}


boost::optional<swganh::messages::BaselinesMessage> CreatureMessageBuilder::BuildBaseline1(Creature* creature)
{
    auto message = creature->CreateBaselinesMessage(Object::VIEW_1, 4);
    message.data.write<uint32_t>(creature->GetBankCredits());
    message.data.write<uint32_t>(creature->GetCashCredits());
    creature->stat_base_list_.Serialize(message);
    creature->GetSkills().Serialize(message);
    return boost::optional<swganh::messages::BaselinesMessage>(std::move(message));
}

boost::optional<swganh::messages::BaselinesMessage> CreatureMessageBuilder::BuildBaseline3(Creature* creature)
{
    auto message = creature->CreateBaselinesMessage(Object::VIEW_3, 18);
    message.data.append(creature->BaseTangible::GetBaseline3().get().data);
    message.data.write<uint8_t>(creature->GetPosture());                    // Posture
    message.data.write<uint8_t>(creature->GetFactionRank());                // Faction Rank
    message.data.write<uint64_t>(creature->GetOwnerId());                   // Owner Id
    message.data.write<float>(creature->GetScale());                        // Scale
    message.data.write<uint32_t>(creature->GetBattleFatigue());             // Battle Fatigue
    message.data.write<uint64_t>(creature->GetStateBitmask());              // States Bitmask
    creature->stat_wound_list_.Serialize(message);
    return boost::optional<swganh::messages::BaselinesMessage>(std::move(message));
}

boost::optional<swganh::messages::BaselinesMessage> CreatureMessageBuilder::BuildBaseline4(Creature* creature)
{
    auto message = creature->CreateBaselinesMessage(Object::VIEW_4, 20);
    message.data.write<float>(creature->GetAccelerationMultiplierBase());
    message.data.write<float>(creature->GetAccelerationMultiplierModifier());
    creature->stat_encumberance_list_.Serialize(message);
    creature->skill_mod_list_.Serialize(message);
    message.data.write<float>(creature->GetSpeedMultiplierBase());
    message.data.write<float>(creature->GetSpeedMultiplierModifier());
    message.data.write<uint64_t>(creature->GetListenToId());
    message.data.write<float>(creature->GetRunSpeed());
    message.data.write<float>(creature->GetSlopeModifierAngle());
    message.data.write<float>(creature->GetSlopeModifierPercent());
    message.data.write<float>(creature->GetTurnRadius());
    message.data.write<float>(creature->GetWalkingSpeed());
    message.data.write<float>(creature->GetWaterModifierPercent());
    creature->mission_critical_object_list_.Serialize(message);
    return boost::optional<swganh::messages::BaselinesMessage>(std::move(message));
}

boost::optional<swganh::messages::BaselinesMessage> CreatureMessageBuilder::BuildBaseline6(Creature* creature)
{
    auto message = creature->CreateBaselinesMessage(Object::VIEW_6, 23);
    message.data.append(creature->BaseTangible::GetBaseline6().get().data);
    message.data.write<uint16_t>(creature->GetCombatLevel());                   // Combat Level
    message.data.write<std::string>(creature->GetAnimation());                  // Current Animation
    message.data.write<std::string>(creature->GetMoodAnimation());              // Mood Animation
    message.data.write<uint64_t>(creature->GetWeaponId());                      // Weapon Id
    message.data.write<uint64_t>(creature->GetGroupId());                       // Group Id
    message.data.write<uint64_t>(creature->GetInviteSenderId());                // Invite Sender Id
    message.data.write<uint64_t>(creature->invite_counter_);                    // Invite Sender Counter
    message.data.write<uint32_t>(creature->GetGuildId());                       // Guild Id
    message.data.write<uint64_t>(creature->GetTargetId());                      // Target Id
    message.data.write<uint8_t>(creature->GetMoodId());                         // Mood Id
    message.data.write<uint32_t>(creature->performance_counter_++);             // Performance Update Counter
    message.data.write<uint32_t>(creature->GetPerformanceId());                 // Performance Id
    creature->stat_current_list_.Serialize(message);
    creature->stat_max_list_.Serialize(message); 
    creature->equipment_list_.Serialize(message);
    message.data.write<std::string>(creature->GetDisguise());                   // Disguise Template
    message.data.write<uint8_t>(creature->IsStationary());                      // Stationary
    return boost::optional<swganh::messages::BaselinesMessage>(std::move(message));
}