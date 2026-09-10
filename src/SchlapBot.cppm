module;
#include <iostream>
#include <string>
#include <vector>
export module SchlapBot;
import Agent;
import point;
import error_handler;
import game_types;
import map_info;
import map_data;
import search;
import type_enums;
import unit;

export namespace sc2 {
using namespace std;
using enum Unit::Alliance;

// The main bot class.
struct SchlapBot final : Agent
{
    GameInfo        game_info { };
    MapData         map_data { };
    Point3D         starting_location_{};
    vector<Point3D> expansions { };

    SchlapBot ( ) = default;

    void OnGameFullStart ( ) override {}

    void OnGameStart ( ) override {
        game_info = Observation( )->GetGameInfo( );
        cout << "game started." << '\n';

        starting_location_ = Observation( )->GetStartLocation( );
        cout << "GetStartLocation finished" << '\n';

        // vector<Point3D> expansions = CalculateExpansionLocations (
        //     Observation( ),
        //     Query( ),
        //     ExpansionParameters { }
        // );

    }

    void OnStep ( ) override {
        // uint32_t game_loop = Observation()->GetGameLoop();

        // Units units = Observation()->GetUnits(Self);
    }

//------------------------------------------------------------------------------

    void OnBuildingConstructionComplete ( const Unit* building_ ) override {
        cout << UnitTypeToName ( building_->unit_type ) << "(" << building_->tag
             << ") constructed" << '\n';
    }

    void OnUnitCreated ( const Unit* unit_ ) override {
        cout << UnitTypeToName ( unit_->unit_type ) << "(" << unit_->tag
             << ") was created" << '\n';
    }

    void OnUnitIdle ( const Unit* unit_ ) override {
        cout << UnitTypeToName ( unit_->unit_type ) << "(" << unit_->tag
             << ") is idle" << '\n';
    }

    void OnUnitDestroyed ( const Unit* unit_ ) override {
        cout << UnitTypeToName ( unit_->unit_type ) << "(" << unit_->tag
             << ") was destroyed" << '\n';
    }

    void OnUpgradeCompleted ( const UpgradeID id_ ) override {
        cout << UpgradeIDToName ( id_ ) << " completed" << '\n';
    }

    void OnError (
        const vector<ClientError>& client_errors,
        const vector<string>&      protocol_errors
    ) override {
        for ( const auto err : client_errors ) {
            cerr << "Encountered client error: " << static_cast<int> ( err )
                 << '\n';
        }

        for ( const auto& err : protocol_errors ) {
            cerr << "Encountered protocol error: " << err << '\n';
        }
    }

    void OnGameEnd ( ) override {
        cout << "Game over!" << '\n';
    }

}; // struct SchlapBot

} // namespace sc2
