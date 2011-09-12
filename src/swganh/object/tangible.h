
#ifndef SWGANH_OBJECT_TANGIBLE_H_
#define SWGANH_OBJECT_TANGIBLE_H_

#include "swganh/object/base_object.h"
#include <set>

namespace swganh {
namespace object {
    
class Tangible : public BaseObject
{
public:
    Tangible();
    //void AddCustomization(uint8_t customization_bit);
    void AddCustomization(const std::string& customization);
    void SetCustomization(const std::string& customization);
    const std::string& GetCustomization() { return customization_; }

    const std::vector<uint32_t> GetComponentCustomization() { return component_customization_list_; }
    void AddComponentCustomization(uint32_t customization);
    void RemoveComponentCustomization(uint32_t customization);
    void SetComponentCustomization(std::vector<uint32_t> component_customization);

    // no idea what options these are...
    void ToggleOption(uint32_t option);
    void SetOptionsMask(uint32_t options);

    uint32_t GetIncapTimer() { return incap_timer_; }
    void SetIncapTimer(uint32_t incap_timer);

    uint32_t GetCondition() { return condition_damage_; }
    void SetConditionDamage(uint32_t damage_amount);

    bool IsStatic() { return is_static_; }
    void SetStatic(bool is_static);

    std::set<uint64_t> GetDefenders() { return defender_list_; }
    void AddDefender(uint64_t defender);
    void RemoveDefender(uint64_t defender);
    void ClearDefenders();

private:
    std::string customization_;                          // update 3
    std::vector<uint32_t> component_customization_list_; // update 3
    uint32_t component_customization_list_counter_;      // update 3
    uint32_t options_bitmask_;                           // update 3
    uint32_t incap_timer_;                               // update 3
    uint32_t condition_damage_;                          // update 3
    uint32_t max_condition_;                             // update 3
    bool is_static_;                                     // update 3
    std::set<uint64_t> defender_list_;                   // update 6
    uint32_t defender_list_counter_;                     // update 6
	// crafting session
	// Both can be set to 0 ??
	// uint64_t manufacturing_schematic_;
	// uint64_t prototype_object_;
};
    
}}  // namespace

#endif  // SWGANH_OBJECT_TANGIBLE_H_
