module;
#include <flat_map>

#include "types.h"
export module type_enums:ability_enums;
// import data;


export namespace sc2 {
using namespace std;

enum class ABILITY_ID : uint16_t {
    ADVANCEDCONSTRUCTION_CANCEL                                       = 2840,
    AGGRESSIVEMUTATION                                                = 2540,
    AIURLIGHTBRIDGEABANDONEDNE10OUT_BRIDGEEXTEND                      = 2568,
    AIURLIGHTBRIDGEABANDONEDNE10_BRIDGERETRACT                        = 2570,
    AIURLIGHTBRIDGEABANDONEDNE12OUT_BRIDGEEXTEND                      = 2572,
    AIURLIGHTBRIDGEABANDONEDNE12_BRIDGERETRACT                        = 2574,
    AIURLIGHTBRIDGEABANDONEDNE8OUT_BRIDGEEXTEND                       = 2564,
    AIURLIGHTBRIDGEABANDONEDNE8_BRIDGERETRACT                         = 2566,
    AIURLIGHTBRIDGEABANDONEDNW10OUT_BRIDGEEXTEND                      = 2580,
    AIURLIGHTBRIDGEABANDONEDNW10_BRIDGERETRACT                        = 2582,
    AIURLIGHTBRIDGEABANDONEDNW12OUT_BRIDGEEXTEND                      = 2584,
    AIURLIGHTBRIDGEABANDONEDNW12_BRIDGERETRACT                        = 2586,
    AIURLIGHTBRIDGEABANDONEDNW8OUT_BRIDGEEXTEND                       = 2576,
    AIURLIGHTBRIDGEABANDONEDNW8_BRIDGERETRACT                         = 2578,
    AIURLIGHTBRIDGENE10OUT_BRIDGEEXTEND                               = 2401,
    AIURLIGHTBRIDGENE10_BRIDGERETRACT                                 = 2403,
    AIURLIGHTBRIDGENE12OUT_BRIDGEEXTEND                               = 2405,
    AIURLIGHTBRIDGENE12_BRIDGERETRACT                                 = 2407,
    AIURLIGHTBRIDGENE8OUT_BRIDGEEXTEND                                = 2397,
    AIURLIGHTBRIDGENE8_BRIDGERETRACT                                  = 2399,
    AIURLIGHTBRIDGENW10OUT_BRIDGEEXTEND                               = 2413,
    AIURLIGHTBRIDGENW10_BRIDGERETRACT                                 = 2415,
    AIURLIGHTBRIDGENW12OUT_BRIDGEEXTEND                               = 2417,
    AIURLIGHTBRIDGENW12_BRIDGERETRACT                                 = 2419,
    AIURLIGHTBRIDGENW8OUT_BRIDGEEXTEND                                = 2409,
    AIURLIGHTBRIDGENW8_BRIDGERETRACT                                  = 2411,
    AIURTEMPLEBRIDGENE10OUT_BRIDGEEXTEND                              = 2425,
    AIURTEMPLEBRIDGENE10_BRIDGERETRACT                                = 2427,
    AIURTEMPLEBRIDGENE12OUT_BRIDGEEXTEND                              = 2429,
    AIURTEMPLEBRIDGENE12_BRIDGERETRACT                                = 2431,
    AIURTEMPLEBRIDGENE8OUT_BRIDGEEXTEND                               = 2421,
    AIURTEMPLEBRIDGENE8_BRIDGERETRACT                                 = 2423,
    AIURTEMPLEBRIDGENW10OUT_BRIDGEEXTEND                              = 2437,
    AIURTEMPLEBRIDGENW10_BRIDGERETRACT                                = 2439,
    AIURTEMPLEBRIDGENW12OUT_BRIDGEEXTEND                              = 2441,
    AIURTEMPLEBRIDGENW12_BRIDGERETRACT                                = 2443,
    AIURTEMPLEBRIDGENW8OUT_BRIDGEEXTEND                               = 2433,
    AIURTEMPLEBRIDGENW8_BRIDGERETRACT                                 = 2435,
    ARBITERMPRECALL                                                   = 2475,
    ARBITERMPSTASISFIELD                                              = 2473,
    ARCHIVESEAL                                                       = 2884,
    ARCHONWARP_ARCHONWARPTARGET                                       = 1767,
    ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL1             = 2297,
    ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL2             = 2298,
    ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL3             = 2299,
    ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL1             = 2294,
    ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL2             = 2295,
    ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL3             = 2296,
    ARTANISVORTEX_VORTEX                                              = 2886,
    ARTANISWORMHOLETRANSIT_WORMHOLETRANSIT                            = 2888,
    ATTACK                                                            = 3674,
    ATTACK_ATTACK                                                     = 23,
    ATTACK_ATTACKALLOWSINVULNERABLE                                   = 3295,
    ATTACK_ATTACKBARRAGE                                              = 25,
    ATTACK_ATTACKBUILDING                                             = 2048,
    ATTACK_ATTACKTOWARDS                                              = 24,
    ATTACK_ATTACKWARPPRISM                                            = 301,
    ATTACK_BATTLECRUISER                                              = 3771,
    ATTACK_REDIRECT                                                   = 1682,
    BARRACKSREACTORMORPH_REACTOR                                      = 1676,
    BARRACKSTECHLABMORPH_TECHLABBARRACKS                              = 1668,
    BARRACKSTECHREACTORMORPH_TECHLABBARRACKS                          = 3304,
    BATTERYOVERCHARGE                                                 = 4107,
    BATTLECRUISERATTACKEVALUATOR_MOTHERSHIPCOREATTACK                 = 3774,
    BATTLECRUISERMOVE_ACQUIREMOVE                                     = 3779,
    BATTLECRUISERMOVE_MOVE                                            = 3776,
    BATTLECRUISERMOVE_MOVEHOLDPOSITION                                = 3778,
    BATTLECRUISERMOVE_MOVEPATROL                                      = 3777,
    BATTLECRUISERMOVE_TURN                                            = 3780,
    BATTLECRUISERSTOPEVALUATOR_STOP                                   = 3781,
    BATTLECRUISERSTOP_CHEER                                           = 3785,
    BATTLECRUISERSTOP_DANCE                                           = 3786,
    BATTLECRUISERSTOP_HOLDFIRE                                        = 3784,
    BEACON_BEACONMOVE                                                 = 22,
    BEACON_CANCEL                                                     = 21,
    BEHAVIOR_BUILDINGATTACKOFF                                        = 2082,
    BEHAVIOR_BUILDINGATTACKON                                         = 2081,
    BEHAVIOR_CLOAKOFF                                                 = 3677,
    BEHAVIOR_CLOAKOFF_BANSHEE                                         = 393,
    BEHAVIOR_CLOAKOFF_GHOST                                           = 383,
    BEHAVIOR_CLOAKON                                                  = 3676,
    BEHAVIOR_CLOAKON_BANSHEE                                          = 392,
    BEHAVIOR_CLOAKON_GHOST                                            = 382,
    BEHAVIOR_GENERATECREEPOFF                                         = 1693,
    BEHAVIOR_GENERATECREEPON                                          = 1692,
    BEHAVIOR_HOLDFIREOFF                                              = 3689,
    BEHAVIOR_HOLDFIREOFF_GHOST                                        = 38,
    BEHAVIOR_HOLDFIREOFF_LURKER                                       = 2552,
    BEHAVIOR_HOLDFIREON                                               = 3688,
    BEHAVIOR_HOLDFIREON_GHOST                                         = 36,
    BEHAVIOR_HOLDFIREON_LURKER                                        = 2550,
    BEHAVIOR_PULSARBEAMOFF                                            = 2376,
    BEHAVIOR_PULSARBEAMON                                             = 2375,
    BIODOMECOMMANDLAND_LAND                                           = 3352,
    BIODOMECOMMANDLIFTOFF_LIFT                                        = 3350,
    BIODOMETRANSPORT_BIODOMELOAD                                      = 3274,
    BIODOMETRANSPORT_BIODOMEUNLOADALL                                 = 3275,
    BIOPLASMIDDISCHARGE                                               = 3378,
    BIOSTASIS                                                         = 3384,
    BONESHEAL                                                         = 2938,
    BONESTOSSGRENADE_TOSSGRENADETYCHUS                                = 2940,
    BROODLORDQUEUE2_CANCEL                                            = 1040,
    BROODLORDQUEUE2_CANCELSLOT                                        = 1041,
    BUILDINGSHIELD                                                    = 1994,
    BUILDINGSTASIS                                                    = 2000,
    BUILDINPROGRESSNONCANCELLABLE_CANCEL                              = 2842,
    BUILDINPROGRESSNYDUSCANAL_CANCEL                                  = 175,
    BUILDNYDUSCANAL_CANCEL                                            = 1798,
    BUILDNYDUSCANAL_SUMMONNYDUSCANALATTACKER                          = 1769,
    BUILD_ARMORY                                                      = 331,
    BUILD_ASSIMILATOR                                                 = 882,
    BUILD_BANELINGNEST                                                = 1162,
    BUILD_BARRACKS                                                    = 321,
    BUILD_BUNKER                                                      = 324,
    BUILD_CANCEL                                                      = 910,
    BUILD_COMMANDCENTER                                               = 318,
    BUILD_CREEPTUMOR                                                  = 1153,
    BUILD_CREEPTUMOR_QUEEN                                            = 1694,
    BUILD_CREEPTUMOR_TUMOR                                            = 1733,
    BUILD_CYBERNETICSCORE                                             = 894,
    BUILD_DARKSHRINE                                                  = 891,
    BUILD_ENGINEERINGBAY                                              = 322,
    BUILD_EVOLUTIONCHAMBER                                            = 1156,
    BUILD_EXTRACTOR                                                   = 1154,
    BUILD_FACTORY                                                     = 328,
    BUILD_FLEETBEACON                                                 = 885,
    BUILD_FORGE                                                       = 884,
    BUILD_FUSIONCORE                                                  = 333,
    BUILD_GATEWAY                                                     = 883,
    BUILD_GHOSTACADEMY                                                = 327,
    BUILD_HATCHERY                                                    = 1152,
    BUILD_HYDRALISKDEN                                                = 1157,
    BUILD_INFESTATIONPIT                                              = 1160,
    BUILD_INTERCEPTORS                                                = 1042,
    BUILD_LURKERDEN                                                   = 1163,
    BUILD_MISSILETURRET                                               = 323,
    BUILD_NEXUS                                                       = 880,
    BUILD_NUKE                                                        = 710,
    BUILD_NYDUSNETWORK                                                = 1161,
    BUILD_NYDUSWORM                                                   = 1768,
    BUILD_PHOTONCANNON                                                = 887,
    BUILD_PYLON                                                       = 881,
    BUILD_REACTOR                                                     = 3683,
    BUILD_REACTOR_BARRACKS                                            = 422,
    BUILD_REACTOR_FACTORY                                             = 455,
    BUILD_REACTOR_STARPORT                                            = 488,
    BUILD_REFINERY                                                    = 320,
    BUILD_ROACHWARREN                                                 = 1165,
    BUILD_ROBOTICSBAY                                                 = 892,
    BUILD_ROBOTICSFACILITY                                            = 893,
    BUILD_SENSORTOWER                                                 = 326,
    BUILD_SHIELDBATTERY                                               = 895,
    BUILD_SPAWNINGPOOL                                                = 1155,
    BUILD_SPINECRAWLER                                                = 1166,
    BUILD_SPIRE                                                       = 1158,
    BUILD_SPORECRAWLER                                                = 1167,
    BUILD_STARGATE                                                    = 889,
    BUILD_STARPORT                                                    = 329,
    BUILD_STASISTRAP                                                  = 2505,
    BUILD_SUPPLYDEPOT                                                 = 319,
    BUILD_TECHLAB                                                     = 3682,
    BUILD_TECHLAB_BARRACKS                                            = 421,
    BUILD_TECHLAB_FACTORY                                             = 454,
    BUILD_TECHLAB_STARPORT                                            = 487,
    BUILD_TEMPLARARCHIVE                                              = 890,
    BUILD_TWILIGHTCOUNCIL                                             = 886,
    BUILD_ULTRALISKCAVERN                                             = 1159,
    BUNKERATTACK                                                      = 2890,
    BUNKERSTOP_HOLDFIRESPECIAL                                        = 2894,
    BUNKERSTOP_STOPBUNKER                                             = 2893,
    BURROWBANELINGDOWN_CANCEL                                         = 1375,
    BURROWCREEPTUMORDOWN_BURROWDOWN                                   = 1662,
    BURROWDOWN                                                        = 3661,
    BURROWDOWN_BANELING                                               = 1374,
    BURROWDOWN_DRONE                                                  = 1378,
    BURROWDOWN_HYDRALISK                                              = 1382,
    BURROWDOWN_INFESTOR                                               = 1444,
    BURROWDOWN_INFESTORTERRAN                                         = 1394,
    BURROWDOWN_LURKER                                                 = 2108,
    BURROWDOWN_QUEEN                                                  = 1433,
    BURROWDOWN_RAVAGER                                                = 2340,
    BURROWDOWN_ROACH                                                  = 1386,
    BURROWDOWN_SWARMHOST                                              = 2014,
    BURROWDOWN_ULTRALISK                                              = 1512,
    BURROWDOWN_WIDOWMINE                                              = 2095,
    BURROWDOWN_ZERGLING                                               = 1390,
    BURROWDRONEDOWN_CANCEL                                            = 1379,
    BURROWEDBANELINGSTOP_HOLDFIRESPECIAL                              = 2052,
    BURROWEDBANELINGSTOP_STOPROACHBURROWED                            = 2051,
    BURROWEDSTOP_HOLDFIRESPECIAL                                      = 1686,
    BURROWEDSTOP_STOPROACHBURROWED                                    = 1685,
    BURROWHUNTERKILLERDOWN_BURROWDOWN                                 = 3228,
    BURROWHUNTERKILLERDOWN_CANCEL                                     = 3229,
    BURROWHUNTERKILLERUP_BURROWUP                                     = 3230,
    BURROWHYDRALISKDOWN_CANCEL                                        = 1383,
    BURROWINFESTEDABOMINATIONDOWN_BURROWDOWN                          = 3224,
    BURROWINFESTEDABOMINATIONUP_BURROWUP                              = 3226,
    BURROWINFESTEDCIVILIANDOWN_BURROWDOWN                             = 2963,
    BURROWINFESTEDCIVILIANUP_BURROWUP                                 = 2965,
    BURROWINFESTEDTERRANCAMPAIGNDOWN_BURROWDOWN                       = 3240,
    BURROWINFESTEDTERRANCAMPAIGNUP_BURROWUP                           = 3242,
    BURROWINFESTORDOWN_CANCEL                                         = 1445,
    BURROWLURKERDOWN_BURROWDOWN                                       = 2754,
    BURROWLURKERDOWN_CANCEL                                           = 2755,
    BURROWLURKERMPDOWN_CANCEL                                         = 2109,
    BURROWLURKERUP_BURROWUP                                           = 2756,
    BURROWOMEGALISKDOWN_BURROWDOWN                                    = 3220,
    BURROWOMEGALISKUP_BURROWUP                                        = 3222,
    BURROWQUEENDOWN_CANCEL                                            = 1434,
    BURROWRAVAGERDOWN_CANCEL                                          = 2341,
    BURROWROACHDOWN_CANCEL                                            = 1387,
    BURROWUP                                                          = 3662,
    BURROWUP_BANELING                                                 = 1376,
    BURROWUP_DRONE                                                    = 1380,
    BURROWUP_HYDRALISK                                                = 1384,
    BURROWUP_INFESTOR                                                 = 1446,
    BURROWUP_INFESTORTERRAN                                           = 1396,
    BURROWUP_LURKER                                                   = 2110,
    BURROWUP_QUEEN                                                    = 1435,
    BURROWUP_RAVAGER                                                  = 2342,
    BURROWUP_ROACH                                                    = 1388,
    BURROWUP_SWARMHOST                                                = 2016,
    BURROWUP_ULTRALISK                                                = 1514,
    BURROWUP_WIDOWMINE                                                = 2097,
    BURROWUP_ZERGLING                                                 = 1392,
    BURROWZERGLINGDOWN_CANCEL                                         = 1391,
    CANCEL                                                            = 3659,
    CANCELSLOT_ADDON                                                  = 313,
    CANCELSLOT_HANGARQUEUE5                                           = 1039,
    CANCELSLOT_QUEUE1                                                 = 305,
    CANCELSLOT_QUEUE5                                                 = 307,
    CANCELSLOT_QUEUECANCELTOSELECTION                                 = 309,
    CANCELSLOT_QUEUEPASSIVE                                           = 1832,
    CANCELSLOT_QUEUEPASSIVECANCELTOSELECTION                          = 1834,
    CANCELTERRAZINEHARVEST_CANCEL                                     = 2899,
    CANCEL_ADEPTPHASESHIFT                                            = 2594,
    CANCEL_ADEPTSHADEPHASESHIFT                                       = 2596,
    CANCEL_BARRACKSADDON                                              = 451,
    CANCEL_BUILDINPROGRESS                                            = 314,
    CANCEL_CREEPTUMOR                                                 = 1763,
    CANCEL_FACTORYADDON                                               = 484,
    CANCEL_GRAVITONBEAM                                               = 174,
    CANCEL_HANGARQUEUE5                                               = 1038,
    CANCEL_LAST                                                       = 3671,
    CANCEL_LOCKON                                                     = 2354,
    CANCEL_MORPHBROODLORD                                             = 1373,
    CANCEL_MORPHGREATERSPIRE                                          = 1221,
    CANCEL_MORPHHIVE                                                  = 1219,
    CANCEL_MORPHLAIR                                                  = 1217,
    CANCEL_MORPHLURKER                                                = 2333,
    CANCEL_MORPHLURKERDEN                                             = 2113,
    CANCEL_MORPHMOTHERSHIP                                            = 1848,
    CANCEL_MORPHORBITAL                                               = 1517,
    CANCEL_MORPHOVERLORDTRANSPORT                                     = 2709,
    CANCEL_MORPHOVERSEER                                              = 1449,
    CANCEL_MORPHPLANETARYFORTRESS                                     = 1451,
    CANCEL_MORPHRAVAGER                                               = 2331,
    CANCEL_MORPHTHOREXPLOSIVEMODE                                     = 2365,
    CANCEL_MOTHERSHIPSTASIS                                           = 1850,
    CANCEL_NEURALPARASITE                                             = 250,
    CANCEL_NUKE                                                       = 1623,
    CANCEL_PROTOSSBUILDINGQUEUE                                       = 2075,
    CANCEL_QUEUE1                                                     = 304,
    CANCEL_QUEUE5                                                     = 306,
    CANCEL_QUEUEADDON                                                 = 312,
    CANCEL_QUEUECANCELTOSELECTION                                     = 308,
    CANCEL_QUEUEPASIVE                                                = 1831,
    CANCEL_QUEUEPASSIVECANCELTOSELECTION                              = 1833,
    CANCEL_SLOT                                                       = 3672,
    CANCEL_SPINECRAWLERROOT                                           = 1730,
    CANCEL_SPORECRAWLERROOT                                           = 1732,
    CANCEL_STARPORTADDON                                              = 517,
    CANCEL_STASISTRAP                                                 = 2535,
    CANCEL_TEMPESTDISRUPTIONBLAST                                     = 2699,
    CANCEL_VOIDRAYPRISMATICALIGNMENT                                  = 3707,
    CHANGESHRINEPROTOSS                                               = 3619,
    CHANGESHRINETERRAN                                                = 3617,
    CHANNELSNIPE_CANCEL                                               = 2715,
    CLIFFDOORCLOSE0_SPACEPLATFORMDOORCLOSE                            = 3517,
    CLIFFDOORCLOSE1_SPACEPLATFORMDOORCLOSE                            = 3521,
    CLIFFDOOROPEN0_SPACEPLATFORMDOOROPEN                              = 3515,
    CLIFFDOOROPEN1_SPACEPLATFORMDOOROPEN                              = 3519,
    CLOAKINGDRONE                                                     = 2592,
    CLONE                                                             = 1992,
    COLONISTSHIPLAND_LAND                                             = 3348,
    COLONISTSHIPLIFTOFF_LIFT                                          = 3346,
    COLONISTTRANSPORTTRANSPORT_COLONISTTRANSPORTLOAD                  = 3386,
    COLONISTTRANSPORTTRANSPORT_COLONISTTRANSPORTUNLOADALL             = 3387,
    COLONYINFESTATION                                                 = 3131,
    COLONYSHIPTRANSPORT_MEDIVACLOAD                                   = 3126,
    COLONYSHIPTRANSPORT_MEDIVACUNLOADALL                              = 3128,
    CONSUMEDNA                                                        = 2909,
    CONSUMPTION                                                       = 2907,
    CORRUPTIONBOMB                                                    = 2356,
    CORRUPTIONBOMB_CANCEL                                             = 2357,
    CORRUPTION_CANCEL                                                 = 35,
    CORRUPTION_CORRUPTIONABILITY                                      = 34,
    CORSAIRMPDISRUPTIONWEB                                            = 2477,
    CRITTERFLEE                                                       = 2144,
    D8CHARGE                                                          = 2758,
    DEFENSIVEMATRIX                                                   = 2760,
    DEFILERMPBURROW_BURROWDOWN                                        = 2489,
    DEFILERMPBURROW_CANCEL                                            = 2490,
    DEFILERMPCONSUME                                                  = 2483,
    DEFILERMPDARKSWARM                                                = 2485,
    DEFILERMPPLAGUE                                                   = 2487,
    DEFILERMPUNBURROW_BURROWUP                                        = 2491,
    DESTRUCTIBLEGATEDIAGONALBLURLOWERED_GATEOPEN                      = 3523,
    DESTRUCTIBLEGATEDIAGONALBLUR_GATECLOSE                            = 3535,
    DESTRUCTIBLEGATEDIAGONALULBRLOWERED_GATEOPEN                      = 3525,
    DESTRUCTIBLEGATEDIAGONALULBR_GATECLOSE                            = 3537,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN              = 3527,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTALBF_GATECLOSE                    = 3539,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN                = 3529,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTAL_GATECLOSE                      = 3541,
    DESTRUCTIBLEGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN                = 3531,
    DESTRUCTIBLEGATESTRAIGHTVERTICALLF_GATECLOSE                      = 3543,
    DESTRUCTIBLEGATESTRAIGHTVERTICALLOWERED_GATEOPEN                  = 3533,
    DESTRUCTIBLEGATESTRAIGHTVERTICAL_GATECLOSE                        = 3545,
    DIGESTERCREEPSPRAY                                                = 1839,
    DIGESTERTRANSPORT_LOADDIGESTER                                    = 1921,
    DISGUISEASMARINEWITHOUTSHIELD_MARINE                              = 187,
    DISGUISEASMARINEWITHSHIELD_MARINE                                 = 185,
    DISGUISEASZEALOT_ZEALOT                                           = 183,
    DISGUISEASZERGLINGWITHOUTWINGS_ZERGLING                           = 191,
    DISGUISEASZERGLINGWITHWINGS_ZERGLING                              = 189,
    DOMINATION                                                        = 3133,
    DOMINATION_CANCEL                                                 = 3134,
    DROPTOSUPPLYDEPOT_RAISE                                           = 3391,
    DUKESREVENGEDEFENSIVEMATRIX_DEFENSIVEMATRIX                       = 3314,
    DUKESREVENGEMISSILEPODS_MISSILEPODS                               = 3316,
    DUSKWINGBANSHEECLOAKINGFIELD_CLOAKOFF                             = 2953,
    DUSKWINGBANSHEECLOAKINGFIELD_CLOAKONBANSHEE                       = 2952,
    DUTCHPLACETURRET                                                  = 2961,
    EFFECT_ABDUCT                                                     = 2067,
    EFFECT_ADEPTPHASESHIFT                                            = 2544,
    EFFECT_AMORPHOUSARMORCLOUD                                        = 4109,
    EFFECT_ANTIARMORMISSILE                                           = 3753,
    EFFECT_AUTOTURRET                                                 = 349,
    EFFECT_BLINDINGCLOUD                                              = 2063,
    EFFECT_BLINK                                                      = 3687,
    EFFECT_BLINK_STALKER                                              = 1442,
    EFFECT_CALLDOWNMULE                                               = 171,
    EFFECT_CAUSTICSPRAY                                               = 2324,
    EFFECT_CHARGE                                                     = 1819,
    EFFECT_CHRONOBOOST                                                = 261,
    EFFECT_CHRONOBOOSTENERGYCOST                                      = 3755,
    EFFECT_CONTAMINATE                                                = 1825,
    EFFECT_CORROSIVEBILE                                              = 2338,
    EFFECT_EMP                                                        = 1628,
    EFFECT_EXPLODE                                                    = 42,
    EFFECT_FEEDBACK                                                   = 140,
    EFFECT_FORCEFIELD                                                 = 1526,
    EFFECT_FUNGALGROWTH                                               = 74,
    EFFECT_GHOSTSNIPE                                                 = 2714,
    EFFECT_GRAVITONBEAM                                               = 173,
    EFFECT_GUARDIANSHIELD                                             = 76,
    EFFECT_HEAL                                                       = 386,
    EFFECT_HUNTERSEEKERMISSILE                                        = 169,
    EFFECT_IMMORTALBARRIER                                            = 2328,
    EFFECT_INFESTEDTERRANS                                            = 40,
    EFFECT_INJECTLARVA                                                = 251,
    EFFECT_INTERFERENCEMATRIX                                         = 3747,
    EFFECT_KD8CHARGE                                                  = 2588,
    EFFECT_LOCKON                                                     = 2350,
    EFFECT_LOCUSTSWOOP                                                = 2387,
    EFFECT_MASSRECALL                                                 = 3686,
    EFFECT_MASSRECALL_MOTHERSHIP                                      = 2368,
    EFFECT_MASSRECALL_MOTHERSHIPCORE                                  = 1974,
    EFFECT_MASSRECALL_NEXUS                                           = 3757,
    EFFECT_MASSRECALL_STRATEGICRECALL                                 = 142,
    EFFECT_MEDIVACIGNITEAFTERBURNERS                                  = 2116,
    EFFECT_NEURALPARASITE                                             = 249,
    EFFECT_NUKECALLDOWN                                               = 1622,
    EFFECT_ORACLEREVELATION                                           = 2146,
    EFFECT_PARASITICBOMB                                              = 2542,
    EFFECT_PHOTONOVERCHARGE                                           = 2162,
    EFFECT_POINTDEFENSEDRONE                                          = 144,
    EFFECT_PSISTORM                                                   = 1036,
    EFFECT_PURIFICATIONNOVA                                           = 2346,
    EFFECT_REPAIR                                                     = 3685,
    EFFECT_REPAIRDRONE                                                = 3749,
    EFFECT_REPAIR_MULE                                                = 78,
    EFFECT_REPAIR_REPAIRDRONE                                         = 3751,
    EFFECT_REPAIR_SCV                                                 = 316,
    EFFECT_RESTORE                                                    = 3765,
    EFFECT_SALVAGE                                                    = 32,
    EFFECT_SCAN                                                       = 399,
    EFFECT_SHADOWSTRIDE                                               = 2700,
    EFFECT_SPAWNCHANGELING                                            = 181,
    EFFECT_SPAWNLOCUSTS                                               = 2704,
    EFFECT_SPRAY                                                      = 3684,
    EFFECT_SPRAY_PROTOSS                                              = 30,
    EFFECT_SPRAY_TERRAN                                               = 26,
    EFFECT_SPRAY_ZERG                                                 = 28,
    EFFECT_STIM                                                       = 3675,
    EFFECT_STIM_MARAUDER                                              = 253,
    EFFECT_STIM_MARAUDER_REDIRECT                                     = 1684,
    EFFECT_STIM_MARINE                                                = 380,
    EFFECT_STIM_MARINE_REDIRECT                                       = 1683,
    EFFECT_SUPPLYDROP                                                 = 255,
    EFFECT_TACTICALJUMP                                               = 2358,
    EFFECT_TEMPESTDISRUPTIONBLAST                                     = 2698,
    EFFECT_TIMEWARP                                                   = 2244,
    EFFECT_TRANSFUSION                                                = 1664,
    EFFECT_VIPERCONSUME                                               = 2069,
    EFFECT_VOIDRAYPRISMATICALIGNMENT                                  = 2393,
    EFFECT_WIDOWMINEATTACK                                            = 2099,
    EFFECT_YAMATOGUN                                                  = 401,
    EGGPOP                                                            = 2911,
    ENERGYNOVA                                                        = 3075,
    EVOLUTIONCHAMBERRESEARCH_EVOLVEPROPULSIVEPERISTALSIS              = 1195,
    EXPERIMENTALPLASMAGUN                                             = 2913,
    EXTENDINGBRIDGENEWIDE10OUT_BRIDGEEXTEND                           = 2126,
    EXTENDINGBRIDGENEWIDE10_BRIDGERETRACT                             = 2128,
    EXTENDINGBRIDGENEWIDE12OUT_BRIDGEEXTEND                           = 2134,
    EXTENDINGBRIDGENEWIDE12_BRIDGERETRACT                             = 2136,
    EXTENDINGBRIDGENEWIDE8OUT_BRIDGEEXTEND                            = 2118,
    EXTENDINGBRIDGENEWIDE8_BRIDGERETRACT                              = 2120,
    EXTENDINGBRIDGENWWIDE10OUT_BRIDGEEXTEND                           = 2130,
    EXTENDINGBRIDGENWWIDE10_BRIDGERETRACT                             = 2132,
    EXTENDINGBRIDGENWWIDE12OUT_BRIDGEEXTEND                           = 2138,
    EXTENDINGBRIDGENWWIDE12_BRIDGERETRACT                             = 2140,
    EXTENDINGBRIDGENWWIDE8OUT_BRIDGEEXTEND                            = 2122,
    EXTENDINGBRIDGENWWIDE8_BRIDGERETRACT                              = 2124,
    EYESTALK                                                          = 2065,
    EYESTALK_CANCEL                                                   = 2066,
    FACTORYREACTORMORPH_REACTOR                                       = 1678,
    FACTORYTECHLABMORPH_TECHLABFACTORY                                = 1670,
    FACTORYTECHREACTORMORPH_TECHLABFACTORY                            = 3306,
    FLYERSHIELD                                                       = 1942,
    FORCEFIELD_CANCEL                                                 = 1527,
    FRENZY                                                            = 1823,
    GATHERSPECIALOBJECT                                               = 2915,
    GENERAL_HOLDPOSITION                                              = 3793,
    GENERAL_MOVE                                                      = 3794,
    GENERAL_PATROL                                                    = 3795,
    GRAPPLE                                                           = 2501,
    GRAVITONPRISON                                                    = 3005,
    GWALEARN_TESTLEARN                                                = 3625,
    HALLUCINATION_ADEPT                                               = 2391,
    HALLUCINATION_ARCHON                                              = 146,
    HALLUCINATION_COLOSSUS                                            = 148,
    HALLUCINATION_DISRUPTOR                                           = 2389,
    HALLUCINATION_HIGHTEMPLAR                                         = 150,
    HALLUCINATION_IMMORTAL                                            = 152,
    HALLUCINATION_ORACLE                                              = 2114,
    HALLUCINATION_PHOENIX                                             = 154,
    HALLUCINATION_PROBE                                               = 156,
    HALLUCINATION_STALKER                                             = 158,
    HALLUCINATION_VOIDRAY                                             = 160,
    HALLUCINATION_WARPPRISM                                           = 162,
    HALLUCINATION_ZEALOT                                              = 164,
    HALT                                                              = 3660,
    HALT_BUILDING                                                     = 315,
    HALT_TERRANBUILD                                                  = 348,
    HARVEST_GATHER                                                    = 3666,
    HARVEST_GATHER_DRONE                                              = 1183,
    HARVEST_GATHER_MULE                                               = 166,
    HARVEST_GATHER_PROBE                                              = 298,
    HARVEST_GATHER_SCV                                                = 295,
    HARVEST_RETURN                                                    = 3667,
    HARVEST_RETURN_DRONE                                              = 1184,
    HARVEST_RETURN_MULE                                               = 167,
    HARVEST_RETURN_PROBE                                              = 299,
    HARVEST_RETURN_SCV                                                = 296,
    HEAL_MEDICHEAL                                                    = 2750,
    HELIOSCRASHMORPH_CRASHMORPH                                       = 3395,
    HERCULESLAND                                                      = 3356,
    HERCULESLIFTOFF_LIFT                                              = 3354,
    HERCULESTRANSPORT_MEDIVACLOAD                                     = 2942,
    HERCULESTRANSPORT_MEDIVACUNLOADALL                                = 2944,
    HERDINTERACT_HERD                                                 = 1821,
    HEROARMNUKE_NUKEARM                                               = 3143,
    HERONUCLEARSTRIKE_CANCEL                                          = 3164,
    HOLDFIRE                                                          = 11,
    HOLDFIRE_STOPSPECIAL                                              = 10,
    HUTTRANSPORT_HUTLOAD                                              = 2766,
    HUTTRANSPORT_HUTUNLOADALL                                         = 2767,
    HYBRIDBLINK_ZERATULBLINK                                          = 3139,
    HYBRIDCPLASMABLAST                                                = 3141,
    HYBRIDFAOESTUN                                                    = 3013,
    HYPERIONYAMATOSPECIAL_HYPERIONYAMATOGUN                           = 2954,
    IMPALE                                                            = 2348,
    IMPLOSION                                                         = 3007,
    INFESTABLEHUTTRANSPORT_HUTLOAD                                    = 2956,
    INFESTABLEHUTTRANSPORT_HUTUNLOADALL                               = 2957,
    INFESTEDVENTSPAWNBROODLORD_SPAWNBROODLORD                         = 2846,
    INFESTEDVENTSPAWNCORRUPTOR_SPAWNCORRUPTOR                         = 2844,
    INFESTEDVENTSPAWNMUTALISK_LEVIATHANSPAWNMUTALISK                  = 2850,
    INFESTORENSNARE                                                   = 3763,
    INVALID                                                           = 0,
    INVULNERABILITYSHIELD                                             = 2142,
    IRRADIATE                                                         = 2848,
    IRRADIATE_CANCEL                                                  = 2849,
    KARASSPLASMASURGE                                                 = 3135,
    LAND                                                              = 3678,
    LAND_BARRACKS                                                     = 554,
    LAND_COMMANDCENTER                                                = 419,
    LAND_FACTORY                                                      = 520,
    LAND_ORBITALCOMMAND                                               = 1524,
    LAND_STARPORT                                                     = 522,
    LEECH                                                             = 179,
    LEECHRESOURCES_CANCEL                                             = 1987,
    LEVIATHANSPAWNBROODLORD_SPAWNBROODLORD                            = 2773,
    LEVIATHANSPAWNMUTALISK                                            = 2901,
    LIBERATORMORPHTOAA_LIBERATORAAMODE                                = 2556,
    LIBERATORMORPHTOAG_LIBERATORAGMODE                                = 2554,
    LIBRARYDOWN                                                       = 3362,
    LIBRARYUP                                                         = 3364,
    LIFT                                                              = 3679,
    LIFT_BARRACKS                                                     = 452,
    LIFT_COMMANDCENTER                                                = 417,
    LIFT_FACTORY                                                      = 485,
    LIFT_ORBITALCOMMAND                                               = 1522,
    LIFT_STARPORT                                                     = 518,
    LIGHTBRIDGEOFF                                                    = 3358,
    LIGHTBRIDGEOFFTOPRIGHT_LIGHTBRIDGEOFF                             = 3647,
    LIGHTBRIDGEON                                                     = 3360,
    LIGHTBRIDGEONTOPRIGHT_LIGHTBRIDGEON                               = 3649,
    LIGHTNINGBOMB                                                     = 2499,
    LIGHTOFAIUR                                                       = 2366,
    LOAD                                                              = 3668,
    LOADALL                                                           = 3663,
    LOADALL_COMMANDCENTER                                             = 416,
    LOADOUTSPRAY_LOADOUTSPRAY_1                                       = 3797,
    LOADOUTSPRAY_LOADOUTSPRAY_10                                      = 3806,
    LOADOUTSPRAY_LOADOUTSPRAY_11                                      = 3807,
    LOADOUTSPRAY_LOADOUTSPRAY_12                                      = 3808,
    LOADOUTSPRAY_LOADOUTSPRAY_13                                      = 3809,
    LOADOUTSPRAY_LOADOUTSPRAY_14                                      = 3810,
    LOADOUTSPRAY_LOADOUTSPRAY_2                                       = 3798,
    LOADOUTSPRAY_LOADOUTSPRAY_3                                       = 3799,
    LOADOUTSPRAY_LOADOUTSPRAY_4                                       = 3800,
    LOADOUTSPRAY_LOADOUTSPRAY_5                                       = 3801,
    LOADOUTSPRAY_LOADOUTSPRAY_6                                       = 3802,
    LOADOUTSPRAY_LOADOUTSPRAY_7                                       = 3803,
    LOADOUTSPRAY_LOADOUTSPRAY_8                                       = 3804,
    LOADOUTSPRAY_LOADOUTSPRAY_9                                       = 3805,
    LOAD_BUNKER                                                       = 407,
    LOAD_MEDIVAC                                                      = 394,
    LOAD_NYDUSNETWORK                                                 = 1437,
    LOAD_NYDUSWORM                                                    = 2370,
    LOAD_OVERLORD                                                     = 1406,
    LOAD_WARPPRISM                                                    = 911,
    LOCKONAIR                                                         = 2352,
    LOCUSTMPFLYINGMORPHTOGROUND_LOCUSTMPFLYINGSWOOP                   = 2383,
    LOCUSTMPFLYINGSWOOPATTACK_LOCUSTMPFLYINGSWOOP                     = 2706,
    LOCUSTMPMORPHTOAIR_LOCUSTMPFLYINGSWOOP                            = 2385,
    LOKIMISSILEPODS_MISSILEPODS                                       = 2764,
    LOKIUNDOCK_LIFT                                                   = 2919,
    LOKIYAMATO_LOKIYAMATOGUN                                          = 3188,
    LURKERASPECTFROMHYDRALISKBURROWED_CANCEL                          = 2837,
    LURKERASPECTFROMHYDRALISKBURROWED_LURKERFROMHYDRALISKBURROWED     = 2836,
    LURKERASPECTMPFROMHYDRALISKBURROWED_CANCEL                        = 2105,
    LURKERASPECTMPFROMHYDRALISKBURROWED_LURKERMPFROMHYDRALISKBURROWED = 2104,
    LURKERASPECTMP_CANCEL                                             = 2107,
    LURKERASPECTMP_LURKERMP                                           = 2106,
    LURKERASPECT_CANCEL                                               = 2753,
    LURKERASPECT_LURKER                                               = 2752,
    MAKEVULTURESPIDERMINES_SPIDERMINEREPLENISH                        = 2852,
    MASSIVEKNOCKOVER                                                  = 2093,
    MAXIUMTHRUST_MAXIMUMTHRUST                                        = 2006,
    MERGEABLE_CANCEL                                                  = 1411,
    METALGATEDIAGONALBLURLOWERED_GATEOPEN                             = 3569,
    METALGATEDIAGONALBLUR_GATECLOSE                                   = 3581,
    METALGATEDIAGONALULBRLOWERED_GATEOPEN                             = 3571,
    METALGATEDIAGONALULBR_GATECLOSE                                   = 3583,
    METALGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN                     = 3573,
    METALGATESTRAIGHTHORIZONTALBF_GATECLOSE                           = 3585,
    METALGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN                       = 3575,
    METALGATESTRAIGHTHORIZONTAL_GATECLOSE                             = 3587,
    METALGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN                       = 3577,
    METALGATESTRAIGHTVERTICALLF_GATECLOSE                             = 3589,
    METALGATESTRAIGHTVERTICALLOWERED_GATEOPEN                         = 3579,
    METALGATESTRAIGHTVERTICAL_GATECLOSE                               = 3591,
    MINDBLAST                                                         = 2921,
    MINDCONTROL                                                       = 2874,
    MISSILEPODS                                                       = 2762,
    MORPH_ARCHON                                                      = 1766,
    MORPH_BANELING                                                    = 4119,
    MORPH_BROODLORD                                                   = 1372,
    MORPH_CANCEL                                                      = 1519,
    MORPH_GATEWAY                                                     = 1520,
    MORPH_GREATERSPIRE                                                = 1220,
    MORPH_HELLBAT                                                     = 1998,
    MORPH_HELLION                                                     = 1978,
    MORPH_HIVE                                                        = 1218,
    MORPH_LAIR                                                        = 1216,
    MORPH_LIBERATORAAMODE                                             = 2560,
    MORPH_LIBERATORAGMODE                                             = 2558,
    MORPH_LURKER                                                      = 2332,
    MORPH_LURKERDEN                                                   = 2112,
    MORPH_MORPHTODEVOURERMP                                           = 2481,
    MORPH_MORPHTOGUARDIANMP                                           = 2479,
    MORPH_MORPHTOINFESTEDCIVILIAN                                     = 2923,
    MORPH_MOTHERSHIP                                                  = 1847,
    MORPH_MOVE                                                        = 1835,
    MORPH_OBSERVERMODE                                                = 3739,
    MORPH_ORBITALCOMMAND                                              = 1516,
    MORPH_OVERLORDTRANSPORT                                           = 2708,
    MORPH_OVERSEER                                                    = 1448,
    MORPH_OVERSEERMODE                                                = 3745,
    MORPH_OVERSIGHTMODE                                               = 3743,
    MORPH_PLANETARYFORTRESS                                           = 1450,
    MORPH_RAVAGER                                                     = 2330,
    MORPH_ROOT                                                        = 3680,
    MORPH_SIEGEMODE                                                   = 388,
    MORPH_SPINECRAWLERROOT                                            = 1729,
    MORPH_SPINECRAWLERUPROOT                                          = 1725,
    MORPH_SPORECRAWLERROOT                                            = 1731,
    MORPH_SPORECRAWLERUPROOT                                          = 1727,
    MORPH_SUPPLYDEPOT_LOWER                                           = 556,
    MORPH_SUPPLYDEPOT_RAISE                                           = 558,
    MORPH_SURVEILLANCEMODE                                            = 3741,
    MORPH_THOREXPLOSIVEMODE                                           = 2364,
    MORPH_THORHIGHIMPACTMODE                                          = 2362,
    MORPH_UNSIEGE                                                     = 390,
    MORPH_UPROOT                                                      = 3681,
    MORPH_VIKINGASSAULTMODE                                           = 403,
    MORPH_VIKINGFIGHTERMODE                                           = 405,
    MORPH_WARPGATE                                                    = 1518,
    MORPH_WARPPRISMPHASINGMODE                                        = 1528,
    MORPH_WARPPRISMTRANSPORTMODE                                      = 1530,
    MOTHERSHIPCLOAK_ORACLECLOAKFIELD                                  = 4122,
    MOTHERSHIPCOREENERGIZE                                            = 2102,
    MOTHERSHIPCOREENERGIZE_CANCEL                                     = 2103,
    MOTHERSHIPCOREPURIFYNEXUSCANCEL_CANCEL                            = 2160,
    MOTHERSHIPCORETELEPORT                                            = 1883,
    MOTHERSHIPCOREWEAPON_MOTHERSHIPSTASIS                             = 1851,
    MOTHERSHIPSTASIS                                                  = 1849,
    MOVE_ACQUIREMOVE                                                  = 19,
    MOVE_MOVE                                                         = 16,
    MOVE_MOVEHOLDPOSITION                                             = 18,
    MOVE_MOVEPATROL                                                   = 17,
    MOVE_TURN                                                         = 20,
    NEXUSINVULNERABILITY                                              = 1930,
    NEXUSPHASESHIFT                                                   = 1932,
    NEXUSSHIELDOVERCHARGE                                             = 3767,
    NEXUSSHIELDOVERCHARGEOFF                                          = 3769,
    NEXUSSHIELDRECHARGE                                               = 3759,
    NEXUSSHIELDRECHARGEONPYLON                                        = 3761,
    NOVASNIPE                                                         = 3232,
    OBLITERATE                                                        = 2876,
    ODINBARRAGE                                                       = 3165,
    ODINBARRAGE_CANCEL                                                = 3166,
    ODINNUCLEARSTRIKE_CANCEL                                          = 3118,
    ODINNUCLEARSTRIKE_ODINNUKECALLDOWN                                = 3117,
    ODINWRECKAGE_ODIN                                                 = 3119,
    OMEGASTORM                                                        = 3009,
    ORACLECLOAKFIELD                                                  = 1940,
    ORACLECLOAKINGFIELDTARGETED                                       = 2326,
    ORACLENORMALMODE                                                  = 2150,
    ORACLENORMALMODE_CANCEL                                           = 2151,
    ORACLEPHASESHIFT                                                  = 2334,
    ORACLEREVELATIONMODE                                              = 2148,
    ORACLEREVELATIONMODE_CANCEL                                       = 2149,
    ORACLESTASISTRAPACTIVATE_ACTIVATESTASISWARD                       = 2536,
    ORACLESTASISTRAP_ORACLEBUILDSTASISTRAP                            = 2503,
    OVERCHARGE                                                        = 2360,
    PARKCOLONISTVEHICLE                                               = 2903,
    PENETRATINGSHOT                                                   = 2590,
    PHASEMINEBLAST                                                    = 3169,
    PHASESHIFT                                                        = 193,
    PHASINGMODE_CANCEL                                                = 1529,
    PICKUP                                                            = 3399,
    PICKUPARCADE_PICKUP                                               = 3401,
    PICKUPGAS100                                                      = 3403,
    PICKUPMINERALS100                                                 = 3405,
    PICKUPPALLETGAS                                                   = 2089,
    PICKUPPALLETMINERALS                                              = 2091,
    PICKUPSCRAPLARGE                                                  = 2087,
    PICKUPSCRAPMEDIUM                                                 = 2085,
    PICKUPSCRAPSMALL                                                  = 2083,
    PORTCITY_BRIDGE_UNITE10OUT_BRIDGEEXTEND                           = 2674,
    PORTCITY_BRIDGE_UNITE10_BRIDGERETRACT                             = 2676,
    PORTCITY_BRIDGE_UNITE12OUT_BRIDGEEXTEND                           = 2690,
    PORTCITY_BRIDGE_UNITE12_BRIDGERETRACT                             = 2692,
    PORTCITY_BRIDGE_UNITE8OUT_BRIDGEEXTEND                            = 2658,
    PORTCITY_BRIDGE_UNITE8_BRIDGERETRACT                              = 2660,
    PORTCITY_BRIDGE_UNITN10OUT_BRIDGEEXTEND                           = 2666,
    PORTCITY_BRIDGE_UNITN10_BRIDGERETRACT                             = 2668,
    PORTCITY_BRIDGE_UNITN12OUT_BRIDGEEXTEND                           = 2682,
    PORTCITY_BRIDGE_UNITN12_BRIDGERETRACT                             = 2684,
    PORTCITY_BRIDGE_UNITN8OUT_BRIDGEEXTEND                            = 2650,
    PORTCITY_BRIDGE_UNITN8_BRIDGERETRACT                              = 2652,
    PORTCITY_BRIDGE_UNITNE10OUT_BRIDGEEXTEND                          = 2618,
    PORTCITY_BRIDGE_UNITNE10_BRIDGERETRACT                            = 2620,
    PORTCITY_BRIDGE_UNITNE12OUT_BRIDGEEXTEND                          = 2634,
    PORTCITY_BRIDGE_UNITNE12_BRIDGERETRACT                            = 2636,
    PORTCITY_BRIDGE_UNITNE8OUT_BRIDGEEXTEND                           = 2602,
    PORTCITY_BRIDGE_UNITNE8_BRIDGERETRACT                             = 2604,
    PORTCITY_BRIDGE_UNITNW10OUT_BRIDGEEXTEND                          = 2626,
    PORTCITY_BRIDGE_UNITNW10_BRIDGERETRACT                            = 2628,
    PORTCITY_BRIDGE_UNITNW12OUT_BRIDGEEXTEND                          = 2642,
    PORTCITY_BRIDGE_UNITNW12_BRIDGERETRACT                            = 2644,
    PORTCITY_BRIDGE_UNITNW8OUT_BRIDGEEXTEND                           = 2610,
    PORTCITY_BRIDGE_UNITNW8_BRIDGERETRACT                             = 2612,
    PORTCITY_BRIDGE_UNITS10OUT_BRIDGEEXTEND                           = 2670,
    PORTCITY_BRIDGE_UNITS10_BRIDGERETRACT                             = 2672,
    PORTCITY_BRIDGE_UNITS12OUT_BRIDGEEXTEND                           = 2686,
    PORTCITY_BRIDGE_UNITS12_BRIDGERETRACT                             = 2688,
    PORTCITY_BRIDGE_UNITS8OUT_BRIDGEEXTEND                            = 2654,
    PORTCITY_BRIDGE_UNITS8_BRIDGERETRACT                              = 2656,
    PORTCITY_BRIDGE_UNITSE10OUT_BRIDGEEXTEND                          = 2622,
    PORTCITY_BRIDGE_UNITSE10_BRIDGERETRACT                            = 2624,
    PORTCITY_BRIDGE_UNITSE12OUT_BRIDGEEXTEND                          = 2638,
    PORTCITY_BRIDGE_UNITSE12_BRIDGERETRACT                            = 2640,
    PORTCITY_BRIDGE_UNITSE8OUT_BRIDGEEXTEND                           = 2606,
    PORTCITY_BRIDGE_UNITSE8_BRIDGERETRACT                             = 2608,
    PORTCITY_BRIDGE_UNITSW10OUT_BRIDGEEXTEND                          = 2630,
    PORTCITY_BRIDGE_UNITSW10_BRIDGERETRACT                            = 2632,
    PORTCITY_BRIDGE_UNITSW12OUT_BRIDGEEXTEND                          = 2646,
    PORTCITY_BRIDGE_UNITSW12_BRIDGERETRACT                            = 2648,
    PORTCITY_BRIDGE_UNITSW8OUT_BRIDGEEXTEND                           = 2614,
    PORTCITY_BRIDGE_UNITSW8_BRIDGERETRACT                             = 2616,
    PORTCITY_BRIDGE_UNITW10OUT_BRIDGEEXTEND                           = 2678,
    PORTCITY_BRIDGE_UNITW10_BRIDGERETRACT                             = 2680,
    PORTCITY_BRIDGE_UNITW12OUT_BRIDGEEXTEND                           = 2694,
    PORTCITY_BRIDGE_UNITW12_BRIDGERETRACT                             = 2696,
    PORTCITY_BRIDGE_UNITW8OUT_BRIDGEEXTEND                            = 2662,
    PORTCITY_BRIDGE_UNITW8_BRIDGERETRACT                              = 2664,
    PROTOSSBUILDINGQUEUE_CANCELSLOT                                   = 2076,
    PSIONICSHOCKWAVE                                                  = 3011,
    PSYTROUSOXIDE_PSYTROUSOXIDEOFF                                    = 3375,
    PSYTROUSOXIDE_PSYTROUSOXIDEON                                     = 3374,
    PULSARBEAM_RIPFIELD                                               = 2377,
    PULSARCANNON                                                      = 2379,
    PURIFICATIONNOVA                                                  = 2344,
    PURIFICATIONNOVAMORPHBACK_PURIFICATIONNOVA                        = 2548,
    PURIFICATIONNOVAMORPH_PURIFICATIONNOVA                            = 2546,
    PURIFIERPLANETCRACKER_PLANETCRACKER                               = 3238,
    PURIFIERTOGGLEPOWER_PURIFIERPOWERDOWN                             = 3167,
    PURIFIERTOGGLEPOWER_PURIFIERPOWERUP                               = 3168,
    PURIFYMORPHPYLONBACK_MOTHERSHIPCOREWEAPON                         = 2718,
    PURIFYMORPHPYLON_MOTHERSHIPCOREWEAPON                             = 2716,
    QUE5LONGBLEND_CANCEL                                              = 310,
    QUE5LONGBLEND_CANCELSLOT                                          = 311,
    QUE8_CANCEL                                                       = 2077,
    QUE8_CANCELSLOT                                                   = 2078,
    QUEENBUILD_CANCEL                                                 = 1724,
    QUEENFLY                                                          = 1938,
    QUEENLAND                                                         = 1936,
    QUEENMPENSNARE                                                    = 2493,
    QUEENMPINFESTCOMMANDCENTER                                        = 2497,
    QUEENMPSPAWNBROODLINGS                                            = 2495,
    QUEENSHOCKWAVE                                                    = 2925,
    RALLY_BUILDING                                                    = 195,
    RALLY_COMMANDCENTER                                               = 203,
    RALLY_HATCHERY_UNITS                                              = 211,
    RALLY_HATCHERY_WORKERS                                            = 212,
    RALLY_MORPHING_UNIT                                               = 199,
    RALLY_NEXUS                                                       = 207,
    RALLY_UNITS                                                       = 3673,
    RALLY_WORKERS                                                     = 3690,
    RAVENBUILD_CANCEL                                                 = 379,
    RAYNORC4_PLANTC4CHARGE                                            = 3312,
    RAYNORSNIPE                                                       = 2936,
    REDSTONELAVACRITTERBURROW_BURROWDOWN                              = 1398,
    REDSTONELAVACRITTERINJUREDBURROW_BURROWDOWN                       = 1400,
    REDSTONELAVACRITTERINJUREDUNBURROW_BURROWUP                       = 1404,
    REDSTONELAVACRITTERUNBURROW_BURROWUP                              = 1402,
    REFINERYTOAUTOMATEDREFINERY_RAISE                                 = 3393,
    RELEASEINTERCEPTORS                                               = 2336,
    RELEASEMINION                                                     = 2880,
    RESEARCHLABTRANSPORT_HUTLOAD                                      = 3121,
    RESEARCHLABTRANSPORT_HUTUNLOADALL                                 = 3122,
    RESEARCH_ADAPTIVETALONS                                           = 3709,
    RESEARCH_ADEPTRESONATINGGLAIVES                                   = 1594,
    RESEARCH_ADVANCEDBALLISTICS                                       = 805,
    RESEARCH_AMPLIFIEDSHIELDING                                       = 1596,
    RESEARCH_ANABOLICSYNTHESIS                                        = 263,
    RESEARCH_ARMORPIERCINGROCKETS                                     = 767,
    RESEARCH_BALLISTICRANGE                                           = 1533,
    RESEARCH_BANSHEECLOAKINGFIELD                                     = 790,
    RESEARCH_BANSHEEHYPERFLIGHTROTORS                                 = 799,
    RESEARCH_BATTLECRUISERWEAPONREFIT                                 = 1532,
    RESEARCH_BLINK                                                    = 1593,
    RESEARCH_BURROW                                                   = 1225,
    RESEARCH_CENTRIFUGALHOOKS                                         = 1482,
    RESEARCH_CHARGE                                                   = 1592,
    RESEARCH_CHITINOUSPLATING                                         = 265,
    RESEARCH_COMBATSHIELD                                             = 731,
    RESEARCH_CONCUSSIVESHELLS                                         = 732,
    RESEARCH_CYCLONELOCKONDAMAGE                                      = 769,
    RESEARCH_CYCLONERAPIDFIRELAUNCHERS                                = 768,
    RESEARCH_CYCLONERESEARCHHURRICANETHRUSTERS                        = 770,
    RESEARCH_DRILLINGCLAWS                                            = 764,
    RESEARCH_DURABLEMATERIALS                                         = 797,
    RESEARCH_ENHANCEDMUNITIONS                                        = 806,
    RESEARCH_EVOLVEAMORPHOUSARMORCLOUD                                = 1457,
    RESEARCH_EVOLVEVENTRALSACKS                                       = 1224,
    RESEARCH_EXTENDEDTHERMALLANCE                                     = 1097,
    RESEARCH_GLIALREGENERATION                                        = 216,
    RESEARCH_GRAVITICBOOSTER                                          = 1093,
    RESEARCH_GRAVITICDRIVE                                            = 1094,
    RESEARCH_GROOVEDSPINES                                            = 1282,
    RESEARCH_HALLUCINATION                                            = 1571,
    RESEARCH_HIGHCAPACITYFUELTANKS                                    = 804,
    RESEARCH_HISECAUTOTRACKING                                        = 650,
    RESEARCH_IMMORTALREVIVE                                           = 1099,
    RESEARCH_INFERNALPREIGNITER                                       = 761,
    RESEARCH_INTERCEPTORGRAVITONCATAPULT                              = 44,
    RESEARCH_INTERCEPTORLAUNCHSPEEDUPGRADE                            = 45,
    RESEARCH_LIBERATORAGMODE                                          = 800,
    RESEARCH_LOCKONRANGEUPGRADE                                       = 765,
    RESEARCH_LOCUSTLIFETIMEINCREASE                                   = 1456,
    RESEARCH_LURKERRANGE                                              = 1286,
    RESEARCH_MEDIVACENERGYUPGRADE                                     = 792,
    RESEARCH_MUSCULARAUGMENTS                                         = 1283,
    RESEARCH_NEOSTEELFRAME                                            = 655,
    RESEARCH_NEURALPARASITE                                           = 1455,
    RESEARCH_PERSONALCLOAKING                                         = 820,
    RESEARCH_PHOENIXANIONPULSECRYSTALS                                = 46,
    RESEARCH_PNEUMATIZEDCARAPACE                                      = 1223,
    RESEARCH_PROTOSSAIRARMOR                                          = 3692,
    RESEARCH_PROTOSSAIRARMORLEVEL1                                    = 1565,
    RESEARCH_PROTOSSAIRARMORLEVEL2                                    = 1566,
    RESEARCH_PROTOSSAIRARMORLEVEL3                                    = 1567,
    RESEARCH_PROTOSSAIRWEAPONS                                        = 3693,
    RESEARCH_PROTOSSAIRWEAPONSLEVEL1                                  = 1562,
    RESEARCH_PROTOSSAIRWEAPONSLEVEL2                                  = 1563,
    RESEARCH_PROTOSSAIRWEAPONSLEVEL3                                  = 1564,
    RESEARCH_PROTOSSGROUNDARMOR                                       = 3694,
    RESEARCH_PROTOSSGROUNDARMORLEVEL1                                 = 1065,
    RESEARCH_PROTOSSGROUNDARMORLEVEL2                                 = 1066,
    RESEARCH_PROTOSSGROUNDARMORLEVEL3                                 = 1067,
    RESEARCH_PROTOSSGROUNDWEAPONS                                     = 3695,
    RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1                               = 1062,
    RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2                               = 1063,
    RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3                               = 1064,
    RESEARCH_PROTOSSSHIELDS                                           = 3696,
    RESEARCH_PROTOSSSHIELDSLEVEL1                                     = 1068,
    RESEARCH_PROTOSSSHIELDSLEVEL2                                     = 1069,
    RESEARCH_PROTOSSSHIELDSLEVEL3                                     = 1070,
    RESEARCH_PSIONICAMPLIFIERS                                        = 1597,
    RESEARCH_PSIONICSURGE                                             = 1595,
    RESEARCH_PSISTORM                                                 = 1126,
    RESEARCH_RAPIDDEPLOYMENT                                          = 802,
    RESEARCH_RAPIDREIGNITIONSYSTEM                                    = 1534,
    RESEARCH_RAVENCORVIDREACTOR                                       = 793,
    RESEARCH_RAVENINTERFERENCEMATRIX                                  = 807,
    RESEARCH_RAVENRECALIBRATEDEXPLOSIVES                              = 803,
    RESEARCH_REAPERSPEED                                              = 683,
    RESEARCH_ROACHSUPPLY                                              = 218,
    RESEARCH_SEEKERMISSILE                                            = 796,
    RESEARCH_SHADOWSTRIKE                                             = 2720,
    RESEARCH_SMARTSERVOS                                              = 766,
    RESEARCH_STIMPACK                                                 = 730,
    RESEARCH_TEMPESTRANGEUPGRADE                                      = 47,
    RESEARCH_TEMPESTRESEARCHGROUNDATTACKUPGRADE                       = 49,
    RESEARCH_TERRANINFANTRYARMOR                                      = 3697,
    RESEARCH_TERRANINFANTRYARMORLEVEL1                                = 656,
    RESEARCH_TERRANINFANTRYARMORLEVEL2                                = 657,
    RESEARCH_TERRANINFANTRYARMORLEVEL3                                = 658,
    RESEARCH_TERRANINFANTRYWEAPONS                                    = 3698,
    RESEARCH_TERRANINFANTRYWEAPONSLEVEL1                              = 652,
    RESEARCH_TERRANINFANTRYWEAPONSLEVEL2                              = 653,
    RESEARCH_TERRANINFANTRYWEAPONSLEVEL3                              = 654,
    RESEARCH_TERRANSHIPPLATINGLEVEL1                                  = 858,
    RESEARCH_TERRANSHIPPLATINGLEVEL2                                  = 859,
    RESEARCH_TERRANSHIPPLATINGLEVEL3                                  = 860,
    RESEARCH_TERRANSHIPWEAPONS                                        = 3699,
    RESEARCH_TERRANSHIPWEAPONSLEVEL1                                  = 861,
    RESEARCH_TERRANSHIPWEAPONSLEVEL2                                  = 862,
    RESEARCH_TERRANSHIPWEAPONSLEVEL3                                  = 863,
    RESEARCH_TERRANSTRUCTUREARMORUPGRADE                              = 651,
    RESEARCH_TERRANVEHICLEANDSHIPPLATING                              = 3700,
    RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1                        = 864,
    RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2                        = 865,
    RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3                        = 866,
    RESEARCH_TERRANVEHICLEPLATINGLEVEL1                               = 852,
    RESEARCH_TERRANVEHICLEPLATINGLEVEL2                               = 853,
    RESEARCH_TERRANVEHICLEPLATINGLEVEL3                               = 854,
    RESEARCH_TERRANVEHICLEWEAPONS                                     = 3701,
    RESEARCH_TERRANVEHICLEWEAPONSLEVEL1                               = 855,
    RESEARCH_TERRANVEHICLEWEAPONSLEVEL2                               = 856,
    RESEARCH_TERRANVEHICLEWEAPONSLEVEL3                               = 857,
    RESEARCH_TRANSFORMATIONSERVOS                                     = 763,
    RESEARCH_TUNNELINGCLAWS                                           = 217,
    RESEARCH_VOIDRAYSPEEDUPGRADE                                      = 48,
    RESEARCH_WARPGATE                                                 = 1568,
    RESEARCH_ZERGFLYERARMOR                                           = 3702,
    RESEARCH_ZERGFLYERARMORLEVEL1                                     = 1315,
    RESEARCH_ZERGFLYERARMORLEVEL2                                     = 1316,
    RESEARCH_ZERGFLYERARMORLEVEL3                                     = 1317,
    RESEARCH_ZERGFLYERATTACK                                          = 3703,
    RESEARCH_ZERGFLYERATTACKLEVEL1                                    = 1312,
    RESEARCH_ZERGFLYERATTACKLEVEL2                                    = 1313,
    RESEARCH_ZERGFLYERATTACKLEVEL3                                    = 1314,
    RESEARCH_ZERGGROUNDARMOR                                          = 3704,
    RESEARCH_ZERGGROUNDARMORLEVEL1                                    = 1189,
    RESEARCH_ZERGGROUNDARMORLEVEL2                                    = 1190,
    RESEARCH_ZERGGROUNDARMORLEVEL3                                    = 1191,
    RESEARCH_ZERGLINGADRENALGLANDS                                    = 1252,
    RESEARCH_ZERGLINGMETABOLICBOOST                                   = 1253,
    RESEARCH_ZERGMELEEWEAPONS                                         = 3705,
    RESEARCH_ZERGMELEEWEAPONSLEVEL1                                   = 1186,
    RESEARCH_ZERGMELEEWEAPONSLEVEL2                                   = 1187,
    RESEARCH_ZERGMELEEWEAPONSLEVEL3                                   = 1188,
    RESEARCH_ZERGMISSILEWEAPONS                                       = 3706,
    RESEARCH_ZERGMISSILEWEAPONSLEVEL1                                 = 1192,
    RESEARCH_ZERGMISSILEWEAPONSLEVEL2                                 = 1193,
    RESEARCH_ZERGMISSILEWEAPONSLEVEL3                                 = 1194,
    RESTORESHIELDS                                                    = 1980,
    ROGUEGHOSTCLOAK_CLOAKOFF                                          = 3195,
    ROGUEGHOSTCLOAK_CLOAKONSPECTRE                                    = 3194,
    SALVAGEBANELINGREFUND_SALVAGE                                     = 1901,
    SALVAGEBANELING_SALVAGE                                           = 1903,
    SALVAGEBUNKERREFUND_SALVAGE                                       = 1624,
    SALVAGEBUNKER_SALVAGE                                             = 1626,
    SALVAGEDRONEREFUND_SALVAGE                                        = 1885,
    SALVAGEDRONE_SALVAGE                                              = 1887,
    SALVAGEHYDRALISKREFUND_SALVAGE                                    = 1905,
    SALVAGEHYDRALISK_SALVAGE                                          = 1907,
    SALVAGEINFESTORREFUND_SALVAGE                                     = 1909,
    SALVAGEINFESTOR_SALVAGE                                           = 1911,
    SALVAGEQUEENREFUND_SALVAGE                                        = 1893,
    SALVAGEQUEEN_SALVAGE                                              = 1895,
    SALVAGEROACHREFUND_SALVAGE                                        = 1897,
    SALVAGEROACH_SALVAGE                                              = 1899,
    SALVAGESWARMHOSTREFUND_SALVAGE                                    = 1913,
    SALVAGESWARMHOST_SALVAGE                                          = 1915,
    SALVAGEULTRALISKREFUND_SALVAGE                                    = 1917,
    SALVAGEULTRALISK_SALVAGE                                          = 1919,
    SALVAGEZERGLINGREFUND_SALVAGE                                     = 1889,
    SALVAGEZERGLING_SALVAGE                                           = 1891,
    SAPSTRUCTURE                                                      = 245,
    SCRYER                                                            = 1982,
    SECURITYGATEDIAGONALBLURLOWERED_GATEOPEN                          = 3593,
    SECURITYGATEDIAGONALBLUR_GATECLOSE                                = 3605,
    SECURITYGATEDIAGONALULBRLOWERED_GATEOPEN                          = 3595,
    SECURITYGATEDIAGONALULBR_GATECLOSE                                = 3607,
    SECURITYGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN                  = 3597,
    SECURITYGATESTRAIGHTHORIZONTALBF_GATECLOSE                        = 3609,
    SECURITYGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN                    = 3599,
    SECURITYGATESTRAIGHTHORIZONTAL_GATECLOSE                          = 3611,
    SECURITYGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN                    = 3601,
    SECURITYGATESTRAIGHTVERTICALLF_GATECLOSE                          = 3613,
    SECURITYGATESTRAIGHTVERTICALLOWERED_GATEOPEN                      = 3603,
    SECURITYGATESTRAIGHTVERTICAL_GATECLOSE                            = 3615,
    SELENDISHANGAR_INTERCEPTOR                                        = 2967,
    SELFREPAIR                                                        = 2538,
    SELFREPAIR_CANCEL                                                 = 2539,
    SENTRYGUNBURROW_BURROWTURRET                                      = 2999,
    SENTRYGUNUNBURROW_UNBURROWTURRET                                  = 3001,
    SHAKURASLIGHTBRIDGENE10OUT_BRIDGEEXTEND                           = 2449,
    SHAKURASLIGHTBRIDGENE10_BRIDGERETRACT                             = 2451,
    SHAKURASLIGHTBRIDGENE12OUT_BRIDGEEXTEND                           = 2453,
    SHAKURASLIGHTBRIDGENE12_BRIDGERETRACT                             = 2455,
    SHAKURASLIGHTBRIDGENE8OUT_BRIDGEEXTEND                            = 2445,
    SHAKURASLIGHTBRIDGENE8_BRIDGERETRACT                              = 2447,
    SHAKURASLIGHTBRIDGENW10OUT_BRIDGEEXTEND                           = 2461,
    SHAKURASLIGHTBRIDGENW10_BRIDGERETRACT                             = 2463,
    SHAKURASLIGHTBRIDGENW12OUT_BRIDGEEXTEND                           = 2465,
    SHAKURASLIGHTBRIDGENW12_BRIDGERETRACT                             = 2467,
    SHAKURASLIGHTBRIDGENW8OUT_BRIDGEEXTEND                            = 2457,
    SHAKURASLIGHTBRIDGENW8_BRIDGERETRACT                              = 2459,
    SHIELDBATTERYRECHARGEEX5_SHIELDBATTERYRECHARGE                    = 4111,
    SHIELDBATTERYRECHARGEEX5_STOP                                     = 4112,
    SINGLERECALL                                                      = 1976,
    SIPHON                                                            = 177,
    SIPHON_CANCEL                                                     = 178,
    SLAYNELEMENTALGRAB                                                = 2598,
    SMART                                                             = 1,
    SNIPE                                                             = 384,
    SNIPEDOT                                                          = 1988,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT10OUT_BRIDGEEXTEND      = 2254,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT10_BRIDGERETRACT        = 2256,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT_BRIDGEEXTEND       = 2246,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8_BRIDGERETRACT         = 2248,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT10OUT_BRIDGEEXTEND      = 2258,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT10_BRIDGERETRACT        = 2260,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT_BRIDGEEXTEND       = 2250,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8_BRIDGERETRACT         = 2252,
    SOULCHANNEL_CANCEL                                                = 2994,
    SPAWNINFESTEDTERRAN_LOCUSTMP                                      = 2018,
    SPECOPSDROPSHIPTRANSPORT_MEDIVACLOAD                              = 2947,
    SPECOPSDROPSHIPTRANSPORT_MEDIVACUNLOADALL                         = 2949,
    SPECTREHOLDFIRE                                                   = 3621,
    SPECTRENUKESILOARMMAGAZINE_SPECTRENUKEARM                         = 3327,
    SPECTRENUKE_CANCEL                                                = 3325,
    SPECTRENUKE_SPECTRENUKECALLDOWN                                   = 3324,
    SPECTRESHIELD                                                     = 1926,
    SPECTREWEAPONSFREE_WEAPONSFREE                                    = 3623,
    SPINECRAWLERUPROOT_CANCEL                                         = 1726,
    SPORECRAWLERUPROOT_CANCEL                                         = 1728,
    SS_BATTLECRUISERHUNTERSEEKERATTACK_SS_SHOOTING                    = 2793,
    SS_BATTLECRUISERMISSILEATTACK_SS_SHOOTING                         = 2789,
    SS_CARRIERBOSSATTACKLAUNCH_SS_SHOOTING                            = 2775,
    SS_CARRIERBOSSATTACKTARGET_SS_SHOOTING                            = 2779,
    SS_CARRIERSPAWNINTERCEPTOR                                        = 2777,
    SS_CORRUPTORATTACK_SS_SHOOTING                                    = 2823,
    SS_FIGHTERBOMB                                                    = 2781,
    SS_FIGHTERSHOOTING_SS_SHOOTING                                    = 3310,
    SS_INTERCEPTORATTACK_SS_SHOOTING                                  = 2821,
    SS_LEVIATHANSPAWNBOMBS                                            = 2791,
    SS_LEVIATHANTENTACLEATTACKL1                                      = 2829,
    SS_LEVIATHANTENTACLEATTACKL1NODELAY                               = 2797,
    SS_LEVIATHANTENTACLEATTACKL2                                      = 2825,
    SS_LEVIATHANTENTACLEATTACKL2NODELAY                               = 2799,
    SS_LEVIATHANTENTACLEATTACKR1                                      = 2827,
    SS_LEVIATHANTENTACLEATTACKR1NODELAY                               = 2801,
    SS_LEVIATHANTENTACLEATTACKR2                                      = 2831,
    SS_LEVIATHANTENTACLEATTACKR2NODELAY                               = 2803,
    SS_PHOENIXSHOOTING_SS_SHOOTING                                    = 2785,
    SS_SCIENCEVESSELATTACK_SS_SHOOTING                                = 2833,
    SS_SCIENCEVESSELTELEPORT_ZERATULBLINK                             = 2805,
    SS_SCOUTATTACK_SS_SHOOTING                                        = 2819,
    SS_SWARMGUARDIANATTACK_SS_SHOOTING                                = 2813,
    SS_TERRATRONBEAMATTACK                                            = 2807,
    SS_TERRATRONSAWATTACK                                             = 2809,
    SS_WRAITHATTACK_SS_SHOOTING                                       = 2811,
    STARPORTREACTORMORPH_REACTOR                                      = 1680,
    STARPORTTECHLABMORPH_TECHLABSTARPORT                              = 1672,
    STARPORTTECHREACTORMORPH_TECHLABSTARPORT                          = 3308,
    STARTCOLONISTVEHICLE                                              = 2905,
    STOP                                                              = 3665,
    STOPPROTOSSBUILDING_CHEER                                         = 2059,
    STOPPROTOSSBUILDING_DANCE                                         = 2060,
    STOPPROTOSSBUILDING_HOLDFIRE                                      = 2058,
    STOP_BATTLECRUISER                                                = 3783,
    STOP_BUILDING                                                     = 2057,
    STOP_CHEER                                                        = 6,
    STOP_DANCE                                                        = 7,
    STOP_HOLDFIRESPECIAL                                              = 5,
    STOP_REDIRECT                                                     = 1691,
    STOP_STOP                                                         = 4,
    SUMMONMERCENARIESPH_HIREKELMORIANMINERSPH                         = 3045,
    SUMMONMERCENARIES_HIREDEVILDOGS                                   = 3016,
    SUMMONMERCENARIES_HIREDUKESREVENGE                                = 3022,
    SUMMONMERCENARIES_HIREDUSKWING                                    = 3021,
    SUMMONMERCENARIES_HIREHAMMERSECURITIES                            = 3018,
    SUMMONMERCENARIES_HIREHELSANGELS                                  = 3020,
    SUMMONMERCENARIES_HIREKELMORIANMINERS                             = 3015,
    SUMMONMERCENARIES_HIRESIEGEBREAKERS                               = 3019,
    SUMMONMERCENARIES_HIRESPARTANCOMPANY                              = 3017,
    SWARMHOSTSPAWNLOCUSTS_LOCUSTMP                                    = 1990,
    TALDARIMVORTEX_VORTEX                                             = 3236,
    TAUNT                                                             = 2,
    TAURENOUTHOUSELIFTOFF_TAURENOUTHOUSEFLY                           = 2927,
    TAURENOUTHOUSETRANSPORT_LOADTAURENOUTHOUSE                        = 2929,
    TAURENOUTHOUSETRANSPORT_UNLOADTAURENOUTHOUSE                      = 2930,
    TAURENSTIMPACK_STIM                                               = 3423,
    TEMPLEDOORDOWN                                                    = 3366,
    TEMPLEDOORDOWNURDL                                                = 3370,
    TEMPLEDOORUP                                                      = 3368,
    TEMPLEDOORUPURDL                                                  = 3372,
    TEMPORALRIFT                                                      = 259,
    TERRANBUILDDROP_CANCEL                                            = 3116,
    TERRANBUILDDROP_SUPPLYDEPOTDROP                                   = 3086,
    TESTHERODEBUGMISSILEABILITY                                       = 3655,
    TESTHERODEBUGTRACKINGABILITY                                      = 3657,
    TESTHERODEBUGTRACKINGABILITY_CANCEL                               = 3658,
    TESTHEROGRAB_GRABZERGLING                                         = 3651,
    TESTHEROTHROW_THROWZERGLING                                       = 3653,
    TESTINTERACT_DESIGNATE                                            = 3514,
    TESTLEARN                                                         = 3547,
    TESTREVIVE_SCV                                                    = 3454,
    TESTZERG_CANCEL                                                   = 2080,
    THEMOROSDEVICE                                                    = 3077,
    THORAPMODE_CANCEL                                                 = 2363,
    THORREBORN_CANCEL                                                 = 3323,
    THORREBORN_THOR                                                   = 3322,
    THORWRECKAGE_THOR                                                 = 3318,
    TIMESTOP                                                          = 2562,
    TIMESTOP_CANCEL                                                   = 2563,
    TORNADOMISSILE                                                    = 2101,
    TOSSGRENADE                                                       = 3079,
    TRAINWARP_ADEPT                                                   = 1419,
    TRAINWARP_DARKTEMPLAR                                             = 1417,
    TRAINWARP_HIGHTEMPLAR                                             = 1416,
    TRAINWARP_SENTRY                                                  = 1418,
    TRAINWARP_STALKER                                                 = 1414,
    TRAINWARP_ZEALOT                                                  = 1413,
    TRAIN_ADEPT                                                       = 922,
    TRAIN_ARCHON                                                      = 3209,
    TRAIN_BANSHEE                                                     = 621,
    TRAIN_BATTLECRUISER                                               = 623,
    TRAIN_CARRIER                                                     = 948,
    TRAIN_COLOSSUS                                                    = 978,
    TRAIN_CORRUPTOR                                                   = 1353,
    TRAIN_CYCLONE                                                     = 597,
    TRAIN_DARKTEMPLAR                                                 = 920,
    TRAIN_DISRUPTOR                                                   = 994,
    TRAIN_DRONE                                                       = 1342,
    TRAIN_GHOST                                                       = 562,
    TRAIN_HELLBAT                                                     = 596,
    TRAIN_HELLION                                                     = 595,
    TRAIN_HIGHTEMPLAR                                                 = 919,
    TRAIN_HYDRALISK                                                   = 1345,
    TRAIN_IMMORTAL                                                    = 979,
    TRAIN_INFESTEDABOMINATION                                         = 3246,
    TRAIN_INFESTEDCIVILIAN                                            = 3244,
    TRAIN_INFESTEDTERRANCAMPAIGN                                      = 3245,
    TRAIN_INFESTOR                                                    = 1352,
    TRAIN_LIBERATOR                                                   = 626,
    TRAIN_MARAUDER                                                    = 563,
    TRAIN_MARINE                                                      = 560,
    TRAIN_MEDIVAC                                                     = 620,
    TRAIN_MOTHERSHIP                                                  = 110,
    TRAIN_MOTHERSHIPCORE                                              = 1853,
    TRAIN_MUTALISK                                                    = 1346,
    TRAIN_OBSERVER                                                    = 977,
    TRAIN_ORACLE                                                      = 954,
    TRAIN_OVERLORD                                                    = 1344,
    TRAIN_PHOENIX                                                     = 946,
    TRAIN_PROBE                                                       = 1006,
    TRAIN_QUEEN                                                       = 1632,
    TRAIN_RAVEN                                                       = 622,
    TRAIN_REAPER                                                      = 561,
    TRAIN_ROACH                                                       = 1351,
    TRAIN_SCV                                                         = 524,
    TRAIN_SENTRY                                                      = 921,
    TRAIN_SIEGETANK                                                   = 591,
    TRAIN_STALKER                                                     = 917,
    TRAIN_SWARMHOST                                                   = 1356,
    TRAIN_TEMPEST                                                     = 955,
    TRAIN_THOR                                                        = 594,
    TRAIN_ULTRALISK                                                   = 1348,
    TRAIN_VIKINGFIGHTER                                               = 624,
    TRAIN_VIPER                                                       = 1354,
    TRAIN_VOIDRAY                                                     = 950,
    TRAIN_WARPINMOHANDAR                                              = 3212,
    TRAIN_WARPINSCOUT                                                 = 3214,
    TRAIN_WARPINSELENDIS                                              = 3213,
    TRAIN_WARPINURUN                                                  = 3211,
    TRAIN_WARPINZERATUL                                               = 3210,
    TRAIN_WARPPRISM                                                   = 976,
    TRAIN_WIDOWMINE                                                   = 614,
    TRAIN_ZEALOT                                                      = 916,
    TRAIN_ZERGLING                                                    = 1343,
    TRANSPORTMODE_CANCEL                                              = 1531,
    TRANSPORTTRUCKTRANSPORT_TRANSPORTTRUCKLOAD                        = 3173,
    TRANSPORTTRUCKTRANSPORT_TRANSPORTTRUCKUNLOADALL                   = 3174,
    TYCHUS03OMEGASTORM_OMEGASTORM                                     = 2934,
    ULTRALISKWEAPONCOOLDOWN                                           = 2158,
    ULTRASONICPULSE                                                   = 2882,
    UNLOADALL                                                         = 3664,
    UNLOADALLAT                                                       = 3669,
    UNLOADALLAT_MEDIVAC                                               = 396,
    UNLOADALLAT_OVERLORD                                              = 1408,
    UNLOADALLAT_WARPPRISM                                             = 913,
    UNLOADALL_BUNKER                                                  = 408,
    UNLOADALL_COMMANDCENTER                                           = 413,
    UNLOADALL_NYDASNETWORK                                            = 1438,
    UNLOADALL_NYDUSWORM                                               = 2371,
    UNLOADALL_WARPPRISM                                               = 912,
    UNLOADUNIT                                                        = 3670,
    UNLOADUNIT_BUNKER                                                 = 410,
    UNLOADUNIT_COMMANDCENTER                                          = 415,
    UNLOADUNIT_MEDIVAC                                                = 397,
    UNLOADUNIT_NYDASNETWORK                                           = 1440,
    UNLOADUNIT_OVERLORD                                               = 1409,
    UNLOADUNIT_WARPPRISM                                              = 914,
    VAL03QUEENOFBLADESBURROW_BURROWDOWN                               = 3178,
    VAL03QUEENOFBLADESDEEPTUNNEL_DEEPTUNNEL                           = 3180,
    VAL03QUEENOFBLADESUNBURROW_BURROWUP                               = 3182,
    VOIDMPIMMORTALREVIVEDEATH_IMMORTAL                                = 2471,
    VOIDMPIMMORTALREVIVEREBUILD_IMMORTAL                              = 2469,
    VOIDSEEKERPHASEMINEBLAST_PHASEMINEBLAST                           = 3171,
    VOIDSEEKERTRANSPORT_MEDIVACLOAD                                   = 3081,
    VOIDSEEKERTRANSPORT_MEDIVACUNLOADALL                              = 3083,
    VOIDSIPHON                                                        = 2156,
    VOIDSWARMHOSTSPAWNLOCUST                                          = 2381,
    VOODOOSHIELD                                                      = 2878,
    VORTEX                                                            = 1630,
    VORTEXPURIFIER_VORTEX                                             = 3234,
    VULTUREQUEUE3_CANCEL                                              = 3198,
    VULTUREQUEUE3_CANCELSLOT                                          = 3199,
    VULTURESPIDERMINES_SPIDERMINE                                     = 3196,
    WARPABLE_CANCEL                                                   = 1412,
    WIDOWMINEBURROW_CANCEL                                            = 2096,
    WORMHOLETRANSIT                                                   = 293,
    WRAITHCLOAK_CLOAKOFF                                              = 3301,
    WRECKINGCREWASSAULTMODE_ASSAULTMODE                               = 3380,
    WRECKINGCREWFIGHTERMODE_FIGHTERMODE                               = 3382,
    XELNAGAHEALINGSHRINE                                              = 1928,
    XELNAGA_CAVERNS_DOOREOPENED_XELNAGA_CAVERNS_DOORDEFAULTCLOSE      = 2166,
    XELNAGA_CAVERNS_DOORE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE            = 2164,
    XELNAGA_CAVERNS_DOORNEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN      = 2172,
    XELNAGA_CAVERNS_DOORNE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE           = 2170,
    XELNAGA_CAVERNS_DOORNOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN       = 2174,
    XELNAGA_CAVERNS_DOORNWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN      = 2178,
    XELNAGA_CAVERNS_DOORNW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE           = 2176,
    XELNAGA_CAVERNS_DOORN_XELNAGA_CAVERNS_DOORDEFAULTCLOSE            = 2168,
    XELNAGA_CAVERNS_DOORSEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN      = 2184,
    XELNAGA_CAVERNS_DOORSE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE           = 2182,
    XELNAGA_CAVERNS_DOORSOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN       = 2186,
    XELNAGA_CAVERNS_DOORSWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN      = 2190,
    XELNAGA_CAVERNS_DOORSW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE           = 2188,
    XELNAGA_CAVERNS_DOORS_XELNAGA_CAVERNS_DOORDEFAULTCLOSE            = 2180,
    XELNAGA_CAVERNS_DOORWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN       = 2194,
    XELNAGA_CAVERNS_DOORW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE            = 2192,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT_BRIDGEEXTEND                = 2228,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH10_BRIDGERETRACT                  = 2230,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT_BRIDGEEXTEND                = 2236,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH12_BRIDGERETRACT                  = 2238,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT_BRIDGEEXTEND                 = 2220,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH8_BRIDGERETRACT                   = 2222,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT_BRIDGEEXTEND               = 2204,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE10_BRIDGERETRACT                 = 2206,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT_BRIDGEEXTEND               = 2212,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE12_BRIDGERETRACT                 = 2214,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT_BRIDGEEXTEND                = 2196,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE8_BRIDGERETRACT                  = 2198,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT_BRIDGEEXTEND               = 2208,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW10_BRIDGERETRACT                 = 2210,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT_BRIDGEEXTEND               = 2216,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW12_BRIDGERETRACT                 = 2218,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT_BRIDGEEXTEND                = 2200,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW8_BRIDGERETRACT                  = 2202,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT_BRIDGEEXTEND                = 2232,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV10_BRIDGERETRACT                  = 2234,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT_BRIDGEEXTEND                = 2240,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV12_BRIDGERETRACT                  = 2242,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT_BRIDGEEXTEND                 = 2224,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV8_BRIDGERETRACT                   = 2226,
    ZERATULBLINK                                                      = 3192,
    ZERATULSTUN                                                       = 3298,
    _250MMSTRIKECANNONS                                               = 257,
    _250MMSTRIKECANNONS_CANCEL                                        = 258,
    _330MMBARRAGECANNONS                                              = 3320,
    _330MMBARRAGECANNONS_CANCEL                                       = 3321,
};

using AbilityID = SC2Type<ABILITY_ID>;

//! Converts a ABILITY_ID into a string of the same name.
const char* AbilityTypeToName ( const AbilityID id ) {
    switch ( static_cast<ABILITY_ID> ( id ) ) {
        case ABILITY_ID::ADVANCEDCONSTRUCTION_CANCEL :
            return "ADVANCEDCONSTRUCTION_CANCEL";
        case ABILITY_ID::AGGRESSIVEMUTATION : return "AGGRESSIVEMUTATION";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNE10OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGEABANDONEDNE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNE10_BRIDGERETRACT :
            return "AIURLIGHTBRIDGEABANDONEDNE10_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNE12OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGEABANDONEDNE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNE12_BRIDGERETRACT :
            return "AIURLIGHTBRIDGEABANDONEDNE12_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNE8OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGEABANDONEDNE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNE8_BRIDGERETRACT :
            return "AIURLIGHTBRIDGEABANDONEDNE8_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNW10OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGEABANDONEDNW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNW10_BRIDGERETRACT :
            return "AIURLIGHTBRIDGEABANDONEDNW10_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNW12OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGEABANDONEDNW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNW12_BRIDGERETRACT :
            return "AIURLIGHTBRIDGEABANDONEDNW12_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNW8OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGEABANDONEDNW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGEABANDONEDNW8_BRIDGERETRACT :
            return "AIURLIGHTBRIDGEABANDONEDNW8_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGENE10OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGENE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGENE10_BRIDGERETRACT :
            return "AIURLIGHTBRIDGENE10_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGENE12OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGENE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGENE12_BRIDGERETRACT :
            return "AIURLIGHTBRIDGENE12_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGENE8OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGENE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGENE8_BRIDGERETRACT :
            return "AIURLIGHTBRIDGENE8_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGENW10OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGENW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGENW10_BRIDGERETRACT :
            return "AIURLIGHTBRIDGENW10_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGENW12OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGENW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGENW12_BRIDGERETRACT :
            return "AIURLIGHTBRIDGENW12_BRIDGERETRACT";
        case ABILITY_ID::AIURLIGHTBRIDGENW8OUT_BRIDGEEXTEND :
            return "AIURLIGHTBRIDGENW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURLIGHTBRIDGENW8_BRIDGERETRACT :
            return "AIURLIGHTBRIDGENW8_BRIDGERETRACT";
        case ABILITY_ID::AIURTEMPLEBRIDGENE10OUT_BRIDGEEXTEND :
            return "AIURTEMPLEBRIDGENE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURTEMPLEBRIDGENE10_BRIDGERETRACT :
            return "AIURTEMPLEBRIDGENE10_BRIDGERETRACT";
        case ABILITY_ID::AIURTEMPLEBRIDGENE12OUT_BRIDGEEXTEND :
            return "AIURTEMPLEBRIDGENE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURTEMPLEBRIDGENE12_BRIDGERETRACT :
            return "AIURTEMPLEBRIDGENE12_BRIDGERETRACT";
        case ABILITY_ID::AIURTEMPLEBRIDGENE8OUT_BRIDGEEXTEND :
            return "AIURTEMPLEBRIDGENE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURTEMPLEBRIDGENE8_BRIDGERETRACT :
            return "AIURTEMPLEBRIDGENE8_BRIDGERETRACT";
        case ABILITY_ID::AIURTEMPLEBRIDGENW10OUT_BRIDGEEXTEND :
            return "AIURTEMPLEBRIDGENW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURTEMPLEBRIDGENW10_BRIDGERETRACT :
            return "AIURTEMPLEBRIDGENW10_BRIDGERETRACT";
        case ABILITY_ID::AIURTEMPLEBRIDGENW12OUT_BRIDGEEXTEND :
            return "AIURTEMPLEBRIDGENW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURTEMPLEBRIDGENW12_BRIDGERETRACT :
            return "AIURTEMPLEBRIDGENW12_BRIDGERETRACT";
        case ABILITY_ID::AIURTEMPLEBRIDGENW8OUT_BRIDGEEXTEND :
            return "AIURTEMPLEBRIDGENW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::AIURTEMPLEBRIDGENW8_BRIDGERETRACT :
            return "AIURTEMPLEBRIDGENW8_BRIDGERETRACT";
        case ABILITY_ID::ARBITERMPRECALL      : return "ARBITERMPRECALL";
        case ABILITY_ID::ARBITERMPSTASISFIELD : return "ARBITERMPSTASISFIELD";
        case ABILITY_ID::ARCHIVESEAL          : return "ARCHIVESEAL";
        case ABILITY_ID::ARCHONWARP_ARCHONWARPTARGET :
            return "ARCHONWARP_ARCHONWARPTARGET";
        case ABILITY_ID::ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL1 :
            return "ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL1";
        case ABILITY_ID::ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL2 :
            return "ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL2";
        case ABILITY_ID::ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL3 :
            return "ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPPLATINGLEVEL3";
        case ABILITY_ID::ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL1 :
            return "ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL1";
        case ABILITY_ID::ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL2 :
            return "ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL2";
        case ABILITY_ID::ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL3 :
            return "ARMORYRESEARCHSWARM_TERRANVEHICLEANDSHIPWEAPONSLEVEL3";
        case ABILITY_ID::ARTANISVORTEX_VORTEX : return "ARTANISVORTEX_VORTEX";
        case ABILITY_ID::ARTANISWORMHOLETRANSIT_WORMHOLETRANSIT :
            return "ARTANISWORMHOLETRANSIT_WORMHOLETRANSIT";
        case ABILITY_ID::ATTACK        : return "ATTACK";
        case ABILITY_ID::ATTACK_ATTACK : return "ATTACK_ATTACK";
        case ABILITY_ID::ATTACK_ATTACKALLOWSINVULNERABLE :
            return "ATTACK_ATTACKALLOWSINVULNERABLE";
        case ABILITY_ID::ATTACK_ATTACKBARRAGE  : return "ATTACK_ATTACKBARRAGE";
        case ABILITY_ID::ATTACK_ATTACKBUILDING : return "ATTACK_ATTACKBUILDING";
        case ABILITY_ID::ATTACK_ATTACKTOWARDS  : return "ATTACK_ATTACKTOWARDS";
        case ABILITY_ID::ATTACK_ATTACKWARPPRISM :
            return "ATTACK_ATTACKWARPPRISM";
        case ABILITY_ID::ATTACK_BATTLECRUISER : return "ATTACK_BATTLECRUISER";
        case ABILITY_ID::ATTACK_REDIRECT      : return "ATTACK_REDIRECT";
        case ABILITY_ID::BARRACKSREACTORMORPH_REACTOR :
            return "BARRACKSREACTORMORPH_REACTOR";
        case ABILITY_ID::BARRACKSTECHLABMORPH_TECHLABBARRACKS :
            return "BARRACKSTECHLABMORPH_TECHLABBARRACKS";
        case ABILITY_ID::BARRACKSTECHREACTORMORPH_TECHLABBARRACKS :
            return "BARRACKSTECHREACTORMORPH_TECHLABBARRACKS";
        case ABILITY_ID::BATTERYOVERCHARGE : return "BATTERYOVERCHARGE";
        case ABILITY_ID::BATTLECRUISERATTACKEVALUATOR_MOTHERSHIPCOREATTACK :
            return "BATTLECRUISERATTACKEVALUATOR_MOTHERSHIPCOREATTACK";
        case ABILITY_ID::BATTLECRUISERMOVE_ACQUIREMOVE :
            return "BATTLECRUISERMOVE_ACQUIREMOVE";
        case ABILITY_ID::BATTLECRUISERMOVE_MOVE :
            return "BATTLECRUISERMOVE_MOVE";
        case ABILITY_ID::BATTLECRUISERMOVE_MOVEHOLDPOSITION :
            return "BATTLECRUISERMOVE_MOVEHOLDPOSITION";
        case ABILITY_ID::BATTLECRUISERMOVE_MOVEPATROL :
            return "BATTLECRUISERMOVE_MOVEPATROL";
        case ABILITY_ID::BATTLECRUISERMOVE_TURN :
            return "BATTLECRUISERMOVE_TURN";
        case ABILITY_ID::BATTLECRUISERSTOPEVALUATOR_STOP :
            return "BATTLECRUISERSTOPEVALUATOR_STOP";
        case ABILITY_ID::BATTLECRUISERSTOP_CHEER :
            return "BATTLECRUISERSTOP_CHEER";
        case ABILITY_ID::BATTLECRUISERSTOP_DANCE :
            return "BATTLECRUISERSTOP_DANCE";
        case ABILITY_ID::BATTLECRUISERSTOP_HOLDFIRE :
            return "BATTLECRUISERSTOP_HOLDFIRE";
        case ABILITY_ID::BEACON_BEACONMOVE : return "BEACON_BEACONMOVE";
        case ABILITY_ID::BEACON_CANCEL     : return "BEACON_CANCEL";
        case ABILITY_ID::BEHAVIOR_BUILDINGATTACKOFF :
            return "BEHAVIOR_BUILDINGATTACKOFF";
        case ABILITY_ID::BEHAVIOR_BUILDINGATTACKON :
            return "BEHAVIOR_BUILDINGATTACKON";
        case ABILITY_ID::BEHAVIOR_CLOAKOFF : return "BEHAVIOR_CLOAKOFF";
        case ABILITY_ID::BEHAVIOR_CLOAKOFF_BANSHEE :
            return "BEHAVIOR_CLOAKOFF_BANSHEE";
        case ABILITY_ID::BEHAVIOR_CLOAKOFF_GHOST :
            return "BEHAVIOR_CLOAKOFF_GHOST";
        case ABILITY_ID::BEHAVIOR_CLOAKON : return "BEHAVIOR_CLOAKON";
        case ABILITY_ID::BEHAVIOR_CLOAKON_BANSHEE :
            return "BEHAVIOR_CLOAKON_BANSHEE";
        case ABILITY_ID::BEHAVIOR_CLOAKON_GHOST :
            return "BEHAVIOR_CLOAKON_GHOST";
        case ABILITY_ID::BEHAVIOR_GENERATECREEPOFF :
            return "BEHAVIOR_GENERATECREEPOFF";
        case ABILITY_ID::BEHAVIOR_GENERATECREEPON :
            return "BEHAVIOR_GENERATECREEPON";
        case ABILITY_ID::BEHAVIOR_HOLDFIREOFF : return "BEHAVIOR_HOLDFIREOFF";
        case ABILITY_ID::BEHAVIOR_HOLDFIREOFF_GHOST :
            return "BEHAVIOR_HOLDFIREOFF_GHOST";
        case ABILITY_ID::BEHAVIOR_HOLDFIREOFF_LURKER :
            return "BEHAVIOR_HOLDFIREOFF_LURKER";
        case ABILITY_ID::BEHAVIOR_HOLDFIREON : return "BEHAVIOR_HOLDFIREON";
        case ABILITY_ID::BEHAVIOR_HOLDFIREON_GHOST :
            return "BEHAVIOR_HOLDFIREON_GHOST";
        case ABILITY_ID::BEHAVIOR_HOLDFIREON_LURKER :
            return "BEHAVIOR_HOLDFIREON_LURKER";
        case ABILITY_ID::BEHAVIOR_PULSARBEAMOFF :
            return "BEHAVIOR_PULSARBEAMOFF";
        case ABILITY_ID::BEHAVIOR_PULSARBEAMON : return "BEHAVIOR_PULSARBEAMON";
        case ABILITY_ID::BIODOMECOMMANDLAND_LAND :
            return "BIODOMECOMMANDLAND_LAND";
        case ABILITY_ID::BIODOMECOMMANDLIFTOFF_LIFT :
            return "BIODOMECOMMANDLIFTOFF_LIFT";
        case ABILITY_ID::BIODOMETRANSPORT_BIODOMELOAD :
            return "BIODOMETRANSPORT_BIODOMELOAD";
        case ABILITY_ID::BIODOMETRANSPORT_BIODOMEUNLOADALL :
            return "BIODOMETRANSPORT_BIODOMEUNLOADALL";
        case ABILITY_ID::BIOPLASMIDDISCHARGE : return "BIOPLASMIDDISCHARGE";
        case ABILITY_ID::BIOSTASIS           : return "BIOSTASIS";
        case ABILITY_ID::BONESHEAL           : return "BONESHEAL";
        case ABILITY_ID::BONESTOSSGRENADE_TOSSGRENADETYCHUS :
            return "BONESTOSSGRENADE_TOSSGRENADETYCHUS";
        case ABILITY_ID::BROODLORDQUEUE2_CANCEL :
            return "BROODLORDQUEUE2_CANCEL";
        case ABILITY_ID::BROODLORDQUEUE2_CANCELSLOT :
            return "BROODLORDQUEUE2_CANCELSLOT";
        case ABILITY_ID::BUILDINGSHIELD : return "BUILDINGSHIELD";
        case ABILITY_ID::BUILDINGSTASIS : return "BUILDINGSTASIS";
        case ABILITY_ID::BUILDINPROGRESSNONCANCELLABLE_CANCEL :
            return "BUILDINPROGRESSNONCANCELLABLE_CANCEL";
        case ABILITY_ID::BUILDINPROGRESSNYDUSCANAL_CANCEL :
            return "BUILDINPROGRESSNYDUSCANAL_CANCEL";
        case ABILITY_ID::BUILDNYDUSCANAL_CANCEL :
            return "BUILDNYDUSCANAL_CANCEL";
        case ABILITY_ID::BUILDNYDUSCANAL_SUMMONNYDUSCANALATTACKER :
            return "BUILDNYDUSCANAL_SUMMONNYDUSCANALATTACKER";
        case ABILITY_ID::BUILD_ARMORY        : return "BUILD_ARMORY";
        case ABILITY_ID::BUILD_ASSIMILATOR   : return "BUILD_ASSIMILATOR";
        case ABILITY_ID::BUILD_BANELINGNEST  : return "BUILD_BANELINGNEST";
        case ABILITY_ID::BUILD_BARRACKS      : return "BUILD_BARRACKS";
        case ABILITY_ID::BUILD_BUNKER        : return "BUILD_BUNKER";
        case ABILITY_ID::BUILD_CANCEL        : return "BUILD_CANCEL";
        case ABILITY_ID::BUILD_COMMANDCENTER : return "BUILD_COMMANDCENTER";
        case ABILITY_ID::BUILD_CREEPTUMOR    : return "BUILD_CREEPTUMOR";
        case ABILITY_ID::BUILD_CREEPTUMOR_QUEEN :
            return "BUILD_CREEPTUMOR_QUEEN";
        case ABILITY_ID::BUILD_CREEPTUMOR_TUMOR :
            return "BUILD_CREEPTUMOR_TUMOR";
        case ABILITY_ID::BUILD_CYBERNETICSCORE : return "BUILD_CYBERNETICSCORE";
        case ABILITY_ID::BUILD_DARKSHRINE      : return "BUILD_DARKSHRINE";
        case ABILITY_ID::BUILD_ENGINEERINGBAY  : return "BUILD_ENGINEERINGBAY";
        case ABILITY_ID::BUILD_EVOLUTIONCHAMBER :
            return "BUILD_EVOLUTIONCHAMBER";
        case ABILITY_ID::BUILD_EXTRACTOR      : return "BUILD_EXTRACTOR";
        case ABILITY_ID::BUILD_FACTORY        : return "BUILD_FACTORY";
        case ABILITY_ID::BUILD_FLEETBEACON    : return "BUILD_FLEETBEACON";
        case ABILITY_ID::BUILD_FORGE          : return "BUILD_FORGE";
        case ABILITY_ID::BUILD_FUSIONCORE     : return "BUILD_FUSIONCORE";
        case ABILITY_ID::BUILD_GATEWAY        : return "BUILD_GATEWAY";
        case ABILITY_ID::BUILD_GHOSTACADEMY   : return "BUILD_GHOSTACADEMY";
        case ABILITY_ID::BUILD_HATCHERY       : return "BUILD_HATCHERY";
        case ABILITY_ID::BUILD_HYDRALISKDEN   : return "BUILD_HYDRALISKDEN";
        case ABILITY_ID::BUILD_INFESTATIONPIT : return "BUILD_INFESTATIONPIT";
        case ABILITY_ID::BUILD_INTERCEPTORS   : return "BUILD_INTERCEPTORS";
        case ABILITY_ID::BUILD_LURKERDEN      : return "BUILD_LURKERDEN";
        case ABILITY_ID::BUILD_MISSILETURRET  : return "BUILD_MISSILETURRET";
        case ABILITY_ID::BUILD_NEXUS          : return "BUILD_NEXUS";
        case ABILITY_ID::BUILD_NUKE           : return "BUILD_NUKE";
        case ABILITY_ID::BUILD_NYDUSNETWORK   : return "BUILD_NYDUSNETWORK";
        case ABILITY_ID::BUILD_NYDUSWORM      : return "BUILD_NYDUSWORM";
        case ABILITY_ID::BUILD_PHOTONCANNON   : return "BUILD_PHOTONCANNON";
        case ABILITY_ID::BUILD_PYLON          : return "BUILD_PYLON";
        case ABILITY_ID::BUILD_REACTOR        : return "BUILD_REACTOR";
        case ABILITY_ID::BUILD_REACTOR_BARRACKS :
            return "BUILD_REACTOR_BARRACKS";
        case ABILITY_ID::BUILD_REACTOR_FACTORY : return "BUILD_REACTOR_FACTORY";
        case ABILITY_ID::BUILD_REACTOR_STARPORT :
            return "BUILD_REACTOR_STARPORT";
        case ABILITY_ID::BUILD_REFINERY    : return "BUILD_REFINERY";
        case ABILITY_ID::BUILD_ROACHWARREN : return "BUILD_ROACHWARREN";
        case ABILITY_ID::BUILD_ROBOTICSBAY : return "BUILD_ROBOTICSBAY";
        case ABILITY_ID::BUILD_ROBOTICSFACILITY :
            return "BUILD_ROBOTICSFACILITY";
        case ABILITY_ID::BUILD_SENSORTOWER   : return "BUILD_SENSORTOWER";
        case ABILITY_ID::BUILD_SHIELDBATTERY : return "BUILD_SHIELDBATTERY";
        case ABILITY_ID::BUILD_SPAWNINGPOOL  : return "BUILD_SPAWNINGPOOL";
        case ABILITY_ID::BUILD_SPINECRAWLER  : return "BUILD_SPINECRAWLER";
        case ABILITY_ID::BUILD_SPIRE         : return "BUILD_SPIRE";
        case ABILITY_ID::BUILD_SPORECRAWLER  : return "BUILD_SPORECRAWLER";
        case ABILITY_ID::BUILD_STARGATE      : return "BUILD_STARGATE";
        case ABILITY_ID::BUILD_STARPORT      : return "BUILD_STARPORT";
        case ABILITY_ID::BUILD_STASISTRAP    : return "BUILD_STASISTRAP";
        case ABILITY_ID::BUILD_SUPPLYDEPOT   : return "BUILD_SUPPLYDEPOT";
        case ABILITY_ID::BUILD_TECHLAB       : return "BUILD_TECHLAB";
        case ABILITY_ID::BUILD_TECHLAB_BARRACKS :
            return "BUILD_TECHLAB_BARRACKS";
        case ABILITY_ID::BUILD_TECHLAB_FACTORY : return "BUILD_TECHLAB_FACTORY";
        case ABILITY_ID::BUILD_TECHLAB_STARPORT :
            return "BUILD_TECHLAB_STARPORT";
        case ABILITY_ID::BUILD_TEMPLARARCHIVE  : return "BUILD_TEMPLARARCHIVE";
        case ABILITY_ID::BUILD_TWILIGHTCOUNCIL : return "BUILD_TWILIGHTCOUNCIL";
        case ABILITY_ID::BUILD_ULTRALISKCAVERN : return "BUILD_ULTRALISKCAVERN";
        case ABILITY_ID::BUNKERATTACK          : return "BUNKERATTACK";
        case ABILITY_ID::BUNKERSTOP_HOLDFIRESPECIAL :
            return "BUNKERSTOP_HOLDFIRESPECIAL";
        case ABILITY_ID::BUNKERSTOP_STOPBUNKER : return "BUNKERSTOP_STOPBUNKER";
        case ABILITY_ID::BURROWBANELINGDOWN_CANCEL :
            return "BURROWBANELINGDOWN_CANCEL";
        case ABILITY_ID::BURROWCREEPTUMORDOWN_BURROWDOWN :
            return "BURROWCREEPTUMORDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWDOWN           : return "BURROWDOWN";
        case ABILITY_ID::BURROWDOWN_BANELING  : return "BURROWDOWN_BANELING";
        case ABILITY_ID::BURROWDOWN_DRONE     : return "BURROWDOWN_DRONE";
        case ABILITY_ID::BURROWDOWN_HYDRALISK : return "BURROWDOWN_HYDRALISK";
        case ABILITY_ID::BURROWDOWN_INFESTOR  : return "BURROWDOWN_INFESTOR";
        case ABILITY_ID::BURROWDOWN_INFESTORTERRAN :
            return "BURROWDOWN_INFESTORTERRAN";
        case ABILITY_ID::BURROWDOWN_LURKER    : return "BURROWDOWN_LURKER";
        case ABILITY_ID::BURROWDOWN_QUEEN     : return "BURROWDOWN_QUEEN";
        case ABILITY_ID::BURROWDOWN_RAVAGER   : return "BURROWDOWN_RAVAGER";
        case ABILITY_ID::BURROWDOWN_ROACH     : return "BURROWDOWN_ROACH";
        case ABILITY_ID::BURROWDOWN_SWARMHOST : return "BURROWDOWN_SWARMHOST";
        case ABILITY_ID::BURROWDOWN_ULTRALISK : return "BURROWDOWN_ULTRALISK";
        case ABILITY_ID::BURROWDOWN_WIDOWMINE : return "BURROWDOWN_WIDOWMINE";
        case ABILITY_ID::BURROWDOWN_ZERGLING  : return "BURROWDOWN_ZERGLING";
        case ABILITY_ID::BURROWDRONEDOWN_CANCEL :
            return "BURROWDRONEDOWN_CANCEL";
        case ABILITY_ID::BURROWEDBANELINGSTOP_HOLDFIRESPECIAL :
            return "BURROWEDBANELINGSTOP_HOLDFIRESPECIAL";
        case ABILITY_ID::BURROWEDBANELINGSTOP_STOPROACHBURROWED :
            return "BURROWEDBANELINGSTOP_STOPROACHBURROWED";
        case ABILITY_ID::BURROWEDSTOP_HOLDFIRESPECIAL :
            return "BURROWEDSTOP_HOLDFIRESPECIAL";
        case ABILITY_ID::BURROWEDSTOP_STOPROACHBURROWED :
            return "BURROWEDSTOP_STOPROACHBURROWED";
        case ABILITY_ID::BURROWHUNTERKILLERDOWN_BURROWDOWN :
            return "BURROWHUNTERKILLERDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWHUNTERKILLERDOWN_CANCEL :
            return "BURROWHUNTERKILLERDOWN_CANCEL";
        case ABILITY_ID::BURROWHUNTERKILLERUP_BURROWUP :
            return "BURROWHUNTERKILLERUP_BURROWUP";
        case ABILITY_ID::BURROWHYDRALISKDOWN_CANCEL :
            return "BURROWHYDRALISKDOWN_CANCEL";
        case ABILITY_ID::BURROWINFESTEDABOMINATIONDOWN_BURROWDOWN :
            return "BURROWINFESTEDABOMINATIONDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWINFESTEDABOMINATIONUP_BURROWUP :
            return "BURROWINFESTEDABOMINATIONUP_BURROWUP";
        case ABILITY_ID::BURROWINFESTEDCIVILIANDOWN_BURROWDOWN :
            return "BURROWINFESTEDCIVILIANDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWINFESTEDCIVILIANUP_BURROWUP :
            return "BURROWINFESTEDCIVILIANUP_BURROWUP";
        case ABILITY_ID::BURROWINFESTEDTERRANCAMPAIGNDOWN_BURROWDOWN :
            return "BURROWINFESTEDTERRANCAMPAIGNDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWINFESTEDTERRANCAMPAIGNUP_BURROWUP :
            return "BURROWINFESTEDTERRANCAMPAIGNUP_BURROWUP";
        case ABILITY_ID::BURROWINFESTORDOWN_CANCEL :
            return "BURROWINFESTORDOWN_CANCEL";
        case ABILITY_ID::BURROWLURKERDOWN_BURROWDOWN :
            return "BURROWLURKERDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWLURKERDOWN_CANCEL :
            return "BURROWLURKERDOWN_CANCEL";
        case ABILITY_ID::BURROWLURKERMPDOWN_CANCEL :
            return "BURROWLURKERMPDOWN_CANCEL";
        case ABILITY_ID::BURROWLURKERUP_BURROWUP :
            return "BURROWLURKERUP_BURROWUP";
        case ABILITY_ID::BURROWOMEGALISKDOWN_BURROWDOWN :
            return "BURROWOMEGALISKDOWN_BURROWDOWN";
        case ABILITY_ID::BURROWOMEGALISKUP_BURROWUP :
            return "BURROWOMEGALISKUP_BURROWUP";
        case ABILITY_ID::BURROWQUEENDOWN_CANCEL :
            return "BURROWQUEENDOWN_CANCEL";
        case ABILITY_ID::BURROWRAVAGERDOWN_CANCEL :
            return "BURROWRAVAGERDOWN_CANCEL";
        case ABILITY_ID::BURROWROACHDOWN_CANCEL :
            return "BURROWROACHDOWN_CANCEL";
        case ABILITY_ID::BURROWUP           : return "BURROWUP";
        case ABILITY_ID::BURROWUP_BANELING  : return "BURROWUP_BANELING";
        case ABILITY_ID::BURROWUP_DRONE     : return "BURROWUP_DRONE";
        case ABILITY_ID::BURROWUP_HYDRALISK : return "BURROWUP_HYDRALISK";
        case ABILITY_ID::BURROWUP_INFESTOR  : return "BURROWUP_INFESTOR";
        case ABILITY_ID::BURROWUP_INFESTORTERRAN :
            return "BURROWUP_INFESTORTERRAN";
        case ABILITY_ID::BURROWUP_LURKER    : return "BURROWUP_LURKER";
        case ABILITY_ID::BURROWUP_QUEEN     : return "BURROWUP_QUEEN";
        case ABILITY_ID::BURROWUP_RAVAGER   : return "BURROWUP_RAVAGER";
        case ABILITY_ID::BURROWUP_ROACH     : return "BURROWUP_ROACH";
        case ABILITY_ID::BURROWUP_SWARMHOST : return "BURROWUP_SWARMHOST";
        case ABILITY_ID::BURROWUP_ULTRALISK : return "BURROWUP_ULTRALISK";
        case ABILITY_ID::BURROWUP_WIDOWMINE : return "BURROWUP_WIDOWMINE";
        case ABILITY_ID::BURROWUP_ZERGLING  : return "BURROWUP_ZERGLING";
        case ABILITY_ID::BURROWZERGLINGDOWN_CANCEL :
            return "BURROWZERGLINGDOWN_CANCEL";
        case ABILITY_ID::CANCEL           : return "CANCEL";
        case ABILITY_ID::CANCELSLOT_ADDON : return "CANCELSLOT_ADDON";
        case ABILITY_ID::CANCELSLOT_HANGARQUEUE5 :
            return "CANCELSLOT_HANGARQUEUE5";
        case ABILITY_ID::CANCELSLOT_QUEUE1 : return "CANCELSLOT_QUEUE1";
        case ABILITY_ID::CANCELSLOT_QUEUE5 : return "CANCELSLOT_QUEUE5";
        case ABILITY_ID::CANCELSLOT_QUEUECANCELTOSELECTION :
            return "CANCELSLOT_QUEUECANCELTOSELECTION";
        case ABILITY_ID::CANCELSLOT_QUEUEPASSIVE :
            return "CANCELSLOT_QUEUEPASSIVE";
        case ABILITY_ID::CANCELSLOT_QUEUEPASSIVECANCELTOSELECTION :
            return "CANCELSLOT_QUEUEPASSIVECANCELTOSELECTION";
        case ABILITY_ID::CANCELTERRAZINEHARVEST_CANCEL :
            return "CANCELTERRAZINEHARVEST_CANCEL";
        case ABILITY_ID::CANCEL_ADEPTPHASESHIFT :
            return "CANCEL_ADEPTPHASESHIFT";
        case ABILITY_ID::CANCEL_ADEPTSHADEPHASESHIFT :
            return "CANCEL_ADEPTSHADEPHASESHIFT";
        case ABILITY_ID::CANCEL_BARRACKSADDON : return "CANCEL_BARRACKSADDON";
        case ABILITY_ID::CANCEL_BUILDINPROGRESS :
            return "CANCEL_BUILDINPROGRESS";
        case ABILITY_ID::CANCEL_CREEPTUMOR     : return "CANCEL_CREEPTUMOR";
        case ABILITY_ID::CANCEL_FACTORYADDON   : return "CANCEL_FACTORYADDON";
        case ABILITY_ID::CANCEL_GRAVITONBEAM   : return "CANCEL_GRAVITONBEAM";
        case ABILITY_ID::CANCEL_HANGARQUEUE5   : return "CANCEL_HANGARQUEUE5";
        case ABILITY_ID::CANCEL_LAST           : return "CANCEL_LAST";
        case ABILITY_ID::CANCEL_LOCKON         : return "CANCEL_LOCKON";
        case ABILITY_ID::CANCEL_MORPHBROODLORD : return "CANCEL_MORPHBROODLORD";
        case ABILITY_ID::CANCEL_MORPHGREATERSPIRE :
            return "CANCEL_MORPHGREATERSPIRE";
        case ABILITY_ID::CANCEL_MORPHHIVE      : return "CANCEL_MORPHHIVE";
        case ABILITY_ID::CANCEL_MORPHLAIR      : return "CANCEL_MORPHLAIR";
        case ABILITY_ID::CANCEL_MORPHLURKER    : return "CANCEL_MORPHLURKER";
        case ABILITY_ID::CANCEL_MORPHLURKERDEN : return "CANCEL_MORPHLURKERDEN";
        case ABILITY_ID::CANCEL_MORPHMOTHERSHIP :
            return "CANCEL_MORPHMOTHERSHIP";
        case ABILITY_ID::CANCEL_MORPHORBITAL : return "CANCEL_MORPHORBITAL";
        case ABILITY_ID::CANCEL_MORPHOVERLORDTRANSPORT :
            return "CANCEL_MORPHOVERLORDTRANSPORT";
        case ABILITY_ID::CANCEL_MORPHOVERSEER : return "CANCEL_MORPHOVERSEER";
        case ABILITY_ID::CANCEL_MORPHPLANETARYFORTRESS :
            return "CANCEL_MORPHPLANETARYFORTRESS";
        case ABILITY_ID::CANCEL_MORPHRAVAGER : return "CANCEL_MORPHRAVAGER";
        case ABILITY_ID::CANCEL_MORPHTHOREXPLOSIVEMODE :
            return "CANCEL_MORPHTHOREXPLOSIVEMODE";
        case ABILITY_ID::CANCEL_MOTHERSHIPSTASIS :
            return "CANCEL_MOTHERSHIPSTASIS";
        case ABILITY_ID::CANCEL_NEURALPARASITE : return "CANCEL_NEURALPARASITE";
        case ABILITY_ID::CANCEL_NUKE           : return "CANCEL_NUKE";
        case ABILITY_ID::CANCEL_PROTOSSBUILDINGQUEUE :
            return "CANCEL_PROTOSSBUILDINGQUEUE";
        case ABILITY_ID::CANCEL_QUEUE1     : return "CANCEL_QUEUE1";
        case ABILITY_ID::CANCEL_QUEUE5     : return "CANCEL_QUEUE5";
        case ABILITY_ID::CANCEL_QUEUEADDON : return "CANCEL_QUEUEADDON";
        case ABILITY_ID::CANCEL_QUEUECANCELTOSELECTION :
            return "CANCEL_QUEUECANCELTOSELECTION";
        case ABILITY_ID::CANCEL_QUEUEPASIVE : return "CANCEL_QUEUEPASIVE";
        case ABILITY_ID::CANCEL_QUEUEPASSIVECANCELTOSELECTION :
            return "CANCEL_QUEUEPASSIVECANCELTOSELECTION";
        case ABILITY_ID::CANCEL_SLOT : return "CANCEL_SLOT";
        case ABILITY_ID::CANCEL_SPINECRAWLERROOT :
            return "CANCEL_SPINECRAWLERROOT";
        case ABILITY_ID::CANCEL_SPORECRAWLERROOT :
            return "CANCEL_SPORECRAWLERROOT";
        case ABILITY_ID::CANCEL_STARPORTADDON : return "CANCEL_STARPORTADDON";
        case ABILITY_ID::CANCEL_STASISTRAP    : return "CANCEL_STASISTRAP";
        case ABILITY_ID::CANCEL_TEMPESTDISRUPTIONBLAST :
            return "CANCEL_TEMPESTDISRUPTIONBLAST";
        case ABILITY_ID::CANCEL_VOIDRAYPRISMATICALIGNMENT :
            return "CANCEL_VOIDRAYPRISMATICALIGNMENT";
        case ABILITY_ID::CHANGESHRINEPROTOSS : return "CHANGESHRINEPROTOSS";
        case ABILITY_ID::CHANGESHRINETERRAN  : return "CHANGESHRINETERRAN";
        case ABILITY_ID::CHANNELSNIPE_CANCEL : return "CHANNELSNIPE_CANCEL";
        case ABILITY_ID::CLIFFDOORCLOSE0_SPACEPLATFORMDOORCLOSE :
            return "CLIFFDOORCLOSE0_SPACEPLATFORMDOORCLOSE";
        case ABILITY_ID::CLIFFDOORCLOSE1_SPACEPLATFORMDOORCLOSE :
            return "CLIFFDOORCLOSE1_SPACEPLATFORMDOORCLOSE";
        case ABILITY_ID::CLIFFDOOROPEN0_SPACEPLATFORMDOOROPEN :
            return "CLIFFDOOROPEN0_SPACEPLATFORMDOOROPEN";
        case ABILITY_ID::CLIFFDOOROPEN1_SPACEPLATFORMDOOROPEN :
            return "CLIFFDOOROPEN1_SPACEPLATFORMDOOROPEN";
        case ABILITY_ID::CLOAKINGDRONE         : return "CLOAKINGDRONE";
        case ABILITY_ID::CLONE                 : return "CLONE";
        case ABILITY_ID::COLONISTSHIPLAND_LAND : return "COLONISTSHIPLAND_LAND";
        case ABILITY_ID::COLONISTSHIPLIFTOFF_LIFT :
            return "COLONISTSHIPLIFTOFF_LIFT";
        case ABILITY_ID::COLONISTTRANSPORTTRANSPORT_COLONISTTRANSPORTLOAD :
            return "COLONISTTRANSPORTTRANSPORT_COLONISTTRANSPORTLOAD";
        case ABILITY_ID::COLONISTTRANSPORTTRANSPORT_COLONISTTRANSPORTUNLOADALL :
            return "COLONISTTRANSPORTTRANSPORT_COLONISTTRANSPORTUNLOADALL";
        case ABILITY_ID::COLONYINFESTATION : return "COLONYINFESTATION";
        case ABILITY_ID::COLONYSHIPTRANSPORT_MEDIVACLOAD :
            return "COLONYSHIPTRANSPORT_MEDIVACLOAD";
        case ABILITY_ID::COLONYSHIPTRANSPORT_MEDIVACUNLOADALL :
            return "COLONYSHIPTRANSPORT_MEDIVACUNLOADALL";
        case ABILITY_ID::CONSUMEDNA            : return "CONSUMEDNA";
        case ABILITY_ID::CONSUMPTION           : return "CONSUMPTION";
        case ABILITY_ID::CORRUPTIONBOMB        : return "CORRUPTIONBOMB";
        case ABILITY_ID::CORRUPTIONBOMB_CANCEL : return "CORRUPTIONBOMB_CANCEL";
        case ABILITY_ID::CORRUPTION_CANCEL     : return "CORRUPTION_CANCEL";
        case ABILITY_ID::CORRUPTION_CORRUPTIONABILITY :
            return "CORRUPTION_CORRUPTIONABILITY";
        case ABILITY_ID::CORSAIRMPDISRUPTIONWEB :
            return "CORSAIRMPDISRUPTIONWEB";
        case ABILITY_ID::CRITTERFLEE     : return "CRITTERFLEE";
        case ABILITY_ID::D8CHARGE        : return "D8CHARGE";
        case ABILITY_ID::DEFENSIVEMATRIX : return "DEFENSIVEMATRIX";
        case ABILITY_ID::DEFILERMPBURROW_BURROWDOWN :
            return "DEFILERMPBURROW_BURROWDOWN";
        case ABILITY_ID::DEFILERMPBURROW_CANCEL :
            return "DEFILERMPBURROW_CANCEL";
        case ABILITY_ID::DEFILERMPCONSUME   : return "DEFILERMPCONSUME";
        case ABILITY_ID::DEFILERMPDARKSWARM : return "DEFILERMPDARKSWARM";
        case ABILITY_ID::DEFILERMPPLAGUE    : return "DEFILERMPPLAGUE";
        case ABILITY_ID::DEFILERMPUNBURROW_BURROWUP :
            return "DEFILERMPUNBURROW_BURROWUP";
        case ABILITY_ID::DESTRUCTIBLEGATEDIAGONALBLURLOWERED_GATEOPEN :
            return "DESTRUCTIBLEGATEDIAGONALBLURLOWERED_GATEOPEN";
        case ABILITY_ID::DESTRUCTIBLEGATEDIAGONALBLUR_GATECLOSE :
            return "DESTRUCTIBLEGATEDIAGONALBLUR_GATECLOSE";
        case ABILITY_ID::DESTRUCTIBLEGATEDIAGONALULBRLOWERED_GATEOPEN :
            return "DESTRUCTIBLEGATEDIAGONALULBRLOWERED_GATEOPEN";
        case ABILITY_ID::DESTRUCTIBLEGATEDIAGONALULBR_GATECLOSE :
            return "DESTRUCTIBLEGATEDIAGONALULBR_GATECLOSE";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTHORIZONTALBF_GATECLOSE :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTALBF_GATECLOSE";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTHORIZONTAL_GATECLOSE :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTAL_GATECLOSE";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTVERTICALLF_GATECLOSE :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICALLF_GATECLOSE";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTVERTICALLOWERED_GATEOPEN :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICALLOWERED_GATEOPEN";
        case ABILITY_ID::DESTRUCTIBLEGATESTRAIGHTVERTICAL_GATECLOSE :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICAL_GATECLOSE";
        case ABILITY_ID::DIGESTERCREEPSPRAY : return "DIGESTERCREEPSPRAY";
        case ABILITY_ID::DIGESTERTRANSPORT_LOADDIGESTER :
            return "DIGESTERTRANSPORT_LOADDIGESTER";
        case ABILITY_ID::DISGUISEASMARINEWITHOUTSHIELD_MARINE :
            return "DISGUISEASMARINEWITHOUTSHIELD_MARINE";
        case ABILITY_ID::DISGUISEASMARINEWITHSHIELD_MARINE :
            return "DISGUISEASMARINEWITHSHIELD_MARINE";
        case ABILITY_ID::DISGUISEASZEALOT_ZEALOT :
            return "DISGUISEASZEALOT_ZEALOT";
        case ABILITY_ID::DISGUISEASZERGLINGWITHOUTWINGS_ZERGLING :
            return "DISGUISEASZERGLINGWITHOUTWINGS_ZERGLING";
        case ABILITY_ID::DISGUISEASZERGLINGWITHWINGS_ZERGLING :
            return "DISGUISEASZERGLINGWITHWINGS_ZERGLING";
        case ABILITY_ID::DOMINATION        : return "DOMINATION";
        case ABILITY_ID::DOMINATION_CANCEL : return "DOMINATION_CANCEL";
        case ABILITY_ID::DROPTOSUPPLYDEPOT_RAISE :
            return "DROPTOSUPPLYDEPOT_RAISE";
        case ABILITY_ID::DUKESREVENGEDEFENSIVEMATRIX_DEFENSIVEMATRIX :
            return "DUKESREVENGEDEFENSIVEMATRIX_DEFENSIVEMATRIX";
        case ABILITY_ID::DUKESREVENGEMISSILEPODS_MISSILEPODS :
            return "DUKESREVENGEMISSILEPODS_MISSILEPODS";
        case ABILITY_ID::DUSKWINGBANSHEECLOAKINGFIELD_CLOAKOFF :
            return "DUSKWINGBANSHEECLOAKINGFIELD_CLOAKOFF";
        case ABILITY_ID::DUSKWINGBANSHEECLOAKINGFIELD_CLOAKONBANSHEE :
            return "DUSKWINGBANSHEECLOAKINGFIELD_CLOAKONBANSHEE";
        case ABILITY_ID::DUTCHPLACETURRET : return "DUTCHPLACETURRET";
        case ABILITY_ID::EFFECT_ABDUCT    : return "EFFECT_ABDUCT";
        case ABILITY_ID::EFFECT_ADEPTPHASESHIFT :
            return "EFFECT_ADEPTPHASESHIFT";
        case ABILITY_ID::EFFECT_AMORPHOUSARMORCLOUD :
            return "EFFECT_AMORPHOUSARMORCLOUD";
        case ABILITY_ID::EFFECT_ANTIARMORMISSILE :
            return "EFFECT_ANTIARMORMISSILE";
        case ABILITY_ID::EFFECT_AUTOTURRET    : return "EFFECT_AUTOTURRET";
        case ABILITY_ID::EFFECT_BLINDINGCLOUD : return "EFFECT_BLINDINGCLOUD";
        case ABILITY_ID::EFFECT_BLINK         : return "EFFECT_BLINK";
        case ABILITY_ID::EFFECT_BLINK_STALKER : return "EFFECT_BLINK_STALKER";
        case ABILITY_ID::EFFECT_CALLDOWNMULE  : return "EFFECT_CALLDOWNMULE";
        case ABILITY_ID::EFFECT_CAUSTICSPRAY  : return "EFFECT_CAUSTICSPRAY";
        case ABILITY_ID::EFFECT_CHARGE        : return "EFFECT_CHARGE";
        case ABILITY_ID::EFFECT_CHRONOBOOST   : return "EFFECT_CHRONOBOOST";
        case ABILITY_ID::EFFECT_CHRONOBOOSTENERGYCOST :
            return "EFFECT_CHRONOBOOSTENERGYCOST";
        case ABILITY_ID::EFFECT_CONTAMINATE    : return "EFFECT_CONTAMINATE";
        case ABILITY_ID::EFFECT_CORROSIVEBILE  : return "EFFECT_CORROSIVEBILE";
        case ABILITY_ID::EFFECT_EMP            : return "EFFECT_EMP";
        case ABILITY_ID::EFFECT_EXPLODE        : return "EFFECT_EXPLODE";
        case ABILITY_ID::EFFECT_FEEDBACK       : return "EFFECT_FEEDBACK";
        case ABILITY_ID::EFFECT_FORCEFIELD     : return "EFFECT_FORCEFIELD";
        case ABILITY_ID::EFFECT_FUNGALGROWTH   : return "EFFECT_FUNGALGROWTH";
        case ABILITY_ID::EFFECT_GHOSTSNIPE     : return "EFFECT_GHOSTSNIPE";
        case ABILITY_ID::EFFECT_GRAVITONBEAM   : return "EFFECT_GRAVITONBEAM";
        case ABILITY_ID::EFFECT_GUARDIANSHIELD : return "EFFECT_GUARDIANSHIELD";
        case ABILITY_ID::EFFECT_HEAL           : return "EFFECT_HEAL";
        case ABILITY_ID::EFFECT_HUNTERSEEKERMISSILE :
            return "EFFECT_HUNTERSEEKERMISSILE";
        case ABILITY_ID::EFFECT_IMMORTALBARRIER :
            return "EFFECT_IMMORTALBARRIER";
        case ABILITY_ID::EFFECT_INFESTEDTERRANS :
            return "EFFECT_INFESTEDTERRANS";
        case ABILITY_ID::EFFECT_INJECTLARVA : return "EFFECT_INJECTLARVA";
        case ABILITY_ID::EFFECT_INTERFERENCEMATRIX :
            return "EFFECT_INTERFERENCEMATRIX";
        case ABILITY_ID::EFFECT_KD8CHARGE   : return "EFFECT_KD8CHARGE";
        case ABILITY_ID::EFFECT_LOCKON      : return "EFFECT_LOCKON";
        case ABILITY_ID::EFFECT_LOCUSTSWOOP : return "EFFECT_LOCUSTSWOOP";
        case ABILITY_ID::EFFECT_MASSRECALL  : return "EFFECT_MASSRECALL";
        case ABILITY_ID::EFFECT_MASSRECALL_MOTHERSHIP :
            return "EFFECT_MASSRECALL_MOTHERSHIP";
        case ABILITY_ID::EFFECT_MASSRECALL_MOTHERSHIPCORE :
            return "EFFECT_MASSRECALL_MOTHERSHIPCORE";
        case ABILITY_ID::EFFECT_MASSRECALL_NEXUS :
            return "EFFECT_MASSRECALL_NEXUS";
        case ABILITY_ID::EFFECT_MASSRECALL_STRATEGICRECALL :
            return "EFFECT_MASSRECALL_STRATEGICRECALL";
        case ABILITY_ID::EFFECT_MEDIVACIGNITEAFTERBURNERS :
            return "EFFECT_MEDIVACIGNITEAFTERBURNERS";
        case ABILITY_ID::EFFECT_NEURALPARASITE : return "EFFECT_NEURALPARASITE";
        case ABILITY_ID::EFFECT_NUKECALLDOWN   : return "EFFECT_NUKECALLDOWN";
        case ABILITY_ID::EFFECT_ORACLEREVELATION :
            return "EFFECT_ORACLEREVELATION";
        case ABILITY_ID::EFFECT_PARASITICBOMB : return "EFFECT_PARASITICBOMB";
        case ABILITY_ID::EFFECT_PHOTONOVERCHARGE :
            return "EFFECT_PHOTONOVERCHARGE";
        case ABILITY_ID::EFFECT_POINTDEFENSEDRONE :
            return "EFFECT_POINTDEFENSEDRONE";
        case ABILITY_ID::EFFECT_PSISTORM : return "EFFECT_PSISTORM";
        case ABILITY_ID::EFFECT_PURIFICATIONNOVA :
            return "EFFECT_PURIFICATIONNOVA";
        case ABILITY_ID::EFFECT_REPAIR      : return "EFFECT_REPAIR";
        case ABILITY_ID::EFFECT_REPAIRDRONE : return "EFFECT_REPAIRDRONE";
        case ABILITY_ID::EFFECT_REPAIR_MULE : return "EFFECT_REPAIR_MULE";
        case ABILITY_ID::EFFECT_REPAIR_REPAIRDRONE :
            return "EFFECT_REPAIR_REPAIRDRONE";
        case ABILITY_ID::EFFECT_REPAIR_SCV   : return "EFFECT_REPAIR_SCV";
        case ABILITY_ID::EFFECT_RESTORE      : return "EFFECT_RESTORE";
        case ABILITY_ID::EFFECT_SALVAGE      : return "EFFECT_SALVAGE";
        case ABILITY_ID::EFFECT_SCAN         : return "EFFECT_SCAN";
        case ABILITY_ID::EFFECT_SHADOWSTRIDE : return "EFFECT_SHADOWSTRIDE";
        case ABILITY_ID::EFFECT_SPAWNCHANGELING :
            return "EFFECT_SPAWNCHANGELING";
        case ABILITY_ID::EFFECT_SPAWNLOCUSTS  : return "EFFECT_SPAWNLOCUSTS";
        case ABILITY_ID::EFFECT_SPRAY         : return "EFFECT_SPRAY";
        case ABILITY_ID::EFFECT_SPRAY_PROTOSS : return "EFFECT_SPRAY_PROTOSS";
        case ABILITY_ID::EFFECT_SPRAY_TERRAN  : return "EFFECT_SPRAY_TERRAN";
        case ABILITY_ID::EFFECT_SPRAY_ZERG    : return "EFFECT_SPRAY_ZERG";
        case ABILITY_ID::EFFECT_STIM          : return "EFFECT_STIM";
        case ABILITY_ID::EFFECT_STIM_MARAUDER : return "EFFECT_STIM_MARAUDER";
        case ABILITY_ID::EFFECT_STIM_MARAUDER_REDIRECT :
            return "EFFECT_STIM_MARAUDER_REDIRECT";
        case ABILITY_ID::EFFECT_STIM_MARINE : return "EFFECT_STIM_MARINE";
        case ABILITY_ID::EFFECT_STIM_MARINE_REDIRECT :
            return "EFFECT_STIM_MARINE_REDIRECT";
        case ABILITY_ID::EFFECT_SUPPLYDROP   : return "EFFECT_SUPPLYDROP";
        case ABILITY_ID::EFFECT_TACTICALJUMP : return "EFFECT_TACTICALJUMP";
        case ABILITY_ID::EFFECT_TEMPESTDISRUPTIONBLAST :
            return "EFFECT_TEMPESTDISRUPTIONBLAST";
        case ABILITY_ID::EFFECT_TIMEWARP     : return "EFFECT_TIMEWARP";
        case ABILITY_ID::EFFECT_TRANSFUSION  : return "EFFECT_TRANSFUSION";
        case ABILITY_ID::EFFECT_VIPERCONSUME : return "EFFECT_VIPERCONSUME";
        case ABILITY_ID::EFFECT_VOIDRAYPRISMATICALIGNMENT :
            return "EFFECT_VOIDRAYPRISMATICALIGNMENT";
        case ABILITY_ID::EFFECT_WIDOWMINEATTACK :
            return "EFFECT_WIDOWMINEATTACK";
        case ABILITY_ID::EFFECT_YAMATOGUN : return "EFFECT_YAMATOGUN";
        case ABILITY_ID::EGGPOP           : return "EGGPOP";
        case ABILITY_ID::ENERGYNOVA       : return "ENERGYNOVA";
        case ABILITY_ID::EVOLUTIONCHAMBERRESEARCH_EVOLVEPROPULSIVEPERISTALSIS :
            return "EVOLUTIONCHAMBERRESEARCH_EVOLVEPROPULSIVEPERISTALSIS";
        case ABILITY_ID::EXPERIMENTALPLASMAGUN : return "EXPERIMENTALPLASMAGUN";
        case ABILITY_ID::EXTENDINGBRIDGENEWIDE10OUT_BRIDGEEXTEND :
            return "EXTENDINGBRIDGENEWIDE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::EXTENDINGBRIDGENEWIDE10_BRIDGERETRACT :
            return "EXTENDINGBRIDGENEWIDE10_BRIDGERETRACT";
        case ABILITY_ID::EXTENDINGBRIDGENEWIDE12OUT_BRIDGEEXTEND :
            return "EXTENDINGBRIDGENEWIDE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::EXTENDINGBRIDGENEWIDE12_BRIDGERETRACT :
            return "EXTENDINGBRIDGENEWIDE12_BRIDGERETRACT";
        case ABILITY_ID::EXTENDINGBRIDGENEWIDE8OUT_BRIDGEEXTEND :
            return "EXTENDINGBRIDGENEWIDE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::EXTENDINGBRIDGENEWIDE8_BRIDGERETRACT :
            return "EXTENDINGBRIDGENEWIDE8_BRIDGERETRACT";
        case ABILITY_ID::EXTENDINGBRIDGENWWIDE10OUT_BRIDGEEXTEND :
            return "EXTENDINGBRIDGENWWIDE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::EXTENDINGBRIDGENWWIDE10_BRIDGERETRACT :
            return "EXTENDINGBRIDGENWWIDE10_BRIDGERETRACT";
        case ABILITY_ID::EXTENDINGBRIDGENWWIDE12OUT_BRIDGEEXTEND :
            return "EXTENDINGBRIDGENWWIDE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::EXTENDINGBRIDGENWWIDE12_BRIDGERETRACT :
            return "EXTENDINGBRIDGENWWIDE12_BRIDGERETRACT";
        case ABILITY_ID::EXTENDINGBRIDGENWWIDE8OUT_BRIDGEEXTEND :
            return "EXTENDINGBRIDGENWWIDE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::EXTENDINGBRIDGENWWIDE8_BRIDGERETRACT :
            return "EXTENDINGBRIDGENWWIDE8_BRIDGERETRACT";
        case ABILITY_ID::EYESTALK        : return "EYESTALK";
        case ABILITY_ID::EYESTALK_CANCEL : return "EYESTALK_CANCEL";
        case ABILITY_ID::FACTORYREACTORMORPH_REACTOR :
            return "FACTORYREACTORMORPH_REACTOR";
        case ABILITY_ID::FACTORYTECHLABMORPH_TECHLABFACTORY :
            return "FACTORYTECHLABMORPH_TECHLABFACTORY";
        case ABILITY_ID::FACTORYTECHREACTORMORPH_TECHLABFACTORY :
            return "FACTORYTECHREACTORMORPH_TECHLABFACTORY";
        case ABILITY_ID::FLYERSHIELD          : return "FLYERSHIELD";
        case ABILITY_ID::FORCEFIELD_CANCEL    : return "FORCEFIELD_CANCEL";
        case ABILITY_ID::FRENZY               : return "FRENZY";
        case ABILITY_ID::GATHERSPECIALOBJECT  : return "GATHERSPECIALOBJECT";
        case ABILITY_ID::GENERAL_HOLDPOSITION : return "GENERAL_HOLDPOSITION";
        case ABILITY_ID::GENERAL_MOVE         : return "GENERAL_MOVE";
        case ABILITY_ID::GENERAL_PATROL       : return "GENERAL_PATROL";
        case ABILITY_ID::GRAPPLE              : return "GRAPPLE";
        case ABILITY_ID::GRAVITONPRISON       : return "GRAVITONPRISON";
        case ABILITY_ID::GWALEARN_TESTLEARN   : return "GWALEARN_TESTLEARN";
        case ABILITY_ID::HALLUCINATION_ADEPT  : return "HALLUCINATION_ADEPT";
        case ABILITY_ID::HALLUCINATION_ARCHON : return "HALLUCINATION_ARCHON";
        case ABILITY_ID::HALLUCINATION_COLOSSUS :
            return "HALLUCINATION_COLOSSUS";
        case ABILITY_ID::HALLUCINATION_DISRUPTOR :
            return "HALLUCINATION_DISRUPTOR";
        case ABILITY_ID::HALLUCINATION_HIGHTEMPLAR :
            return "HALLUCINATION_HIGHTEMPLAR";
        case ABILITY_ID::HALLUCINATION_IMMORTAL :
            return "HALLUCINATION_IMMORTAL";
        case ABILITY_ID::HALLUCINATION_ORACLE  : return "HALLUCINATION_ORACLE";
        case ABILITY_ID::HALLUCINATION_PHOENIX : return "HALLUCINATION_PHOENIX";
        case ABILITY_ID::HALLUCINATION_PROBE   : return "HALLUCINATION_PROBE";
        case ABILITY_ID::HALLUCINATION_STALKER : return "HALLUCINATION_STALKER";
        case ABILITY_ID::HALLUCINATION_VOIDRAY : return "HALLUCINATION_VOIDRAY";
        case ABILITY_ID::HALLUCINATION_WARPPRISM :
            return "HALLUCINATION_WARPPRISM";
        case ABILITY_ID::HALLUCINATION_ZEALOT : return "HALLUCINATION_ZEALOT";
        case ABILITY_ID::HALT                 : return "HALT";
        case ABILITY_ID::HALT_BUILDING        : return "HALT_BUILDING";
        case ABILITY_ID::HALT_TERRANBUILD     : return "HALT_TERRANBUILD";
        case ABILITY_ID::HARVEST_GATHER       : return "HARVEST_GATHER";
        case ABILITY_ID::HARVEST_GATHER_DRONE : return "HARVEST_GATHER_DRONE";
        case ABILITY_ID::HARVEST_GATHER_MULE  : return "HARVEST_GATHER_MULE";
        case ABILITY_ID::HARVEST_GATHER_PROBE : return "HARVEST_GATHER_PROBE";
        case ABILITY_ID::HARVEST_GATHER_SCV   : return "HARVEST_GATHER_SCV";
        case ABILITY_ID::HARVEST_RETURN       : return "HARVEST_RETURN";
        case ABILITY_ID::HARVEST_RETURN_DRONE : return "HARVEST_RETURN_DRONE";
        case ABILITY_ID::HARVEST_RETURN_MULE  : return "HARVEST_RETURN_MULE";
        case ABILITY_ID::HARVEST_RETURN_PROBE : return "HARVEST_RETURN_PROBE";
        case ABILITY_ID::HARVEST_RETURN_SCV   : return "HARVEST_RETURN_SCV";
        case ABILITY_ID::HEAL_MEDICHEAL       : return "HEAL_MEDICHEAL";
        case ABILITY_ID::HELIOSCRASHMORPH_CRASHMORPH :
            return "HELIOSCRASHMORPH_CRASHMORPH";
        case ABILITY_ID::HERCULESLAND         : return "HERCULESLAND";
        case ABILITY_ID::HERCULESLIFTOFF_LIFT : return "HERCULESLIFTOFF_LIFT";
        case ABILITY_ID::HERCULESTRANSPORT_MEDIVACLOAD :
            return "HERCULESTRANSPORT_MEDIVACLOAD";
        case ABILITY_ID::HERCULESTRANSPORT_MEDIVACUNLOADALL :
            return "HERCULESTRANSPORT_MEDIVACUNLOADALL";
        case ABILITY_ID::HERDINTERACT_HERD   : return "HERDINTERACT_HERD";
        case ABILITY_ID::HEROARMNUKE_NUKEARM : return "HEROARMNUKE_NUKEARM";
        case ABILITY_ID::HERONUCLEARSTRIKE_CANCEL :
            return "HERONUCLEARSTRIKE_CANCEL";
        case ABILITY_ID::HOLDFIRE             : return "HOLDFIRE";
        case ABILITY_ID::HOLDFIRE_STOPSPECIAL : return "HOLDFIRE_STOPSPECIAL";
        case ABILITY_ID::HUTTRANSPORT_HUTLOAD : return "HUTTRANSPORT_HUTLOAD";
        case ABILITY_ID::HUTTRANSPORT_HUTUNLOADALL :
            return "HUTTRANSPORT_HUTUNLOADALL";
        case ABILITY_ID::HYBRIDBLINK_ZERATULBLINK :
            return "HYBRIDBLINK_ZERATULBLINK";
        case ABILITY_ID::HYBRIDCPLASMABLAST : return "HYBRIDCPLASMABLAST";
        case ABILITY_ID::HYBRIDFAOESTUN     : return "HYBRIDFAOESTUN";
        case ABILITY_ID::HYPERIONYAMATOSPECIAL_HYPERIONYAMATOGUN :
            return "HYPERIONYAMATOSPECIAL_HYPERIONYAMATOGUN";
        case ABILITY_ID::IMPALE    : return "IMPALE";
        case ABILITY_ID::IMPLOSION : return "IMPLOSION";
        case ABILITY_ID::INFESTABLEHUTTRANSPORT_HUTLOAD :
            return "INFESTABLEHUTTRANSPORT_HUTLOAD";
        case ABILITY_ID::INFESTABLEHUTTRANSPORT_HUTUNLOADALL :
            return "INFESTABLEHUTTRANSPORT_HUTUNLOADALL";
        case ABILITY_ID::INFESTEDVENTSPAWNBROODLORD_SPAWNBROODLORD :
            return "INFESTEDVENTSPAWNBROODLORD_SPAWNBROODLORD";
        case ABILITY_ID::INFESTEDVENTSPAWNCORRUPTOR_SPAWNCORRUPTOR :
            return "INFESTEDVENTSPAWNCORRUPTOR_SPAWNCORRUPTOR";
        case ABILITY_ID::INFESTEDVENTSPAWNMUTALISK_LEVIATHANSPAWNMUTALISK :
            return "INFESTEDVENTSPAWNMUTALISK_LEVIATHANSPAWNMUTALISK";
        case ABILITY_ID::INFESTORENSNARE       : return "INFESTORENSNARE";
        case ABILITY_ID::INVALID               : return "INVALID";
        case ABILITY_ID::INVULNERABILITYSHIELD : return "INVULNERABILITYSHIELD";
        case ABILITY_ID::IRRADIATE             : return "IRRADIATE";
        case ABILITY_ID::IRRADIATE_CANCEL      : return "IRRADIATE_CANCEL";
        case ABILITY_ID::KARASSPLASMASURGE     : return "KARASSPLASMASURGE";
        case ABILITY_ID::LAND                  : return "LAND";
        case ABILITY_ID::LAND_BARRACKS         : return "LAND_BARRACKS";
        case ABILITY_ID::LAND_COMMANDCENTER    : return "LAND_COMMANDCENTER";
        case ABILITY_ID::LAND_FACTORY          : return "LAND_FACTORY";
        case ABILITY_ID::LAND_ORBITALCOMMAND   : return "LAND_ORBITALCOMMAND";
        case ABILITY_ID::LAND_STARPORT         : return "LAND_STARPORT";
        case ABILITY_ID::LEECH                 : return "LEECH";
        case ABILITY_ID::LEECHRESOURCES_CANCEL : return "LEECHRESOURCES_CANCEL";
        case ABILITY_ID::LEVIATHANSPAWNBROODLORD_SPAWNBROODLORD :
            return "LEVIATHANSPAWNBROODLORD_SPAWNBROODLORD";
        case ABILITY_ID::LEVIATHANSPAWNMUTALISK :
            return "LEVIATHANSPAWNMUTALISK";
        case ABILITY_ID::LIBERATORMORPHTOAA_LIBERATORAAMODE :
            return "LIBERATORMORPHTOAA_LIBERATORAAMODE";
        case ABILITY_ID::LIBERATORMORPHTOAG_LIBERATORAGMODE :
            return "LIBERATORMORPHTOAG_LIBERATORAGMODE";
        case ABILITY_ID::LIBRARYDOWN         : return "LIBRARYDOWN";
        case ABILITY_ID::LIBRARYUP           : return "LIBRARYUP";
        case ABILITY_ID::LIFT                : return "LIFT";
        case ABILITY_ID::LIFT_BARRACKS       : return "LIFT_BARRACKS";
        case ABILITY_ID::LIFT_COMMANDCENTER  : return "LIFT_COMMANDCENTER";
        case ABILITY_ID::LIFT_FACTORY        : return "LIFT_FACTORY";
        case ABILITY_ID::LIFT_ORBITALCOMMAND : return "LIFT_ORBITALCOMMAND";
        case ABILITY_ID::LIFT_STARPORT       : return "LIFT_STARPORT";
        case ABILITY_ID::LIGHTBRIDGEOFF      : return "LIGHTBRIDGEOFF";
        case ABILITY_ID::LIGHTBRIDGEOFFTOPRIGHT_LIGHTBRIDGEOFF :
            return "LIGHTBRIDGEOFFTOPRIGHT_LIGHTBRIDGEOFF";
        case ABILITY_ID::LIGHTBRIDGEON : return "LIGHTBRIDGEON";
        case ABILITY_ID::LIGHTBRIDGEONTOPRIGHT_LIGHTBRIDGEON :
            return "LIGHTBRIDGEONTOPRIGHT_LIGHTBRIDGEON";
        case ABILITY_ID::LIGHTNINGBOMB         : return "LIGHTNINGBOMB";
        case ABILITY_ID::LIGHTOFAIUR           : return "LIGHTOFAIUR";
        case ABILITY_ID::LOAD                  : return "LOAD";
        case ABILITY_ID::LOADALL               : return "LOADALL";
        case ABILITY_ID::LOADALL_COMMANDCENTER : return "LOADALL_COMMANDCENTER";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_1 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_1";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_10 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_10";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_11 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_11";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_12 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_12";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_13 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_13";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_14 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_14";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_2 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_2";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_3 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_3";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_4 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_4";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_5 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_5";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_6 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_6";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_7 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_7";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_8 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_8";
        case ABILITY_ID::LOADOUTSPRAY_LOADOUTSPRAY_9 :
            return "LOADOUTSPRAY_LOADOUTSPRAY_9";
        case ABILITY_ID::LOAD_BUNKER       : return "LOAD_BUNKER";
        case ABILITY_ID::LOAD_MEDIVAC      : return "LOAD_MEDIVAC";
        case ABILITY_ID::LOAD_NYDUSNETWORK : return "LOAD_NYDUSNETWORK";
        case ABILITY_ID::LOAD_NYDUSWORM    : return "LOAD_NYDUSWORM";
        case ABILITY_ID::LOAD_OVERLORD     : return "LOAD_OVERLORD";
        case ABILITY_ID::LOAD_WARPPRISM    : return "LOAD_WARPPRISM";
        case ABILITY_ID::LOCKONAIR         : return "LOCKONAIR";
        case ABILITY_ID::LOCUSTMPFLYINGMORPHTOGROUND_LOCUSTMPFLYINGSWOOP :
            return "LOCUSTMPFLYINGMORPHTOGROUND_LOCUSTMPFLYINGSWOOP";
        case ABILITY_ID::LOCUSTMPFLYINGSWOOPATTACK_LOCUSTMPFLYINGSWOOP :
            return "LOCUSTMPFLYINGSWOOPATTACK_LOCUSTMPFLYINGSWOOP";
        case ABILITY_ID::LOCUSTMPMORPHTOAIR_LOCUSTMPFLYINGSWOOP :
            return "LOCUSTMPMORPHTOAIR_LOCUSTMPFLYINGSWOOP";
        case ABILITY_ID::LOKIMISSILEPODS_MISSILEPODS :
            return "LOKIMISSILEPODS_MISSILEPODS";
        case ABILITY_ID::LOKIUNDOCK_LIFT : return "LOKIUNDOCK_LIFT";
        case ABILITY_ID::LOKIYAMATO_LOKIYAMATOGUN :
            return "LOKIYAMATO_LOKIYAMATOGUN";
        case ABILITY_ID::LURKERASPECTFROMHYDRALISKBURROWED_CANCEL :
            return "LURKERASPECTFROMHYDRALISKBURROWED_CANCEL";
        case ABILITY_ID::
            LURKERASPECTFROMHYDRALISKBURROWED_LURKERFROMHYDRALISKBURROWED :
            return "LURKERASPECTFROMHYDRALISKBURROWED_"
                   "LURKERFROMHYDRALISKBURROWED";
        case ABILITY_ID::LURKERASPECTMPFROMHYDRALISKBURROWED_CANCEL :
            return "LURKERASPECTMPFROMHYDRALISKBURROWED_CANCEL";
        case ABILITY_ID::
            LURKERASPECTMPFROMHYDRALISKBURROWED_LURKERMPFROMHYDRALISKBURROWED :
            return "LURKERASPECTMPFROMHYDRALISKBURROWED_"
                   "LURKERMPFROMHYDRALISKBURROWED";
        case ABILITY_ID::LURKERASPECTMP_CANCEL : return "LURKERASPECTMP_CANCEL";
        case ABILITY_ID::LURKERASPECTMP_LURKERMP :
            return "LURKERASPECTMP_LURKERMP";
        case ABILITY_ID::LURKERASPECT_CANCEL : return "LURKERASPECT_CANCEL";
        case ABILITY_ID::LURKERASPECT_LURKER : return "LURKERASPECT_LURKER";
        case ABILITY_ID::MAKEVULTURESPIDERMINES_SPIDERMINEREPLENISH :
            return "MAKEVULTURESPIDERMINES_SPIDERMINEREPLENISH";
        case ABILITY_ID::MASSIVEKNOCKOVER : return "MASSIVEKNOCKOVER";
        case ABILITY_ID::MAXIUMTHRUST_MAXIMUMTHRUST :
            return "MAXIUMTHRUST_MAXIMUMTHRUST";
        case ABILITY_ID::MERGEABLE_CANCEL : return "MERGEABLE_CANCEL";
        case ABILITY_ID::METALGATEDIAGONALBLURLOWERED_GATEOPEN :
            return "METALGATEDIAGONALBLURLOWERED_GATEOPEN";
        case ABILITY_ID::METALGATEDIAGONALBLUR_GATECLOSE :
            return "METALGATEDIAGONALBLUR_GATECLOSE";
        case ABILITY_ID::METALGATEDIAGONALULBRLOWERED_GATEOPEN :
            return "METALGATEDIAGONALULBRLOWERED_GATEOPEN";
        case ABILITY_ID::METALGATEDIAGONALULBR_GATECLOSE :
            return "METALGATEDIAGONALULBR_GATECLOSE";
        case ABILITY_ID::METALGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN :
            return "METALGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN";
        case ABILITY_ID::METALGATESTRAIGHTHORIZONTALBF_GATECLOSE :
            return "METALGATESTRAIGHTHORIZONTALBF_GATECLOSE";
        case ABILITY_ID::METALGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN :
            return "METALGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN";
        case ABILITY_ID::METALGATESTRAIGHTHORIZONTAL_GATECLOSE :
            return "METALGATESTRAIGHTHORIZONTAL_GATECLOSE";
        case ABILITY_ID::METALGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN :
            return "METALGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN";
        case ABILITY_ID::METALGATESTRAIGHTVERTICALLF_GATECLOSE :
            return "METALGATESTRAIGHTVERTICALLF_GATECLOSE";
        case ABILITY_ID::METALGATESTRAIGHTVERTICALLOWERED_GATEOPEN :
            return "METALGATESTRAIGHTVERTICALLOWERED_GATEOPEN";
        case ABILITY_ID::METALGATESTRAIGHTVERTICAL_GATECLOSE :
            return "METALGATESTRAIGHTVERTICAL_GATECLOSE";
        case ABILITY_ID::MINDBLAST             : return "MINDBLAST";
        case ABILITY_ID::MINDCONTROL           : return "MINDCONTROL";
        case ABILITY_ID::MISSILEPODS           : return "MISSILEPODS";
        case ABILITY_ID::MORPH_ARCHON          : return "MORPH_ARCHON";
        case ABILITY_ID::MORPH_BANELING        : return "MORPH_BANELING";
        case ABILITY_ID::MORPH_BROODLORD       : return "MORPH_BROODLORD";
        case ABILITY_ID::MORPH_CANCEL          : return "MORPH_CANCEL";
        case ABILITY_ID::MORPH_GATEWAY         : return "MORPH_GATEWAY";
        case ABILITY_ID::MORPH_GREATERSPIRE    : return "MORPH_GREATERSPIRE";
        case ABILITY_ID::MORPH_HELLBAT         : return "MORPH_HELLBAT";
        case ABILITY_ID::MORPH_HELLION         : return "MORPH_HELLION";
        case ABILITY_ID::MORPH_HIVE            : return "MORPH_HIVE";
        case ABILITY_ID::MORPH_LAIR            : return "MORPH_LAIR";
        case ABILITY_ID::MORPH_LIBERATORAAMODE : return "MORPH_LIBERATORAAMODE";
        case ABILITY_ID::MORPH_LIBERATORAGMODE : return "MORPH_LIBERATORAGMODE";
        case ABILITY_ID::MORPH_LURKER          : return "MORPH_LURKER";
        case ABILITY_ID::MORPH_LURKERDEN       : return "MORPH_LURKERDEN";
        case ABILITY_ID::MORPH_MORPHTODEVOURERMP :
            return "MORPH_MORPHTODEVOURERMP";
        case ABILITY_ID::MORPH_MORPHTOGUARDIANMP :
            return "MORPH_MORPHTOGUARDIANMP";
        case ABILITY_ID::MORPH_MORPHTOINFESTEDCIVILIAN :
            return "MORPH_MORPHTOINFESTEDCIVILIAN";
        case ABILITY_ID::MORPH_MOTHERSHIP     : return "MORPH_MOTHERSHIP";
        case ABILITY_ID::MORPH_MOVE           : return "MORPH_MOVE";
        case ABILITY_ID::MORPH_OBSERVERMODE   : return "MORPH_OBSERVERMODE";
        case ABILITY_ID::MORPH_ORBITALCOMMAND : return "MORPH_ORBITALCOMMAND";
        case ABILITY_ID::MORPH_OVERLORDTRANSPORT :
            return "MORPH_OVERLORDTRANSPORT";
        case ABILITY_ID::MORPH_OVERSEER      : return "MORPH_OVERSEER";
        case ABILITY_ID::MORPH_OVERSEERMODE  : return "MORPH_OVERSEERMODE";
        case ABILITY_ID::MORPH_OVERSIGHTMODE : return "MORPH_OVERSIGHTMODE";
        case ABILITY_ID::MORPH_PLANETARYFORTRESS :
            return "MORPH_PLANETARYFORTRESS";
        case ABILITY_ID::MORPH_RAVAGER   : return "MORPH_RAVAGER";
        case ABILITY_ID::MORPH_ROOT      : return "MORPH_ROOT";
        case ABILITY_ID::MORPH_SIEGEMODE : return "MORPH_SIEGEMODE";
        case ABILITY_ID::MORPH_SPINECRAWLERROOT :
            return "MORPH_SPINECRAWLERROOT";
        case ABILITY_ID::MORPH_SPINECRAWLERUPROOT :
            return "MORPH_SPINECRAWLERUPROOT";
        case ABILITY_ID::MORPH_SPORECRAWLERROOT :
            return "MORPH_SPORECRAWLERROOT";
        case ABILITY_ID::MORPH_SPORECRAWLERUPROOT :
            return "MORPH_SPORECRAWLERUPROOT";
        case ABILITY_ID::MORPH_SUPPLYDEPOT_LOWER :
            return "MORPH_SUPPLYDEPOT_LOWER";
        case ABILITY_ID::MORPH_SUPPLYDEPOT_RAISE :
            return "MORPH_SUPPLYDEPOT_RAISE";
        case ABILITY_ID::MORPH_SURVEILLANCEMODE :
            return "MORPH_SURVEILLANCEMODE";
        case ABILITY_ID::MORPH_THOREXPLOSIVEMODE :
            return "MORPH_THOREXPLOSIVEMODE";
        case ABILITY_ID::MORPH_THORHIGHIMPACTMODE :
            return "MORPH_THORHIGHIMPACTMODE";
        case ABILITY_ID::MORPH_UNSIEGE : return "MORPH_UNSIEGE";
        case ABILITY_ID::MORPH_UPROOT  : return "MORPH_UPROOT";
        case ABILITY_ID::MORPH_VIKINGASSAULTMODE :
            return "MORPH_VIKINGASSAULTMODE";
        case ABILITY_ID::MORPH_VIKINGFIGHTERMODE :
            return "MORPH_VIKINGFIGHTERMODE";
        case ABILITY_ID::MORPH_WARPGATE : return "MORPH_WARPGATE";
        case ABILITY_ID::MORPH_WARPPRISMPHASINGMODE :
            return "MORPH_WARPPRISMPHASINGMODE";
        case ABILITY_ID::MORPH_WARPPRISMTRANSPORTMODE :
            return "MORPH_WARPPRISMTRANSPORTMODE";
        case ABILITY_ID::MOTHERSHIPCLOAK_ORACLECLOAKFIELD :
            return "MOTHERSHIPCLOAK_ORACLECLOAKFIELD";
        case ABILITY_ID::MOTHERSHIPCOREENERGIZE :
            return "MOTHERSHIPCOREENERGIZE";
        case ABILITY_ID::MOTHERSHIPCOREENERGIZE_CANCEL :
            return "MOTHERSHIPCOREENERGIZE_CANCEL";
        case ABILITY_ID::MOTHERSHIPCOREPURIFYNEXUSCANCEL_CANCEL :
            return "MOTHERSHIPCOREPURIFYNEXUSCANCEL_CANCEL";
        case ABILITY_ID::MOTHERSHIPCORETELEPORT :
            return "MOTHERSHIPCORETELEPORT";
        case ABILITY_ID::MOTHERSHIPCOREWEAPON_MOTHERSHIPSTASIS :
            return "MOTHERSHIPCOREWEAPON_MOTHERSHIPSTASIS";
        case ABILITY_ID::MOTHERSHIPSTASIS      : return "MOTHERSHIPSTASIS";
        case ABILITY_ID::MOVE_ACQUIREMOVE      : return "MOVE_ACQUIREMOVE";
        case ABILITY_ID::MOVE_MOVE             : return "MOVE_MOVE";
        case ABILITY_ID::MOVE_MOVEHOLDPOSITION : return "MOVE_MOVEHOLDPOSITION";
        case ABILITY_ID::MOVE_MOVEPATROL       : return "MOVE_MOVEPATROL";
        case ABILITY_ID::MOVE_TURN             : return "MOVE_TURN";
        case ABILITY_ID::NEXUSINVULNERABILITY  : return "NEXUSINVULNERABILITY";
        case ABILITY_ID::NEXUSPHASESHIFT       : return "NEXUSPHASESHIFT";
        case ABILITY_ID::NEXUSSHIELDOVERCHARGE : return "NEXUSSHIELDOVERCHARGE";
        case ABILITY_ID::NEXUSSHIELDOVERCHARGEOFF :
            return "NEXUSSHIELDOVERCHARGEOFF";
        case ABILITY_ID::NEXUSSHIELDRECHARGE : return "NEXUSSHIELDRECHARGE";
        case ABILITY_ID::NEXUSSHIELDRECHARGEONPYLON :
            return "NEXUSSHIELDRECHARGEONPYLON";
        case ABILITY_ID::NOVASNIPE          : return "NOVASNIPE";
        case ABILITY_ID::OBLITERATE         : return "OBLITERATE";
        case ABILITY_ID::ODINBARRAGE        : return "ODINBARRAGE";
        case ABILITY_ID::ODINBARRAGE_CANCEL : return "ODINBARRAGE_CANCEL";
        case ABILITY_ID::ODINNUCLEARSTRIKE_CANCEL :
            return "ODINNUCLEARSTRIKE_CANCEL";
        case ABILITY_ID::ODINNUCLEARSTRIKE_ODINNUKECALLDOWN :
            return "ODINNUCLEARSTRIKE_ODINNUKECALLDOWN";
        case ABILITY_ID::ODINWRECKAGE_ODIN : return "ODINWRECKAGE_ODIN";
        case ABILITY_ID::OMEGASTORM        : return "OMEGASTORM";
        case ABILITY_ID::ORACLECLOAKFIELD  : return "ORACLECLOAKFIELD";
        case ABILITY_ID::ORACLECLOAKINGFIELDTARGETED :
            return "ORACLECLOAKINGFIELDTARGETED";
        case ABILITY_ID::ORACLENORMALMODE : return "ORACLENORMALMODE";
        case ABILITY_ID::ORACLENORMALMODE_CANCEL :
            return "ORACLENORMALMODE_CANCEL";
        case ABILITY_ID::ORACLEPHASESHIFT     : return "ORACLEPHASESHIFT";
        case ABILITY_ID::ORACLEREVELATIONMODE : return "ORACLEREVELATIONMODE";
        case ABILITY_ID::ORACLEREVELATIONMODE_CANCEL :
            return "ORACLEREVELATIONMODE_CANCEL";
        case ABILITY_ID::ORACLESTASISTRAPACTIVATE_ACTIVATESTASISWARD :
            return "ORACLESTASISTRAPACTIVATE_ACTIVATESTASISWARD";
        case ABILITY_ID::ORACLESTASISTRAP_ORACLEBUILDSTASISTRAP :
            return "ORACLESTASISTRAP_ORACLEBUILDSTASISTRAP";
        case ABILITY_ID::OVERCHARGE           : return "OVERCHARGE";
        case ABILITY_ID::PARKCOLONISTVEHICLE  : return "PARKCOLONISTVEHICLE";
        case ABILITY_ID::PENETRATINGSHOT      : return "PENETRATINGSHOT";
        case ABILITY_ID::PHASEMINEBLAST       : return "PHASEMINEBLAST";
        case ABILITY_ID::PHASESHIFT           : return "PHASESHIFT";
        case ABILITY_ID::PHASINGMODE_CANCEL   : return "PHASINGMODE_CANCEL";
        case ABILITY_ID::PICKUP               : return "PICKUP";
        case ABILITY_ID::PICKUPARCADE_PICKUP  : return "PICKUPARCADE_PICKUP";
        case ABILITY_ID::PICKUPGAS100         : return "PICKUPGAS100";
        case ABILITY_ID::PICKUPMINERALS100    : return "PICKUPMINERALS100";
        case ABILITY_ID::PICKUPPALLETGAS      : return "PICKUPPALLETGAS";
        case ABILITY_ID::PICKUPPALLETMINERALS : return "PICKUPPALLETMINERALS";
        case ABILITY_ID::PICKUPSCRAPLARGE     : return "PICKUPSCRAPLARGE";
        case ABILITY_ID::PICKUPSCRAPMEDIUM    : return "PICKUPSCRAPMEDIUM";
        case ABILITY_ID::PICKUPSCRAPSMALL     : return "PICKUPSCRAPSMALL";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITE10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITE10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITE10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITE12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITE12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITE12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITE8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITE8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITE8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITN10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITN10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITN10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITN10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITN12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITN12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITN12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITN12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITN8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITN8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITN8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITN8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNE10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITNE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNE10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITNE10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNE12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITNE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNE12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITNE12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNE8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITNE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNE8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITNE8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNW10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITNW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNW10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITNW10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNW12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITNW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNW12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITNW12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNW8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITNW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITNW8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITNW8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITS10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITS10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITS10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITS10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITS12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITS12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITS12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITS12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITS8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITS8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITS8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITS8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSE10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITSE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSE10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITSE10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSE12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITSE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSE12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITSE12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSE8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITSE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSE8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITSE8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSW10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITSW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSW10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITSW10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSW12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITSW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSW12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITSW12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSW8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITSW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITSW8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITSW8_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITW10OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITW10_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITW10_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITW12OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITW12_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITW12_BRIDGERETRACT";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITW8OUT_BRIDGEEXTEND :
            return "PORTCITY_BRIDGE_UNITW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::PORTCITY_BRIDGE_UNITW8_BRIDGERETRACT :
            return "PORTCITY_BRIDGE_UNITW8_BRIDGERETRACT";
        case ABILITY_ID::PROTOSSBUILDINGQUEUE_CANCELSLOT :
            return "PROTOSSBUILDINGQUEUE_CANCELSLOT";
        case ABILITY_ID::PSIONICSHOCKWAVE : return "PSIONICSHOCKWAVE";
        case ABILITY_ID::PSYTROUSOXIDE_PSYTROUSOXIDEOFF :
            return "PSYTROUSOXIDE_PSYTROUSOXIDEOFF";
        case ABILITY_ID::PSYTROUSOXIDE_PSYTROUSOXIDEON :
            return "PSYTROUSOXIDE_PSYTROUSOXIDEON";
        case ABILITY_ID::PULSARBEAM_RIPFIELD : return "PULSARBEAM_RIPFIELD";
        case ABILITY_ID::PULSARCANNON        : return "PULSARCANNON";
        case ABILITY_ID::PURIFICATIONNOVA    : return "PURIFICATIONNOVA";
        case ABILITY_ID::PURIFICATIONNOVAMORPHBACK_PURIFICATIONNOVA :
            return "PURIFICATIONNOVAMORPHBACK_PURIFICATIONNOVA";
        case ABILITY_ID::PURIFICATIONNOVAMORPH_PURIFICATIONNOVA :
            return "PURIFICATIONNOVAMORPH_PURIFICATIONNOVA";
        case ABILITY_ID::PURIFIERPLANETCRACKER_PLANETCRACKER :
            return "PURIFIERPLANETCRACKER_PLANETCRACKER";
        case ABILITY_ID::PURIFIERTOGGLEPOWER_PURIFIERPOWERDOWN :
            return "PURIFIERTOGGLEPOWER_PURIFIERPOWERDOWN";
        case ABILITY_ID::PURIFIERTOGGLEPOWER_PURIFIERPOWERUP :
            return "PURIFIERTOGGLEPOWER_PURIFIERPOWERUP";
        case ABILITY_ID::PURIFYMORPHPYLONBACK_MOTHERSHIPCOREWEAPON :
            return "PURIFYMORPHPYLONBACK_MOTHERSHIPCOREWEAPON";
        case ABILITY_ID::PURIFYMORPHPYLON_MOTHERSHIPCOREWEAPON :
            return "PURIFYMORPHPYLON_MOTHERSHIPCOREWEAPON";
        case ABILITY_ID::QUE5LONGBLEND_CANCEL : return "QUE5LONGBLEND_CANCEL";
        case ABILITY_ID::QUE5LONGBLEND_CANCELSLOT :
            return "QUE5LONGBLEND_CANCELSLOT";
        case ABILITY_ID::QUE8_CANCEL       : return "QUE8_CANCEL";
        case ABILITY_ID::QUE8_CANCELSLOT   : return "QUE8_CANCELSLOT";
        case ABILITY_ID::QUEENBUILD_CANCEL : return "QUEENBUILD_CANCEL";
        case ABILITY_ID::QUEENFLY          : return "QUEENFLY";
        case ABILITY_ID::QUEENLAND         : return "QUEENLAND";
        case ABILITY_ID::QUEENMPENSNARE    : return "QUEENMPENSNARE";
        case ABILITY_ID::QUEENMPINFESTCOMMANDCENTER :
            return "QUEENMPINFESTCOMMANDCENTER";
        case ABILITY_ID::QUEENMPSPAWNBROODLINGS :
            return "QUEENMPSPAWNBROODLINGS";
        case ABILITY_ID::QUEENSHOCKWAVE       : return "QUEENSHOCKWAVE";
        case ABILITY_ID::RALLY_BUILDING       : return "RALLY_BUILDING";
        case ABILITY_ID::RALLY_COMMANDCENTER  : return "RALLY_COMMANDCENTER";
        case ABILITY_ID::RALLY_HATCHERY_UNITS : return "RALLY_HATCHERY_UNITS";
        case ABILITY_ID::RALLY_HATCHERY_WORKERS :
            return "RALLY_HATCHERY_WORKERS";
        case ABILITY_ID::RALLY_MORPHING_UNIT : return "RALLY_MORPHING_UNIT";
        case ABILITY_ID::RALLY_NEXUS         : return "RALLY_NEXUS";
        case ABILITY_ID::RALLY_UNITS         : return "RALLY_UNITS";
        case ABILITY_ID::RALLY_WORKERS       : return "RALLY_WORKERS";
        case ABILITY_ID::RAVENBUILD_CANCEL   : return "RAVENBUILD_CANCEL";
        case ABILITY_ID::RAYNORC4_PLANTC4CHARGE :
            return "RAYNORC4_PLANTC4CHARGE";
        case ABILITY_ID::RAYNORSNIPE : return "RAYNORSNIPE";
        case ABILITY_ID::REDSTONELAVACRITTERBURROW_BURROWDOWN :
            return "REDSTONELAVACRITTERBURROW_BURROWDOWN";
        case ABILITY_ID::REDSTONELAVACRITTERINJUREDBURROW_BURROWDOWN :
            return "REDSTONELAVACRITTERINJUREDBURROW_BURROWDOWN";
        case ABILITY_ID::REDSTONELAVACRITTERINJUREDUNBURROW_BURROWUP :
            return "REDSTONELAVACRITTERINJUREDUNBURROW_BURROWUP";
        case ABILITY_ID::REDSTONELAVACRITTERUNBURROW_BURROWUP :
            return "REDSTONELAVACRITTERUNBURROW_BURROWUP";
        case ABILITY_ID::REFINERYTOAUTOMATEDREFINERY_RAISE :
            return "REFINERYTOAUTOMATEDREFINERY_RAISE";
        case ABILITY_ID::RELEASEINTERCEPTORS : return "RELEASEINTERCEPTORS";
        case ABILITY_ID::RELEASEMINION       : return "RELEASEMINION";
        case ABILITY_ID::RESEARCHLABTRANSPORT_HUTLOAD :
            return "RESEARCHLABTRANSPORT_HUTLOAD";
        case ABILITY_ID::RESEARCHLABTRANSPORT_HUTUNLOADALL :
            return "RESEARCHLABTRANSPORT_HUTUNLOADALL";
        case ABILITY_ID::RESEARCH_ADAPTIVETALONS :
            return "RESEARCH_ADAPTIVETALONS";
        case ABILITY_ID::RESEARCH_ADEPTRESONATINGGLAIVES :
            return "RESEARCH_ADEPTRESONATINGGLAIVES";
        case ABILITY_ID::RESEARCH_ADVANCEDBALLISTICS :
            return "RESEARCH_ADVANCEDBALLISTICS";
        case ABILITY_ID::RESEARCH_AMPLIFIEDSHIELDING :
            return "RESEARCH_AMPLIFIEDSHIELDING";
        case ABILITY_ID::RESEARCH_ANABOLICSYNTHESIS :
            return "RESEARCH_ANABOLICSYNTHESIS";
        case ABILITY_ID::RESEARCH_ARMORPIERCINGROCKETS :
            return "RESEARCH_ARMORPIERCINGROCKETS";
        case ABILITY_ID::RESEARCH_BALLISTICRANGE :
            return "RESEARCH_BALLISTICRANGE";
        case ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD :
            return "RESEARCH_BANSHEECLOAKINGFIELD";
        case ABILITY_ID::RESEARCH_BANSHEEHYPERFLIGHTROTORS :
            return "RESEARCH_BANSHEEHYPERFLIGHTROTORS";
        case ABILITY_ID::RESEARCH_BATTLECRUISERWEAPONREFIT :
            return "RESEARCH_BATTLECRUISERWEAPONREFIT";
        case ABILITY_ID::RESEARCH_BLINK  : return "RESEARCH_BLINK";
        case ABILITY_ID::RESEARCH_BURROW : return "RESEARCH_BURROW";
        case ABILITY_ID::RESEARCH_CENTRIFUGALHOOKS :
            return "RESEARCH_CENTRIFUGALHOOKS";
        case ABILITY_ID::RESEARCH_CHARGE : return "RESEARCH_CHARGE";
        case ABILITY_ID::RESEARCH_CHITINOUSPLATING :
            return "RESEARCH_CHITINOUSPLATING";
        case ABILITY_ID::RESEARCH_COMBATSHIELD : return "RESEARCH_COMBATSHIELD";
        case ABILITY_ID::RESEARCH_CONCUSSIVESHELLS :
            return "RESEARCH_CONCUSSIVESHELLS";
        case ABILITY_ID::RESEARCH_CYCLONELOCKONDAMAGE :
            return "RESEARCH_CYCLONELOCKONDAMAGE";
        case ABILITY_ID::RESEARCH_CYCLONERAPIDFIRELAUNCHERS :
            return "RESEARCH_CYCLONERAPIDFIRELAUNCHERS";
        case ABILITY_ID::RESEARCH_CYCLONERESEARCHHURRICANETHRUSTERS :
            return "RESEARCH_CYCLONERESEARCHHURRICANETHRUSTERS";
        case ABILITY_ID::RESEARCH_DRILLINGCLAWS :
            return "RESEARCH_DRILLINGCLAWS";
        case ABILITY_ID::RESEARCH_DURABLEMATERIALS :
            return "RESEARCH_DURABLEMATERIALS";
        case ABILITY_ID::RESEARCH_ENHANCEDMUNITIONS :
            return "RESEARCH_ENHANCEDMUNITIONS";
        case ABILITY_ID::RESEARCH_EVOLVEAMORPHOUSARMORCLOUD :
            return "RESEARCH_EVOLVEAMORPHOUSARMORCLOUD";
        case ABILITY_ID::RESEARCH_EVOLVEVENTRALSACKS :
            return "RESEARCH_EVOLVEVENTRALSACKS";
        case ABILITY_ID::RESEARCH_EXTENDEDTHERMALLANCE :
            return "RESEARCH_EXTENDEDTHERMALLANCE";
        case ABILITY_ID::RESEARCH_GLIALREGENERATION :
            return "RESEARCH_GLIALREGENERATION";
        case ABILITY_ID::RESEARCH_GRAVITICBOOSTER :
            return "RESEARCH_GRAVITICBOOSTER";
        case ABILITY_ID::RESEARCH_GRAVITICDRIVE :
            return "RESEARCH_GRAVITICDRIVE";
        case ABILITY_ID::RESEARCH_GROOVEDSPINES :
            return "RESEARCH_GROOVEDSPINES";
        case ABILITY_ID::RESEARCH_HALLUCINATION :
            return "RESEARCH_HALLUCINATION";
        case ABILITY_ID::RESEARCH_HIGHCAPACITYFUELTANKS :
            return "RESEARCH_HIGHCAPACITYFUELTANKS";
        case ABILITY_ID::RESEARCH_HISECAUTOTRACKING :
            return "RESEARCH_HISECAUTOTRACKING";
        case ABILITY_ID::RESEARCH_IMMORTALREVIVE :
            return "RESEARCH_IMMORTALREVIVE";
        case ABILITY_ID::RESEARCH_INFERNALPREIGNITER :
            return "RESEARCH_INFERNALPREIGNITER";
        case ABILITY_ID::RESEARCH_INTERCEPTORGRAVITONCATAPULT :
            return "RESEARCH_INTERCEPTORGRAVITONCATAPULT";
        case ABILITY_ID::RESEARCH_INTERCEPTORLAUNCHSPEEDUPGRADE :
            return "RESEARCH_INTERCEPTORLAUNCHSPEEDUPGRADE";
        case ABILITY_ID::RESEARCH_LIBERATORAGMODE :
            return "RESEARCH_LIBERATORAGMODE";
        case ABILITY_ID::RESEARCH_LOCKONRANGEUPGRADE :
            return "RESEARCH_LOCKONRANGEUPGRADE";
        case ABILITY_ID::RESEARCH_LOCUSTLIFETIMEINCREASE :
            return "RESEARCH_LOCUSTLIFETIMEINCREASE";
        case ABILITY_ID::RESEARCH_LURKERRANGE : return "RESEARCH_LURKERRANGE";
        case ABILITY_ID::RESEARCH_MEDIVACENERGYUPGRADE :
            return "RESEARCH_MEDIVACENERGYUPGRADE";
        case ABILITY_ID::RESEARCH_MUSCULARAUGMENTS :
            return "RESEARCH_MUSCULARAUGMENTS";
        case ABILITY_ID::RESEARCH_NEOSTEELFRAME :
            return "RESEARCH_NEOSTEELFRAME";
        case ABILITY_ID::RESEARCH_NEURALPARASITE :
            return "RESEARCH_NEURALPARASITE";
        case ABILITY_ID::RESEARCH_PERSONALCLOAKING :
            return "RESEARCH_PERSONALCLOAKING";
        case ABILITY_ID::RESEARCH_PHOENIXANIONPULSECRYSTALS :
            return "RESEARCH_PHOENIXANIONPULSECRYSTALS";
        case ABILITY_ID::RESEARCH_PNEUMATIZEDCARAPACE :
            return "RESEARCH_PNEUMATIZEDCARAPACE";
        case ABILITY_ID::RESEARCH_PROTOSSAIRARMOR :
            return "RESEARCH_PROTOSSAIRARMOR";
        case ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1 :
            return "RESEARCH_PROTOSSAIRARMORLEVEL1";
        case ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2 :
            return "RESEARCH_PROTOSSAIRARMORLEVEL2";
        case ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3 :
            return "RESEARCH_PROTOSSAIRARMORLEVEL3";
        case ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONS :
            return "RESEARCH_PROTOSSAIRWEAPONS";
        case ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1 :
            return "RESEARCH_PROTOSSAIRWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2 :
            return "RESEARCH_PROTOSSAIRWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3 :
            return "RESEARCH_PROTOSSAIRWEAPONSLEVEL3";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDARMOR :
            return "RESEARCH_PROTOSSGROUNDARMOR";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1 :
            return "RESEARCH_PROTOSSGROUNDARMORLEVEL1";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2 :
            return "RESEARCH_PROTOSSGROUNDARMORLEVEL2";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3 :
            return "RESEARCH_PROTOSSGROUNDARMORLEVEL3";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONS :
            return "RESEARCH_PROTOSSGROUNDWEAPONS";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1 :
            return "RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2 :
            return "RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3 :
            return "RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3";
        case ABILITY_ID::RESEARCH_PROTOSSSHIELDS :
            return "RESEARCH_PROTOSSSHIELDS";
        case ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1 :
            return "RESEARCH_PROTOSSSHIELDSLEVEL1";
        case ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2 :
            return "RESEARCH_PROTOSSSHIELDSLEVEL2";
        case ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3 :
            return "RESEARCH_PROTOSSSHIELDSLEVEL3";
        case ABILITY_ID::RESEARCH_PSIONICAMPLIFIERS :
            return "RESEARCH_PSIONICAMPLIFIERS";
        case ABILITY_ID::RESEARCH_PSIONICSURGE : return "RESEARCH_PSIONICSURGE";
        case ABILITY_ID::RESEARCH_PSISTORM     : return "RESEARCH_PSISTORM";
        case ABILITY_ID::RESEARCH_RAPIDDEPLOYMENT :
            return "RESEARCH_RAPIDDEPLOYMENT";
        case ABILITY_ID::RESEARCH_RAPIDREIGNITIONSYSTEM :
            return "RESEARCH_RAPIDREIGNITIONSYSTEM";
        case ABILITY_ID::RESEARCH_RAVENCORVIDREACTOR :
            return "RESEARCH_RAVENCORVIDREACTOR";
        case ABILITY_ID::RESEARCH_RAVENINTERFERENCEMATRIX :
            return "RESEARCH_RAVENINTERFERENCEMATRIX";
        case ABILITY_ID::RESEARCH_RAVENRECALIBRATEDEXPLOSIVES :
            return "RESEARCH_RAVENRECALIBRATEDEXPLOSIVES";
        case ABILITY_ID::RESEARCH_REAPERSPEED : return "RESEARCH_REAPERSPEED";
        case ABILITY_ID::RESEARCH_ROACHSUPPLY : return "RESEARCH_ROACHSUPPLY";
        case ABILITY_ID::RESEARCH_SEEKERMISSILE :
            return "RESEARCH_SEEKERMISSILE";
        case ABILITY_ID::RESEARCH_SHADOWSTRIKE : return "RESEARCH_SHADOWSTRIKE";
        case ABILITY_ID::RESEARCH_SMARTSERVOS  : return "RESEARCH_SMARTSERVOS";
        case ABILITY_ID::RESEARCH_STIMPACK     : return "RESEARCH_STIMPACK";
        case ABILITY_ID::RESEARCH_TEMPESTRANGEUPGRADE :
            return "RESEARCH_TEMPESTRANGEUPGRADE";
        case ABILITY_ID::RESEARCH_TEMPESTRESEARCHGROUNDATTACKUPGRADE :
            return "RESEARCH_TEMPESTRESEARCHGROUNDATTACKUPGRADE";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYARMOR :
            return "RESEARCH_TERRANINFANTRYARMOR";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1 :
            return "RESEARCH_TERRANINFANTRYARMORLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2 :
            return "RESEARCH_TERRANINFANTRYARMORLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3 :
            return "RESEARCH_TERRANINFANTRYARMORLEVEL3";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONS :
            return "RESEARCH_TERRANINFANTRYWEAPONS";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1 :
            return "RESEARCH_TERRANINFANTRYWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2 :
            return "RESEARCH_TERRANINFANTRYWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3 :
            return "RESEARCH_TERRANINFANTRYWEAPONSLEVEL3";
        case ABILITY_ID::RESEARCH_TERRANSHIPPLATINGLEVEL1 :
            return "RESEARCH_TERRANSHIPPLATINGLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANSHIPPLATINGLEVEL2 :
            return "RESEARCH_TERRANSHIPPLATINGLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANSHIPPLATINGLEVEL3 :
            return "RESEARCH_TERRANSHIPPLATINGLEVEL3";
        case ABILITY_ID::RESEARCH_TERRANSHIPWEAPONS :
            return "RESEARCH_TERRANSHIPWEAPONS";
        case ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1 :
            return "RESEARCH_TERRANSHIPWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2 :
            return "RESEARCH_TERRANSHIPWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3 :
            return "RESEARCH_TERRANSHIPWEAPONSLEVEL3";
        case ABILITY_ID::RESEARCH_TERRANSTRUCTUREARMORUPGRADE :
            return "RESEARCH_TERRANSTRUCTUREARMORUPGRADE";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATING :
            return "RESEARCH_TERRANVEHICLEANDSHIPPLATING";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1 :
            return "RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2 :
            return "RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3 :
            return "RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEPLATINGLEVEL1 :
            return "RESEARCH_TERRANVEHICLEPLATINGLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEPLATINGLEVEL2 :
            return "RESEARCH_TERRANVEHICLEPLATINGLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEPLATINGLEVEL3 :
            return "RESEARCH_TERRANVEHICLEPLATINGLEVEL3";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONS :
            return "RESEARCH_TERRANVEHICLEWEAPONS";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1 :
            return "RESEARCH_TERRANVEHICLEWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2 :
            return "RESEARCH_TERRANVEHICLEWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3 :
            return "RESEARCH_TERRANVEHICLEWEAPONSLEVEL3";
        case ABILITY_ID::RESEARCH_TRANSFORMATIONSERVOS :
            return "RESEARCH_TRANSFORMATIONSERVOS";
        case ABILITY_ID::RESEARCH_TUNNELINGCLAWS :
            return "RESEARCH_TUNNELINGCLAWS";
        case ABILITY_ID::RESEARCH_VOIDRAYSPEEDUPGRADE :
            return "RESEARCH_VOIDRAYSPEEDUPGRADE";
        case ABILITY_ID::RESEARCH_WARPGATE : return "RESEARCH_WARPGATE";
        case ABILITY_ID::RESEARCH_ZERGFLYERARMOR :
            return "RESEARCH_ZERGFLYERARMOR";
        case ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL1 :
            return "RESEARCH_ZERGFLYERARMORLEVEL1";
        case ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL2 :
            return "RESEARCH_ZERGFLYERARMORLEVEL2";
        case ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL3 :
            return "RESEARCH_ZERGFLYERARMORLEVEL3";
        case ABILITY_ID::RESEARCH_ZERGFLYERATTACK :
            return "RESEARCH_ZERGFLYERATTACK";
        case ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL1 :
            return "RESEARCH_ZERGFLYERATTACKLEVEL1";
        case ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL2 :
            return "RESEARCH_ZERGFLYERATTACKLEVEL2";
        case ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL3 :
            return "RESEARCH_ZERGFLYERATTACKLEVEL3";
        case ABILITY_ID::RESEARCH_ZERGGROUNDARMOR :
            return "RESEARCH_ZERGGROUNDARMOR";
        case ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL1 :
            return "RESEARCH_ZERGGROUNDARMORLEVEL1";
        case ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL2 :
            return "RESEARCH_ZERGGROUNDARMORLEVEL2";
        case ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL3 :
            return "RESEARCH_ZERGGROUNDARMORLEVEL3";
        case ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS :
            return "RESEARCH_ZERGLINGADRENALGLANDS";
        case ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST :
            return "RESEARCH_ZERGLINGMETABOLICBOOST";
        case ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS :
            return "RESEARCH_ZERGMELEEWEAPONS";
        case ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1 :
            return "RESEARCH_ZERGMELEEWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2 :
            return "RESEARCH_ZERGMELEEWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3 :
            return "RESEARCH_ZERGMELEEWEAPONSLEVEL3";
        case ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS :
            return "RESEARCH_ZERGMISSILEWEAPONS";
        case ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL1 :
            return "RESEARCH_ZERGMISSILEWEAPONSLEVEL1";
        case ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL2 :
            return "RESEARCH_ZERGMISSILEWEAPONSLEVEL2";
        case ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL3 :
            return "RESEARCH_ZERGMISSILEWEAPONSLEVEL3";
        case ABILITY_ID::RESTORESHIELDS : return "RESTORESHIELDS";
        case ABILITY_ID::ROGUEGHOSTCLOAK_CLOAKOFF :
            return "ROGUEGHOSTCLOAK_CLOAKOFF";
        case ABILITY_ID::ROGUEGHOSTCLOAK_CLOAKONSPECTRE :
            return "ROGUEGHOSTCLOAK_CLOAKONSPECTRE";
        case ABILITY_ID::SALVAGEBANELINGREFUND_SALVAGE :
            return "SALVAGEBANELINGREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEBANELING_SALVAGE :
            return "SALVAGEBANELING_SALVAGE";
        case ABILITY_ID::SALVAGEBUNKERREFUND_SALVAGE :
            return "SALVAGEBUNKERREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEBUNKER_SALVAGE : return "SALVAGEBUNKER_SALVAGE";
        case ABILITY_ID::SALVAGEDRONEREFUND_SALVAGE :
            return "SALVAGEDRONEREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEDRONE_SALVAGE : return "SALVAGEDRONE_SALVAGE";
        case ABILITY_ID::SALVAGEHYDRALISKREFUND_SALVAGE :
            return "SALVAGEHYDRALISKREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEHYDRALISK_SALVAGE :
            return "SALVAGEHYDRALISK_SALVAGE";
        case ABILITY_ID::SALVAGEINFESTORREFUND_SALVAGE :
            return "SALVAGEINFESTORREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEINFESTOR_SALVAGE :
            return "SALVAGEINFESTOR_SALVAGE";
        case ABILITY_ID::SALVAGEQUEENREFUND_SALVAGE :
            return "SALVAGEQUEENREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEQUEEN_SALVAGE : return "SALVAGEQUEEN_SALVAGE";
        case ABILITY_ID::SALVAGEROACHREFUND_SALVAGE :
            return "SALVAGEROACHREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEROACH_SALVAGE : return "SALVAGEROACH_SALVAGE";
        case ABILITY_ID::SALVAGESWARMHOSTREFUND_SALVAGE :
            return "SALVAGESWARMHOSTREFUND_SALVAGE";
        case ABILITY_ID::SALVAGESWARMHOST_SALVAGE :
            return "SALVAGESWARMHOST_SALVAGE";
        case ABILITY_ID::SALVAGEULTRALISKREFUND_SALVAGE :
            return "SALVAGEULTRALISKREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEULTRALISK_SALVAGE :
            return "SALVAGEULTRALISK_SALVAGE";
        case ABILITY_ID::SALVAGEZERGLINGREFUND_SALVAGE :
            return "SALVAGEZERGLINGREFUND_SALVAGE";
        case ABILITY_ID::SALVAGEZERGLING_SALVAGE :
            return "SALVAGEZERGLING_SALVAGE";
        case ABILITY_ID::SAPSTRUCTURE : return "SAPSTRUCTURE";
        case ABILITY_ID::SCRYER       : return "SCRYER";
        case ABILITY_ID::SECURITYGATEDIAGONALBLURLOWERED_GATEOPEN :
            return "SECURITYGATEDIAGONALBLURLOWERED_GATEOPEN";
        case ABILITY_ID::SECURITYGATEDIAGONALBLUR_GATECLOSE :
            return "SECURITYGATEDIAGONALBLUR_GATECLOSE";
        case ABILITY_ID::SECURITYGATEDIAGONALULBRLOWERED_GATEOPEN :
            return "SECURITYGATEDIAGONALULBRLOWERED_GATEOPEN";
        case ABILITY_ID::SECURITYGATEDIAGONALULBR_GATECLOSE :
            return "SECURITYGATEDIAGONALULBR_GATECLOSE";
        case ABILITY_ID::SECURITYGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN :
            return "SECURITYGATESTRAIGHTHORIZONTALBFLOWERED_GATEOPEN";
        case ABILITY_ID::SECURITYGATESTRAIGHTHORIZONTALBF_GATECLOSE :
            return "SECURITYGATESTRAIGHTHORIZONTALBF_GATECLOSE";
        case ABILITY_ID::SECURITYGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN :
            return "SECURITYGATESTRAIGHTHORIZONTALLOWERED_GATEOPEN";
        case ABILITY_ID::SECURITYGATESTRAIGHTHORIZONTAL_GATECLOSE :
            return "SECURITYGATESTRAIGHTHORIZONTAL_GATECLOSE";
        case ABILITY_ID::SECURITYGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN :
            return "SECURITYGATESTRAIGHTVERTICALLFLOWERED_GATEOPEN";
        case ABILITY_ID::SECURITYGATESTRAIGHTVERTICALLF_GATECLOSE :
            return "SECURITYGATESTRAIGHTVERTICALLF_GATECLOSE";
        case ABILITY_ID::SECURITYGATESTRAIGHTVERTICALLOWERED_GATEOPEN :
            return "SECURITYGATESTRAIGHTVERTICALLOWERED_GATEOPEN";
        case ABILITY_ID::SECURITYGATESTRAIGHTVERTICAL_GATECLOSE :
            return "SECURITYGATESTRAIGHTVERTICAL_GATECLOSE";
        case ABILITY_ID::SELENDISHANGAR_INTERCEPTOR :
            return "SELENDISHANGAR_INTERCEPTOR";
        case ABILITY_ID::SELFREPAIR        : return "SELFREPAIR";
        case ABILITY_ID::SELFREPAIR_CANCEL : return "SELFREPAIR_CANCEL";
        case ABILITY_ID::SENTRYGUNBURROW_BURROWTURRET :
            return "SENTRYGUNBURROW_BURROWTURRET";
        case ABILITY_ID::SENTRYGUNUNBURROW_UNBURROWTURRET :
            return "SENTRYGUNUNBURROW_UNBURROWTURRET";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENE10OUT_BRIDGEEXTEND :
            return "SHAKURASLIGHTBRIDGENE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENE10_BRIDGERETRACT :
            return "SHAKURASLIGHTBRIDGENE10_BRIDGERETRACT";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENE12OUT_BRIDGEEXTEND :
            return "SHAKURASLIGHTBRIDGENE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENE12_BRIDGERETRACT :
            return "SHAKURASLIGHTBRIDGENE12_BRIDGERETRACT";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENE8OUT_BRIDGEEXTEND :
            return "SHAKURASLIGHTBRIDGENE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENE8_BRIDGERETRACT :
            return "SHAKURASLIGHTBRIDGENE8_BRIDGERETRACT";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENW10OUT_BRIDGEEXTEND :
            return "SHAKURASLIGHTBRIDGENW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENW10_BRIDGERETRACT :
            return "SHAKURASLIGHTBRIDGENW10_BRIDGERETRACT";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENW12OUT_BRIDGEEXTEND :
            return "SHAKURASLIGHTBRIDGENW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENW12_BRIDGERETRACT :
            return "SHAKURASLIGHTBRIDGENW12_BRIDGERETRACT";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENW8OUT_BRIDGEEXTEND :
            return "SHAKURASLIGHTBRIDGENW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::SHAKURASLIGHTBRIDGENW8_BRIDGERETRACT :
            return "SHAKURASLIGHTBRIDGENW8_BRIDGERETRACT";
        case ABILITY_ID::SHIELDBATTERYRECHARGEEX5_SHIELDBATTERYRECHARGE :
            return "SHIELDBATTERYRECHARGEEX5_SHIELDBATTERYRECHARGE";
        case ABILITY_ID::SHIELDBATTERYRECHARGEEX5_STOP :
            return "SHIELDBATTERYRECHARGEEX5_STOP";
        case ABILITY_ID::SINGLERECALL       : return "SINGLERECALL";
        case ABILITY_ID::SIPHON             : return "SIPHON";
        case ABILITY_ID::SIPHON_CANCEL      : return "SIPHON_CANCEL";
        case ABILITY_ID::SLAYNELEMENTALGRAB : return "SLAYNELEMENTALGRAB";
        case ABILITY_ID::SMART              : return "SMART";
        case ABILITY_ID::SNIPE              : return "SNIPE";
        case ABILITY_ID::SNIPEDOT           : return "SNIPEDOT";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT10OUT_BRIDGEEXTEND :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT10OUT_"
                   "BRIDGEEXTEND";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT10_BRIDGERETRACT :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT10_BRIDGERETRACT";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT_BRIDGEEXTEND :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT_"
                   "BRIDGEEXTEND";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8_BRIDGERETRACT :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8_BRIDGERETRACT";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT10OUT_BRIDGEEXTEND :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT10OUT_"
                   "BRIDGEEXTEND";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT10_BRIDGERETRACT :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT10_BRIDGERETRACT";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT_BRIDGEEXTEND :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT_"
                   "BRIDGEEXTEND";
        case ABILITY_ID::
            SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8_BRIDGERETRACT :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8_BRIDGERETRACT";
        case ABILITY_ID::SOULCHANNEL_CANCEL : return "SOULCHANNEL_CANCEL";
        case ABILITY_ID::SPAWNINFESTEDTERRAN_LOCUSTMP :
            return "SPAWNINFESTEDTERRAN_LOCUSTMP";
        case ABILITY_ID::SPECOPSDROPSHIPTRANSPORT_MEDIVACLOAD :
            return "SPECOPSDROPSHIPTRANSPORT_MEDIVACLOAD";
        case ABILITY_ID::SPECOPSDROPSHIPTRANSPORT_MEDIVACUNLOADALL :
            return "SPECOPSDROPSHIPTRANSPORT_MEDIVACUNLOADALL";
        case ABILITY_ID::SPECTREHOLDFIRE : return "SPECTREHOLDFIRE";
        case ABILITY_ID::SPECTRENUKESILOARMMAGAZINE_SPECTRENUKEARM :
            return "SPECTRENUKESILOARMMAGAZINE_SPECTRENUKEARM";
        case ABILITY_ID::SPECTRENUKE_CANCEL : return "SPECTRENUKE_CANCEL";
        case ABILITY_ID::SPECTRENUKE_SPECTRENUKECALLDOWN :
            return "SPECTRENUKE_SPECTRENUKECALLDOWN";
        case ABILITY_ID::SPECTRESHIELD : return "SPECTRESHIELD";
        case ABILITY_ID::SPECTREWEAPONSFREE_WEAPONSFREE :
            return "SPECTREWEAPONSFREE_WEAPONSFREE";
        case ABILITY_ID::SPINECRAWLERUPROOT_CANCEL :
            return "SPINECRAWLERUPROOT_CANCEL";
        case ABILITY_ID::SPORECRAWLERUPROOT_CANCEL :
            return "SPORECRAWLERUPROOT_CANCEL";
        case ABILITY_ID::SS_BATTLECRUISERHUNTERSEEKERATTACK_SS_SHOOTING :
            return "SS_BATTLECRUISERHUNTERSEEKERATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_BATTLECRUISERMISSILEATTACK_SS_SHOOTING :
            return "SS_BATTLECRUISERMISSILEATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_CARRIERBOSSATTACKLAUNCH_SS_SHOOTING :
            return "SS_CARRIERBOSSATTACKLAUNCH_SS_SHOOTING";
        case ABILITY_ID::SS_CARRIERBOSSATTACKTARGET_SS_SHOOTING :
            return "SS_CARRIERBOSSATTACKTARGET_SS_SHOOTING";
        case ABILITY_ID::SS_CARRIERSPAWNINTERCEPTOR :
            return "SS_CARRIERSPAWNINTERCEPTOR";
        case ABILITY_ID::SS_CORRUPTORATTACK_SS_SHOOTING :
            return "SS_CORRUPTORATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_FIGHTERBOMB : return "SS_FIGHTERBOMB";
        case ABILITY_ID::SS_FIGHTERSHOOTING_SS_SHOOTING :
            return "SS_FIGHTERSHOOTING_SS_SHOOTING";
        case ABILITY_ID::SS_INTERCEPTORATTACK_SS_SHOOTING :
            return "SS_INTERCEPTORATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_LEVIATHANSPAWNBOMBS :
            return "SS_LEVIATHANSPAWNBOMBS";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKL1 :
            return "SS_LEVIATHANTENTACLEATTACKL1";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKL1NODELAY :
            return "SS_LEVIATHANTENTACLEATTACKL1NODELAY";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKL2 :
            return "SS_LEVIATHANTENTACLEATTACKL2";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKL2NODELAY :
            return "SS_LEVIATHANTENTACLEATTACKL2NODELAY";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKR1 :
            return "SS_LEVIATHANTENTACLEATTACKR1";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKR1NODELAY :
            return "SS_LEVIATHANTENTACLEATTACKR1NODELAY";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKR2 :
            return "SS_LEVIATHANTENTACLEATTACKR2";
        case ABILITY_ID::SS_LEVIATHANTENTACLEATTACKR2NODELAY :
            return "SS_LEVIATHANTENTACLEATTACKR2NODELAY";
        case ABILITY_ID::SS_PHOENIXSHOOTING_SS_SHOOTING :
            return "SS_PHOENIXSHOOTING_SS_SHOOTING";
        case ABILITY_ID::SS_SCIENCEVESSELATTACK_SS_SHOOTING :
            return "SS_SCIENCEVESSELATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_SCIENCEVESSELTELEPORT_ZERATULBLINK :
            return "SS_SCIENCEVESSELTELEPORT_ZERATULBLINK";
        case ABILITY_ID::SS_SCOUTATTACK_SS_SHOOTING :
            return "SS_SCOUTATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_SWARMGUARDIANATTACK_SS_SHOOTING :
            return "SS_SWARMGUARDIANATTACK_SS_SHOOTING";
        case ABILITY_ID::SS_TERRATRONBEAMATTACK :
            return "SS_TERRATRONBEAMATTACK";
        case ABILITY_ID::SS_TERRATRONSAWATTACK : return "SS_TERRATRONSAWATTACK";
        case ABILITY_ID::SS_WRAITHATTACK_SS_SHOOTING :
            return "SS_WRAITHATTACK_SS_SHOOTING";
        case ABILITY_ID::STARPORTREACTORMORPH_REACTOR :
            return "STARPORTREACTORMORPH_REACTOR";
        case ABILITY_ID::STARPORTTECHLABMORPH_TECHLABSTARPORT :
            return "STARPORTTECHLABMORPH_TECHLABSTARPORT";
        case ABILITY_ID::STARPORTTECHREACTORMORPH_TECHLABSTARPORT :
            return "STARPORTTECHREACTORMORPH_TECHLABSTARPORT";
        case ABILITY_ID::STARTCOLONISTVEHICLE : return "STARTCOLONISTVEHICLE";
        case ABILITY_ID::STOP                 : return "STOP";
        case ABILITY_ID::STOPPROTOSSBUILDING_CHEER :
            return "STOPPROTOSSBUILDING_CHEER";
        case ABILITY_ID::STOPPROTOSSBUILDING_DANCE :
            return "STOPPROTOSSBUILDING_DANCE";
        case ABILITY_ID::STOPPROTOSSBUILDING_HOLDFIRE :
            return "STOPPROTOSSBUILDING_HOLDFIRE";
        case ABILITY_ID::STOP_BATTLECRUISER   : return "STOP_BATTLECRUISER";
        case ABILITY_ID::STOP_BUILDING        : return "STOP_BUILDING";
        case ABILITY_ID::STOP_CHEER           : return "STOP_CHEER";
        case ABILITY_ID::STOP_DANCE           : return "STOP_DANCE";
        case ABILITY_ID::STOP_HOLDFIRESPECIAL : return "STOP_HOLDFIRESPECIAL";
        case ABILITY_ID::STOP_REDIRECT        : return "STOP_REDIRECT";
        case ABILITY_ID::STOP_STOP            : return "STOP_STOP";
        case ABILITY_ID::SUMMONMERCENARIESPH_HIREKELMORIANMINERSPH :
            return "SUMMONMERCENARIESPH_HIREKELMORIANMINERSPH";
        case ABILITY_ID::SUMMONMERCENARIES_HIREDEVILDOGS :
            return "SUMMONMERCENARIES_HIREDEVILDOGS";
        case ABILITY_ID::SUMMONMERCENARIES_HIREDUKESREVENGE :
            return "SUMMONMERCENARIES_HIREDUKESREVENGE";
        case ABILITY_ID::SUMMONMERCENARIES_HIREDUSKWING :
            return "SUMMONMERCENARIES_HIREDUSKWING";
        case ABILITY_ID::SUMMONMERCENARIES_HIREHAMMERSECURITIES :
            return "SUMMONMERCENARIES_HIREHAMMERSECURITIES";
        case ABILITY_ID::SUMMONMERCENARIES_HIREHELSANGELS :
            return "SUMMONMERCENARIES_HIREHELSANGELS";
        case ABILITY_ID::SUMMONMERCENARIES_HIREKELMORIANMINERS :
            return "SUMMONMERCENARIES_HIREKELMORIANMINERS";
        case ABILITY_ID::SUMMONMERCENARIES_HIRESIEGEBREAKERS :
            return "SUMMONMERCENARIES_HIRESIEGEBREAKERS";
        case ABILITY_ID::SUMMONMERCENARIES_HIRESPARTANCOMPANY :
            return "SUMMONMERCENARIES_HIRESPARTANCOMPANY";
        case ABILITY_ID::SWARMHOSTSPAWNLOCUSTS_LOCUSTMP :
            return "SWARMHOSTSPAWNLOCUSTS_LOCUSTMP";
        case ABILITY_ID::TALDARIMVORTEX_VORTEX : return "TALDARIMVORTEX_VORTEX";
        case ABILITY_ID::TAUNT                 : return "TAUNT";
        case ABILITY_ID::TAURENOUTHOUSELIFTOFF_TAURENOUTHOUSEFLY :
            return "TAURENOUTHOUSELIFTOFF_TAURENOUTHOUSEFLY";
        case ABILITY_ID::TAURENOUTHOUSETRANSPORT_LOADTAURENOUTHOUSE :
            return "TAURENOUTHOUSETRANSPORT_LOADTAURENOUTHOUSE";
        case ABILITY_ID::TAURENOUTHOUSETRANSPORT_UNLOADTAURENOUTHOUSE :
            return "TAURENOUTHOUSETRANSPORT_UNLOADTAURENOUTHOUSE";
        case ABILITY_ID::TAURENSTIMPACK_STIM : return "TAURENSTIMPACK_STIM";
        case ABILITY_ID::TEMPLEDOORDOWN      : return "TEMPLEDOORDOWN";
        case ABILITY_ID::TEMPLEDOORDOWNURDL  : return "TEMPLEDOORDOWNURDL";
        case ABILITY_ID::TEMPLEDOORUP        : return "TEMPLEDOORUP";
        case ABILITY_ID::TEMPLEDOORUPURDL    : return "TEMPLEDOORUPURDL";
        case ABILITY_ID::TEMPORALRIFT        : return "TEMPORALRIFT";
        case ABILITY_ID::TERRANBUILDDROP_CANCEL :
            return "TERRANBUILDDROP_CANCEL";
        case ABILITY_ID::TERRANBUILDDROP_SUPPLYDEPOTDROP :
            return "TERRANBUILDDROP_SUPPLYDEPOTDROP";
        case ABILITY_ID::TESTHERODEBUGMISSILEABILITY :
            return "TESTHERODEBUGMISSILEABILITY";
        case ABILITY_ID::TESTHERODEBUGTRACKINGABILITY :
            return "TESTHERODEBUGTRACKINGABILITY";
        case ABILITY_ID::TESTHERODEBUGTRACKINGABILITY_CANCEL :
            return "TESTHERODEBUGTRACKINGABILITY_CANCEL";
        case ABILITY_ID::TESTHEROGRAB_GRABZERGLING :
            return "TESTHEROGRAB_GRABZERGLING";
        case ABILITY_ID::TESTHEROTHROW_THROWZERGLING :
            return "TESTHEROTHROW_THROWZERGLING";
        case ABILITY_ID::TESTINTERACT_DESIGNATE :
            return "TESTINTERACT_DESIGNATE";
        case ABILITY_ID::TESTLEARN             : return "TESTLEARN";
        case ABILITY_ID::TESTREVIVE_SCV        : return "TESTREVIVE_SCV";
        case ABILITY_ID::TESTZERG_CANCEL       : return "TESTZERG_CANCEL";
        case ABILITY_ID::THEMOROSDEVICE        : return "THEMOROSDEVICE";
        case ABILITY_ID::THORAPMODE_CANCEL     : return "THORAPMODE_CANCEL";
        case ABILITY_ID::THORREBORN_CANCEL     : return "THORREBORN_CANCEL";
        case ABILITY_ID::THORREBORN_THOR       : return "THORREBORN_THOR";
        case ABILITY_ID::THORWRECKAGE_THOR     : return "THORWRECKAGE_THOR";
        case ABILITY_ID::TIMESTOP              : return "TIMESTOP";
        case ABILITY_ID::TIMESTOP_CANCEL       : return "TIMESTOP_CANCEL";
        case ABILITY_ID::TORNADOMISSILE        : return "TORNADOMISSILE";
        case ABILITY_ID::TOSSGRENADE           : return "TOSSGRENADE";
        case ABILITY_ID::TRAINWARP_ADEPT       : return "TRAINWARP_ADEPT";
        case ABILITY_ID::TRAINWARP_DARKTEMPLAR : return "TRAINWARP_DARKTEMPLAR";
        case ABILITY_ID::TRAINWARP_HIGHTEMPLAR : return "TRAINWARP_HIGHTEMPLAR";
        case ABILITY_ID::TRAINWARP_SENTRY      : return "TRAINWARP_SENTRY";
        case ABILITY_ID::TRAINWARP_STALKER     : return "TRAINWARP_STALKER";
        case ABILITY_ID::TRAINWARP_ZEALOT      : return "TRAINWARP_ZEALOT";
        case ABILITY_ID::TRAIN_ADEPT           : return "TRAIN_ADEPT";
        case ABILITY_ID::TRAIN_ARCHON          : return "TRAIN_ARCHON";
        case ABILITY_ID::TRAIN_BANSHEE         : return "TRAIN_BANSHEE";
        case ABILITY_ID::TRAIN_BATTLECRUISER   : return "TRAIN_BATTLECRUISER";
        case ABILITY_ID::TRAIN_CARRIER         : return "TRAIN_CARRIER";
        case ABILITY_ID::TRAIN_COLOSSUS        : return "TRAIN_COLOSSUS";
        case ABILITY_ID::TRAIN_CORRUPTOR       : return "TRAIN_CORRUPTOR";
        case ABILITY_ID::TRAIN_CYCLONE         : return "TRAIN_CYCLONE";
        case ABILITY_ID::TRAIN_DARKTEMPLAR     : return "TRAIN_DARKTEMPLAR";
        case ABILITY_ID::TRAIN_DISRUPTOR       : return "TRAIN_DISRUPTOR";
        case ABILITY_ID::TRAIN_DRONE           : return "TRAIN_DRONE";
        case ABILITY_ID::TRAIN_GHOST           : return "TRAIN_GHOST";
        case ABILITY_ID::TRAIN_HELLBAT         : return "TRAIN_HELLBAT";
        case ABILITY_ID::TRAIN_HELLION         : return "TRAIN_HELLION";
        case ABILITY_ID::TRAIN_HIGHTEMPLAR     : return "TRAIN_HIGHTEMPLAR";
        case ABILITY_ID::TRAIN_HYDRALISK       : return "TRAIN_HYDRALISK";
        case ABILITY_ID::TRAIN_IMMORTAL        : return "TRAIN_IMMORTAL";
        case ABILITY_ID::TRAIN_INFESTEDABOMINATION :
            return "TRAIN_INFESTEDABOMINATION";
        case ABILITY_ID::TRAIN_INFESTEDCIVILIAN :
            return "TRAIN_INFESTEDCIVILIAN";
        case ABILITY_ID::TRAIN_INFESTEDTERRANCAMPAIGN :
            return "TRAIN_INFESTEDTERRANCAMPAIGN";
        case ABILITY_ID::TRAIN_INFESTOR       : return "TRAIN_INFESTOR";
        case ABILITY_ID::TRAIN_LIBERATOR      : return "TRAIN_LIBERATOR";
        case ABILITY_ID::TRAIN_MARAUDER       : return "TRAIN_MARAUDER";
        case ABILITY_ID::TRAIN_MARINE         : return "TRAIN_MARINE";
        case ABILITY_ID::TRAIN_MEDIVAC        : return "TRAIN_MEDIVAC";
        case ABILITY_ID::TRAIN_MOTHERSHIP     : return "TRAIN_MOTHERSHIP";
        case ABILITY_ID::TRAIN_MOTHERSHIPCORE : return "TRAIN_MOTHERSHIPCORE";
        case ABILITY_ID::TRAIN_MUTALISK       : return "TRAIN_MUTALISK";
        case ABILITY_ID::TRAIN_OBSERVER       : return "TRAIN_OBSERVER";
        case ABILITY_ID::TRAIN_ORACLE         : return "TRAIN_ORACLE";
        case ABILITY_ID::TRAIN_OVERLORD       : return "TRAIN_OVERLORD";
        case ABILITY_ID::TRAIN_PHOENIX        : return "TRAIN_PHOENIX";
        case ABILITY_ID::TRAIN_PROBE          : return "TRAIN_PROBE";
        case ABILITY_ID::TRAIN_QUEEN          : return "TRAIN_QUEEN";
        case ABILITY_ID::TRAIN_RAVEN          : return "TRAIN_RAVEN";
        case ABILITY_ID::TRAIN_REAPER         : return "TRAIN_REAPER";
        case ABILITY_ID::TRAIN_ROACH          : return "TRAIN_ROACH";
        case ABILITY_ID::TRAIN_SCV            : return "TRAIN_SCV";
        case ABILITY_ID::TRAIN_SENTRY         : return "TRAIN_SENTRY";
        case ABILITY_ID::TRAIN_SIEGETANK      : return "TRAIN_SIEGETANK";
        case ABILITY_ID::TRAIN_STALKER        : return "TRAIN_STALKER";
        case ABILITY_ID::TRAIN_SWARMHOST      : return "TRAIN_SWARMHOST";
        case ABILITY_ID::TRAIN_TEMPEST        : return "TRAIN_TEMPEST";
        case ABILITY_ID::TRAIN_THOR           : return "TRAIN_THOR";
        case ABILITY_ID::TRAIN_ULTRALISK      : return "TRAIN_ULTRALISK";
        case ABILITY_ID::TRAIN_VIKINGFIGHTER  : return "TRAIN_VIKINGFIGHTER";
        case ABILITY_ID::TRAIN_VIPER          : return "TRAIN_VIPER";
        case ABILITY_ID::TRAIN_VOIDRAY        : return "TRAIN_VOIDRAY";
        case ABILITY_ID::TRAIN_WARPINMOHANDAR : return "TRAIN_WARPINMOHANDAR";
        case ABILITY_ID::TRAIN_WARPINSCOUT    : return "TRAIN_WARPINSCOUT";
        case ABILITY_ID::TRAIN_WARPINSELENDIS : return "TRAIN_WARPINSELENDIS";
        case ABILITY_ID::TRAIN_WARPINURUN     : return "TRAIN_WARPINURUN";
        case ABILITY_ID::TRAIN_WARPINZERATUL  : return "TRAIN_WARPINZERATUL";
        case ABILITY_ID::TRAIN_WARPPRISM      : return "TRAIN_WARPPRISM";
        case ABILITY_ID::TRAIN_WIDOWMINE      : return "TRAIN_WIDOWMINE";
        case ABILITY_ID::TRAIN_ZEALOT         : return "TRAIN_ZEALOT";
        case ABILITY_ID::TRAIN_ZERGLING       : return "TRAIN_ZERGLING";
        case ABILITY_ID::TRANSPORTMODE_CANCEL : return "TRANSPORTMODE_CANCEL";
        case ABILITY_ID::TRANSPORTTRUCKTRANSPORT_TRANSPORTTRUCKLOAD :
            return "TRANSPORTTRUCKTRANSPORT_TRANSPORTTRUCKLOAD";
        case ABILITY_ID::TRANSPORTTRUCKTRANSPORT_TRANSPORTTRUCKUNLOADALL :
            return "TRANSPORTTRUCKTRANSPORT_TRANSPORTTRUCKUNLOADALL";
        case ABILITY_ID::TYCHUS03OMEGASTORM_OMEGASTORM :
            return "TYCHUS03OMEGASTORM_OMEGASTORM";
        case ABILITY_ID::ULTRALISKWEAPONCOOLDOWN :
            return "ULTRALISKWEAPONCOOLDOWN";
        case ABILITY_ID::ULTRASONICPULSE       : return "ULTRASONICPULSE";
        case ABILITY_ID::UNLOADALL             : return "UNLOADALL";
        case ABILITY_ID::UNLOADALLAT           : return "UNLOADALLAT";
        case ABILITY_ID::UNLOADALLAT_MEDIVAC   : return "UNLOADALLAT_MEDIVAC";
        case ABILITY_ID::UNLOADALLAT_OVERLORD  : return "UNLOADALLAT_OVERLORD";
        case ABILITY_ID::UNLOADALLAT_WARPPRISM : return "UNLOADALLAT_WARPPRISM";
        case ABILITY_ID::UNLOADALL_BUNKER      : return "UNLOADALL_BUNKER";
        case ABILITY_ID::UNLOADALL_COMMANDCENTER :
            return "UNLOADALL_COMMANDCENTER";
        case ABILITY_ID::UNLOADALL_NYDASNETWORK :
            return "UNLOADALL_NYDASNETWORK";
        case ABILITY_ID::UNLOADALL_NYDUSWORM : return "UNLOADALL_NYDUSWORM";
        case ABILITY_ID::UNLOADALL_WARPPRISM : return "UNLOADALL_WARPPRISM";
        case ABILITY_ID::UNLOADUNIT          : return "UNLOADUNIT";
        case ABILITY_ID::UNLOADUNIT_BUNKER   : return "UNLOADUNIT_BUNKER";
        case ABILITY_ID::UNLOADUNIT_COMMANDCENTER :
            return "UNLOADUNIT_COMMANDCENTER";
        case ABILITY_ID::UNLOADUNIT_MEDIVAC : return "UNLOADUNIT_MEDIVAC";
        case ABILITY_ID::UNLOADUNIT_NYDASNETWORK :
            return "UNLOADUNIT_NYDASNETWORK";
        case ABILITY_ID::UNLOADUNIT_OVERLORD  : return "UNLOADUNIT_OVERLORD";
        case ABILITY_ID::UNLOADUNIT_WARPPRISM : return "UNLOADUNIT_WARPPRISM";
        case ABILITY_ID::VAL03QUEENOFBLADESBURROW_BURROWDOWN :
            return "VAL03QUEENOFBLADESBURROW_BURROWDOWN";
        case ABILITY_ID::VAL03QUEENOFBLADESDEEPTUNNEL_DEEPTUNNEL :
            return "VAL03QUEENOFBLADESDEEPTUNNEL_DEEPTUNNEL";
        case ABILITY_ID::VAL03QUEENOFBLADESUNBURROW_BURROWUP :
            return "VAL03QUEENOFBLADESUNBURROW_BURROWUP";
        case ABILITY_ID::VOIDMPIMMORTALREVIVEDEATH_IMMORTAL :
            return "VOIDMPIMMORTALREVIVEDEATH_IMMORTAL";
        case ABILITY_ID::VOIDMPIMMORTALREVIVEREBUILD_IMMORTAL :
            return "VOIDMPIMMORTALREVIVEREBUILD_IMMORTAL";
        case ABILITY_ID::VOIDSEEKERPHASEMINEBLAST_PHASEMINEBLAST :
            return "VOIDSEEKERPHASEMINEBLAST_PHASEMINEBLAST";
        case ABILITY_ID::VOIDSEEKERTRANSPORT_MEDIVACLOAD :
            return "VOIDSEEKERTRANSPORT_MEDIVACLOAD";
        case ABILITY_ID::VOIDSEEKERTRANSPORT_MEDIVACUNLOADALL :
            return "VOIDSEEKERTRANSPORT_MEDIVACUNLOADALL";
        case ABILITY_ID::VOIDSIPHON : return "VOIDSIPHON";
        case ABILITY_ID::VOIDSWARMHOSTSPAWNLOCUST :
            return "VOIDSWARMHOSTSPAWNLOCUST";
        case ABILITY_ID::VOODOOSHIELD          : return "VOODOOSHIELD";
        case ABILITY_ID::VORTEX                : return "VORTEX";
        case ABILITY_ID::VORTEXPURIFIER_VORTEX : return "VORTEXPURIFIER_VORTEX";
        case ABILITY_ID::VULTUREQUEUE3_CANCEL  : return "VULTUREQUEUE3_CANCEL";
        case ABILITY_ID::VULTUREQUEUE3_CANCELSLOT :
            return "VULTUREQUEUE3_CANCELSLOT";
        case ABILITY_ID::VULTURESPIDERMINES_SPIDERMINE :
            return "VULTURESPIDERMINES_SPIDERMINE";
        case ABILITY_ID::WARPABLE_CANCEL : return "WARPABLE_CANCEL";
        case ABILITY_ID::WIDOWMINEBURROW_CANCEL :
            return "WIDOWMINEBURROW_CANCEL";
        case ABILITY_ID::WORMHOLETRANSIT      : return "WORMHOLETRANSIT";
        case ABILITY_ID::WRAITHCLOAK_CLOAKOFF : return "WRAITHCLOAK_CLOAKOFF";
        case ABILITY_ID::WRECKINGCREWASSAULTMODE_ASSAULTMODE :
            return "WRECKINGCREWASSAULTMODE_ASSAULTMODE";
        case ABILITY_ID::WRECKINGCREWFIGHTERMODE_FIGHTERMODE :
            return "WRECKINGCREWFIGHTERMODE_FIGHTERMODE";
        case ABILITY_ID::XELNAGAHEALINGSHRINE : return "XELNAGAHEALINGSHRINE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOOREOPENED_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOOREOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORNEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORNEOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORNE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORNE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORNOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORNOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORNWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORNWOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORNW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORNW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORN_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORN_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORSEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORSEOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORSE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORSE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORSOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORSOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORSWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORSWOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORSW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORSW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORS_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORS_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN :
            return "XELNAGA_CAVERNS_DOORWOPENED_XELNAGA_CAVERNS_"
                   "DOORDEFAULTOPEN";
        case ABILITY_ID::
            XELNAGA_CAVERNS_DOORW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE :
            return "XELNAGA_CAVERNS_DOORW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEH10_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH10_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEH12_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH12_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEH8_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH8_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENE10_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE10_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENE12_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE12_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENE8_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE8_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENW10_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW10_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENW12_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW12_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGENW8_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW8_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEV10_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV10_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEV12_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV12_BRIDGERETRACT";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT_BRIDGEEXTEND :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT_BRIDGEEXTEND";
        case ABILITY_ID::XELNAGA_CAVERNS_FLOATING_BRIDGEV8_BRIDGERETRACT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV8_BRIDGERETRACT";
        case ABILITY_ID::ZERATULBLINK        : return "ZERATULBLINK";
        case ABILITY_ID::ZERATULSTUN         : return "ZERATULSTUN";
        case ABILITY_ID::_250MMSTRIKECANNONS : return "_250MMSTRIKECANNONS";
        case ABILITY_ID::_250MMSTRIKECANNONS_CANCEL :
            return "_250MMSTRIKECANNONS_CANCEL";
        case ABILITY_ID::_330MMBARRAGECANNONS : return "_330MMBARRAGECANNONS";
        case ABILITY_ID::_330MMBARRAGECANNONS_CANCEL :
            return "_330MMBARRAGECANNONS_CANCEL";
        default : return "UNKNOWN";
    }
}

const flat_map<AbilityID, AbilityID> generalize_ability {
    // clang-format off
    { ABILITY_ID::STOP_STOP,
        ABILITY_ID::STOP },
    { ABILITY_ID::STOP_HOLDFIRESPECIAL,
        ABILITY_ID::STOP },
    { ABILITY_ID::STOP_CHEER,
        ABILITY_ID::STOP },
    { ABILITY_ID::STOP_DANCE,
        ABILITY_ID::STOP },
    { ABILITY_ID::MOVE_MOVE,
        ABILITY_ID::GENERAL_MOVE },
    { ABILITY_ID::MOVE_MOVEPATROL,
        ABILITY_ID::GENERAL_PATROL },
    { ABILITY_ID::MOVE_MOVEHOLDPOSITION,
        ABILITY_ID::GENERAL_HOLDPOSITION },
    { ABILITY_ID::MOVE_ACQUIREMOVE,
        ABILITY_ID::ATTACK },
    { ABILITY_ID::BEACON_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::ATTACK_ATTACK,
        ABILITY_ID::ATTACK },
    { ABILITY_ID::EFFECT_SPRAY_TERRAN,
        ABILITY_ID::EFFECT_SPRAY },
    { ABILITY_ID::EFFECT_SPRAY_ZERG,
        ABILITY_ID::EFFECT_SPRAY },
    { ABILITY_ID::EFFECT_SPRAY_PROTOSS,
        ABILITY_ID::EFFECT_SPRAY },
    { ABILITY_ID::CORRUPTION_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BEHAVIOR_HOLDFIREON_GHOST,
        ABILITY_ID::BEHAVIOR_HOLDFIREON },
    { ABILITY_ID::BEHAVIOR_HOLDFIREOFF_GHOST,
        ABILITY_ID::BEHAVIOR_HOLDFIREOFF },
    { ABILITY_ID::EFFECT_REPAIR_MULE,
        ABILITY_ID::EFFECT_REPAIR },
    { ABILITY_ID::EFFECT_MASSRECALL_STRATEGICRECALL,
        ABILITY_ID::EFFECT_MASSRECALL },
    { ABILITY_ID::HARVEST_GATHER_MULE,
        ABILITY_ID::HARVEST_GATHER },
    { ABILITY_ID::HARVEST_RETURN_MULE,
        ABILITY_ID::HARVEST_RETURN },
    { ABILITY_ID::CANCEL_GRAVITONBEAM,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BUILDINPROGRESSNYDUSCANAL_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::SIPHON_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::RALLY_BUILDING,
        ABILITY_ID::RALLY_UNITS },
    { ABILITY_ID::RALLY_MORPHING_UNIT,
        ABILITY_ID::RALLY_UNITS },
    { ABILITY_ID::RALLY_COMMANDCENTER,
        ABILITY_ID::RALLY_WORKERS },
    { ABILITY_ID::RALLY_NEXUS,
        ABILITY_ID::RALLY_WORKERS },
    { ABILITY_ID::RALLY_HATCHERY_UNITS,
        ABILITY_ID::RALLY_UNITS },
    { ABILITY_ID::RALLY_HATCHERY_WORKERS,
        ABILITY_ID::RALLY_WORKERS },
    { ABILITY_ID::CANCEL_NEURALPARASITE,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::EFFECT_STIM_MARAUDER,
        ABILITY_ID::EFFECT_STIM },
    { ABILITY_ID::_250MMSTRIKECANNONS_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::HARVEST_GATHER_SCV,
        ABILITY_ID::HARVEST_GATHER },
    { ABILITY_ID::HARVEST_RETURN_SCV,
        ABILITY_ID::HARVEST_RETURN },
    { ABILITY_ID::HARVEST_GATHER_PROBE,
        ABILITY_ID::HARVEST_GATHER },
    { ABILITY_ID::HARVEST_RETURN_PROBE,
        ABILITY_ID::HARVEST_RETURN },
    { ABILITY_ID::CANCEL_QUEUE1,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_QUEUE1,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::CANCEL_QUEUE5,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_QUEUE5,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::CANCEL_QUEUECANCELTOSELECTION,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_QUEUECANCELTOSELECTION,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::QUE5LONGBLEND_CANCEL,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::QUE5LONGBLEND_CANCELSLOT,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::CANCEL_QUEUEADDON,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_ADDON,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::CANCEL_BUILDINPROGRESS,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::HALT_BUILDING,
        ABILITY_ID::HALT },
    { ABILITY_ID::EFFECT_REPAIR_SCV,
        ABILITY_ID::EFFECT_REPAIR },
    { ABILITY_ID::HALT_TERRANBUILD,
        ABILITY_ID::HALT },
    { ABILITY_ID::RAVENBUILD_CANCEL,
        ABILITY_ID::HALT },
    { ABILITY_ID::EFFECT_STIM_MARINE,
        ABILITY_ID::EFFECT_STIM },
    { ABILITY_ID::BEHAVIOR_CLOAKON_GHOST,
        ABILITY_ID::BEHAVIOR_CLOAKON },
    { ABILITY_ID::BEHAVIOR_CLOAKOFF_GHOST,
        ABILITY_ID::BEHAVIOR_CLOAKOFF },
    { ABILITY_ID::BEHAVIOR_CLOAKON_BANSHEE,
        ABILITY_ID::BEHAVIOR_CLOAKON },
    { ABILITY_ID::BEHAVIOR_CLOAKOFF_BANSHEE,
        ABILITY_ID::BEHAVIOR_CLOAKOFF },
    { ABILITY_ID::LOAD_MEDIVAC,
        ABILITY_ID::LOAD },
    { ABILITY_ID::UNLOADALLAT_MEDIVAC,
        ABILITY_ID::UNLOADALLAT },
    { ABILITY_ID::UNLOADUNIT_MEDIVAC,
        ABILITY_ID::UNLOADUNIT }, // Replaced 3796 with 3670
    { ABILITY_ID::LOAD_BUNKER,
        ABILITY_ID::LOAD },
    { ABILITY_ID::UNLOADALL_BUNKER,
        ABILITY_ID::UNLOADALL },
    { ABILITY_ID::UNLOADUNIT_BUNKER,
        ABILITY_ID::UNLOADUNIT }, // Replaced 3796 with 3670
    { ABILITY_ID::UNLOADALL_COMMANDCENTER,
        ABILITY_ID::UNLOADALL },
    { ABILITY_ID::UNLOADUNIT_COMMANDCENTER,
        ABILITY_ID::UNLOADUNIT }, // Replaced 3796 with 3670
    { ABILITY_ID::LOADALL_COMMANDCENTER,
        ABILITY_ID::LOADALL },
    { ABILITY_ID::LIFT_COMMANDCENTER,
        ABILITY_ID::LIFT },
    { ABILITY_ID::LAND_COMMANDCENTER,
        ABILITY_ID::LAND },
    { ABILITY_ID::BUILD_TECHLAB_BARRACKS,
        ABILITY_ID::BUILD_TECHLAB },
    { ABILITY_ID::BUILD_REACTOR_BARRACKS,
        ABILITY_ID::BUILD_REACTOR },
    { ABILITY_ID::CANCEL_BARRACKSADDON,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::LIFT_BARRACKS,
        ABILITY_ID::LIFT },
    { ABILITY_ID::BUILD_TECHLAB_FACTORY,
        ABILITY_ID::BUILD_TECHLAB },
    { ABILITY_ID::BUILD_REACTOR_FACTORY,
        ABILITY_ID::BUILD_REACTOR },
    { ABILITY_ID::CANCEL_FACTORYADDON,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::LIFT_FACTORY,
        ABILITY_ID::LIFT },
    { ABILITY_ID::BUILD_TECHLAB_STARPORT,
        ABILITY_ID::BUILD_TECHLAB },
    { ABILITY_ID::BUILD_REACTOR_STARPORT,
        ABILITY_ID::BUILD_REACTOR },
    { ABILITY_ID::CANCEL_STARPORTADDON,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::LIFT_STARPORT,
        ABILITY_ID::LIFT },
    { ABILITY_ID::LAND_FACTORY,
        ABILITY_ID::LAND },
    { ABILITY_ID::LAND_STARPORT,
        ABILITY_ID::LAND },
    { ABILITY_ID::LAND_BARRACKS,
        ABILITY_ID::LAND },
    { ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1,
        ABILITY_ID::RESEARCH_TERRANINFANTRYARMOR },
    { ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2,
        ABILITY_ID::RESEARCH_TERRANINFANTRYARMOR },
    { ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3,
        ABILITY_ID::RESEARCH_TERRANINFANTRYARMOR },
    { ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_TERRANSHIPWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_TERRANSHIPWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANSHIPWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_TERRANSHIPWEAPONS },
    { ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1,
        ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATING },
    { ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2,
        ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATING },
    { ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL3,
        ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATING },
    { ABILITY_ID::BUILD_CANCEL,
        ABILITY_ID::HALT },
    { ABILITY_ID::LOAD_WARPPRISM,
        ABILITY_ID::LOAD },
    { ABILITY_ID::UNLOADALL_WARPPRISM,
        ABILITY_ID::UNLOADALL },
    { ABILITY_ID::UNLOADALLAT_WARPPRISM,
        ABILITY_ID::UNLOADALLAT },
    { ABILITY_ID::UNLOADUNIT_WARPPRISM,
        ABILITY_ID::UNLOADUNIT }, // Replaced 3796 with 3670
    { ABILITY_ID::CANCEL_HANGARQUEUE5,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_HANGARQUEUE5,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::BROODLORDQUEUE2_CANCEL,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::BROODLORDQUEUE2_CANCELSLOT,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONS },
    { ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONS },
    { ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONS },
    { ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1,
        ABILITY_ID::RESEARCH_PROTOSSGROUNDARMOR },
    { ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2,
        ABILITY_ID::RESEARCH_PROTOSSGROUNDARMOR },
    { ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3,
        ABILITY_ID::RESEARCH_PROTOSSGROUNDARMOR },
    { ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1,
        ABILITY_ID::RESEARCH_PROTOSSSHIELDS },
    { ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2,
        ABILITY_ID::RESEARCH_PROTOSSSHIELDS },
    { ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3,
        ABILITY_ID::RESEARCH_PROTOSSSHIELDS },
    { ABILITY_ID::HARVEST_GATHER_DRONE,
        ABILITY_ID::HARVEST_GATHER },
    { ABILITY_ID::HARVEST_RETURN_DRONE,
        ABILITY_ID::HARVEST_RETURN },
    { ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS },
    { ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS },
    { ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_ZERGMELEEWEAPONS },
    { ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL1,
        ABILITY_ID::RESEARCH_ZERGGROUNDARMOR },
    { ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL2,
        ABILITY_ID::RESEARCH_ZERGGROUNDARMOR },
    { ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL3,
        ABILITY_ID::RESEARCH_ZERGGROUNDARMOR },
    { ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS },
    { ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS },
    { ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONS },
    { ABILITY_ID::CANCEL_MORPHLAIR,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MORPHHIVE,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MORPHGREATERSPIRE,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL1,
        ABILITY_ID::RESEARCH_ZERGFLYERATTACK },
    { ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL2,
        ABILITY_ID::RESEARCH_ZERGFLYERATTACK },
    { ABILITY_ID::RESEARCH_ZERGFLYERATTACKLEVEL3,
        ABILITY_ID::RESEARCH_ZERGFLYERATTACK },
    { ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL1,
        ABILITY_ID::RESEARCH_ZERGFLYERARMOR },
    { ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL2,
        ABILITY_ID::RESEARCH_ZERGFLYERARMOR },
    { ABILITY_ID::RESEARCH_ZERGFLYERARMORLEVEL3,
        ABILITY_ID::RESEARCH_ZERGFLYERARMOR },
    { ABILITY_ID::CANCEL_MORPHBROODLORD,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_BANELING,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWBANELINGDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_BANELING,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::BURROWDOWN_DRONE,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWDRONEDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_DRONE,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::BURROWDOWN_HYDRALISK,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWHYDRALISKDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_HYDRALISK,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::BURROWDOWN_ROACH,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWROACHDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_ROACH,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::BURROWDOWN_ZERGLING,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWZERGLINGDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_ZERGLING,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::BURROWDOWN_INFESTORTERRAN,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWUP_INFESTORTERRAN,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::REDSTONELAVACRITTERBURROW_BURROWDOWN,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::REDSTONELAVACRITTERINJUREDBURROW_BURROWDOWN,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::REDSTONELAVACRITTERUNBURROW_BURROWUP,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::REDSTONELAVACRITTERINJUREDUNBURROW_BURROWUP,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::LOAD_OVERLORD,
        ABILITY_ID::LOAD },
    { ABILITY_ID::UNLOADALLAT_OVERLORD,
        ABILITY_ID::UNLOADALLAT },
    { ABILITY_ID::UNLOADUNIT_OVERLORD,
        ABILITY_ID::UNLOADUNIT }, // Replaced 3796 with 3670
    { ABILITY_ID::MERGEABLE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::WARPABLE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_QUEEN,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWQUEENDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_QUEEN,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::LOAD_NYDUSNETWORK,
        ABILITY_ID::LOAD },
    { ABILITY_ID::UNLOADALL_NYDASNETWORK,
        ABILITY_ID::UNLOADALL },
    { ABILITY_ID::UNLOADUNIT_NYDASNETWORK,
        ABILITY_ID::UNLOADUNIT }, // Replaced 3796 with 3670
    { ABILITY_ID::EFFECT_BLINK_STALKER,
        ABILITY_ID::EFFECT_BLINK },
    { ABILITY_ID::BURROWDOWN_INFESTOR,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWINFESTORDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_INFESTOR,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::CANCEL_MORPHOVERSEER,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MORPHPLANETARYFORTRESS,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_ULTRALISK,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWUP_ULTRALISK,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::CANCEL_MORPHORBITAL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::MORPH_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::LIFT_ORBITALCOMMAND,
        ABILITY_ID::LIFT },
    { ABILITY_ID::LAND_ORBITALCOMMAND,
        ABILITY_ID::LAND },
    { ABILITY_ID::FORCEFIELD_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::PHASINGMODE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::TRANSPORTMODE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1,
        ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONS },
    { ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2,
        ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONS },
    { ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3,
        ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONS },
    { ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL1,
        ABILITY_ID::RESEARCH_PROTOSSAIRARMOR },
    { ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL2,
        ABILITY_ID::RESEARCH_PROTOSSAIRARMOR },
    { ABILITY_ID::RESEARCH_PROTOSSAIRARMORLEVEL3,
        ABILITY_ID::RESEARCH_PROTOSSAIRARMOR },
    { ABILITY_ID::CANCEL_NUKE,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWCREEPTUMORDOWN_BURROWDOWN,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::ATTACK_REDIRECT,
        ABILITY_ID::ATTACK },
    { ABILITY_ID::EFFECT_STIM_MARINE_REDIRECT,
        ABILITY_ID::EFFECT_STIM },
    { ABILITY_ID::EFFECT_STIM_MARAUDER_REDIRECT,
        ABILITY_ID::EFFECT_STIM },
    { ABILITY_ID::STOP_REDIRECT,
        ABILITY_ID::STOP },
    { ABILITY_ID::BUILD_CREEPTUMOR_QUEEN,
        ABILITY_ID::BUILD_CREEPTUMOR }, // Replaced 3691 with 1153
    { ABILITY_ID::QUEENBUILD_CANCEL,
        ABILITY_ID::HALT },
    { ABILITY_ID::MORPH_SPINECRAWLERUPROOT,
        ABILITY_ID::MORPH_UPROOT },
    { ABILITY_ID::SPINECRAWLERUPROOT_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::MORPH_SPORECRAWLERUPROOT,
        ABILITY_ID::MORPH_UPROOT },
    { ABILITY_ID::SPORECRAWLERUPROOT_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::MORPH_SPINECRAWLERROOT,
        ABILITY_ID::MORPH_ROOT },
    { ABILITY_ID::CANCEL_SPINECRAWLERROOT,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::MORPH_SPORECRAWLERROOT,
        ABILITY_ID::MORPH_ROOT },
    { ABILITY_ID::CANCEL_SPORECRAWLERROOT,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BUILD_CREEPTUMOR_TUMOR,
        ABILITY_ID::BUILD_CREEPTUMOR }, // Replaced 3691 with 1153
    { ABILITY_ID::CANCEL_CREEPTUMOR,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BUILDNYDUSCANAL_CANCEL,
        ABILITY_ID::HALT },
    { ABILITY_ID::CANCEL_QUEUEPASIVE,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_QUEUEPASSIVE,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::CANCEL_QUEUEPASSIVECANCELTOSELECTION,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::CANCELSLOT_QUEUEPASSIVECANCELTOSELECTION,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::CANCEL_MORPHMOTHERSHIP,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MOTHERSHIPSTASIS,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::DIGESTERTRANSPORT_LOADDIGESTER,
        ABILITY_ID::LOAD },
    { ABILITY_ID::EFFECT_MASSRECALL_MOTHERSHIPCORE,
        ABILITY_ID::EFFECT_MASSRECALL },
    { ABILITY_ID::LEECHRESOURCES_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_SWARMHOST,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWUP_SWARMHOST,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::ATTACK_ATTACKBUILDING,
        ABILITY_ID::ATTACK },
    { ABILITY_ID::STOP_BUILDING,
        ABILITY_ID::STOP },
    { ABILITY_ID::EYESTALK_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_PROTOSSBUILDINGQUEUE,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::PROTOSSBUILDINGQUEUE_CANCELSLOT,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::QUE8_CANCEL,
        ABILITY_ID::CANCEL_LAST },
    { ABILITY_ID::QUE8_CANCELSLOT,
        ABILITY_ID::CANCEL_SLOT },
    { ABILITY_ID::TESTZERG_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_WIDOWMINE,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::WIDOWMINEBURROW_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_WIDOWMINE,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::MOTHERSHIPCOREENERGIZE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::LURKERASPECTMPFROMHYDRALISKBURROWED_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::LURKERASPECTMP_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_LURKER,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWLURKERMPDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_LURKER,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::CANCEL_MORPHLURKERDEN,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::ORACLEREVELATIONMODE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::ORACLENORMALMODE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MORPHRAVAGER,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MORPHLURKER,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWDOWN_RAVAGER,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::BURROWRAVAGERDOWN_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BURROWUP_RAVAGER,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::CANCEL_LOCKON,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CORRUPTIONBOMB_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::THORAPMODE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_MORPHTHOREXPLOSIVEMODE,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::EFFECT_MASSRECALL_MOTHERSHIP,
        ABILITY_ID::EFFECT_MASSRECALL },
    { ABILITY_ID::LOAD_NYDUSWORM,
        ABILITY_ID::LOAD },
    { ABILITY_ID::UNLOADALL_NYDUSWORM,
        ABILITY_ID::UNLOADALL },
    { ABILITY_ID::DEFILERMPBURROW_BURROWDOWN,
        ABILITY_ID::BURROWDOWN },
    { ABILITY_ID::DEFILERMPBURROW_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::DEFILERMPUNBURROW_BURROWUP,
        ABILITY_ID::BURROWUP },
    { ABILITY_ID::CANCEL_STASISTRAP,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::SELFREPAIR_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::BEHAVIOR_HOLDFIREON_LURKER,
        ABILITY_ID::BEHAVIOR_HOLDFIREON },
    { ABILITY_ID::BEHAVIOR_HOLDFIREOFF_LURKER,
        ABILITY_ID::BEHAVIOR_HOLDFIREOFF },
    { ABILITY_ID::TIMESTOP_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_ADEPTPHASESHIFT,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_ADEPTSHADEPHASESHIFT,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_TEMPESTDISRUPTIONBLAST,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::EFFECT_SHADOWSTRIDE,
        ABILITY_ID::EFFECT_BLINK },
    { ABILITY_ID::CANCEL_MORPHOVERLORDTRANSPORT,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CHANNELSNIPE_CANCEL,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::CANCEL_VOIDRAYPRISMATICALIGNMENT,
        ABILITY_ID::CANCEL },
    { ABILITY_ID::EFFECT_REPAIR_REPAIRDRONE,
        ABILITY_ID::EFFECT_REPAIR },
    { ABILITY_ID::EFFECT_MASSRECALL_NEXUS,
        ABILITY_ID::EFFECT_MASSRECALL },
    { ABILITY_ID::ATTACK_BATTLECRUISER,
        ABILITY_ID::ATTACK },
    { ABILITY_ID::BATTLECRUISERMOVE_MOVE,
        ABILITY_ID::GENERAL_MOVE },
    { ABILITY_ID::BATTLECRUISERMOVE_MOVEPATROL,
        ABILITY_ID::GENERAL_PATROL },
    { ABILITY_ID::BATTLECRUISERMOVE_MOVEHOLDPOSITION,
        ABILITY_ID::GENERAL_HOLDPOSITION },
    { ABILITY_ID::BATTLECRUISERSTOPEVALUATOR_STOP,
        ABILITY_ID::STOP },
    { ABILITY_ID::STOP_BATTLECRUISER,
        ABILITY_ID::STOP },
    { ABILITY_ID::SHIELDBATTERYRECHARGEEX5_STOP,
        ABILITY_ID::CANCEL }, // clang-format on
};

AbilityID GetGeneralizedAbilityID ( const AbilityID ability_id ) {
    if ( const auto it = generalize_ability.find ( ability_id );
         it != generalize_ability.end( ) )
    {
        return AbilityID (
            it->second
        ); // Found: return the mapped ability wrapped in SC2Type
    }
    return AbilityID (
        ability_id
    ); // Not found: return the original ability wrapped
}

} // namespace sc2