#pragma once

#include <utility>
#include <vector>

#include "interfaces.h"
#include "unit.h"

import observation_interface;

namespace sc2::search {
// Clusters units within some distance of each other and returns a list of them and their center of mass.
std::vector<std::pair<Point3D, std::vector<Unit>>> Cluster(const Units& units, float distance_apart);

struct ExpansionParameters {
    // By default we use values that generally work but may require tuning for certain maps.

    // The various radius to check at from the center of an expansion.
    std::vector<float> radii_ = {6.4F, 5.3F};

    // With what granularity to step the circumference of the circle.
    float circle_step_size_ = 0.5F;

    // With what distance to cluster mineral/vespene in, this will be used for center of mass calculation.
    float cluster_distance_ = 15.0F;

    // If filled out CalculateExpansionLocations will render spheres to show what it calculated.
    DebugInterface* debug_ = nullptr;
};

// Calculates expansion locations, this call can take on the order of 100ms since it makes blocking queries to SC2 so
// call it once and cache the results.
std::vector<Point3D> CalculateExpansionLocations(const ObservationInterface* resources, QueryInterface* query,
                                                 const ExpansionParameters& parameters = ExpansionParameters());
} // namespace sc2::search
