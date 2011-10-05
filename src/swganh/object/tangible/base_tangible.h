
#ifndef SWGANH_OBJECT_TANGIBLE_BASE_TANGIBLE_H_
#define SWGANH_OBJECT_TANGIBLE_BASE_TANGIBLE_H_

#include <cstdint>
#include <set>
#include <string>
#include <vector>
#include <list>

#include "swganh/object/object.h"

namespace swganh {
namespace object {
namespace tangible {

enum StaticType {
    MOVEABLE = 0,
    STATIC
};

class TangibleMessageBuilder;
    
class BaseTangible : public swganh::object::Object
{
public:
    BaseTangible();
    BaseTangible(const std::string& customization, std::vector<uint32_t> component_customization, uint32_t bitmask_options,
        uint32_t incap_timer, uint32_t damage_amount, uint32_t max_condition, bool is_static, std::vector<uint64_t> defenders);
    void AddCustomization(const std::string& customization);
    void SetCustomization(const std::string& customization);
    const std::string& GetCustomization() { return customization_; }

    const std::vector<uint32_t> GetComponentCustomization() { return component_customization_list_; }
    void AddComponentCustomization(uint32_t customization);
    void RemoveComponentCustomization(uint32_t customization);
    void ClearComponentCustomization();
    
    // no idea what options these are...
    uint32_t GetOptionsMask() { return options_bitmask_; }
    void ToggleOption(uint32_t option);
    void SetOptionsMask(uint32_t options);

    uint32_t GetIncapTimer() { return incap_timer_; }
    void SetIncapTimer(uint32_t incap_timer);

    uint32_t GetCondition() { return condition_damage_; }
    void SetConditionDamage(uint32_t damage_amount);

    uint32_t GetMaxCondition() { return max_condition_; }
    void SetMaxCondition(uint32_t max_condition);

    bool IsStatic() { return is_static_; }
    void SetStatic(bool is_static);

    void AddDefender(uint64_t defender);
    void RemoveDefender(uint64_t defender);
    void ResetDefenders(std::vector<uint64_t> defenders);
    bool IsDefending(uint64_t defender);
    std::vector<uint64_t> GetDefenders() { return defender_list_; }
    void ClearDefenders();

    virtual boost::optional<swganh::messages::BaselinesMessage> GetBaseline3();
    virtual boost::optional<swganh::messages::BaselinesMessage> GetBaseline6();
    virtual boost::optional<swganh::messages::BaselinesMessage> GetBaseline7();
private:
    friend TangibleMessageBuilder;

    std::vector<uint64_t>::iterator FindDefender_(uint64_t defender);

    std::string customization_;                          // update 3
    std::vector<uint32_t> component_customization_list_; // update 3
    uint32_t component_customization_counter_;           // update 3
    uint32_t options_bitmask_;                           // update 3
    uint32_t incap_timer_;                               // update 3
    uint32_t condition_damage_;                          // update 3
    uint32_t max_condition_;                             // update 3
    bool is_static_;                                     // update 3
    std::vector<uint64_t> defender_list_;                // update 6
    std::list<uint16_t> defender_index_free_list_;
    uint32_t defender_list_counter_;                     // update 6
};
    
}}}  // namespace swganh::object::tangible

#endif  // SWGANH_OBJECT_TANGIBLE_BASE_TANGIBLE_H_
