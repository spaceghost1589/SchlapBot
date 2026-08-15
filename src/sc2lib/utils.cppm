// module;
// #include "sc2api/sc2_common.h"
// export module utils;
//
// import SchlapBot;
// import map_info;
//
//
// namespace sc2 {
//
// //! Finds a random location within a rectangle with diagonal vertices.
// //! @param
// //! @param
// Point2D FindRandomLocation(const Point2D& min, const Point2D& max)
// {
//     // if (!min > Observation()->GetGameInfo().playable_min)
//
//     Point2D target_pos;
//     const float playable_w = max.x - min.x;
//     const float playable_h = max.y - min.y;
//     target_pos.x = playable_w * GetRandomFraction() + min.x;
//     target_pos.y = playable_h * GetRandomFraction() + min.y;
//     return target_pos;
// }
//
// //! Finds a random location on the playable map.
// Point2D FindRandomLocation(const GameInfo& game_info)
// {
//     return FindRandomLocation(game_info.playable_min, game_info.playable_max);
// }
//
// Point2D FindCenterOfMap(const GameInfo& game_info)
// {
//     Point2D target_pos;
//     target_pos.x = game_info.playable_max.x / 2.0F;
//     target_pos.y = game_info.playable_max.y / 2.0F;
//     return target_pos;
// }
//
// // float DistanceSquared(const Point2D& a, const Point2D& b);
// // {
// //
// // }
//
// }  // namespace sc2
//
//
