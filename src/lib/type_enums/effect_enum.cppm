module;
#include "types.h"
export module type_enums:effect_enum;

export namespace sc2 {

enum class EFFECT_ID : uint16_t {
    BLINDINGCLOUD              = 10,
    CORROSIVEBILE              = 11,
    GUARDIANSHIELD             = 2,
    INVALID                    = 0,
    LIBERATORDEFENDERZONE      = 9,
    LIBERATORDEFENDERZONESETUP = 8,
    LURKERSPINES               = 12,
    NUKEDOT                    = 7,
    PSISTORM                   = 1,
    SCANNERSWEEP               = 6,
    TEMPORALFIELD              = 4,
    TEMPORALFIELDGROWING       = 3,
    THERMALLANCE               = 5,
};

using EffectID = SC2Type<EFFECT_ID>;

//! Converts a EFFECT_ID into a string of the same name.
const char* EffectIDToName ( const EffectID id ) {
    switch ( static_cast<EFFECT_ID> ( id ) ) {
        case EFFECT_ID::BLINDINGCLOUD         : return "BLINDINGCLOUD";
        case EFFECT_ID::CORROSIVEBILE         : return "CORROSIVEBILE";
        case EFFECT_ID::GUARDIANSHIELD        : return "GUARDIANSHIELD";
        case EFFECT_ID::INVALID               : return "INVALID";
        case EFFECT_ID::LIBERATORDEFENDERZONE : return "LIBERATORDEFENDERZONE";
        case EFFECT_ID::LIBERATORDEFENDERZONESETUP :
            return "LIBERATORDEFENDERZONESETUP";
        case EFFECT_ID::LURKERSPINES         : return "LURKERSPINES";
        case EFFECT_ID::NUKEDOT              : return "NUKEDOT";
        case EFFECT_ID::PSISTORM             : return "PSISTORM";
        case EFFECT_ID::SCANNERSWEEP         : return "SCANNERSWEEP";
        case EFFECT_ID::TEMPORALFIELD        : return "TEMPORALFIELD";
        case EFFECT_ID::TEMPORALFIELDGROWING : return "TEMPORALFIELDGROWING";
        case EFFECT_ID::THERMALLANCE         : return "THERMALLANCE";
        default                              : return "UNKNOWN";
    }
}

}