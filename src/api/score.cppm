/*! @file score.cppm
 * @brief Scores accumulated in a game as calculated by the game engine. */
module;
#include <string>
#include <vector>

#include "lib/gametypes.h"
export module score;

using std::string, std::vector;

export namespace sc2 {

//! Source of a score.\n
//! Curriculum vs Melee
enum class ScoreType {
    Curriculum = 1, //! Map generated score (from curriculum maps with special
                    //! scoring).
    Melee = 2 //! Summation of in-progress and current units/buildings value +
              //! minerals + vespene.
};

struct ScoreEntry {
    string name    = "";
    int    offset  = 0;
    bool   use     = true;
    bool   nonzero = false;
};

#define SET_ENTRY_BASE(STRUCTNAME, ENTRYNAME)                                  \
    {                                                                          \
        ScoreEntry new_entry;                                                  \
        new_entry.offset += (int) int64_t (&(((STRUCTNAME*) 0)->ENTRYNAME));   \
        new_entry.name   += #STRUCTNAME "." #ENTRYNAME;                        \
        entries.push_back (new_entry);                                         \
    }

#define SET_ENTRY_BASE_STRUCT(STRUCTNAME, ENTRYNAME)                           \
    {                                                                          \
        ScoreEntry base_entry;                                                 \
        base_entry.offset += (int) int64_t (&(((STRUCTNAME*) 0)->ENTRYNAME));  \
        base_entry.name   += #STRUCTNAME "." #ENTRYNAME;                       \
        ((STRUCTNAME*) 0)->ENTRYNAME.AddEntries (base_entry, entries);         \
    }

#define SET_ENTRY(STRUCTNAME, ENTRYNAME)                                        \
    {                                                                           \
        ScoreEntry new_entry = base;                                            \
        new_entry.offset    += (int) int64_t (&(((STRUCTNAME*) 0)->ENTRYNAME)); \
        new_entry.name      += "." #ENTRYNAME;                                  \
        entries.push_back (new_entry);                                          \
    }

#define SET_ENTRY_STRUCT(STRUCTNAME, ENTRYNAME)                                 \
    {                                                                           \
        ScoreEntry new_entry = base;                                            \
        new_entry.offset    += (int) int64_t (&(((STRUCTNAME*) 0)->ENTRYNAME)); \
        new_entry.name      += "." #ENTRYNAME;                                  \
        ((STRUCTNAME*) 0)->ENTRYNAME.AddEntries (new_entry, entries);           \
    }

//! Score by category.
struct CategoryScoreDetails {
    float none;
    float army;
    float economy;
    float technology;
    float upgrade;

    CategoryScoreDetails::CategoryScoreDetails ():
            none {0.0f},
            army {0.0f},
            economy {0.0f},
            technology {0.0f},
            upgrade {0.0f} {}

    static void AddEntries (
            const ScoreEntry& base, vector<ScoreEntry>& entries
    ) {
        SET_ENTRY (CategoryScoreDetails, none)
        SET_ENTRY (CategoryScoreDetails, army)
        SET_ENTRY (CategoryScoreDetails, economy)
        SET_ENTRY (CategoryScoreDetails, technology)
        SET_ENTRY (CategoryScoreDetails, upgrade)
    }
};

//! Score for vitals.
struct VitalScoreDetails {
    float life;
    float shields;
    float energy;

    VitalScoreDetails::VitalScoreDetails ():
            life (0.0f), shields (0.0f), energy (0.0f) {}

    static void AddEntries (
            const ScoreEntry& base, vector<ScoreEntry>& entries
    ) {
        SET_ENTRY (VitalScoreDetails, life)
        SET_ENTRY (VitalScoreDetails, shields)
        SET_ENTRY (VitalScoreDetails, energy)
    }
};

//! Detailed scores.
struct ScoreDetails {
    float idle_production_time;
    float idle_worker_time;

    float total_value_units;
    float total_value_structures;

    // Note the "killed_value" fields are a combination of minerals, vespene and
    // a human designer guess. Maybe useful as a delta. The weighting of the
    // combination and the human designer guess is different (not symmetric)
    // with the "total_value" fields!
    float killed_value_units;
    float killed_value_structures;

    float collected_minerals;
    float collected_vespene;

    float collection_rate_minerals;
    float collection_rate_vespene;

    float spent_minerals;
    float spent_vespene;

    CategoryScoreDetails supply_used;

    CategoryScoreDetails killed_minerals;
    CategoryScoreDetails killed_vespene;

    CategoryScoreDetails lost_minerals;
    CategoryScoreDetails lost_vespene;

    CategoryScoreDetails friendly_fire_minerals;
    CategoryScoreDetails friendly_fire_vespene;

    CategoryScoreDetails used_minerals;
    CategoryScoreDetails used_vespene;

    CategoryScoreDetails total_used_minerals;
    CategoryScoreDetails total_used_vespene;

    VitalScoreDetails total_damage_dealt;
    VitalScoreDetails total_damage_taken;
    VitalScoreDetails total_healed;

    ScoreDetails::ScoreDetails ():
            idle_production_time (0.0f),
            idle_worker_time (0.0f),
            total_value_units (0.0f),
            total_value_structures (0.0f),
            killed_value_units (0.0f),
            killed_value_structures (0.0f),
            collected_minerals (0.0f),
            collected_vespene (0.0f),
            collection_rate_minerals (0.0f),
            collection_rate_vespene (0.0f),
            spent_minerals (0.0f),
            spent_vespene (0.0f) {}

    static void AddEntries (ScoreEntry base, vector<ScoreEntry>& entries) {
        SET_ENTRY (ScoreDetails, idle_production_time)
        SET_ENTRY (ScoreDetails, idle_worker_time)
        SET_ENTRY (ScoreDetails, total_value_units)
        SET_ENTRY (ScoreDetails, total_value_structures)
        SET_ENTRY (ScoreDetails, killed_value_units)
        SET_ENTRY (ScoreDetails, killed_value_structures)
        SET_ENTRY (ScoreDetails, collected_minerals)
        SET_ENTRY (ScoreDetails, collected_vespene)
        SET_ENTRY (ScoreDetails, collection_rate_minerals)
        SET_ENTRY (ScoreDetails, collection_rate_vespene)
        SET_ENTRY (ScoreDetails, spent_minerals)
        SET_ENTRY (ScoreDetails, spent_vespene)

        SET_ENTRY_STRUCT (ScoreDetails, supply_used)
        SET_ENTRY_STRUCT (ScoreDetails, killed_minerals)
        SET_ENTRY_STRUCT (ScoreDetails, killed_vespene)
        SET_ENTRY_STRUCT (ScoreDetails, lost_minerals)
        SET_ENTRY_STRUCT (ScoreDetails, lost_vespene)
        SET_ENTRY_STRUCT (ScoreDetails, friendly_fire_minerals)
        SET_ENTRY_STRUCT (ScoreDetails, friendly_fire_vespene)
        SET_ENTRY_STRUCT (ScoreDetails, used_minerals)
        SET_ENTRY_STRUCT (ScoreDetails, used_vespene)
        SET_ENTRY_STRUCT (ScoreDetails, total_used_minerals)
        SET_ENTRY_STRUCT (ScoreDetails, total_used_vespene)

        SET_ENTRY_STRUCT (ScoreDetails, total_damage_dealt)
        SET_ENTRY_STRUCT (ScoreDetails, total_damage_taken)
        SET_ENTRY_STRUCT (ScoreDetails, total_healed)
    }
};

//! Scores.
struct Score {
    ScoreDetails score_details;
    ScoreType    score_type;
    float score; // Note: check score_type to know whether this is a melee score
                 // or curriculum score

    // Access as a flat list of floats.
    static constexpr int float_count_ =
            sizeof (ScoreDetails) / sizeof (float) + 1;

    const float* RawFloats () const {
        return &score;
    }

    Score::Score ():
            score_type (ScoreType::Melee), score (0) {}

    static void AddEntries (vector<ScoreEntry>& entries) {
        SET_ENTRY_BASE (Score, score)
        SET_ENTRY_BASE_STRUCT (Score, score_details)
    }

    bool Score::IsEqual (const Score& other_score) const {
        if ( score != other_score.score ) {
            return false;
        }

        for ( int i = 0; i < float_count_; ++i ) {
            if ( RawFloats()[i] != other_score.RawFloats()[i] ) {
                return false;
            }
        }

        return true;
    }
};

} // namespace sc2
