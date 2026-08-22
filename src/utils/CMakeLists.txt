#set (sc2utils_sources
#     dirent.h
#     sc2_arg_parser.cc
#     sc2_arg_parser.h
#     sc2_manage_process.cc
#     sc2_manage_process.h
#     sc2_property_reader.cc
#     property_reader.h
#     simple_serialization.h
#     )
#
#add_library (sc2utils STATIC ${sc2utils_sources})
#
#target_sources (sc2utils
#                PUBLIC
#                FILE_SET CXX_MODULES
#                FILES
#                points.cppm
#                scan_directory.cppm
#                )
#
#if (APPLE)
#	target_link_libraries (sc2utils "-framework Carbon")
#endif ()
