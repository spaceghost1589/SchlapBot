#include "game_settings.h"

using std::string;

namespace sc2 {

ProcessSettings::ProcessSettings(bool          in_real_time,
                                 int           in_step_size,
                                 const string& in_process_path,
                                 const string& in_net_address,
                                 int           in_timeout_ms,
                                 int           in_port_start,
                                 bool          in_multi_threaded,
                                 bool          in_full_screen):
        realtime(in_real_time),
        step_size(in_step_size),
        process_path(in_process_path),
        net_address(in_net_address),
        timeout_ms(in_timeout_ms),
        port_start(in_port_start),
        multi_threaded(in_multi_threaded),
        full_screen(in_full_screen) {}

InterfaceSettings::InterfaceSettings():
        use_feature_layers(false), use_render(false) {}

GameSettings::GameSettings():
        map_name(""), player_setup(), ports() {}

ReplaySettings::ReplaySettings():
        replay_file(), replay_dir(), player_id(1) {}

} // namespace sc2
