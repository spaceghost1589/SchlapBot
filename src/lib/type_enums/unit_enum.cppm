module;
#include "types.h"
export module type_enums:unit_enum;

export namespace sc2 {

enum class UNIT_TYPEID : uint16_t {
    ABANDONEDBUILDING                               = 1720,
    ACCELERATIONZONEFLYINGLARGE                     = 1990,
    ACCELERATIONZONEFLYINGMEDIUM                    = 1989,
    ACCELERATIONZONEFLYINGSMALL                     = 1988,
    ACCELERATIONZONELARGE                           = 1987,
    ACCELERATIONZONEMEDIUM                          = 1986,
    ACCELERATIONZONESMALL                           = 1985,
    ACIDSALIVAWEAPON                                = 278,
    ACIDSPINESWEAPON                                = 293,
    ADEPTPIERCINGWEAPON                             = 896,
    ADEPTUPGRADEWEAPON                              = 826,
    ADEPTWEAPON                                     = 825,
    ADJUTANTCAPSULE                                 = 1226,
    AIURLIGHTBRIDGEABANDONEDNE10                    = 738,
    AIURLIGHTBRIDGEABANDONEDNE10OUT                 = 737,
    AIURLIGHTBRIDGEABANDONEDNE12                    = 740,
    AIURLIGHTBRIDGEABANDONEDNE12OUT                 = 739,
    AIURLIGHTBRIDGEABANDONEDNE8                     = 736,
    AIURLIGHTBRIDGEABANDONEDNE8OUT                  = 735,
    AIURLIGHTBRIDGEABANDONEDNW10                    = 744,
    AIURLIGHTBRIDGEABANDONEDNW10OUT                 = 743,
    AIURLIGHTBRIDGEABANDONEDNW12                    = 746,
    AIURLIGHTBRIDGEABANDONEDNW12OUT                 = 745,
    AIURLIGHTBRIDGEABANDONEDNW8                     = 742,
    AIURLIGHTBRIDGEABANDONEDNW8OUT                  = 741,
    AIURLIGHTBRIDGENE10                             = 698,
    AIURLIGHTBRIDGENE10OUT                          = 697,
    AIURLIGHTBRIDGENE12                             = 700,
    AIURLIGHTBRIDGENE12OUT                          = 699,
    AIURLIGHTBRIDGENE8                              = 696,
    AIURLIGHTBRIDGENE8OUT                           = 695,
    AIURLIGHTBRIDGENW10                             = 704,
    AIURLIGHTBRIDGENW10OUT                          = 703,
    AIURLIGHTBRIDGENW12                             = 706,
    AIURLIGHTBRIDGENW12OUT                          = 705,
    AIURLIGHTBRIDGENW8                              = 702,
    AIURLIGHTBRIDGENW8OUT                           = 701,
    AIURTEMPLEBRIDGEDESTRUCTIBLENE10OUT             = 843,
    AIURTEMPLEBRIDGEDESTRUCTIBLENE12OUT             = 844,
    AIURTEMPLEBRIDGEDESTRUCTIBLENE8OUT              = 842,
    AIURTEMPLEBRIDGEDESTRUCTIBLENW10OUT             = 846,
    AIURTEMPLEBRIDGEDESTRUCTIBLENW12OUT             = 847,
    AIURTEMPLEBRIDGEDESTRUCTIBLENW8OUT              = 845,
    AIURTEMPLEBRIDGEDESTRUCTIBLESE10OUT             = 852,
    AIURTEMPLEBRIDGEDESTRUCTIBLESE12OUT             = 853,
    AIURTEMPLEBRIDGEDESTRUCTIBLESE8OUT              = 851,
    AIURTEMPLEBRIDGEDESTRUCTIBLESW10OUT             = 849,
    AIURTEMPLEBRIDGEDESTRUCTIBLESW12OUT             = 850,
    AIURTEMPLEBRIDGEDESTRUCTIBLESW8OUT              = 848,
    AIURTEMPLEBRIDGENE10OUT                         = 708,
    AIURTEMPLEBRIDGENE12OUT                         = 709,
    AIURTEMPLEBRIDGENE8OUT                          = 707,
    AIURTEMPLEBRIDGENW10OUT                         = 711,
    AIURTEMPLEBRIDGENW12OUT                         = 712,
    AIURTEMPLEBRIDGENW8OUT                          = 710,
    ANTEPLOTT                                       = 660,
    ARBITERMP                                       = 857,
    ARBITERMPWEAPONMISSILE                          = 813,
    ARCHIVE                                         = 1146,
    ARCHIVESEALED                                   = 913,
    ARTANIS                                         = 1271,
    ARTIFACT                                        = 1285,
    ARTIFACTPIECE1                                  = 1276,
    ARTIFACTPIECE2                                  = 1277,
    ARTIFACTPIECE3                                  = 1279,
    ARTIFACTPIECE4                                  = 1278,
    ARTIFACTPIECE5                                  = 1280,
    ARTIFACTVAULT                                   = 1147,
    ARTOSILOPE                                      = 659,
    ATALASERBATTERYLMWEAPON                         = 272,
    ATSLASERBATTERYLMWEAPON                         = 273,
    AUTOMATEDREFINERY                               = 977,
    AUTOTESTATTACKER                                = 393,
    AUTOTESTATTACKTARGETAIR                         = 392,
    AUTOTESTATTACKTARGETGROUND                      = 391,
    AUTOTURRETRELEASEWEAPON                         = 291,
    AVERNUSGATECONTROL                              = 1148,
    BACKLASHROCKETSLMWEAPON                         = 286,
    BALL                                            = 2,
    BARRACKSTECHREACTOR                             = 958,
    BATTLECRUISERHELIOS                             = 1024,
    BATTLECRUISERHELIOSALMWEAPON                    = 1065,
    BATTLECRUISERHELIOSGLMWEAPON                    = 1067,
    BATTLECRUISERHELIOSMORPH                        = 978,
    BATTLECRUISERLOKILMWEAPON                       = 1066,
    BEACONARMY                                      = 297,
    BEACONATTACK                                    = 298,
    BEACONAUTO                                      = 302,
    BEACONCLAIM                                     = 305,
    BEACONCUSTOM1                                   = 307,
    BEACONCUSTOM2                                   = 308,
    BEACONCUSTOM3                                   = 309,
    BEACONCUSTOM4                                   = 310,
    BEACONDEFEND                                    = 299,
    BEACONDETECT                                    = 303,
    BEACONEXPAND                                    = 306,
    BEACONHARASS                                    = 300,
    BEACONIDLE                                      = 301,
    BEACONRALLY                                     = 296,
    BEACONSCOUT                                     = 304,
    BEACON_NOVA                                     = 888,
    BEACON_NOVASMALL                                = 889,
    BEACON_PROTOSS                                  = 315,
    BEACON_PROTOSSSMALL                             = 316,
    BEACON_TERRAN                                   = 317,
    BEACON_TERRANSMALL                              = 318,
    BEACON_ZERG                                     = 319,
    BEACON_ZERGSMALL                                = 320,
    BIODOME                                         = 1232,
    BIODOMECOMMAND                                  = 965,
    BIODOMECOMMANDFLYING                            = 964,
    BIODOMEHALFBUILT                                = 1231,
    BIOPLASMIDDISCHARGEWEAPON                       = 1120,
    BIOSTASISMISSILE                                = 1068,
    BLIMP                                           = 1156,
    BLIMPADS                                        = 1150,
    BLOCKER16X16                                    = 1153,
    BLOCKER4X4                                      = 1158,
    BLOCKER6X6                                      = 1151,
    BLOCKER8X8                                      = 1152,
    BRAXISALPHADESTRUCTIBLE1X1                      = 362,
    BRAXISALPHADESTRUCTIBLE2X2                      = 363,
    BREACHINGCHARGE                                 = 1750,
    BRIDGEBLOCKER4X12                               = 1242,
    BROODLINGESCORT                                 = 143,
    BROODLORDAWEAPON                                = 386,
    BROODLORDBWEAPON                                = 290,
    BROODLORDEGG                                    = 1062,
    BROODLORDEGGMISSILE                             = 1063,
    BROODLORDWEAPON                                 = 385,
    BRUTALISK                                       = 1263,
    BRUTALISKWEAPON                                 = 1081,
    BUBBACOMMERCIAL                                 = 1194,
    BYPASSARMORDRONE                                = 895,
    CABOOSE                                         = 1716,
    CARGOTRUCKUNITBARRELS                           = 1239,
    CARGOTRUCKUNITFLATBED                           = 1154,
    CARGOTRUCKUNITTRAILER                           = 1155,
    CARRIONBIRD                                     = 322,
    CASTANARDESTRUCTIBLEDEBRIS                      = 1772,
    CASTANARULTRALISKSHACKLEDUNIT                   = 1293,
    CASTANARWINDOWLARGEDIAGONALBLURUNIT             = 1238,
    CASTANARWINDOWLARGEDIAGONALULBRUNIT             = 1157,
    CAUSTICSPRAYMISSILE                             = 822,
    CELLBLOCKB                                      = 1286,
    CHARDESTRUCTIBLEROCKCOVER                       = 1762,
    CHARDESTRUCTIBLEROCKCOVERULDR                   = 1764,
    CHARDESTRUCTIBLEROCKCOVERURDL                   = 1765,
    CHARDESTRUCTIBLEROCKCOVERV                      = 1763,
    CHECKSTATION                                    = 950,
    CHECKSTATIONDIAGONALBLUR                        = 951,
    CHECKSTATIONDIAGONALBLUROPENED                  = 955,
    CHECKSTATIONDIAGONALULBR                        = 952,
    CHECKSTATIONDIAGONALULBROPENED                  = 956,
    CHECKSTATIONOPENED                              = 954,
    CHECKSTATIONVERTICAL                            = 953,
    CHECKSTATIONVERTICALOPENED                      = 957,
    CHRYSALISEGG                                    = 1248,
    CIVILIAN                                        = 1655,
    CIVILIANCARSUNIT                                = 1692,
    CIVILIANFEMALE                                  = 1657,
    CIVILIANSHIPWRECKED                             = 1243,
    CIVILIANWEAPON                                  = 1064,
    CLEANINGBOT                                     = 612,
    COLLAPSIBLEPURIFIERTOWERDEBRIS                  = 747,
    COLLAPSIBLEPURIFIERTOWERDIAGONAL                = 882,
    COLLAPSIBLEPURIFIERTOWERPUSHUNIT                = 798,
    COLLAPSIBLEROCKTOWER                            = 609,
    COLLAPSIBLEROCKTOWERDEBRISRAMPLEFT              = 518,
    COLLAPSIBLEROCKTOWERDEBRISRAMPLEFTGREEN         = 1999,
    COLLAPSIBLEROCKTOWERDEBRISRAMPRIGHT             = 517,
    COLLAPSIBLEROCKTOWERDEBRISRAMPRIGHTGREEN        = 2000,
    COLLAPSIBLEROCKTOWERPUSHUNITRAMPLEFT            = 564,
    COLLAPSIBLEROCKTOWERPUSHUNITRAMPLEFTGREEN       = 2001,
    COLLAPSIBLEROCKTOWERPUSHUNITRAMPRIGHT           = 563,
    COLLAPSIBLEROCKTOWERPUSHUNITRAMPRIGHTGREEN      = 2002,
    COLLAPSIBLEROCKTOWERRAMPLEFT                    = 664,
    COLLAPSIBLEROCKTOWERRAMPLEFTGREEN               = 2003,
    COLLAPSIBLEROCKTOWERRAMPRIGHT                   = 663,
    COLLAPSIBLEROCKTOWERRAMPRIGHTGREEN              = 2004,
    COLLAPSIBLETERRANTOWER                          = 610,
    COLONIST                                        = 1656,
    COLONISTBIODOME                                 = 1727,
    COLONISTBIODOMEHALFBUILT                        = 1728,
    COLONISTFEMALE                                  = 1658,
    COLONISTHUT                                     = 1660,
    COLONISTSHIP                                    = 963,
    COLONISTSHIPFLYING                              = 962,
    COLONISTSHIPTHANSON02A                          = 1700,
    COLONISTTRANSPORT                               = 1773,
    COLONISTVEHICLEUNIT                             = 1695,
    COLONISTVEHICLEUNIT01                           = 1696,
    COLONYINFESTATIONWEAPON                         = 1096,
    COMMENTATORBOT1                                 = 331,
    COMMENTATORBOT2                                 = 332,
    COMMENTATORBOT3                                 = 333,
    COMMENTATORBOT4                                 = 334,
    COMPOUNDMANSION_DOORE                           = 683,
    COMPOUNDMANSION_DOORELOWERED                    = 684,
    COMPOUNDMANSION_DOORN                           = 679,
    COMPOUNDMANSION_DOORNE                          = 681,
    COMPOUNDMANSION_DOORNELOWERED                   = 682,
    COMPOUNDMANSION_DOORNLOWERED                    = 680,
    COMPOUNDMANSION_DOORNW                          = 685,
    COMPOUNDMANSION_DOORNWLOWERED                   = 686,
    CONSUMEDNAFEEDBACKWEAPON                        = 1092,
    CONTAMINATEWEAPON                               = 295,
    CORROSIVEPARASITEWEAPON                         = 897,
    CORRUPTIONWEAPON                                = 263,
    CORSAIRMP                                       = 855,
    COW                                             = 338,
    CRABEETLE                                       = 662,
    CREEPBLOCKER1X1                                 = 387,
    CREEPBLOCKER4X4                                 = 623,
    CREEPONLYBLOCKER4X4                             = 883,
    CREEPTUMORMISSILE                               = 583,
    CRUISERBIKE                                     = 1693,
    CYCLONEMISSILE                                  = 805,
    CYCLONEMISSILELARGE                             = 806,
    CYCLONEMISSILELARGEAIR                          = 804,
    CYCLONEMISSILELARGEAIRALTERNATIVE               = 1915,
    D8CHARGE                                        = 902,
    D8CHARGEWEAPON                                  = 275,
    D8CLUSTERBOMB                                   = 1061,
    D8CLUSTERBOMBWEAPON                             = 1060,
    DATACORE                                        = 1290,
    DEBRIS2X2NONCONJOINED                           = 475,
    DEFENSEWALLE                                    = 1825,
    DEFENSEWALLN                                    = 1828,
    DEFENSEWALLNE                                   = 1829,
    DEFENSEWALLNW                                   = 1831,
    DEFENSEWALLS                                    = 1826,
    DEFENSEWALLSE                                   = 1832,
    DEFENSEWALLSW                                   = 1830,
    DEFENSEWALLW                                    = 1827,
    DEFILERBONESAMPLE                               = 1187,
    DEFILERMP                                       = 731,
    DEFILERMPBURROWED                               = 730,
    DEFILERMPDARKSWARMWEAPON                        = 816,
    DEFILERMPPLAGUEWEAPON                           = 859,
    DESERTPLANETSEARCHLIGHT                         = 654,
    DESERTPLANETSTREETLIGHT                         = 655,
    DESTRUCTIBLEBILLBOARDSCROLLINGTEXT              = 351,
    DESTRUCTIBLEBILLBOARDTALL                       = 350,
    DESTRUCTIBLEBULLHORNLIGHTS                      = 346,
    DESTRUCTIBLECITYDEBRIS2X4HORIZONTAL             = 625,
    DESTRUCTIBLECITYDEBRIS2X4VERTICAL               = 624,
    DESTRUCTIBLECITYDEBRIS2X6HORIZONTAL             = 627,
    DESTRUCTIBLECITYDEBRIS2X6VERTICAL               = 626,
    DESTRUCTIBLECITYDEBRIS4X4                       = 628,
    DESTRUCTIBLECITYDEBRISHUGEDIAGONALBLUR          = 630,
    DESTRUCTIBLECITYDEBRISHUGEDIAGONALULBR          = 631,
    DESTRUCTIBLEDEBRIS4X4                           = 364,
    DESTRUCTIBLEEXPEDITIONGATE6X6                   = 836,
    DESTRUCTIBLEGARAGE                              = 358,
    DESTRUCTIBLEGARAGELARGE                         = 359,
    DESTRUCTIBLEGATEDIAGONALBLUR                    = 990,
    DESTRUCTIBLEGATEDIAGONALBLURLOWERED             = 984,
    DESTRUCTIBLEGATEDIAGONALULBR                    = 991,
    DESTRUCTIBLEGATEDIAGONALULBRLOWERED             = 985,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTAL              = 993,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTALBF            = 992,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTALBFLOWERED     = 986,
    DESTRUCTIBLEGATESTRAIGHTHORIZONTALLOWERED       = 987,
    DESTRUCTIBLEGATESTRAIGHTVERTICAL                = 995,
    DESTRUCTIBLEGATESTRAIGHTVERTICALLF              = 994,
    DESTRUCTIBLEGATESTRAIGHTVERTICALLFLOWERED       = 988,
    DESTRUCTIBLEGATESTRAIGHTVERTICALLOWERED         = 989,
    DESTRUCTIBLEICE2X4HORIZONTAL                    = 645,
    DESTRUCTIBLEICE2X4VERTICAL                      = 644,
    DESTRUCTIBLEICE2X6HORIZONTAL                    = 647,
    DESTRUCTIBLEICE2X6VERTICAL                      = 646,
    DESTRUCTIBLEICE4X4                              = 648,
    DESTRUCTIBLEICE6X6                              = 649,
    DESTRUCTIBLEICEDIAGONALHUGEBLUR                 = 651,
    DESTRUCTIBLEICEDIAGONALHUGEULBR                 = 650,
    DESTRUCTIBLEICEHORIZONTALHUGE                   = 653,
    DESTRUCTIBLEICEVERTICALHUGE                     = 652,
    DESTRUCTIBLEKORHALFLAG                          = 1233,
    DESTRUCTIBLEKORHALFOLIAGE                       = 1236,
    DESTRUCTIBLEKORHALPODIUM                        = 1234,
    DESTRUCTIBLEKORHALTREE                          = 1235,
    DESTRUCTIBLERAMPDIAGONALHUGEBLUR                = 373,
    DESTRUCTIBLERAMPDIAGONALHUGEULBR                = 372,
    DESTRUCTIBLERAMPHORIZONTALHUGE                  = 375,
    DESTRUCTIBLERAMPVERTICALHUGE                    = 374,
    DESTRUCTIBLEROCK2X4HORIZONTAL                   = 367,
    DESTRUCTIBLEROCK2X4VERTICAL                     = 366,
    DESTRUCTIBLEROCK2X6HORIZONTAL                   = 369,
    DESTRUCTIBLEROCK2X6VERTICAL                     = 368,
    DESTRUCTIBLEROCK4X4                             = 370,
    DESTRUCTIBLEROCK6X6WEAK                         = 613,
    DESTRUCTIBLEROCKEX12X4HORIZONTAL                = 635,
    DESTRUCTIBLEROCKEX12X4VERTICAL                  = 634,
    DESTRUCTIBLEROCKEX12X6HORIZONTAL                = 637,
    DESTRUCTIBLEROCKEX12X6VERTICAL                  = 636,
    DESTRUCTIBLEROCKEX14X4                          = 638,
    DESTRUCTIBLEROCKEX16X6                          = 639,
    DESTRUCTIBLEROCKEX1DIAGONALHUGEULBR             = 640,
    DESTRUCTIBLEROCKEX1HORIZONTALHUGE               = 643,
    DESTRUCTIBLEROCKEX1VERTICALHUGE                 = 642,
    DESTRUCTIBLESANDBAGS                            = 1237,
    DESTRUCTIBLESEARCHLIGHT                         = 345,
    DESTRUCTIBLESIGNSCONSTRUCTION                   = 354,
    DESTRUCTIBLESIGNSDIRECTIONAL                    = 353,
    DESTRUCTIBLESIGNSFUNNY                          = 355,
    DESTRUCTIBLESIGNSICONS                          = 356,
    DESTRUCTIBLESIGNSWARNING                        = 357,
    DESTRUCTIBLESPACEPLATFORMBARRIER                = 352,
    DESTRUCTIBLESPACEPLATFORMSIGN                   = 348,
    DESTRUCTIBLESTOREFRONTCITYPROPS                 = 349,
    DESTRUCTIBLESTREETLIGHT                         = 347,
    DESTRUCTIBLETRAFFICSIGNAL                       = 360,
    DESTRUCTIBLEWALLCORNER45                        = 1804,
    DESTRUCTIBLEWALLCORNER45BL90R                   = 1807,
    DESTRUCTIBLEWALLCORNER45BR90T                   = 1808,
    DESTRUCTIBLEWALLCORNER45UL90B                   = 1806,
    DESTRUCTIBLEWALLCORNER45ULBL                    = 1801,
    DESTRUCTIBLEWALLCORNER45ULUR                    = 1802,
    DESTRUCTIBLEWALLCORNER45UR90L                   = 1805,
    DESTRUCTIBLEWALLCORNER45URBR                    = 1803,
    DESTRUCTIBLEWALLCORNER90B45UR                   = 1812,
    DESTRUCTIBLEWALLCORNER90BR                      = 1814,
    DESTRUCTIBLEWALLCORNER90L45BR                   = 1809,
    DESTRUCTIBLEWALLCORNER90LB                      = 1815,
    DESTRUCTIBLEWALLCORNER90LT                      = 1816,
    DESTRUCTIBLEWALLCORNER90R45UL                   = 1811,
    DESTRUCTIBLEWALLCORNER90T45BL                   = 1810,
    DESTRUCTIBLEWALLCORNER90TR                      = 1813,
    DESTRUCTIBLEWALLDIAGONALBLUR                    = 1817,
    DESTRUCTIBLEWALLDIAGONALBLURLF                  = 1818,
    DESTRUCTIBLEWALLDIAGONALULBR                    = 1820,
    DESTRUCTIBLEWALLDIAGONALULBRLF                  = 1819,
    DESTRUCTIBLEWALLSTRAIGHTHORIZONTAL              = 1823,
    DESTRUCTIBLEWALLSTRAIGHTHORIZONTALBF            = 1824,
    DESTRUCTIBLEWALLSTRAIGHTVERTICAL                = 1821,
    DESTRUCTIBLEWALLVERTICALLF                      = 1822,
    DESTRUCTIBLEZERGINFESTATION3X3                  = 837,
    DEVASTATORMISSILEWEAPON                         = 1089,
    DEVILDOG                                        = 925,
    DEVOURERCOCOONMP                                = 728,
    DEVOURERMP                                      = 729,
    DEVOURERMPWEAPONMISSILE                         = 815,
    DEVOURERTISSUEDOODAD                            = 1028,
    DEVOURERTISSUEMISSILE                           = 1034,
    DEVOURERTISSUESAMPLE                            = 1188,
    DEVOURERTISSUESAMPLETUBE                        = 1143,
    DIAMONDBACK                                     = 1140,
    DIGESTERCREEPSPRAYTARGETUNIT                    = 565,
    DIGESTERCREEPSPRAYUNIT                          = 566,
    DOG                                             = 336,
    DOMINIONKILLTEAM                                = 1138,
    DOMINIONKILLTEAMLMWEAPON                        = 1128,
    DRAKKENLASERDRILL                               = 1245,
    DRBATTLECRUISERALMWEAPON                        = 1123,
    DRBATTLECRUISERGLMWEAPON                        = 1124,
    DUKESREVENGE                                    = 930,
    DUMPTRUCK                                       = 1697,
    DUSKWING                                        = 929,
    DUSKWINGWEAPON                                  = 1085,
    EGGPURPLE                                       = 1767,
    ELEVATORBLOCKER                                 = 1161,
    ELSECARO_COLONIST_HUT                           = 891,
    EMP2WEAPON                                      = 285,
    ENEMYPATHINGBLOCKER16X16                        = 480,
    ENEMYPATHINGBLOCKER1X1                          = 476,
    ENEMYPATHINGBLOCKER2X2                          = 477,
    ENEMYPATHINGBLOCKER4X4                          = 478,
    ENEMYPATHINGBLOCKER8X8                          = 479,
    EXPERIMENTALPLASMAGUNWEAPON                     = 1080,
    EXPLODINGBARRELLARGE                            = 1305,
    EXTENDINGBRIDGENEWIDE10                         = 510,
    EXTENDINGBRIDGENEWIDE10OUT                      = 509,
    EXTENDINGBRIDGENEWIDE12                         = 514,
    EXTENDINGBRIDGENEWIDE12OUT                      = 513,
    EXTENDINGBRIDGENEWIDE8                          = 506,
    EXTENDINGBRIDGENEWIDE8OUT                       = 505,
    EXTENDINGBRIDGENWWIDE10                         = 512,
    EXTENDINGBRIDGENWWIDE10OUT                      = 511,
    EXTENDINGBRIDGENWWIDE12                         = 516,
    EXTENDINGBRIDGENWWIDE12OUT                      = 515,
    EXTENDINGBRIDGENWWIDE8                          = 508,
    EXTENDINGBRIDGENWWIDE8OUT                       = 507,
    EYESTALKWEAPON                                  = 576,
    FACTORYTECHREACTOR                              = 959,
    FEEDERLING                                      = 1219,
    FIREBAT                                         = 1139,
    FIREWORKSBLUE                                   = 1834,
    FIREWORKSRED                                    = 1835,
    FIREWORKSYELLOW                                 = 1836,
    FLAMINGBETTY                                    = 915,
    FLATBEDTRUCK                                    = 1699,
    FLYOVERUNIT                                     = 854,
    FOOD1000                                        = 1722,
    FREIGHTCAR                                      = 1715,
    FRENZYWEAPON                                    = 294,
    FUNGALGROWTHMISSILE                             = 313,
    FUSIONREACTOR                                   = 1193,
    G4CHARGEWEAPON                                  = 1141,
    GASCANISTER                                     = 1673,
    GASCANISTERPROTOSS                              = 1674,
    GASCANISTERZERG                                 = 1675,
    GATECONTROLUNIT                                 = 1149,
    GHOSTALTERNATE                                  = 144,
    GHOSTLASERLINES                                 = 1287,
    GHOSTNOVA                                       = 145,
    GLAIVEWURMBOUNCEWEAPON                          = 384,
    GLAIVEWURMM2WEAPON                              = 282,
    GLAIVEWURMM3WEAPON                              = 283,
    GLAIVEWURMWEAPON                                = 281,
    GLOBESTATUE                                     = 382,
    GOLIATH                                         = 904,
    GOLIATHAWEAPON                                  = 1117,
    GRAPPLEWEAPON                                   = 821,
    GUARDIANCOCOONMP                                = 726,
    GUARDIANMP                                      = 727,
    GUARDIANMPWEAPON                                = 814,
    HAILSTORMMISSILESWEAPON                         = 1095,
    HAMMERSECURITY                                  = 927,
    HAMMERSECURITYLMWEAPON                          = 1091,
    HEALINGPOTIONTESTINSTANT                        = 979,
    HEALINGPOTIONTESTTARGET                         = 1785,
    HELPEREMITTERSELECTIONARROW                     = 394,
    HELSANGELASSAULT                                = 976,
    HELSANGELFIGHTER                                = 928,
    HELSANGELFIGHTERWEAPON                          = 1122,
    HERC                                            = 838,
    HERCPLACEMENT                                   = 820,
    HERCULES                                        = 1273,
    HERCULESLANDER                                  = 967,
    HERCULESLANDERFLYING                            = 966,
    HERONUKE                                        = 932,
    HIGHTEMPLARSKINPREVIEW                          = 1887,
    HIGHTEMPLARWEAPONMISSILE                        = 1914,
    HIVEMINDEMULATOR                                = 1212,
    HOLDINGPEN                                      = 1228,
    HOMELARGE                                       = 1159,
    HOMESMALL                                       = 1160,
    HUNTERKILLER                                    = 947,
    HUNTERKILLERBURROWED                            = 946,
    HUNTERKILLERWEAPON                              = 1116,
    HUNTERSEEKERWEAPON                              = 267,
    HURRICANEMISSILELEFT                            = 1126,
    HURRICANEMISSILERIGHT                           = 1125,
    HUT                                             = 1659,
    HYBRID                                          = 1299,
    HYBRIDCPLASMAWEAPON                             = 1107,
    HYBRIDDESTROYER                                 = 1297,
    HYBRIDREAVER                                    = 1298,
    HYBRIDSINGULARITYFEEDBACKWEAPON                 = 1127,
    HYDRALISKIMPALEMISSILE                          = 803,
    HYPERION                                        = 1717,
    HYPERIONALMWEAPON                               = 1112,
    HYPERIONLMWEAPON                                = 1111,
    HYPERIONYAMATOSPECIALWEAPON                     = 1110,
    ICE2X2NONCONJOINED                              = 592,
    ICEPROTOSSCRATES                                = 593,
    INFESTABLEBIODOME                               = 1729,
    INFESTABLECOLONISTBIODOME                       = 1730,
    INFESTABLECOLONISTHUT                           = 1662,
    INFESTABLEHUT                                   = 1661,
    INFESTATIONSPIRE                                = 1751,
    INFESTEDABOMINATION                             = 945,
    INFESTEDABOMINATIONBURROWED                     = 944,
    INFESTEDACIDSPINESWEAPON                        = 1919,
    INFESTEDARMORY                                  = 1702,
    INFESTEDBARRACKS                                = 1703,
    INFESTEDBUNKER                                  = 1704,
    INFESTEDCC                                      = 1705,
    INFESTEDCIVILIAN                                = 914,
    INFESTEDCIVILIANBURROWED                        = 916,
    INFESTEDCOCOON                                  = 1192,
    INFESTEDCOLONISTSHIP                            = 1771,
    INFESTEDENGBAY                                  = 1706,
    INFESTEDFACTORY                                 = 1707,
    INFESTEDMERCHAVEN                               = 1257,
    INFESTEDMISSILETURRET                           = 1710,
    INFESTEDREFINERY                                = 1708,
    INFESTEDSTARPORT                                = 1709,
    INFESTEDSUPPLY                                  = 1712,
    INFESTEDTERRAN                                  = 898,
    INFESTEDTERRANCAMPAIGN                          = 949,
    INFESTEDTERRANCAMPAIGNBURROWED                  = 948,
    INFESTEDTERRANSEGGPLACEMENT                     = 339,
    INFESTEDTERRANSWEAPON                           = 264,
    INFESTEDVENTBROODLORDEGG                        = 1069,
    INFESTEDVENTCORRUPTOREGG                        = 1070,
    INFESTEDVENTEGGMISSILE                          = 1078,
    INFESTEDVENTMUTALISKEGG                         = 1076,
    INFESTORENSNAREATTACKMISSILE                    = 1920,
    INFESTORTERRANBURROWED                          = 120,
    INFESTORTERRANSWEAPON                           = 340,
    INHIBITORZONEFLYINGLARGE                        = 1993,
    INHIBITORZONEFLYINGMEDIUM                       = 1992,
    INHIBITORZONEFLYINGSMALL                        = 1991,
    INHIBITORZONELARGE                              = 1984,
    INHIBITORZONEMEDIUM                             = 1983,
    INHIBITORZONESMALL                              = 1982,
    INVALID                                         = 0,
    INVISIBLEPYLON                                  = 1295,
    IONCANNONSWEAPON                                = 277,
    IPISTOLAD                                       = 1200,
    ITEMGRAVITYBOMBS                                = 1838,
    ITEMGRAVITYBOMBSWEAPON                          = 1130,
    ITEMGRENADES                                    = 1839,
    ITEMGRENADESWEAPON                              = 1129,
    ITEMMEDKIT                                      = 1840,
    ITEMMINES                                       = 1841,
    JORIUMSTOCKPILE                                 = 1724,
    KARAKMALE                                       = 323,
    KARASS                                          = 1294,
    KARASSWEAPON                                    = 1106,
    KD8CHARGEWEAPON                                 = 831,
    KERRIGAN                                        = 1289,
    KERRIGANCHAR                                    = 934,
    KERRIGANCHARBURROWED                            = 933,
    KERRIGANCHARWEAPON                              = 1088,
    KERRIGANEGG                                     = 1247,
    KERRIGANWEAPON                                  = 1086,
    L800ETC_AD                                      = 1201,
    LABBOT                                          = 661,
    LARVARELEASEMISSILE                             = 292,
    LEVIATHAN                                       = 1756,
    LEVIATHANSCOURGEMISSILE                         = 1119,
    LIBERATORAGMISSILE                              = 829,
    LIBERATORDAMAGEMISSILE                          = 828,
    LIBERATORMISSILE                                = 827,
    LIBERATORSKINPREVIEW                            = 1890,
    LIGHTNINGBOMBWEAPON                             = 819,
    LOADOUTSPRAY_1                                  = 1967,
    LOADOUTSPRAY_10                                 = 1976,
    LOADOUTSPRAY_11                                 = 1977,
    LOADOUTSPRAY_12                                 = 1978,
    LOADOUTSPRAY_13                                 = 1979,
    LOADOUTSPRAY_14                                 = 1980,
    LOADOUTSPRAY_2                                  = 1968,
    LOADOUTSPRAY_3                                  = 1969,
    LOADOUTSPRAY_4                                  = 1970,
    LOADOUTSPRAY_5                                  = 1971,
    LOADOUTSPRAY_6                                  = 1972,
    LOADOUTSPRAY_7                                  = 1973,
    LOADOUTSPRAY_8                                  = 1974,
    LOADOUTSPRAY_9                                  = 1975,
    LOCUSTMPEGGAMISSILEWEAPON                       = 584,
    LOCUSTMPEGGBMISSILEWEAPON                       = 585,
    LOCUSTMPPRECURSOR                               = 799,
    LOCUSTMPWEAPON                                  = 586,
    LOGISTICSHEADQUARTERS                           = 1711,
    LOKI                                            = 1136,
    LOKIHURRICANEMISSILELEFT                        = 1082,
    LOKIHURRICANEMISSILERIGHT                       = 1083,
    LOKIYAMATOWEAPON                                = 1109,
    LONGBOLTMISSILEWEAPON                           = 274,
    LURKER                                          = 911,
    LURKERBURROWED                                  = 912,
    LURKERDEN                                       = 901,
    LURKEREGG                                       = 910,
    LYOTE                                           = 321,
    MAAR                                            = 1296,
    MAARWARPINUNIT                                  = 1766,
    MAINCELLBLOCK                                   = 1288,
    MARSARABRIDGEBLUR                               = 1779,
    MARSARABRIDGEBRUL                               = 1780,
    MEDIC                                           = 1731,
    MENGSKHOLOGRAMBILLBOARD                         = 1718,
    MENGSKSTATUE                                    = 380,
    MENGSKSTATUEALONE                               = 379,
    MERCCOMPOUND                                    = 899,
    MERCENARYFORTRESS                               = 1274,
    METALGATEDIAGONALBLUR                           = 1002,
    METALGATEDIAGONALBLURLOWERED                    = 996,
    METALGATEDIAGONALULBR                           = 1003,
    METALGATEDIAGONALULBRLOWERED                    = 997,
    METALGATESTRAIGHTHORIZONTAL                     = 1005,
    METALGATESTRAIGHTHORIZONTALBF                   = 1004,
    METALGATESTRAIGHTHORIZONTALBFLOWERED            = 998,
    METALGATESTRAIGHTHORIZONTALLOWERED              = 999,
    METALGATESTRAIGHTVERTICAL                       = 1007,
    METALGATESTRAIGHTVERTICALLF                     = 1006,
    METALGATESTRAIGHTVERTICALLFLOWERED              = 1000,
    METALGATESTRAIGHTVERTICALLOWERED                = 1001,
    MINDSIPHONRETURNWEAPON                          = 1246,
    MINDSIPHONWEAPON                                = 1268,
    MINERALCRYSTAL                                  = 1676,
    MINERALFIELDOPAQUE                              = 1997,
    MINERALFIELDOPAQUE900                           = 1998,
    MINERMALE                                       = 1654,
    MOHANDAR                                        = 939,
    MONLYTHARTIFACTFORCEFIELD                       = 1258,
    MONLYTHFORCEFIELDSTATUE                         = 1259,
    MONOLITH                                        = 1144,
    MOOPY                                           = 839,
    MOTHERSHIPCOREWEAPONWEAPON                      = 579,
    MULTIKILLOBJECT                                 = 395,
    MURLOCMARINE                                    = 1223,
    MUTALISKEGG                                     = 1075,
    MUTALISKEGGMISSILE                              = 1077,
    NATURALGAS                                      = 1679,
    NATURALMINERALS                                 = 1680,
    NATURALMINERALSRED                              = 1681,
    NEEDLESPINESWEAPON                              = 262,
    NEURALPARASITETENTACLEMISSILE                   = 314,
    NEURALPARASITEWEAPON                            = 265,
    NEUTRAL_BATTLESTATIONMINERALFIELD               = 886,
    NEUTRAL_BATTLESTATIONMINERALFIELD750            = 887,
    NEUTRAL_COLLAPSIBLEROCKTOWERDEBRIS              = 490,
    NEUTRAL_COLLAPSIBLEROCKTOWERDIAGONAL            = 588,
    NEUTRAL_COLLAPSIBLEROCKTOWERPUSHUNIT            = 561,
    NEUTRAL_COLLAPSIBLETERRANTOWERDEBRIS            = 485,
    NEUTRAL_COLLAPSIBLETERRANTOWERDIAGONAL          = 589,
    NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNIT          = 562,
    NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPLEFT  = 559,
    NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPRIGHT = 560,
    NEUTRAL_COLLAPSIBLETERRANTOWERRAMPLEFT          = 590,
    NEUTRAL_COLLAPSIBLETERRANTOWERRAMPRIGHT         = 591,
    NEUTRAL_DEBRISRAMPLEFT                          = 486,
    NEUTRAL_DEBRISRAMPRIGHT                         = 487,
    NEUTRAL_DESTRUCTIBLECITYDEBRIS6X6               = 629,
    NEUTRAL_DESTRUCTIBLEDEBRIS6X6                   = 365,
    NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEBLUR  = 377,
    NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEULBR  = 376,
    NEUTRAL_DESTRUCTIBLEROCK6X6                     = 371,
    NEUTRAL_DESTRUCTIBLEROCKEX1DIAGONALHUGEBLUR     = 641,
    NEUTRAL_FORCEFIELD                              = 135,
    NEUTRAL_KARAKFEMALE                             = 324,
    NEUTRAL_LABMINERALFIELD                         = 665,
    NEUTRAL_LABMINERALFIELD750                      = 666,
    NEUTRAL_MINERALFIELD                            = 341,
    NEUTRAL_MINERALFIELD450                         = 1996,
    NEUTRAL_MINERALFIELD750                         = 483,
    NEUTRAL_PROTOSSVESPENEGEYSER                    = 608,
    NEUTRAL_PURIFIERMINERALFIELD                    = 884,
    NEUTRAL_PURIFIERMINERALFIELD750                 = 885,
    NEUTRAL_PURIFIERRICHMINERALFIELD                = 796,
    NEUTRAL_PURIFIERRICHMINERALFIELD750             = 797,
    NEUTRAL_PURIFIERVESPENEGEYSER                   = 880,
    NEUTRAL_RICHMINERALFIELD                        = 146,
    NEUTRAL_RICHMINERALFIELD750                     = 147,
    NEUTRAL_RICHVESPENEGEYSER                       = 344,
    NEUTRAL_SCANTIPEDE                              = 335,
    NEUTRAL_SHAKURASVESPENEGEYSER                   = 881,
    NEUTRAL_SPACEPLATFORMGEYSER                     = 343,
    NEUTRAL_UNBUILDABLEBRICKSDESTRUCTIBLE           = 473,
    NEUTRAL_UNBUILDABLEPLATESDESTRUCTIBLE           = 474,
    NEUTRAL_UTILITYBOT                              = 330,
    NEUTRAL_VESPENEGEYSER                           = 342,
    NEUTRAL_XELNAGATOWER                            = 149,
    NEWFOLSOMPRISONENTRANCE                         = 1759,
    NEWSARCTURUSINTERVIEWSET                        = 1533,
    NEWSARCTURUSPRESSROOM                           = 1534,
    NEWSMEINHOFFREFUGEECENTER                       = 1536,
    NEWSRAYNORLOGO                                  = 1537,
    NEWSTVEFFECT                                    = 1538,
    NOVA                                            = 1721,
    NUKENOODLESCOMMERCIAL                           = 1202,
    NUKEPACK                                        = 1761,
    NUKESILONOVA                                    = 1025,
    NYDUSCANALATTACKER                              = 491,
    NYDUSCANALATTACKERWEAPON                        = 567,
    NYDUSCANALCREEPER                               = 492,
    NYDUSWORMLAVADEATH                              = 1163,
    OBELISK                                         = 1145,
    ODIN                                            = 1026,
    ODINAAWEAPON                                    = 1084,
    ODINBUILD                                       = 1760,
    ODINWRECKAGE                                    = 931,
    OMEGALISK                                       = 943,
    OMEGALISKBURROWED                               = 942,
    ORACLEWEAPON                                    = 808,
    OVERLORDGENERATECREEPKEYBIND                    = 378,
    OVERMIND                                        = 1255,
    OVERMINDREMAINS                                 = 1256,
    PALLETGAS                                       = 1677,
    PALLETMINERALS                                  = 1678,
    PARASITESPOREWEAPON                             = 288,
    PARASITICBOMBMISSILE                            = 823,
    PATHINGBLOCKER1X1                               = 389,
    PATHINGBLOCKER2X2                               = 390,
    PATHINGBLOCKERRADIUS1                           = 633,
    PERDITIONTURRET                                 = 921,
    PERDITIONTURRETUNDERGROUND                      = 920,
    PERMANENTCREEPBLOCKER1X1                        = 388,
    PHOTONCANNONWEAPON                              = 287,
    PHYSICSCAPSULE                                  = 615,
    PHYSICSCUBE                                     = 616,
    PHYSICSCYLINDER                                 = 617,
    PHYSICSKNOT                                     = 618,
    PHYSICSL                                        = 619,
    PHYSICSPRIMITIVES                               = 620,
    PHYSICSSPHERE                                   = 621,
    PHYSICSSTAR                                     = 622,
    PICKUPCHRONORIFTCHARGE                          = 1672,
    PICKUPCHRONORIFTDEVICE                          = 1671,
    PICKUPENERGY100                                 = 1688,
    PICKUPENERGY25                                  = 1686,
    PICKUPENERGY50                                  = 1687,
    PICKUPENERGYFULL                                = 1689,
    PICKUPGRENADES                                  = 1665,
    PICKUPHEALTH100                                 = 1684,
    PICKUPHEALTH25                                  = 1682,
    PICKUPHEALTH50                                  = 1683,
    PICKUPHEALTHFULL                                = 1685,
    PICKUPMANARECHARGE                              = 1669,
    PICKUPMEDICRECHARGE                             = 1668,
    PICKUPMINES                                     = 1690,
    PICKUPPALLETGAS                                 = 596,
    PICKUPPALLETMINERALS                            = 597,
    PICKUPPLASMAGUN                                 = 1666,
    PICKUPPLASMAROUNDS                              = 1667,
    PICKUPPSISTORM                                  = 1691,
    PICKUPRESTORATIONCHARGE                         = 1670,
    PICKUPSCRAPSALVAGE1X1                           = 598,
    PICKUPSCRAPSALVAGE2X2                           = 599,
    PICKUPSCRAPSALVAGE3X3                           = 600,
    PLASMATORPEDOESWEAPON                           = 1210,
    PLATFORMCONNECTOR                               = 1270,
    POINTDEFENSEDRONERELEASEWEAPON                  = 266,
    PORTCITY_BRIDGE_UNITE10                         = 785,
    PORTCITY_BRIDGE_UNITE10OUT                      = 784,
    PORTCITY_BRIDGE_UNITE12                         = 793,
    PORTCITY_BRIDGE_UNITE12OUT                      = 792,
    PORTCITY_BRIDGE_UNITE8                          = 777,
    PORTCITY_BRIDGE_UNITE8OUT                       = 776,
    PORTCITY_BRIDGE_UNITN10                         = 781,
    PORTCITY_BRIDGE_UNITN10OUT                      = 780,
    PORTCITY_BRIDGE_UNITN12                         = 789,
    PORTCITY_BRIDGE_UNITN12OUT                      = 788,
    PORTCITY_BRIDGE_UNITN8                          = 773,
    PORTCITY_BRIDGE_UNITN8OUT                       = 772,
    PORTCITY_BRIDGE_UNITNE10                        = 757,
    PORTCITY_BRIDGE_UNITNE10OUT                     = 756,
    PORTCITY_BRIDGE_UNITNE12                        = 765,
    PORTCITY_BRIDGE_UNITNE12OUT                     = 764,
    PORTCITY_BRIDGE_UNITNE8                         = 749,
    PORTCITY_BRIDGE_UNITNE8OUT                      = 748,
    PORTCITY_BRIDGE_UNITNW10                        = 761,
    PORTCITY_BRIDGE_UNITNW10OUT                     = 760,
    PORTCITY_BRIDGE_UNITNW12                        = 769,
    PORTCITY_BRIDGE_UNITNW12OUT                     = 768,
    PORTCITY_BRIDGE_UNITNW8                         = 753,
    PORTCITY_BRIDGE_UNITNW8OUT                      = 752,
    PORTCITY_BRIDGE_UNITS10                         = 783,
    PORTCITY_BRIDGE_UNITS10OUT                      = 782,
    PORTCITY_BRIDGE_UNITS12                         = 791,
    PORTCITY_BRIDGE_UNITS12OUT                      = 790,
    PORTCITY_BRIDGE_UNITS8                          = 775,
    PORTCITY_BRIDGE_UNITS8OUT                       = 774,
    PORTCITY_BRIDGE_UNITSE10                        = 759,
    PORTCITY_BRIDGE_UNITSE10OUT                     = 758,
    PORTCITY_BRIDGE_UNITSE12                        = 767,
    PORTCITY_BRIDGE_UNITSE12OUT                     = 766,
    PORTCITY_BRIDGE_UNITSE8                         = 751,
    PORTCITY_BRIDGE_UNITSE8OUT                      = 750,
    PORTCITY_BRIDGE_UNITSW10                        = 763,
    PORTCITY_BRIDGE_UNITSW10OUT                     = 762,
    PORTCITY_BRIDGE_UNITSW12                        = 771,
    PORTCITY_BRIDGE_UNITSW12OUT                     = 770,
    PORTCITY_BRIDGE_UNITSW8                         = 755,
    PORTCITY_BRIDGE_UNITSW8OUT                      = 754,
    PORTCITY_BRIDGE_UNITW10                         = 787,
    PORTCITY_BRIDGE_UNITW10OUT                      = 786,
    PORTCITY_BRIDGE_UNITW12                         = 795,
    PORTCITY_BRIDGE_UNITW12OUT                      = 794,
    PORTCITY_BRIDGE_UNITW8                          = 779,
    PORTCITY_BRIDGE_UNITW8OUT                       = 778,
    PORTJUNKER                                      = 1755,
    PREDATOR                                        = 1186,
    PRESERVERA                                      = 1775,
    PRESERVERB                                      = 1776,
    PRESERVERBASE                                   = 1774,
    PRESERVERC                                      = 1777,
    PRESERVERPRISON                                 = 1754,
    PRISONERCIVILIAN                                = 1230,
    PRISONERSPECTRE                                 = 1249,
    PRISONZEALOT                                    = 1250,
    PROTOSSCRATES                                   = 594,
    PROTOSSPSIELEMENTS                              = 1189,
    PROTOSSRELIC                                    = 1664,
    PROTOSSSNAKESEGMENTDEMO                         = 614,
    PROTOSS_ADEPT                                   = 311,
    PROTOSS_ADEPTPHASESHIFT                         = 801,
    PROTOSS_ARCHON                                  = 141,
    PROTOSS_ASSIMILATOR                             = 61,
    PROTOSS_ASSIMILATORRICH                         = 1994,
    PROTOSS_CARRIER                                 = 79,
    PROTOSS_COLOSSUS                                = 4,
    PROTOSS_CYBERNETICSCORE                         = 72,
    PROTOSS_DARKSHRINE                              = 69,
    PROTOSS_DARKTEMPLAR                             = 76,
    PROTOSS_DISRUPTOR                               = 694,
    PROTOSS_DISRUPTORPHASED                         = 733,
    PROTOSS_FLEETBEACON                             = 64,
    PROTOSS_FORGE                                   = 63,
    PROTOSS_GATEWAY                                 = 62,
    PROTOSS_HIGHTEMPLAR                             = 75,
    PROTOSS_IMMORTAL                                = 83,
    PROTOSS_INTERCEPTOR                             = 85,
    PROTOSS_MOTHERSHIP                              = 10,
    PROTOSS_MOTHERSHIPCORE                          = 488,
    PROTOSS_NEXUS                                   = 59,
    PROTOSS_OBSERVER                                = 82,
    PROTOSS_OBSERVERSIEGEMODE                       = 1911,
    PROTOSS_ORACLE                                  = 495,
    PROTOSS_ORACLESTASISTRAP                        = 732,
    PROTOSS_PHOENIX                                 = 78,
    PROTOSS_PHOTONCANNON                            = 66,
    PROTOSS_PROBE                                   = 84,
    PROTOSS_PYLON                                   = 60,
    PROTOSS_PYLONOVERCHARGED                        = 894,
    PROTOSS_ROBOTICSBAY                             = 70,
    PROTOSS_ROBOTICSFACILITY                        = 71,
    PROTOSS_SENTRY                                  = 77,
    PROTOSS_SHIELDBATTERY                           = 1910,
    PROTOSS_STALKER                                 = 74,
    PROTOSS_STARGATE                                = 67,
    PROTOSS_TEMPEST                                 = 496,
    PROTOSS_TEMPLARARCHIVE                          = 68,
    PROTOSS_TWILIGHTCOUNCIL                         = 65,
    PROTOSS_VOIDRAY                                 = 80,
    PROTOSS_WARPGATE                                = 133,
    PROTOSS_WARPPRISM                               = 81,
    PROTOSS_WARPPRISMPHASING                        = 136,
    PROTOSS_ZEALOT                                  = 73,
    PSIDISRUPTOR                                    = 1211,
    PSIINDOCTRINATOR                                = 1723,
    PSIOPSCOMMERCIAL                                = 1203,
    PSISHOCKWEAPON                                  = 1261,
    PUNISHERGRENADESLMWEAPON                        = 270,
    PURIFIER                                        = 1701,
    PURIFIERBLASTMARKUNIT                           = 1837,
    PYGALISK                                        = 1264,
    PYGALISKCOCOON                                  = 1027,
    QUEENMP                                         = 860,
    QUEENMPENSNAREMISSILE                           = 817,
    QUEENMPSPAWNBROODLINGSMISSILE                   = 818,
    QUESTIONMARK                                    = 1162,
    RAVAGERBURROWED                                 = 690,
    RAVAGERCORROSIVEBILEMISSILE                     = 802,
    RAVAGERWEAPONMISSILE                            = 810,
    RAVENREPAIRDRONE                                = 1913,
    RAVENREPAIRDRONERELEASEWEAPON                   = 1917,
    RAVENSCRAMBLERMISSILE                           = 1916,
    RAVENSHREDDERMISSILEWEAPON                      = 1918,
    RAYNOR                                          = 1275,
    RAYNOR01                                        = 1213,
    RAYNORCOMMANDO                                  = 1254,
    REAPERPLACEHOLDER                               = 152,
    REAPERPLACEMENT                                 = 1842,
    REDSTONELAVACRITTER                             = 123,
    REDSTONELAVACRITTERBURROWED                     = 121,
    REDSTONELAVACRITTERINJURED                      = 124,
    REDSTONELAVACRITTERINJUREDBURROWED              = 122,
    RELEASEINTERCEPTORSBEACON                       = 800,
    RENEGADELONGBOLTMISSILEWEAPON                   = 1939,
    RENEGADEMISSILETURRET                           = 1941,
    REPLICANT                                       = 840,
    REPTILECRATE                                    = 877,
    REPULSERFIELD10                                 = 1799,
    REPULSERFIELD12                                 = 1800,
    REPULSERFIELD6                                  = 1797,
    REPULSERFIELD8                                  = 1798,
    REPULSORCANNONWEAPON                            = 587,
    RESOURCEBLOCKER                                 = 569,
    RIPFIELDGENERATOR                               = 1281,
    RIPFIELDGENERATORSMALL                          = 1282,
    ROCKS2X2NONCONJOINED                            = 312,
    ROUGHTERRAIN                                    = 601,
    SCIENCEFACILITY                                 = 1191,
    SCIENCEVESSEL                                   = 1214,
    SCIENTIST                                       = 1653,
    SCOPETEST                                       = 481,
    SCOURGE                                         = 1215,
    SCOURGEMP                                       = 858,
    SCOUT                                           = 941,
    SCOUTAIRWEAPONLEFT                              = 1114,
    SCOUTAIRWEAPONRIGHT                             = 1115,
    SCOUTMP                                         = 856,
    SCOUTMPAIRWEAPONLEFT                            = 811,
    SCOUTMPAIRWEAPONRIGHT                           = 812,
    SCRAPHUGE                                       = 1229,
    SCRAPSALVAGE1X1                                 = 1251,
    SCRAPSALVAGE2X2                                 = 1252,
    SCRAPSALVAGE3X3                                 = 1253,
    SECRETDOCUMENTS                                 = 1185,
    SECURITYGATEDIAGONALBLUR                        = 1014,
    SECURITYGATEDIAGONALBLURLOWERED                 = 1008,
    SECURITYGATEDIAGONALULBR                        = 1015,
    SECURITYGATEDIAGONALULBRLOWERED                 = 1009,
    SECURITYGATESTRAIGHTHORIZONTAL                  = 1017,
    SECURITYGATESTRAIGHTHORIZONTALBF                = 1016,
    SECURITYGATESTRAIGHTHORIZONTALBFLOWERED         = 1010,
    SECURITYGATESTRAIGHTHORIZONTALLOWERED           = 1011,
    SECURITYGATESTRAIGHTVERTICAL                    = 1019,
    SECURITYGATESTRAIGHTVERTICALLF                  = 1018,
    SECURITYGATESTRAIGHTVERTICALLFLOWERED           = 1012,
    SECURITYGATESTRAIGHTVERTICALLOWERED             = 1013,
    SEEKERMISSILE                                   = 841,
    SELENDIS                                        = 940,
    SELENDISINTERCEPTOR                             = 917,
    SENTRYGUN                                       = 923,
    SENTRYGUNUNDERGROUND                            = 922,
    SHAKURASLIGHTBRIDGENE10                         = 716,
    SHAKURASLIGHTBRIDGENE10OUT                      = 715,
    SHAKURASLIGHTBRIDGENE12                         = 718,
    SHAKURASLIGHTBRIDGENE12OUT                      = 717,
    SHAKURASLIGHTBRIDGENE8                          = 714,
    SHAKURASLIGHTBRIDGENE8OUT                       = 713,
    SHAKURASLIGHTBRIDGENW10                         = 722,
    SHAKURASLIGHTBRIDGENW10OUT                      = 721,
    SHAKURASLIGHTBRIDGENW12                         = 724,
    SHAKURASLIGHTBRIDGENW12OUT                      = 723,
    SHAKURASLIGHTBRIDGENW8                          = 720,
    SHAKURASLIGHTBRIDGENW8OUT                       = 719,
    SHAPE4POINTSTAR                                 = 410,
    SHAPE5POINTSTAR                                 = 411,
    SHAPE6POINTSTAR                                 = 412,
    SHAPE8POINTSTAR                                 = 413,
    SHAPEAPPLE                                      = 462,
    SHAPEARROWPOINTER                               = 414,
    SHAPEBANANA                                     = 461,
    SHAPEBASEBALL                                   = 459,
    SHAPEBASEBALLBAT                                = 460,
    SHAPEBASKETBALL                                 = 456,
    SHAPEBOWL                                       = 415,
    SHAPEBOX                                        = 416,
    SHAPECAPSULE                                    = 417,
    SHAPECARROT                                     = 457,
    SHAPECASHLARGE                                  = 463,
    SHAPECASHMEDIUM                                 = 464,
    SHAPECASHSMALL                                  = 465,
    SHAPECHERRY                                     = 458,
    SHAPECONE                                       = 397,
    SHAPECRESCENTMOON                               = 418,
    SHAPECUBE                                       = 398,
    SHAPECYLINDER                                   = 399,
    SHAPEDECAHEDRON                                 = 419,
    SHAPEDIAMOND                                    = 420,
    SHAPEDODECAHEDRON                               = 400,
    SHAPEDOLLARSIGN                                 = 455,
    SHAPEEGG                                        = 429,
    SHAPEEUROSIGN                                   = 454,
    SHAPEFOOTBALL                                   = 421,
    SHAPEFOOTBALLCOLORED                            = 466,
    SHAPEGEMSTONE                                   = 422,
    SHAPEGOLFBALL                                   = 396,
    SHAPEGOLFCLUB                                   = 452,
    SHAPEGRAPE                                      = 453,
    SHAPEHAND                                       = 451,
    SHAPEHEART                                      = 423,
    SHAPEHOCKEYPUCK                                 = 450,
    SHAPEHOCKEYSTICK                                = 449,
    SHAPEHORSESHOE                                  = 448,
    SHAPEICOSAHEDRON                                = 401,
    SHAPEJACK                                       = 424,
    SHAPELEMON                                      = 446,
    SHAPELEMONSMALL                                 = 467,
    SHAPEMONEYBAG                                   = 447,
    SHAPEO                                          = 445,
    SHAPEOCTAHEDRON                                 = 402,
    SHAPEORANGE                                     = 443,
    SHAPEORANGESMALL                                = 468,
    SHAPEPEANUT                                     = 444,
    SHAPEPEAR                                       = 441,
    SHAPEPINEAPPLE                                  = 442,
    SHAPEPLUSSIGN                                   = 425,
    SHAPEPOUNDSIGN                                  = 440,
    SHAPEPYRAMID                                    = 403,
    SHAPERAINBOW                                    = 438,
    SHAPEROUNDEDCUBE                                = 404,
    SHAPESADFACE                                    = 439,
    SHAPESHAMROCK                                   = 426,
    SHAPESMILEYFACE                                 = 436,
    SHAPESOCCERBALL                                 = 437,
    SHAPESPADE                                      = 427,
    SHAPESPHERE                                     = 405,
    SHAPESTRAWBERRY                                 = 435,
    SHAPETENNISBALL                                 = 434,
    SHAPETETRAHEDRON                                = 406,
    SHAPETHICKTORUS                                 = 407,
    SHAPETHINTORUS                                  = 408,
    SHAPETORUS                                      = 409,
    SHAPETREASURECHESTCLOSED                        = 470,
    SHAPETREASURECHESTOPEN                          = 469,
    SHAPETUBE                                       = 428,
    SHAPEWATERMELON                                 = 432,
    SHAPEWATERMELONSMALL                            = 471,
    SHAPEWONSIGN                                    = 433,
    SHAPEX                                          = 431,
    SHAPEYENSIGN                                    = 430,
    SHEEP                                           = 337,
    SHIPALARM                                       = 1204,
    SHORTBRIDGEHORIZONTAL                           = 1782,
    SHORTBRIDGEVERTICAL                             = 1781,
    SIEGEBREAKER                                    = 919,
    SIEGEBREAKERSIEGED                              = 918,
    SIEGETANKSKINPREVIEW                            = 1889,
    SLAYNELEMENTAL                                  = 879,
    SLAYNELEMENTALGRABAIRUNIT                       = 833,
    SLAYNELEMENTALGRABGROUNDUNIT                    = 834,
    SLAYNELEMENTALGRABWEAPON                        = 832,
    SLAYNELEMENTALWEAPON                            = 835,
    SLAYNSWARMHOSTSPAWNFLYER                        = 878,
    SMADJUTANT                                      = 1619,
    SMADJUTANTHOLOGRAM                              = 1620,
    SMANNABELLE                                     = 1634,
    SMARCTURUSHOLOGRAM                              = 1647,
    SMARCTURUSMENGSK                                = 1646,
    SMARMORYBANSHEE                                 = 1508,
    SMARMORYBANSHEEPHCRATE                          = 1515,
    SMARMORYDROPSHIP                                = 1509,
    SMARMORYDROPSHIPPHCRATE                         = 1516,
    SMARMORYGHOSTCRATE                              = 1513,
    SMARMORYGHOSTCRATEPHCRATE                       = 1520,
    SMARMORYRIFLE                                   = 1522,
    SMARMORYSPECTRECRATE                            = 1514,
    SMARMORYSPECTRECRATEPHCRATE                     = 1521,
    SMARMORYSPIDERMINE                              = 1512,
    SMARMORYSPIDERMINEPHCRATE                       = 1519,
    SMARMORYTANK                                    = 1510,
    SMARMORYTANKPHCRATE                             = 1517,
    SMARMORYVIKING                                  = 1511,
    SMARMORYVIKINGPHCRATE                           = 1518,
    SMBANSHEE                                       = 1506,
    SMBOUNTYHUNTER                                  = 1527,
    SMBRALIK                                        = 1633,
    SMBRIDGEPLANETAGRIA                             = 1394,
    SMBRIDGEPLANETAIUR                              = 1395,
    SMBRIDGEPLANETAVERNUS                           = 1396,
    SMBRIDGEPLANETBELSHIR                           = 1397,
    SMBRIDGEPLANETCASTANAR                          = 1398,
    SMBRIDGEPLANETCHAR                              = 1399,
    SMBRIDGEPLANETHAVEN                             = 1400,
    SMBRIDGEPLANETKORHAL                            = 1401,
    SMBRIDGEPLANETMEINHOFF                          = 1402,
    SMBRIDGEPLANETMONLYTH                           = 1403,
    SMBRIDGEPLANETNEWFOLSOM                         = 1404,
    SMBRIDGEPLANETPORTZION                          = 1405,
    SMBRIDGEPLANETREDSTONE                          = 1406,
    SMBRIDGEPLANETSHAKURAS                          = 1407,
    SMBRIDGEPLANETSPACE                             = 1392,
    SMBRIDGEPLANETSPACEASTEROIDS                    = 1393,
    SMBRIDGEPLANETTARSONIS                          = 1408,
    SMBRIDGEPLANETTYPHON                            = 1409,
    SMBRIDGEPLANETTYRADOR                           = 1410,
    SMBRIDGEPLANETULAAN                             = 1411,
    SMBRIDGEPLANETULNAR                             = 1412,
    SMBRIDGEPLANETVALHALLA                          = 1413,
    SMBRIDGEPLANETXIL                               = 1414,
    SMBRIDGEPLANETZHAKULDAS                         = 1415,
    SMBRIDGEWINDOWSPACE                             = 1391,
    SMCADE                                          = 1631,
    SMCAMERABRIDGE                                  = 1309,
    SMCAMERATERRAN01                                = 1324,
    SMCAMERATERRAN02A                               = 1325,
    SMCAMERATERRAN02B                               = 1326,
    SMCAMERATERRAN03                                = 1327,
    SMCAMERATERRAN04                                = 1328,
    SMCAMERATERRAN04A                               = 1329,
    SMCAMERATERRAN04B                               = 1330,
    SMCAMERATERRAN05                                = 1331,
    SMCAMERATERRAN06A                               = 1332,
    SMCAMERATERRAN06B                               = 1333,
    SMCAMERATERRAN06C                               = 1334,
    SMCAMERATERRAN07                                = 1335,
    SMCAMERATERRAN08                                = 1336,
    SMCAMERATERRAN09                                = 1337,
    SMCAMERATERRAN10                                = 1338,
    SMCAMERATERRAN11                                = 1339,
    SMCAMERATERRAN12                                = 1340,
    SMCAMERATERRAN13                                = 1341,
    SMCAMERATERRAN14                                = 1342,
    SMCAMERATERRAN15                                = 1343,
    SMCAMERATERRAN16                                = 1344,
    SMCAMERATERRAN17                                = 1345,
    SMCAMERATERRAN20                                = 1346,
    SMCHARBATTLEFIELDENDPROPS                       = 1421,
    SMCHARBATTLEZONEARTIFACTHS                      = 1375,
    SMCHARBATTLEZONEBRIEFCASEHS                     = 1378,
    SMCHARBATTLEZONEBRIEFINGSET                     = 1379,
    SMCHARBATTLEZONEBRIEFINGSET2                    = 1380,
    SMCHARBATTLEZONEBRIEFINGSETLEFT                 = 1381,
    SMCHARBATTLEZONEBRIEFINGSETRIGHT                = 1382,
    SMCHARBATTLEZONEDROPSHIPHS                      = 1377,
    SMCHARBATTLEZONEFLAG                            = 1367,
    SMCHARBATTLEZONERADIOHS                         = 1376,
    SMCHARBATTLEZONESET                             = 1370,
    SMCHARBATTLEZONESET2                            = 1371,
    SMCHARBATTLEZONESET3                            = 1372,
    SMCHARBATTLEZONESET4                            = 1373,
    SMCHARBATTLEZONESET5                            = 1374,
    SMCHARBATTLEZONESHADOWBOX                       = 1615,
    SMCHARBATTLEZONETURRET                          = 1422,
    SMCHARCUTSCENES00                               = 1471,
    SMCHARCUTSCENES01                               = 1472,
    SMCHARCUTSCENES02                               = 1473,
    SMCHARCUTSCENES03                               = 1474,
    SMCHARGATLINGGUN                                = 1526,
    SMCHARINTERACTIVE02SKYPARALLAX                  = 1617,
    SMCHARINTERACTIVESKYPARALLAX                    = 1616,
    SMCIVILIAN                                      = 1528,
    SMCOOPER                                        = 1642,
    SMDONNYVERMILLION                               = 1542,
    SMDONNYVERMILLIONDEATH                          = 1543,
    SMDONNYVERMILLIONSET                            = 1535,
    SMDROPSHIP                                      = 1523,
    SMDROPSHIPBLUE                                  = 1524,
    SMEARL                                          = 1635,
    SMFIREBAT                                       = 1622,
    SMFIREBATPHCRATE                                = 1624,
    SMFIRSTOFFICER                                  = 1347,
    SMFLY                                           = 1390,
    SMGENERICMALEGREASEMONKEY01                     = 1637,
    SMGENERICMALEGREASEMONKEY02                     = 1638,
    SMGENERICMALEOFFICER01                          = 1639,
    SMGENERICMALEOFFICER02                          = 1640,
    SMHALL                                          = 1632,
    SMHAVENPLANET                                   = 1418,
    SMHILL                                          = 1643,
    SMHYDRALISK                                     = 1649,
    SMHYDRALISKDEAD                                 = 1650,
    SMHYPERIONARMORER                               = 1531,
    SMHYPERIONARMORYSPACELIGHTING                   = 1554,
    SMHYPERIONARMORYSTAGE1SET                       = 1550,
    SMHYPERIONARMORYSTAGE1SET01                     = 1551,
    SMHYPERIONARMORYSTAGE1SET02                     = 1552,
    SMHYPERIONARMORYSTAGE1SET03                     = 1553,
    SMHYPERIONARMORYSTAGE1SWANNCAMERAS              = 1315,
    SMHYPERIONARMORYSTAGE1TECHNOLOGYCONSOLEHS       = 1555,
    SMHYPERIONARMORYVIKING                          = 1525,
    SMHYPERIONBRIDGEBRIEFING                        = 1419,
    SMHYPERIONBRIDGEBRIEFINGCENTER                  = 1420,
    SMHYPERIONBRIDGEBRIEFINGLEFT                    = 1348,
    SMHYPERIONBRIDGEBRIEFINGRIGHT                   = 1349,
    SMHYPERIONBRIDGEHOLOMAP                         = 1560,
    SMHYPERIONBRIDGEPROPS                           = 1564,
    SMHYPERIONBRIDGESTAGE1BATTLECOMMANDHS           = 1599,
    SMHYPERIONBRIDGESTAGE1BATTLEREPORTSHS           = 1597,
    SMHYPERIONBRIDGESTAGE1BOW                       = 1556,
    SMHYPERIONBRIDGESTAGE1CANTINAHS                 = 1600,
    SMHYPERIONBRIDGESTAGE1CENTERCONSOLEHS           = 1598,
    SMHYPERIONBRIDGESTAGE1HANSONCAMERAS             = 1311,
    SMHYPERIONBRIDGESTAGE1HORNERCAMERAS             = 1312,
    SMHYPERIONBRIDGESTAGE1SET                       = 1557,
    SMHYPERIONBRIDGESTAGE1SET2                      = 1558,
    SMHYPERIONBRIDGESTAGE1SET3                      = 1559,
    SMHYPERIONBRIDGESTAGE1TOSHCAMERAS               = 1314,
    SMHYPERIONBRIDGESTAGE1TYCHUSCAMERAS             = 1313,
    SMHYPERIONBRIDGESTAGE1WINDOWHS                  = 1601,
    SMHYPERIONBRIDGETRAYNOR03BRIEFINGCAMERA         = 1322,
    SMHYPERIONCANTINABADGEHS                        = 1384,
    SMHYPERIONCANTINAHYDRACLAWSHS                   = 1588,
    SMHYPERIONCANTINAMERCCOMPUTERHS                 = 1589,
    SMHYPERIONCANTINAPOSTER1HS                      = 1385,
    SMHYPERIONCANTINAPOSTER2HS                      = 1386,
    SMHYPERIONCANTINAPOSTER3HS                      = 1387,
    SMHYPERIONCANTINAPOSTER4HS                      = 1388,
    SMHYPERIONCANTINAPOSTER5HS                      = 1389,
    SMHYPERIONCANTINAPROGRESSFRAME                  = 1587,
    SMHYPERIONCANTINAPROPS                          = 1565,
    SMHYPERIONCANTINASTAGE1ARCADEGAMEHS             = 1584,
    SMHYPERIONCANTINASTAGE1CORKBOARDHS              = 1586,
    SMHYPERIONCANTINASTAGE1EXITHS                   = 1581,
    SMHYPERIONCANTINASTAGE1JUKEBOXHS                = 1585,
    SMHYPERIONCANTINASTAGE1PROGRESS1HS              = 1590,
    SMHYPERIONCANTINASTAGE1PROGRESS2HS              = 1591,
    SMHYPERIONCANTINASTAGE1PROGRESS3HS              = 1592,
    SMHYPERIONCANTINASTAGE1PROGRESS4HS              = 1593,
    SMHYPERIONCANTINASTAGE1PROGRESS5HS              = 1594,
    SMHYPERIONCANTINASTAGE1PROGRESS6HS              = 1595,
    SMHYPERIONCANTINASTAGE1SET                      = 1561,
    SMHYPERIONCANTINASTAGE1SET2                     = 1562,
    SMHYPERIONCANTINASTAGE1STAIRCASEHS              = 1582,
    SMHYPERIONCANTINASTAGE1TVHS                     = 1583,
    SMHYPERIONCANTINASTAGE1WALLPIECE                = 1563,
    SMHYPERIONCANTINATOSHCAMERAS                    = 1316,
    SMHYPERIONCANTINATYCHUSCAMERAS                  = 1317,
    SMHYPERIONCANTINAYBARRACAMERAS                  = 1318,
    SMHYPERIONCORRIDORPROPS                         = 1460,
    SMHYPERIONCORRIDORSET                           = 1596,
    SMHYPERIONEXTERIOR                              = 1468,
    SMHYPERIONEXTERIORHOLOGRAM                      = 1470,
    SMHYPERIONEXTERIORLOW                           = 1469,
    SMHYPERIONLABADJUTANTCAMERAS                    = 1319,
    SMHYPERIONLABARTIFACTBASEHS                     = 1613,
    SMHYPERIONLABARTIFACTPART1HS                    = 1609,
    SMHYPERIONLABARTIFACTPART2HS                    = 1610,
    SMHYPERIONLABARTIFACTPART3HS                    = 1611,
    SMHYPERIONLABARTIFACTPART4HS                    = 1612,
    SMHYPERIONLABCOWINCAMERAS                       = 1320,
    SMHYPERIONLABHANSONCAMERAS                      = 1321,
    SMHYPERIONMEDLABBRIEFING                        = 1350,
    SMHYPERIONMEDLABBRIEFINGCENTER                  = 1351,
    SMHYPERIONMEDLABBRIEFINGLEFT                    = 1352,
    SMHYPERIONMEDLABBRIEFINGRIGHT                   = 1353,
    SMHYPERIONMEDLABCRYOTUBEA                       = 1579,
    SMHYPERIONMEDLABCRYOTUBEB                       = 1580,
    SMHYPERIONMEDLABPROPS                           = 1566,
    SMHYPERIONMEDLABPROTOSSCRYOTUBE0HS              = 1567,
    SMHYPERIONMEDLABPROTOSSCRYOTUBE1HS              = 1568,
    SMHYPERIONMEDLABPROTOSSCRYOTUBE2HS              = 1569,
    SMHYPERIONMEDLABPROTOSSCRYOTUBE3HS              = 1570,
    SMHYPERIONMEDLABPROTOSSCRYOTUBE4HS              = 1571,
    SMHYPERIONMEDLABPROTOSSCRYOTUBE5HS              = 1572,
    SMHYPERIONMEDLABSTAGE1ARTIFACTHS                = 1608,
    SMHYPERIONMEDLABSTAGE1CONSOLEHS                 = 1605,
    SMHYPERIONMEDLABSTAGE1CRYSTALHS                 = 1607,
    SMHYPERIONMEDLABSTAGE1DOORHS                    = 1606,
    SMHYPERIONMEDLABSTAGE1SET                       = 1602,
    SMHYPERIONMEDLABSTAGE1SET2                      = 1603,
    SMHYPERIONMEDLABSTAGE1SETLIGHTS                 = 1604,
    SMHYPERIONMEDLABZERGCRYOTUBE0HS                 = 1573,
    SMHYPERIONMEDLABZERGCRYOTUBE1HS                 = 1574,
    SMHYPERIONMEDLABZERGCRYOTUBE2HS                 = 1575,
    SMHYPERIONMEDLABZERGCRYOTUBE3HS                 = 1576,
    SMHYPERIONMEDLABZERGCRYOTUBE4HS                 = 1577,
    SMHYPERIONMEDLABZERGCRYOTUBE5HS                 = 1578,
    SMKACHINSKY                                     = 1636,
    SMKATELOCKWELL                                  = 1545,
    SMKERRIGANPHOTO                                 = 1355,
    SMLABASSISTANT                                  = 1530,
    SMLEEKENO                                       = 1544,
    SMLEEKENOSET                                    = 1540,
    SMMARAUDER                                      = 1621,
    SMMARAUDERPHCRATE                               = 1623,
    SMMARINE01                                      = 1626,
    SMMARINE02                                      = 1627,
    SMMARINE02AOD                                   = 1628,
    SMMARINE03                                      = 1629,
    SMMARINE04                                      = 1630,
    SMMARINERIFLE                                   = 1465,
    SMMARSARABARBADGEHS                             = 1383,
    SMMARSARABARBOTTLESHS                           = 1503,
    SMMARSARABARBRIEFINGSET                         = 1475,
    SMMARSARABARBRIEFINGSET2                        = 1476,
    SMMARSARABARBRIEFINGSETLEFT                     = 1477,
    SMMARSARABARBRIEFINGSETRIGHT                    = 1478,
    SMMARSARABARBRIEFINGTVMAIN                      = 1479,
    SMMARSARABARBRIEFINGTVMAIN2                     = 1480,
    SMMARSARABARBRIEFINGTVMAIN3                     = 1481,
    SMMARSARABARBRIEFINGTVPORTRAIT1                 = 1482,
    SMMARSARABARBRIEFINGTVPORTRAIT2                 = 1483,
    SMMARSARABARBRIEFINGTVPORTRAIT3                 = 1484,
    SMMARSARABARBRIEFINGTVPORTRAIT4                 = 1485,
    SMMARSARABARBRIEFINGTVPORTRAIT5                 = 1486,
    SMMARSARABARCORKBOARDBACKGROUND                 = 1493,
    SMMARSARABARCORKBOARDHS                         = 1492,
    SMMARSARABARCORKBOARDITEM1HS                    = 1494,
    SMMARSARABARCORKBOARDITEM2HS                    = 1495,
    SMMARSARABARCORKBOARDITEM3HS                    = 1496,
    SMMARSARABARCORKBOARDITEM4HS                    = 1497,
    SMMARSARABARCORKBOARDITEM5HS                    = 1498,
    SMMARSARABARCORKBOARDITEM6HS                    = 1499,
    SMMARSARABARCORKBOARDITEM7HS                    = 1500,
    SMMARSARABARCORKBOARDITEM8HS                    = 1501,
    SMMARSARABARCORKBOARDITEM9HS                    = 1502,
    SMMARSARABARHYDRALISKSKULLHS                    = 1491,
    SMMARSARABARJUKEBOXHS                           = 1357,
    SMMARSARABARKERRIGANPHOTOHS                     = 1358,
    SMMARSARABARPROPS                               = 1459,
    SMMARSARABARSET                                 = 1487,
    SMMARSARABARSET2                                = 1488,
    SMMARSARABARSTARMAPHS                           = 1489,
    SMMARSARABARTVHS                                = 1490,
    SMMARSARABARTYCHUSCAMERAS                       = 1310,
    SMMARSARAPLANET                                 = 1416,
    SMMIKELIBERTY                                   = 1546,
    SMMUTALISK                                      = 1651,
    SMNOVA                                          = 1417,
    SMPRESSROOMPROPS                                = 1463,
    SMRAYNORCOMMANDER                               = 1618,
    SMRAYNORGUN                                     = 1464,
    SMRAYNORHANDS                                   = 1462,
    SMRAYNORMARINE                                  = 1625,
    SMSHADOWBOX                                     = 1614,
    SMSTETMANN                                      = 1641,
    SMTERRAN01FX                                    = 1423,
    SMTERRAN03FX                                    = 1424,
    SMTERRAN05FX                                    = 1425,
    SMTERRAN05FXMUTALISKS                           = 1426,
    SMTERRAN05PROPS                                 = 1427,
    SMTERRAN06AFX                                   = 1428,
    SMTERRAN06APROPS                                = 1434,
    SMTERRAN06BFX                                   = 1429,
    SMTERRAN06BPROPS                                = 1435,
    SMTERRAN06CFX                                   = 1430,
    SMTERRAN07FX                                    = 1437,
    SMTERRAN07PROPS                                 = 1436,
    SMTERRAN08PROPS                                 = 1438,
    SMTERRAN09FX                                    = 1439,
    SMTERRAN09PROPS                                 = 1440,
    SMTERRAN11FX                                    = 1441,
    SMTERRAN11FXBLOOD                               = 1444,
    SMTERRAN11FXDEBRIS                              = 1445,
    SMTERRAN11FXDEBRIS1                             = 1446,
    SMTERRAN11FXDEBRIS2                             = 1447,
    SMTERRAN11FXEXPLOSIONS                          = 1443,
    SMTERRAN11FXMISSILES                            = 1442,
    SMTERRAN11PROPS                                 = 1448,
    SMTERRAN11PROPSBURROWROCKS                      = 1449,
    SMTERRAN11PROPSRIFLESHELLS                      = 1450,
    SMTERRAN12FX                                    = 1431,
    SMTERRAN12PROPS                                 = 1451,
    SMTERRAN13PROPS                                 = 1452,
    SMTERRAN14FX                                    = 1432,
    SMTERRAN14PROPS                                 = 1453,
    SMTERRAN15FX                                    = 1433,
    SMTERRAN15PROPS                                 = 1454,
    SMTERRAN16FX                                    = 1455,
    SMTERRAN16FXFLAK                                = 1456,
    SMTERRAN17FX                                    = 1458,
    SMTERRAN17PROPS                                 = 1457,
    SMTERRANREADYROOMLEFTTV                         = 1547,
    SMTERRANREADYROOMMAINTV                         = 1548,
    SMTERRANREADYROOMRIGHTTV                        = 1549,
    SMTERRANREADYROOMSET                            = 1369,
    SMTESTCAMERA                                    = 1323,
    SMTOSHKNIFE                                     = 1466,
    SMTOSHSHUTTLEPROPS                              = 1467,
    SMTOSHSHUTTLESET                                = 1354,
    SMTOSHSHUTTLESET2                               = 1356,
    SMTVSTATIC                                      = 1541,
    SMUNNCAMERA                                     = 1539,
    SMUNNSCREEN                                     = 1532,
    SMUNNSET                                        = 1368,
    SMVALERIANFLAGSHIPCORRIDORSSET                  = 1359,
    SMVALERIANFLAGSHIPCORRIDORSSET2                 = 1360,
    SMVALERIANFLAGSHIPCORRIDORSSET3                 = 1361,
    SMVALERIANFLAGSHIPCORRIDORSSET4                 = 1362,
    SMVALERIANMENGSK                                = 1645,
    SMVALERIANOBSERVATORYPAINTINGHS                 = 1366,
    SMVALERIANOBSERVATORYPROPS                      = 1504,
    SMVALERIANOBSERVATORYSET                        = 1363,
    SMVALERIANOBSERVATORYSET2                       = 1364,
    SMVALERIANOBSERVATORYSET3                       = 1365,
    SMVALERIANOBSERVATORYSTARMAP                    = 1505,
    SMVIKING                                        = 1507,
    SMYBARRA                                        = 1644,
    SMZERATUL                                       = 1648,
    SMZERGEDHANSON                                  = 1529,
    SMZERGLING                                      = 1652,
    SNARE_PLACEHOLDER                               = 1921,
    SNOWGLAZESTARTERMP                              = 1909,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8     = 668,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT  = 667,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8     = 670,
    SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT  = 669,
    SPACEDIABLO                                     = 1222,
    SPACEPLATFORMCLIFFDOOR0                         = 981,
    SPACEPLATFORMCLIFFDOOR1                         = 983,
    SPACEPLATFORMCLIFFDOOROPEN0                     = 980,
    SPACEPLATFORMCLIFFDOOROPEN1                     = 982,
    SPACEPLATFORMDESTRUCTIBLEJUMBOBLOCKER           = 1205,
    SPACEPLATFORMDESTRUCTIBLELARGEBLOCKER           = 1206,
    SPACEPLATFORMDESTRUCTIBLEMEDIUMBLOCKER          = 1207,
    SPACEPLATFORMDESTRUCTIBLESMALLBLOCKER           = 1208,
    SPACEPLATFORMREACTORPATHINGBLOCKER              = 1216,
    SPACEPLATFORMVENTSUNIT                          = 1752,
    SPARTANCOMPANY                                  = 926,
    SPARTANCOMPANYAWEAPON                           = 1118,
    SPECIALOPSDROPSHIP                              = 1291,
    SPECTRE                                         = 1134,
    SPECTRENUKE                                     = 961,
    SPIDERMINE                                      = 936,
    SPIDERMINEBURROWED                              = 935,
    SPINECRAWLERWEAPON                              = 279,
    SPORECANNON                                     = 1240,
    SPORECANNONFIREMISSILE                          = 1079,
    SPORECRAWLERWEAPON                              = 280,
    SS_BACKGROUNDSPACE00                            = 1737,
    SS_BACKGROUNDSPACE01                            = 1738,
    SS_BACKGROUNDSPACE02                            = 1739,
    SS_BACKGROUNDSPACELARGE                         = 1164,
    SS_BACKGROUNDSPACEPROT00                        = 1740,
    SS_BACKGROUNDSPACEPROT01                        = 1741,
    SS_BACKGROUNDSPACEPROT02                        = 1742,
    SS_BACKGROUNDSPACEPROT03                        = 1743,
    SS_BACKGROUNDSPACEPROT04                        = 1744,
    SS_BACKGROUNDSPACEPROTOSSLARGE                  = 1745,
    SS_BACKGROUNDSPACETERRAN00                      = 1165,
    SS_BACKGROUNDSPACETERRAN01                      = 1749,
    SS_BACKGROUNDSPACETERRAN02                      = 1166,
    SS_BACKGROUNDSPACETERRANLARGE                   = 1747,
    SS_BACKGROUNDSPACEZERG00                        = 1167,
    SS_BACKGROUNDSPACEZERG01                        = 1748,
    SS_BACKGROUNDSPACEZERG02                        = 1168,
    SS_BACKGROUNDSPACEZERGLARGE                     = 1746,
    SS_BACKGROUNDZERG01                             = 1736,
    SS_BATTLECRUISER                                = 1170,
    SS_BATTLECRUISERHUNTERSEEKERMISSILE             = 1032,
    SS_BATTLECRUISERMISSILE                         = 1059,
    SS_BATTLECRUISERMISSILELAUNCHER                 = 1029,
    SS_BLACKEDGEBORDER                              = 1142,
    SS_CARRIER                                      = 1735,
    SS_CARRIERBOSS                                  = 1169,
    SS_CARRIERBOSSMISSILE                           = 1041,
    SS_CORRUPTOR                                    = 1176,
    SS_CORRUPTORMISSILE                             = 1050,
    SS_FIGHTER                                      = 1733,
    SS_FIGHTERDRONEMISSILE                          = 1054,
    SS_FIGHTERMISSILELEFT                           = 1038,
    SS_FIGHTERMISSILERIGHT                          = 1039,
    SS_INTERCEPTOR                                  = 1035,
    SS_INTERCEPTORMISSILE                           = 1057,
    SS_INTERCEPTORSPAWNMISSILE                      = 1040,
    SS_LEVIATHAN                                    = 1182,
    SS_LEVIATHANBOMB                                = 1033,
    SS_LEVIATHANBOMBMISSILE                         = 1036,
    SS_LEVIATHANSPAWNBOMBMISSILE                    = 1037,
    SS_LEVIATHANTENTACLEL1MISSILE                   = 1046,
    SS_LEVIATHANTENTACLEL2MISSILE                   = 1043,
    SS_LEVIATHANTENTACLER1MISSILE                   = 1044,
    SS_LEVIATHANTENTACLER2MISSILE                   = 1045,
    SS_LEVIATHANTENTACLETARGET                      = 1042,
    SS_LIGHTNINGPROJECTORFACELEFT                   = 1178,
    SS_LIGHTNINGPROJECTORFACERIGHT                  = 1174,
    SS_PHOENIX                                      = 1734,
    SS_PHOENIXMISSILE                               = 1055,
    SS_POWERUPBOMB                                  = 906,
    SS_POWERUPHEALTH                                = 907,
    SS_POWERUPSIDEMISSILES                          = 908,
    SS_POWERUPSTRONGERMISSILES                      = 909,
    SS_SCIENCEVESSEL                                = 1183,
    SS_SCIENCEVESSELMISSILE                         = 1058,
    SS_SCOURGE                                      = 1175,
    SS_SCOURGEMISSILE                               = 1049,
    SS_SCOUT                                        = 1181,
    SS_SCOUTMISSILE                                 = 1056,
    SS_STRONGMISSILE1                               = 1052,
    SS_STRONGMISSILE2                               = 1053,
    SS_SWARMGUARDIAN                                = 1180,
    SS_SWARMGUARDIANMISSILE                         = 1051,
    SS_TERRATRON                                    = 1184,
    SS_TERRATRONBEAMTARGET                          = 1173,
    SS_TERRATRONMISSILE                             = 1047,
    SS_TERRATRONMISSILELAUNCHER                     = 1177,
    SS_TERRATRONMISSILESPINNER                      = 1172,
    SS_TERRATRONMISSILESPINNERLAUNCHER              = 1171,
    SS_TERRATRONMISSILESPINNERMISSILE               = 1030,
    SS_TERRATRONSAW                                 = 1031,
    SS_WRAITH                                       = 1179,
    SS_WRAITHMISSILE                                = 1048,
    STALKERWEAPON                                   = 284,
    STARPORTTECHREACTOR                             = 960,
    STEREOSCOPICOPTIONSUNIT                         = 3,
    STETMANN                                        = 1241,
    STONEZEALOT                                     = 1753,
    SUPERWARPGATE                                   = 1306,
    SUPPLYDEPOTDROP                                 = 900,
    SWANN                                           = 1244,
    SWANNWEAPON                                     = 1090,
    SWARMLING                                       = 1757,
    TALDARIMMOTHERSHIP                              = 1209,
    TALDARIMPRISON                                  = 1225,
    TALDARIMPRISONCRYSTAL                           = 1221,
    TALONSMISSILEWEAPON                             = 582,
    TANKERTRUCK                                     = 1698,
    TARSONISENGINE                                  = 1713,
    TARSONISENGINEFAST                              = 1714,
    TARSONIS_DOORE                                  = 675,
    TARSONIS_DOORELOWERED                           = 676,
    TARSONIS_DOORN                                  = 671,
    TARSONIS_DOORNE                                 = 673,
    TARSONIS_DOORNELOWERED                          = 674,
    TARSONIS_DOORNLOWERED                           = 672,
    TARSONIS_DOORNW                                 = 677,
    TARSONIS_DOORNWLOWERED                          = 678,
    TASSADAR                                        = 1190,
    TAURENOUTHOUSE                                  = 1217,
    TAURENSPACEMARINE                               = 1778,
    TECHREACTOR                                     = 905,
    TEMPESTWEAPON                                   = 570,
    TEMPESTWEAPONGROUND                             = 809,
    TENTACLEAMISSILE                                = 1071,
    TENTACLEBMISSILE                                = 1072,
    TENTACLECMISSILE                                = 1073,
    TENTACLEDMISSILE                                = 1074,
    TERRANBUGGY                                     = 1694,
    TERRANDROPPOD                                   = 1726,
    TERRAN_ARMORY                                   = 29,
    TERRAN_AUTOTURRET                               = 31,
    TERRAN_BANSHEE                                  = 55,
    TERRAN_BARRACKS                                 = 21,
    TERRAN_BARRACKSFLYING                           = 46,
    TERRAN_BARRACKSREACTOR                          = 38,
    TERRAN_BARRACKSTECHLAB                          = 37,
    TERRAN_BATTLECRUISER                            = 57,
    TERRAN_BUNKER                                   = 24,
    TERRAN_COMMANDCENTER                            = 18,
    TERRAN_COMMANDCENTERFLYING                      = 36,
    TERRAN_CYCLONE                                  = 692,
    TERRAN_ENGINEERINGBAY                           = 22,
    TERRAN_FACTORY                                  = 27,
    TERRAN_FACTORYFLYING                            = 43,
    TERRAN_FACTORYREACTOR                           = 40,
    TERRAN_FACTORYTECHLAB                           = 39,
    TERRAN_FUSIONCORE                               = 30,
    TERRAN_GHOST                                    = 50,
    TERRAN_GHOSTACADEMY                             = 26,
    TERRAN_HELLION                                  = 53,
    TERRAN_HELLIONTANK                              = 484,
    TERRAN_KD8CHARGE                                = 830,
    TERRAN_LIBERATOR                                = 689,
    TERRAN_LIBERATORAG                              = 734,
    TERRAN_MARAUDER                                 = 51,
    TERRAN_MARINE                                   = 48,
    TERRAN_MEDIVAC                                  = 54,
    TERRAN_MISSILETURRET                            = 23,
    TERRAN_MULE                                     = 268,
    TERRAN_NUKE                                     = 58,
    TERRAN_ORBITALCOMMAND                           = 132,
    TERRAN_ORBITALCOMMANDFLYING                     = 134,
    TERRAN_PLANETARYFORTRESS                        = 130,
    TERRAN_POINTDEFENSEDRONE                        = 11,
    TERRAN_PREVIEWBUNKERUPGRADED                    = 1981,
    TERRAN_RAVEN                                    = 56,
    TERRAN_REACTOR                                  = 6,
    TERRAN_REAPER                                   = 49,
    TERRAN_REFINERY                                 = 20,
    TERRAN_REFINERYRICH                             = 1943,
    TERRAN_SCV                                      = 45,
    TERRAN_SENSORTOWER                              = 25,
    TERRAN_SIEGETANK                                = 33,
    TERRAN_SIEGETANKSIEGED                          = 32,
    TERRAN_STARPORT                                 = 28,
    TERRAN_STARPORTFLYING                           = 44,
    TERRAN_STARPORTREACTOR                          = 42,
    TERRAN_STARPORTTECHLAB                          = 41,
    TERRAN_SUPPLYDEPOT                              = 19,
    TERRAN_SUPPLYDEPOTLOWERED                       = 47,
    TERRAN_TECHLAB                                  = 5,
    TERRAN_THOR                                     = 52,
    TERRAN_THORAP                                   = 691,
    TERRAN_VIKINGASSAULT                            = 34,
    TERRAN_VIKINGFIGHTER                            = 35,
    TERRAN_WIDOWMINE                                = 498,
    TERRAN_WIDOWMINEBURROWED                        = 500,
    TERRAZINECANISTER                               = 1272,
    TERRAZINENODE                                   = 1300,
    TERRAZINENODEDEADTERRAN                         = 1020,
    TERRAZINENODEHAPPYPROTOSS                       = 1021,
    TERRAZINETANK                                   = 1307,
    TESTHERO                                        = 1783,
    TESTHERODEBUGMISSILEABILITY1WEAPON              = 1132,
    TESTHERODEBUGMISSILEABILITY2WEAPON              = 1133,
    TESTHEROTHROWMISSILE                            = 1131,
    TESTSHOP                                        = 1784,
    TESTZERG                                        = 632,
    THORAALANCE                                     = 807,
    THORAAWEAPON                                    = 269,
    THORNLIZARD                                     = 611,
    THORWRECKAGE                                    = 903,
    TORNADOMISSILEDUMMYWEAPON                       = 581,
    TORNADOMISSILEWEAPON                            = 580,
    TOSH                                            = 1292,
    TOSSGRENADEWEAPON                               = 1099,
    TOWERMINE                                       = 595,
    TRAFFICSIGNAL                                   = 361,
    TRANSPORTTRUCK                                  = 1301,
    TRAYNOR01SIGNSDESTRUCTIBLE1                     = 1719,
    TRUCKFLATBEDUNIT                                = 1768,
    TRUCKSEMIUNIT                                   = 1769,
    TRUCKUTILITYUNIT                                = 1770,
    TYCHUSCHAINGUN                                  = 1284,
    TYCHUSCOMMANDO                                  = 1262,
    TYCHUSEJECTMISSILE                              = 1218,
    TYCHUSGRENADEWEAPON                             = 1100,
    ULAANSMOKEBRIDGE                                = 1220,
    ULTRASONICPULSEWEAPON                           = 1087,
    UNBUILDABLEBRICKSSMALLUNIT                      = 602,
    UNBUILDABLEBRICKSUNIT                           = 656,
    UNBUILDABLEPLATESSMALLUNIT                      = 603,
    UNBUILDABLEPLATESUNIT                           = 604,
    UNBUILDABLEROCKSDESTRUCTIBLE                    = 472,
    UNBUILDABLEROCKSSMALLUNIT                       = 605,
    UNBUILDABLEROCKSUNIT                            = 657,
    URSADAKCALF                                     = 328,
    URSADAKFEMALE                                   = 327,
    URSADAKFEMALEEXOTIC                             = 325,
    URSADAKMALE                                     = 326,
    URSADAKMALEEXOTIC                               = 329,
    URSADON                                         = 148,
    URSULA                                          = 890,
    URUN                                            = 938,
    URUNWEAPONLEFT                                  = 1093,
    URUNWEAPONRIGHT                                 = 1094,
    VALHALLABASEDESTRUCTIBLEDOOR                    = 1266,
    VALHALLABASEDESTRUCTIBLEDOORDEAD                = 1265,
    VALHALLADESTRUCTIBLEWALL                        = 1758,
    VIKING                                          = 1940,
    VIKINGFIGHTERWEAPON                             = 271,
    VIKINGSKINPREVIEW                               = 1891,
    VIKINGSKY_UNIT                                  = 1732,
    VILESTREAMWEAPON                                = 1101,
    VIPERCONSUMESTRUCTUREWEAPON                     = 568,
    VIROPHAGE                                       = 1260,
    VOIDMPIMMORTALREVIVECORPSE                      = 725,
    VOIDSEEKER                                      = 1267,
    VOIDSEEKERPHASEMINEBLASTSECONDARYWEAPON         = 1098,
    VOIDSEEKERPHASEMINEBLASTWEAPON                  = 1097,
    VOIDSEEKERWEAPON                                = 1121,
    VULTURE                                         = 1135,
    VULTUREWEAPON                                   = 1113,
    WALLOFFIRE                                      = 1302,
    WARBOT                                          = 1269,
    WARBOTBMISSILE                                  = 1108,
    WARHOUND                                        = 497,
    WARHOUNDWEAPON                                  = 575,
    WARPIG                                          = 924,
    WARPPRISMSKINPREVIEW                            = 1888,
    WEAPON                                          = 383,
    WEAPONHYBRIDC                                   = 1303,
    WEAPONHYBRIDD                                   = 1105,
    WIDOWMINEAIRWEAPON                              = 578,
    WIDOWMINEWEAPON                                 = 577,
    WOLFSTATUE                                      = 381,
    WRAITH                                          = 1137,
    WRAITHAIRWEAPONLEFT                             = 1103,
    WRAITHAIRWEAPONRIGHT                            = 1102,
    WRAITHGROUNDWEAPON                              = 1104,
    WRECKEDBATTLECRUISERHELIOSFINAL                 = 1833,
    XELNAGADESTRUCTIBLEBLOCKER6E                    = 1895,
    XELNAGADESTRUCTIBLEBLOCKER6N                    = 1897,
    XELNAGADESTRUCTIBLEBLOCKER6NE                   = 1896,
    XELNAGADESTRUCTIBLEBLOCKER6NW                   = 1898,
    XELNAGADESTRUCTIBLEBLOCKER6S                    = 1893,
    XELNAGADESTRUCTIBLEBLOCKER6SE                   = 1894,
    XELNAGADESTRUCTIBLEBLOCKER6SW                   = 1900,
    XELNAGADESTRUCTIBLEBLOCKER6W                    = 1899,
    XELNAGADESTRUCTIBLEBLOCKER8E                    = 1903,
    XELNAGADESTRUCTIBLEBLOCKER8N                    = 1905,
    XELNAGADESTRUCTIBLEBLOCKER8NE                   = 1904,
    XELNAGADESTRUCTIBLEBLOCKER8NW                   = 1906,
    XELNAGADESTRUCTIBLEBLOCKER8S                    = 1901,
    XELNAGADESTRUCTIBLEBLOCKER8SE                   = 1902,
    XELNAGADESTRUCTIBLEBLOCKER8SW                   = 1908,
    XELNAGADESTRUCTIBLEBLOCKER8W                    = 1907,
    XELNAGADESTRUCTIBLERAMPBLOCKER6E                = 863,
    XELNAGADESTRUCTIBLERAMPBLOCKER6N                = 865,
    XELNAGADESTRUCTIBLERAMPBLOCKER6NE               = 864,
    XELNAGADESTRUCTIBLERAMPBLOCKER6NW               = 866,
    XELNAGADESTRUCTIBLERAMPBLOCKER6S                = 861,
    XELNAGADESTRUCTIBLERAMPBLOCKER6SE               = 862,
    XELNAGADESTRUCTIBLERAMPBLOCKER6SW               = 868,
    XELNAGADESTRUCTIBLERAMPBLOCKER6W                = 867,
    XELNAGADESTRUCTIBLERAMPBLOCKER8E                = 871,
    XELNAGADESTRUCTIBLERAMPBLOCKER8N                = 873,
    XELNAGADESTRUCTIBLERAMPBLOCKER8NE               = 872,
    XELNAGADESTRUCTIBLERAMPBLOCKER8NW               = 874,
    XELNAGADESTRUCTIBLERAMPBLOCKER8S                = 869,
    XELNAGADESTRUCTIBLERAMPBLOCKER8SE               = 870,
    XELNAGADESTRUCTIBLERAMPBLOCKER8SW               = 876,
    XELNAGADESTRUCTIBLERAMPBLOCKER8W                = 875,
    XELNAGAHEALINGSHRINE                            = 606,
    XELNAGAPRISON                                   = 1196,
    XELNAGAPRISONCONSOLE                            = 1224,
    XELNAGAPRISONHEIGHT2                            = 1195,
    XELNAGAPRISONNORTH                              = 1197,
    XELNAGAPRISONNORTHHEIGHT2                       = 1198,
    XELNAGASHRINE                                   = 1308,
    XELNAGASHRINEXIL                                = 1663,
    XELNAGATEMPLE                                   = 1304,
    XELNAGATEMPLEDOOR                               = 973,
    XELNAGATEMPLEDOORBURROWED                       = 972,
    XELNAGATEMPLEDOORURDL                           = 975,
    XELNAGATEMPLEDOORURDLBURROWED                   = 974,
    XELNAGAVAULT                                    = 1227,
    XELNAGAWORLDSHIPVAULT                           = 1283,
    XELNAGA_CAVERNS_DOORE                           = 519,
    XELNAGA_CAVERNS_DOOREOPENED                     = 520,
    XELNAGA_CAVERNS_DOORN                           = 521,
    XELNAGA_CAVERNS_DOORNE                          = 522,
    XELNAGA_CAVERNS_DOORNEOPENED                    = 523,
    XELNAGA_CAVERNS_DOORNOPENED                     = 524,
    XELNAGA_CAVERNS_DOORNW                          = 525,
    XELNAGA_CAVERNS_DOORNWOPENED                    = 526,
    XELNAGA_CAVERNS_DOORS                           = 527,
    XELNAGA_CAVERNS_DOORSE                          = 528,
    XELNAGA_CAVERNS_DOORSEOPENED                    = 529,
    XELNAGA_CAVERNS_DOORSOPENED                     = 530,
    XELNAGA_CAVERNS_DOORSW                          = 531,
    XELNAGA_CAVERNS_DOORSWOPENED                    = 532,
    XELNAGA_CAVERNS_DOORW                           = 533,
    XELNAGA_CAVERNS_DOORWOPENED                     = 534,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH10              = 552,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT           = 551,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH12              = 556,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT           = 555,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH8               = 548,
    XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT            = 547,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE10             = 540,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT          = 539,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE12             = 544,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT          = 543,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE8              = 536,
    XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT           = 535,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW10             = 542,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT          = 541,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW12             = 546,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT          = 545,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW8              = 538,
    XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT           = 537,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV10              = 554,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT           = 553,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV12              = 558,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT           = 557,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV8               = 550,
    XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT            = 549,
    YAMATOWEAPON                                    = 276,
    YOINKMISSILE                                    = 571,
    YOINKSIEGETANKMISSILE                           = 574,
    YOINKVIKINGAIRMISSILE                           = 572,
    YOINKVIKINGGROUNDMISSILE                        = 573,
    ZERATUL                                         = 937,
    ZERATULCRYSTALCHARGE                            = 1461,
    ZERGDROPPOD                                     = 1725,
    ZERGDROPPODCREEP                                = 1199,
    ZERG_BANELING                                   = 9,
    ZERG_BANELINGBURROWED                           = 115,
    ZERG_BANELINGCOCOON                             = 8,
    ZERG_BANELINGNEST                               = 96,
    ZERG_BROODLING                                  = 289,
    ZERG_BROODLORD                                  = 114,
    ZERG_BROODLORDCOCOON                            = 113,
    ZERG_CHANGELING                                 = 12,
    ZERG_CHANGELINGMARINE                           = 15,
    ZERG_CHANGELINGMARINESHIELD                     = 14,
    ZERG_CHANGELINGZEALOT                           = 13,
    ZERG_CHANGELINGZERGLING                         = 17,
    ZERG_CHANGELINGZERGLINGWINGS                    = 16,
    ZERG_CORRUPTOR                                  = 112,
    ZERG_CREEPTUMOR                                 = 87,
    ZERG_CREEPTUMORBURROWED                         = 137,
    ZERG_CREEPTUMORQUEEN                            = 138,
    ZERG_DRONE                                      = 104,
    ZERG_DRONEBURROWED                              = 116,
    ZERG_EGG                                        = 103,
    ZERG_EVOLUTIONCHAMBER                           = 90,
    ZERG_EXTRACTOR                                  = 88,
    ZERG_EXTRACTORRICH                              = 1995,
    ZERG_GREATERSPIRE                               = 102,
    ZERG_HATCHERY                                   = 86,
    ZERG_HIVE                                       = 101,
    ZERG_HYDRALISK                                  = 107,
    ZERG_HYDRALISKBURROWED                          = 117,
    ZERG_HYDRALISKDEN                               = 91,
    ZERG_INFESTATIONPIT                             = 94,
    ZERG_INFESTEDTERRANSEGG                         = 150,
    ZERG_INFESTOR                                   = 111,
    ZERG_INFESTORBURROWED                           = 127,
    ZERG_INFESTORTERRAN                             = 7,
    ZERG_LAIR                                       = 100,
    ZERG_LARVA                                      = 151,
    ZERG_LOCUSTMP                                   = 489,
    ZERG_LOCUSTMPFLYING                             = 693,
    ZERG_LURKERDENMP                                = 504,
    ZERG_LURKERMP                                   = 502,
    ZERG_LURKERMPBURROWED                           = 503,
    ZERG_LURKERMPEGG                                = 501,
    ZERG_MUTALISK                                   = 108,
    ZERG_NYDUSCANAL                                 = 142,
    ZERG_NYDUSNETWORK                               = 95,
    ZERG_OVERLORD                                   = 106,
    ZERG_OVERLORDCOCOON                             = 128,
    ZERG_OVERLORDTRANSPORT                          = 893,
    ZERG_OVERSEER                                   = 129,
    ZERG_OVERSEERSIEGEMODE                          = 1912,
    ZERG_PARASITICBOMBDUMMY                         = 824,
    ZERG_QUEEN                                      = 126,
    ZERG_QUEENBURROWED                              = 125,
    ZERG_RAVAGER                                    = 688,
    ZERG_RAVAGERCOCOON                              = 687,
    ZERG_ROACH                                      = 110,
    ZERG_ROACHBURROWED                              = 118,
    ZERG_ROACHWARREN                                = 97,
    ZERG_SPAWNINGPOOL                               = 89,
    ZERG_SPINECRAWLER                               = 98,
    ZERG_SPINECRAWLERUPROOTED                       = 139,
    ZERG_SPIRE                                      = 92,
    ZERG_SPORECRAWLER                               = 99,
    ZERG_SPORECRAWLERUPROOTED                       = 140,
    ZERG_SWARMHOSTBURROWEDMP                        = 493,
    ZERG_SWARMHOSTMP                                = 494,
    ZERG_TRANSPORTOVERLORDCOCOON                    = 892,
    ZERG_ULTRALISK                                  = 109,
    ZERG_ULTRALISKBURROWED                          = 131,
    ZERG_ULTRALISKCAVERN                            = 93,
    ZERG_VIPER                                      = 499,
    ZERG_ZERGLING                                   = 105,
    ZERG_ZERGLINGBURROWED                           = 119,
    ZERUSDESTRUCTIBLEARCH                           = 658,
    ZHAKULDASLIBRARYUNIT                            = 971,
    ZHAKULDASLIBRARYUNITBURROWED                    = 970,
    ZHAKULDASLIGHTBRIDGE                            = 969,
    ZHAKULDASLIGHTBRIDGEOFF                         = 968,
    ZHAKULDASLIGHTBRIDGEOFFTOPRIGHT                 = 1022,
    ZHAKULDASLIGHTBRIDGETOPRIGHT                    = 1023,
    _10SLOTBAG                                      = 1789,
    _12SLOTBAG                                      = 1790,
    _14SLOTBAG                                      = 1791,
    _16SLOTBAG                                      = 1792,
    _18SLOTBAG                                      = 1793,
    _20SLOTBAG                                      = 1794,
    _22SLOTBAG                                      = 1795,
    _24SLOTBAG                                      = 1796,
    _4SLOTBAG                                       = 1786,
    _6SLOTBAG                                       = 1787,
    _8SLOTBAG                                       = 1788,
};

using UnitTypeID = SC2Type<UNIT_TYPEID>;

//! Converts a UNIT_TYPEID into a string of the same name.
const char* UnitTypeToName ( const UnitTypeID id ) {
    switch ( static_cast<UNIT_TYPEID> ( id ) ) {
        case UNIT_TYPEID::ABANDONEDBUILDING : return "ABANDONEDBUILDING";
        case UNIT_TYPEID::ACCELERATIONZONEFLYINGLARGE :
            return "ACCELERATIONZONEFLYINGLARGE";
        case UNIT_TYPEID::ACCELERATIONZONEFLYINGMEDIUM :
            return "ACCELERATIONZONEFLYINGMEDIUM";
        case UNIT_TYPEID::ACCELERATIONZONEFLYINGSMALL :
            return "ACCELERATIONZONEFLYINGSMALL";
        case UNIT_TYPEID::ACCELERATIONZONELARGE :
            return "ACCELERATIONZONELARGE";
        case UNIT_TYPEID::ACCELERATIONZONEMEDIUM :
            return "ACCELERATIONZONEMEDIUM";
        case UNIT_TYPEID::ACCELERATIONZONESMALL :
            return "ACCELERATIONZONESMALL";
        case UNIT_TYPEID::ACIDSALIVAWEAPON    : return "ACIDSALIVAWEAPON";
        case UNIT_TYPEID::ACIDSPINESWEAPON    : return "ACIDSPINESWEAPON";
        case UNIT_TYPEID::ADEPTPIERCINGWEAPON : return "ADEPTPIERCINGWEAPON";
        case UNIT_TYPEID::ADEPTUPGRADEWEAPON  : return "ADEPTUPGRADEWEAPON";
        case UNIT_TYPEID::ADEPTWEAPON         : return "ADEPTWEAPON";
        case UNIT_TYPEID::ADJUTANTCAPSULE     : return "ADJUTANTCAPSULE";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNE10 :
            return "AIURLIGHTBRIDGEABANDONEDNE10";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNE10OUT :
            return "AIURLIGHTBRIDGEABANDONEDNE10OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNE12 :
            return "AIURLIGHTBRIDGEABANDONEDNE12";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNE12OUT :
            return "AIURLIGHTBRIDGEABANDONEDNE12OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNE8 :
            return "AIURLIGHTBRIDGEABANDONEDNE8";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNE8OUT :
            return "AIURLIGHTBRIDGEABANDONEDNE8OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNW10 :
            return "AIURLIGHTBRIDGEABANDONEDNW10";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNW10OUT :
            return "AIURLIGHTBRIDGEABANDONEDNW10OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNW12 :
            return "AIURLIGHTBRIDGEABANDONEDNW12";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNW12OUT :
            return "AIURLIGHTBRIDGEABANDONEDNW12OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNW8 :
            return "AIURLIGHTBRIDGEABANDONEDNW8";
        case UNIT_TYPEID::AIURLIGHTBRIDGEABANDONEDNW8OUT :
            return "AIURLIGHTBRIDGEABANDONEDNW8OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGENE10 : return "AIURLIGHTBRIDGENE10";
        case UNIT_TYPEID::AIURLIGHTBRIDGENE10OUT :
            return "AIURLIGHTBRIDGENE10OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGENE12 : return "AIURLIGHTBRIDGENE12";
        case UNIT_TYPEID::AIURLIGHTBRIDGENE12OUT :
            return "AIURLIGHTBRIDGENE12OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGENE8 : return "AIURLIGHTBRIDGENE8";
        case UNIT_TYPEID::AIURLIGHTBRIDGENE8OUT :
            return "AIURLIGHTBRIDGENE8OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGENW10 : return "AIURLIGHTBRIDGENW10";
        case UNIT_TYPEID::AIURLIGHTBRIDGENW10OUT :
            return "AIURLIGHTBRIDGENW10OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGENW12 : return "AIURLIGHTBRIDGENW12";
        case UNIT_TYPEID::AIURLIGHTBRIDGENW12OUT :
            return "AIURLIGHTBRIDGENW12OUT";
        case UNIT_TYPEID::AIURLIGHTBRIDGENW8 : return "AIURLIGHTBRIDGENW8";
        case UNIT_TYPEID::AIURLIGHTBRIDGENW8OUT :
            return "AIURLIGHTBRIDGENW8OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLENE10OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLENE10OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLENE12OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLENE12OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLENE8OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLENE8OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLENW10OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLENW10OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLENW12OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLENW12OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLENW8OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLENW8OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLESE10OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLESE10OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLESE12OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLESE12OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLESE8OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLESE8OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLESW10OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLESW10OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLESW12OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLESW12OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGEDESTRUCTIBLESW8OUT :
            return "AIURTEMPLEBRIDGEDESTRUCTIBLESW8OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGENE10OUT :
            return "AIURTEMPLEBRIDGENE10OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGENE12OUT :
            return "AIURTEMPLEBRIDGENE12OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGENE8OUT :
            return "AIURTEMPLEBRIDGENE8OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGENW10OUT :
            return "AIURTEMPLEBRIDGENW10OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGENW12OUT :
            return "AIURTEMPLEBRIDGENW12OUT";
        case UNIT_TYPEID::AIURTEMPLEBRIDGENW8OUT :
            return "AIURTEMPLEBRIDGENW8OUT";
        case UNIT_TYPEID::ANTEPLOTT : return "ANTEPLOTT";
        case UNIT_TYPEID::ARBITERMP : return "ARBITERMP";
        case UNIT_TYPEID::ARBITERMPWEAPONMISSILE :
            return "ARBITERMPWEAPONMISSILE";
        case UNIT_TYPEID::ARCHIVE        : return "ARCHIVE";
        case UNIT_TYPEID::ARCHIVESEALED  : return "ARCHIVESEALED";
        case UNIT_TYPEID::ARTANIS        : return "ARTANIS";
        case UNIT_TYPEID::ARTIFACT       : return "ARTIFACT";
        case UNIT_TYPEID::ARTIFACTPIECE1 : return "ARTIFACTPIECE1";
        case UNIT_TYPEID::ARTIFACTPIECE2 : return "ARTIFACTPIECE2";
        case UNIT_TYPEID::ARTIFACTPIECE3 : return "ARTIFACTPIECE3";
        case UNIT_TYPEID::ARTIFACTPIECE4 : return "ARTIFACTPIECE4";
        case UNIT_TYPEID::ARTIFACTPIECE5 : return "ARTIFACTPIECE5";
        case UNIT_TYPEID::ARTIFACTVAULT  : return "ARTIFACTVAULT";
        case UNIT_TYPEID::ARTOSILOPE     : return "ARTOSILOPE";
        case UNIT_TYPEID::ATALASERBATTERYLMWEAPON :
            return "ATALASERBATTERYLMWEAPON";
        case UNIT_TYPEID::ATSLASERBATTERYLMWEAPON :
            return "ATSLASERBATTERYLMWEAPON";
        case UNIT_TYPEID::AUTOMATEDREFINERY : return "AUTOMATEDREFINERY";
        case UNIT_TYPEID::AUTOTESTATTACKER  : return "AUTOTESTATTACKER";
        case UNIT_TYPEID::AUTOTESTATTACKTARGETAIR :
            return "AUTOTESTATTACKTARGETAIR";
        case UNIT_TYPEID::AUTOTESTATTACKTARGETGROUND :
            return "AUTOTESTATTACKTARGETGROUND";
        case UNIT_TYPEID::AUTOTURRETRELEASEWEAPON :
            return "AUTOTURRETRELEASEWEAPON";
        case UNIT_TYPEID::AVERNUSGATECONTROL : return "AVERNUSGATECONTROL";
        case UNIT_TYPEID::BACKLASHROCKETSLMWEAPON :
            return "BACKLASHROCKETSLMWEAPON";
        case UNIT_TYPEID::BALL                : return "BALL";
        case UNIT_TYPEID::BARRACKSTECHREACTOR : return "BARRACKSTECHREACTOR";
        case UNIT_TYPEID::BATTLECRUISERHELIOS : return "BATTLECRUISERHELIOS";
        case UNIT_TYPEID::BATTLECRUISERHELIOSALMWEAPON :
            return "BATTLECRUISERHELIOSALMWEAPON";
        case UNIT_TYPEID::BATTLECRUISERHELIOSGLMWEAPON :
            return "BATTLECRUISERHELIOSGLMWEAPON";
        case UNIT_TYPEID::BATTLECRUISERHELIOSMORPH :
            return "BATTLECRUISERHELIOSMORPH";
        case UNIT_TYPEID::BATTLECRUISERLOKILMWEAPON :
            return "BATTLECRUISERLOKILMWEAPON";
        case UNIT_TYPEID::BEACONARMY           : return "BEACONARMY";
        case UNIT_TYPEID::BEACONATTACK         : return "BEACONATTACK";
        case UNIT_TYPEID::BEACONAUTO           : return "BEACONAUTO";
        case UNIT_TYPEID::BEACONCLAIM          : return "BEACONCLAIM";
        case UNIT_TYPEID::BEACONCUSTOM1        : return "BEACONCUSTOM1";
        case UNIT_TYPEID::BEACONCUSTOM2        : return "BEACONCUSTOM2";
        case UNIT_TYPEID::BEACONCUSTOM3        : return "BEACONCUSTOM3";
        case UNIT_TYPEID::BEACONCUSTOM4        : return "BEACONCUSTOM4";
        case UNIT_TYPEID::BEACONDEFEND         : return "BEACONDEFEND";
        case UNIT_TYPEID::BEACONDETECT         : return "BEACONDETECT";
        case UNIT_TYPEID::BEACONEXPAND         : return "BEACONEXPAND";
        case UNIT_TYPEID::BEACONHARASS         : return "BEACONHARASS";
        case UNIT_TYPEID::BEACONIDLE           : return "BEACONIDLE";
        case UNIT_TYPEID::BEACONRALLY          : return "BEACONRALLY";
        case UNIT_TYPEID::BEACONSCOUT          : return "BEACONSCOUT";
        case UNIT_TYPEID::BEACON_NOVA          : return "BEACON_NOVA";
        case UNIT_TYPEID::BEACON_NOVASMALL     : return "BEACON_NOVASMALL";
        case UNIT_TYPEID::BEACON_PROTOSS       : return "BEACON_PROTOSS";
        case UNIT_TYPEID::BEACON_PROTOSSSMALL  : return "BEACON_PROTOSSSMALL";
        case UNIT_TYPEID::BEACON_TERRAN        : return "BEACON_TERRAN";
        case UNIT_TYPEID::BEACON_TERRANSMALL   : return "BEACON_TERRANSMALL";
        case UNIT_TYPEID::BEACON_ZERG          : return "BEACON_ZERG";
        case UNIT_TYPEID::BEACON_ZERGSMALL     : return "BEACON_ZERGSMALL";
        case UNIT_TYPEID::BIODOME              : return "BIODOME";
        case UNIT_TYPEID::BIODOMECOMMAND       : return "BIODOMECOMMAND";
        case UNIT_TYPEID::BIODOMECOMMANDFLYING : return "BIODOMECOMMANDFLYING";
        case UNIT_TYPEID::BIODOMEHALFBUILT     : return "BIODOMEHALFBUILT";
        case UNIT_TYPEID::BIOPLASMIDDISCHARGEWEAPON :
            return "BIOPLASMIDDISCHARGEWEAPON";
        case UNIT_TYPEID::BIOSTASISMISSILE : return "BIOSTASISMISSILE";
        case UNIT_TYPEID::BLIMP            : return "BLIMP";
        case UNIT_TYPEID::BLIMPADS         : return "BLIMPADS";
        case UNIT_TYPEID::BLOCKER16X16     : return "BLOCKER16X16";
        case UNIT_TYPEID::BLOCKER4X4       : return "BLOCKER4X4";
        case UNIT_TYPEID::BLOCKER6X6       : return "BLOCKER6X6";
        case UNIT_TYPEID::BLOCKER8X8       : return "BLOCKER8X8";
        case UNIT_TYPEID::BRAXISALPHADESTRUCTIBLE1X1 :
            return "BRAXISALPHADESTRUCTIBLE1X1";
        case UNIT_TYPEID::BRAXISALPHADESTRUCTIBLE2X2 :
            return "BRAXISALPHADESTRUCTIBLE2X2";
        case UNIT_TYPEID::BREACHINGCHARGE     : return "BREACHINGCHARGE";
        case UNIT_TYPEID::BRIDGEBLOCKER4X12   : return "BRIDGEBLOCKER4X12";
        case UNIT_TYPEID::BROODLINGESCORT     : return "BROODLINGESCORT";
        case UNIT_TYPEID::BROODLORDAWEAPON    : return "BROODLORDAWEAPON";
        case UNIT_TYPEID::BROODLORDBWEAPON    : return "BROODLORDBWEAPON";
        case UNIT_TYPEID::BROODLORDEGG        : return "BROODLORDEGG";
        case UNIT_TYPEID::BROODLORDEGGMISSILE : return "BROODLORDEGGMISSILE";
        case UNIT_TYPEID::BROODLORDWEAPON     : return "BROODLORDWEAPON";
        case UNIT_TYPEID::BRUTALISK           : return "BRUTALISK";
        case UNIT_TYPEID::BRUTALISKWEAPON     : return "BRUTALISKWEAPON";
        case UNIT_TYPEID::BUBBACOMMERCIAL     : return "BUBBACOMMERCIAL";
        case UNIT_TYPEID::BYPASSARMORDRONE    : return "BYPASSARMORDRONE";
        case UNIT_TYPEID::CABOOSE             : return "CABOOSE";
        case UNIT_TYPEID::CARGOTRUCKUNITBARRELS :
            return "CARGOTRUCKUNITBARRELS";
        case UNIT_TYPEID::CARGOTRUCKUNITFLATBED :
            return "CARGOTRUCKUNITFLATBED";
        case UNIT_TYPEID::CARGOTRUCKUNITTRAILER :
            return "CARGOTRUCKUNITTRAILER";
        case UNIT_TYPEID::CARRIONBIRD : return "CARRIONBIRD";
        case UNIT_TYPEID::CASTANARDESTRUCTIBLEDEBRIS :
            return "CASTANARDESTRUCTIBLEDEBRIS";
        case UNIT_TYPEID::CASTANARULTRALISKSHACKLEDUNIT :
            return "CASTANARULTRALISKSHACKLEDUNIT";
        case UNIT_TYPEID::CASTANARWINDOWLARGEDIAGONALBLURUNIT :
            return "CASTANARWINDOWLARGEDIAGONALBLURUNIT";
        case UNIT_TYPEID::CASTANARWINDOWLARGEDIAGONALULBRUNIT :
            return "CASTANARWINDOWLARGEDIAGONALULBRUNIT";
        case UNIT_TYPEID::CAUSTICSPRAYMISSILE : return "CAUSTICSPRAYMISSILE";
        case UNIT_TYPEID::CELLBLOCKB          : return "CELLBLOCKB";
        case UNIT_TYPEID::CHARDESTRUCTIBLEROCKCOVER :
            return "CHARDESTRUCTIBLEROCKCOVER";
        case UNIT_TYPEID::CHARDESTRUCTIBLEROCKCOVERULDR :
            return "CHARDESTRUCTIBLEROCKCOVERULDR";
        case UNIT_TYPEID::CHARDESTRUCTIBLEROCKCOVERURDL :
            return "CHARDESTRUCTIBLEROCKCOVERURDL";
        case UNIT_TYPEID::CHARDESTRUCTIBLEROCKCOVERV :
            return "CHARDESTRUCTIBLEROCKCOVERV";
        case UNIT_TYPEID::CHECKSTATION : return "CHECKSTATION";
        case UNIT_TYPEID::CHECKSTATIONDIAGONALBLUR :
            return "CHECKSTATIONDIAGONALBLUR";
        case UNIT_TYPEID::CHECKSTATIONDIAGONALBLUROPENED :
            return "CHECKSTATIONDIAGONALBLUROPENED";
        case UNIT_TYPEID::CHECKSTATIONDIAGONALULBR :
            return "CHECKSTATIONDIAGONALULBR";
        case UNIT_TYPEID::CHECKSTATIONDIAGONALULBROPENED :
            return "CHECKSTATIONDIAGONALULBROPENED";
        case UNIT_TYPEID::CHECKSTATIONOPENED   : return "CHECKSTATIONOPENED";
        case UNIT_TYPEID::CHECKSTATIONVERTICAL : return "CHECKSTATIONVERTICAL";
        case UNIT_TYPEID::CHECKSTATIONVERTICALOPENED :
            return "CHECKSTATIONVERTICALOPENED";
        case UNIT_TYPEID::CHRYSALISEGG        : return "CHRYSALISEGG";
        case UNIT_TYPEID::CIVILIAN            : return "CIVILIAN";
        case UNIT_TYPEID::CIVILIANCARSUNIT    : return "CIVILIANCARSUNIT";
        case UNIT_TYPEID::CIVILIANFEMALE      : return "CIVILIANFEMALE";
        case UNIT_TYPEID::CIVILIANSHIPWRECKED : return "CIVILIANSHIPWRECKED";
        case UNIT_TYPEID::CIVILIANWEAPON      : return "CIVILIANWEAPON";
        case UNIT_TYPEID::CLEANINGBOT         : return "CLEANINGBOT";
        case UNIT_TYPEID::COLLAPSIBLEPURIFIERTOWERDEBRIS :
            return "COLLAPSIBLEPURIFIERTOWERDEBRIS";
        case UNIT_TYPEID::COLLAPSIBLEPURIFIERTOWERDIAGONAL :
            return "COLLAPSIBLEPURIFIERTOWERDIAGONAL";
        case UNIT_TYPEID::COLLAPSIBLEPURIFIERTOWERPUSHUNIT :
            return "COLLAPSIBLEPURIFIERTOWERPUSHUNIT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWER : return "COLLAPSIBLEROCKTOWER";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERDEBRISRAMPLEFT :
            return "COLLAPSIBLEROCKTOWERDEBRISRAMPLEFT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERDEBRISRAMPLEFTGREEN :
            return "COLLAPSIBLEROCKTOWERDEBRISRAMPLEFTGREEN";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERDEBRISRAMPRIGHT :
            return "COLLAPSIBLEROCKTOWERDEBRISRAMPRIGHT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERDEBRISRAMPRIGHTGREEN :
            return "COLLAPSIBLEROCKTOWERDEBRISRAMPRIGHTGREEN";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERPUSHUNITRAMPLEFT :
            return "COLLAPSIBLEROCKTOWERPUSHUNITRAMPLEFT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERPUSHUNITRAMPLEFTGREEN :
            return "COLLAPSIBLEROCKTOWERPUSHUNITRAMPLEFTGREEN";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERPUSHUNITRAMPRIGHT :
            return "COLLAPSIBLEROCKTOWERPUSHUNITRAMPRIGHT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERPUSHUNITRAMPRIGHTGREEN :
            return "COLLAPSIBLEROCKTOWERPUSHUNITRAMPRIGHTGREEN";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERRAMPLEFT :
            return "COLLAPSIBLEROCKTOWERRAMPLEFT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERRAMPLEFTGREEN :
            return "COLLAPSIBLEROCKTOWERRAMPLEFTGREEN";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERRAMPRIGHT :
            return "COLLAPSIBLEROCKTOWERRAMPRIGHT";
        case UNIT_TYPEID::COLLAPSIBLEROCKTOWERRAMPRIGHTGREEN :
            return "COLLAPSIBLEROCKTOWERRAMPRIGHTGREEN";
        case UNIT_TYPEID::COLLAPSIBLETERRANTOWER :
            return "COLLAPSIBLETERRANTOWER";
        case UNIT_TYPEID::COLONIST        : return "COLONIST";
        case UNIT_TYPEID::COLONISTBIODOME : return "COLONISTBIODOME";
        case UNIT_TYPEID::COLONISTBIODOMEHALFBUILT :
            return "COLONISTBIODOMEHALFBUILT";
        case UNIT_TYPEID::COLONISTFEMALE     : return "COLONISTFEMALE";
        case UNIT_TYPEID::COLONISTHUT        : return "COLONISTHUT";
        case UNIT_TYPEID::COLONISTSHIP       : return "COLONISTSHIP";
        case UNIT_TYPEID::COLONISTSHIPFLYING : return "COLONISTSHIPFLYING";
        case UNIT_TYPEID::COLONISTSHIPTHANSON02A :
            return "COLONISTSHIPTHANSON02A";
        case UNIT_TYPEID::COLONISTTRANSPORT   : return "COLONISTTRANSPORT";
        case UNIT_TYPEID::COLONISTVEHICLEUNIT : return "COLONISTVEHICLEUNIT";
        case UNIT_TYPEID::COLONISTVEHICLEUNIT01 :
            return "COLONISTVEHICLEUNIT01";
        case UNIT_TYPEID::COLONYINFESTATIONWEAPON :
            return "COLONYINFESTATIONWEAPON";
        case UNIT_TYPEID::COMMENTATORBOT1 : return "COMMENTATORBOT1";
        case UNIT_TYPEID::COMMENTATORBOT2 : return "COMMENTATORBOT2";
        case UNIT_TYPEID::COMMENTATORBOT3 : return "COMMENTATORBOT3";
        case UNIT_TYPEID::COMMENTATORBOT4 : return "COMMENTATORBOT4";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORE :
            return "COMPOUNDMANSION_DOORE";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORELOWERED :
            return "COMPOUNDMANSION_DOORELOWERED";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORN :
            return "COMPOUNDMANSION_DOORN";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORNE :
            return "COMPOUNDMANSION_DOORNE";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORNELOWERED :
            return "COMPOUNDMANSION_DOORNELOWERED";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORNLOWERED :
            return "COMPOUNDMANSION_DOORNLOWERED";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORNW :
            return "COMPOUNDMANSION_DOORNW";
        case UNIT_TYPEID::COMPOUNDMANSION_DOORNWLOWERED :
            return "COMPOUNDMANSION_DOORNWLOWERED";
        case UNIT_TYPEID::CONSUMEDNAFEEDBACKWEAPON :
            return "CONSUMEDNAFEEDBACKWEAPON";
        case UNIT_TYPEID::CONTAMINATEWEAPON : return "CONTAMINATEWEAPON";
        case UNIT_TYPEID::CORROSIVEPARASITEWEAPON :
            return "CORROSIVEPARASITEWEAPON";
        case UNIT_TYPEID::CORRUPTIONWEAPON    : return "CORRUPTIONWEAPON";
        case UNIT_TYPEID::CORSAIRMP           : return "CORSAIRMP";
        case UNIT_TYPEID::COW                 : return "COW";
        case UNIT_TYPEID::CRABEETLE           : return "CRABEETLE";
        case UNIT_TYPEID::CREEPBLOCKER1X1     : return "CREEPBLOCKER1X1";
        case UNIT_TYPEID::CREEPBLOCKER4X4     : return "CREEPBLOCKER4X4";
        case UNIT_TYPEID::CREEPONLYBLOCKER4X4 : return "CREEPONLYBLOCKER4X4";
        case UNIT_TYPEID::CREEPTUMORMISSILE   : return "CREEPTUMORMISSILE";
        case UNIT_TYPEID::CRUISERBIKE         : return "CRUISERBIKE";
        case UNIT_TYPEID::CYCLONEMISSILE      : return "CYCLONEMISSILE";
        case UNIT_TYPEID::CYCLONEMISSILELARGE : return "CYCLONEMISSILELARGE";
        case UNIT_TYPEID::CYCLONEMISSILELARGEAIR :
            return "CYCLONEMISSILELARGEAIR";
        case UNIT_TYPEID::CYCLONEMISSILELARGEAIRALTERNATIVE :
            return "CYCLONEMISSILELARGEAIRALTERNATIVE";
        case UNIT_TYPEID::D8CHARGE            : return "D8CHARGE";
        case UNIT_TYPEID::D8CHARGEWEAPON      : return "D8CHARGEWEAPON";
        case UNIT_TYPEID::D8CLUSTERBOMB       : return "D8CLUSTERBOMB";
        case UNIT_TYPEID::D8CLUSTERBOMBWEAPON : return "D8CLUSTERBOMBWEAPON";
        case UNIT_TYPEID::DATACORE            : return "DATACORE";
        case UNIT_TYPEID::DEBRIS2X2NONCONJOINED :
            return "DEBRIS2X2NONCONJOINED";
        case UNIT_TYPEID::DEFENSEWALLE      : return "DEFENSEWALLE";
        case UNIT_TYPEID::DEFENSEWALLN      : return "DEFENSEWALLN";
        case UNIT_TYPEID::DEFENSEWALLNE     : return "DEFENSEWALLNE";
        case UNIT_TYPEID::DEFENSEWALLNW     : return "DEFENSEWALLNW";
        case UNIT_TYPEID::DEFENSEWALLS      : return "DEFENSEWALLS";
        case UNIT_TYPEID::DEFENSEWALLSE     : return "DEFENSEWALLSE";
        case UNIT_TYPEID::DEFENSEWALLSW     : return "DEFENSEWALLSW";
        case UNIT_TYPEID::DEFENSEWALLW      : return "DEFENSEWALLW";
        case UNIT_TYPEID::DEFILERBONESAMPLE : return "DEFILERBONESAMPLE";
        case UNIT_TYPEID::DEFILERMP         : return "DEFILERMP";
        case UNIT_TYPEID::DEFILERMPBURROWED : return "DEFILERMPBURROWED";
        case UNIT_TYPEID::DEFILERMPDARKSWARMWEAPON :
            return "DEFILERMPDARKSWARMWEAPON";
        case UNIT_TYPEID::DEFILERMPPLAGUEWEAPON :
            return "DEFILERMPPLAGUEWEAPON";
        case UNIT_TYPEID::DESERTPLANETSEARCHLIGHT :
            return "DESERTPLANETSEARCHLIGHT";
        case UNIT_TYPEID::DESERTPLANETSTREETLIGHT :
            return "DESERTPLANETSTREETLIGHT";
        case UNIT_TYPEID::DESTRUCTIBLEBILLBOARDSCROLLINGTEXT :
            return "DESTRUCTIBLEBILLBOARDSCROLLINGTEXT";
        case UNIT_TYPEID::DESTRUCTIBLEBILLBOARDTALL :
            return "DESTRUCTIBLEBILLBOARDTALL";
        case UNIT_TYPEID::DESTRUCTIBLEBULLHORNLIGHTS :
            return "DESTRUCTIBLEBULLHORNLIGHTS";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRIS2X4HORIZONTAL :
            return "DESTRUCTIBLECITYDEBRIS2X4HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRIS2X4VERTICAL :
            return "DESTRUCTIBLECITYDEBRIS2X4VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRIS2X6HORIZONTAL :
            return "DESTRUCTIBLECITYDEBRIS2X6HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRIS2X6VERTICAL :
            return "DESTRUCTIBLECITYDEBRIS2X6VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRIS4X4 :
            return "DESTRUCTIBLECITYDEBRIS4X4";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRISHUGEDIAGONALBLUR :
            return "DESTRUCTIBLECITYDEBRISHUGEDIAGONALBLUR";
        case UNIT_TYPEID::DESTRUCTIBLECITYDEBRISHUGEDIAGONALULBR :
            return "DESTRUCTIBLECITYDEBRISHUGEDIAGONALULBR";
        case UNIT_TYPEID::DESTRUCTIBLEDEBRIS4X4 :
            return "DESTRUCTIBLEDEBRIS4X4";
        case UNIT_TYPEID::DESTRUCTIBLEEXPEDITIONGATE6X6 :
            return "DESTRUCTIBLEEXPEDITIONGATE6X6";
        case UNIT_TYPEID::DESTRUCTIBLEGARAGE : return "DESTRUCTIBLEGARAGE";
        case UNIT_TYPEID::DESTRUCTIBLEGARAGELARGE :
            return "DESTRUCTIBLEGARAGELARGE";
        case UNIT_TYPEID::DESTRUCTIBLEGATEDIAGONALBLUR :
            return "DESTRUCTIBLEGATEDIAGONALBLUR";
        case UNIT_TYPEID::DESTRUCTIBLEGATEDIAGONALBLURLOWERED :
            return "DESTRUCTIBLEGATEDIAGONALBLURLOWERED";
        case UNIT_TYPEID::DESTRUCTIBLEGATEDIAGONALULBR :
            return "DESTRUCTIBLEGATEDIAGONALULBR";
        case UNIT_TYPEID::DESTRUCTIBLEGATEDIAGONALULBRLOWERED :
            return "DESTRUCTIBLEGATEDIAGONALULBRLOWERED";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTHORIZONTAL :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTHORIZONTALBF :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTALBF";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTHORIZONTALBFLOWERED :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTALBFLOWERED";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTHORIZONTALLOWERED :
            return "DESTRUCTIBLEGATESTRAIGHTHORIZONTALLOWERED";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTVERTICAL :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTVERTICALLF :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICALLF";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTVERTICALLFLOWERED :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICALLFLOWERED";
        case UNIT_TYPEID::DESTRUCTIBLEGATESTRAIGHTVERTICALLOWERED :
            return "DESTRUCTIBLEGATESTRAIGHTVERTICALLOWERED";
        case UNIT_TYPEID::DESTRUCTIBLEICE2X4HORIZONTAL :
            return "DESTRUCTIBLEICE2X4HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEICE2X4VERTICAL :
            return "DESTRUCTIBLEICE2X4VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEICE2X6HORIZONTAL :
            return "DESTRUCTIBLEICE2X6HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEICE2X6VERTICAL :
            return "DESTRUCTIBLEICE2X6VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEICE4X4 : return "DESTRUCTIBLEICE4X4";
        case UNIT_TYPEID::DESTRUCTIBLEICE6X6 : return "DESTRUCTIBLEICE6X6";
        case UNIT_TYPEID::DESTRUCTIBLEICEDIAGONALHUGEBLUR :
            return "DESTRUCTIBLEICEDIAGONALHUGEBLUR";
        case UNIT_TYPEID::DESTRUCTIBLEICEDIAGONALHUGEULBR :
            return "DESTRUCTIBLEICEDIAGONALHUGEULBR";
        case UNIT_TYPEID::DESTRUCTIBLEICEHORIZONTALHUGE :
            return "DESTRUCTIBLEICEHORIZONTALHUGE";
        case UNIT_TYPEID::DESTRUCTIBLEICEVERTICALHUGE :
            return "DESTRUCTIBLEICEVERTICALHUGE";
        case UNIT_TYPEID::DESTRUCTIBLEKORHALFLAG :
            return "DESTRUCTIBLEKORHALFLAG";
        case UNIT_TYPEID::DESTRUCTIBLEKORHALFOLIAGE :
            return "DESTRUCTIBLEKORHALFOLIAGE";
        case UNIT_TYPEID::DESTRUCTIBLEKORHALPODIUM :
            return "DESTRUCTIBLEKORHALPODIUM";
        case UNIT_TYPEID::DESTRUCTIBLEKORHALTREE :
            return "DESTRUCTIBLEKORHALTREE";
        case UNIT_TYPEID::DESTRUCTIBLERAMPDIAGONALHUGEBLUR :
            return "DESTRUCTIBLERAMPDIAGONALHUGEBLUR";
        case UNIT_TYPEID::DESTRUCTIBLERAMPDIAGONALHUGEULBR :
            return "DESTRUCTIBLERAMPDIAGONALHUGEULBR";
        case UNIT_TYPEID::DESTRUCTIBLERAMPHORIZONTALHUGE :
            return "DESTRUCTIBLERAMPHORIZONTALHUGE";
        case UNIT_TYPEID::DESTRUCTIBLERAMPVERTICALHUGE :
            return "DESTRUCTIBLERAMPVERTICALHUGE";
        case UNIT_TYPEID::DESTRUCTIBLEROCK2X4HORIZONTAL :
            return "DESTRUCTIBLEROCK2X4HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCK2X4VERTICAL :
            return "DESTRUCTIBLEROCK2X4VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCK2X6HORIZONTAL :
            return "DESTRUCTIBLEROCK2X6HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCK2X6VERTICAL :
            return "DESTRUCTIBLEROCK2X6VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCK4X4 : return "DESTRUCTIBLEROCK4X4";
        case UNIT_TYPEID::DESTRUCTIBLEROCK6X6WEAK :
            return "DESTRUCTIBLEROCK6X6WEAK";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX12X4HORIZONTAL :
            return "DESTRUCTIBLEROCKEX12X4HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX12X4VERTICAL :
            return "DESTRUCTIBLEROCKEX12X4VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX12X6HORIZONTAL :
            return "DESTRUCTIBLEROCKEX12X6HORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX12X6VERTICAL :
            return "DESTRUCTIBLEROCKEX12X6VERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX14X4 :
            return "DESTRUCTIBLEROCKEX14X4";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX16X6 :
            return "DESTRUCTIBLEROCKEX16X6";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX1DIAGONALHUGEULBR :
            return "DESTRUCTIBLEROCKEX1DIAGONALHUGEULBR";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX1HORIZONTALHUGE :
            return "DESTRUCTIBLEROCKEX1HORIZONTALHUGE";
        case UNIT_TYPEID::DESTRUCTIBLEROCKEX1VERTICALHUGE :
            return "DESTRUCTIBLEROCKEX1VERTICALHUGE";
        case UNIT_TYPEID::DESTRUCTIBLESANDBAGS : return "DESTRUCTIBLESANDBAGS";
        case UNIT_TYPEID::DESTRUCTIBLESEARCHLIGHT :
            return "DESTRUCTIBLESEARCHLIGHT";
        case UNIT_TYPEID::DESTRUCTIBLESIGNSCONSTRUCTION :
            return "DESTRUCTIBLESIGNSCONSTRUCTION";
        case UNIT_TYPEID::DESTRUCTIBLESIGNSDIRECTIONAL :
            return "DESTRUCTIBLESIGNSDIRECTIONAL";
        case UNIT_TYPEID::DESTRUCTIBLESIGNSFUNNY :
            return "DESTRUCTIBLESIGNSFUNNY";
        case UNIT_TYPEID::DESTRUCTIBLESIGNSICONS :
            return "DESTRUCTIBLESIGNSICONS";
        case UNIT_TYPEID::DESTRUCTIBLESIGNSWARNING :
            return "DESTRUCTIBLESIGNSWARNING";
        case UNIT_TYPEID::DESTRUCTIBLESPACEPLATFORMBARRIER :
            return "DESTRUCTIBLESPACEPLATFORMBARRIER";
        case UNIT_TYPEID::DESTRUCTIBLESPACEPLATFORMSIGN :
            return "DESTRUCTIBLESPACEPLATFORMSIGN";
        case UNIT_TYPEID::DESTRUCTIBLESTOREFRONTCITYPROPS :
            return "DESTRUCTIBLESTOREFRONTCITYPROPS";
        case UNIT_TYPEID::DESTRUCTIBLESTREETLIGHT :
            return "DESTRUCTIBLESTREETLIGHT";
        case UNIT_TYPEID::DESTRUCTIBLETRAFFICSIGNAL :
            return "DESTRUCTIBLETRAFFICSIGNAL";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45 :
            return "DESTRUCTIBLEWALLCORNER45";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45BL90R :
            return "DESTRUCTIBLEWALLCORNER45BL90R";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45BR90T :
            return "DESTRUCTIBLEWALLCORNER45BR90T";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45UL90B :
            return "DESTRUCTIBLEWALLCORNER45UL90B";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45ULBL :
            return "DESTRUCTIBLEWALLCORNER45ULBL";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45ULUR :
            return "DESTRUCTIBLEWALLCORNER45ULUR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45UR90L :
            return "DESTRUCTIBLEWALLCORNER45UR90L";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER45URBR :
            return "DESTRUCTIBLEWALLCORNER45URBR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90B45UR :
            return "DESTRUCTIBLEWALLCORNER90B45UR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90BR :
            return "DESTRUCTIBLEWALLCORNER90BR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90L45BR :
            return "DESTRUCTIBLEWALLCORNER90L45BR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90LB :
            return "DESTRUCTIBLEWALLCORNER90LB";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90LT :
            return "DESTRUCTIBLEWALLCORNER90LT";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90R45UL :
            return "DESTRUCTIBLEWALLCORNER90R45UL";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90T45BL :
            return "DESTRUCTIBLEWALLCORNER90T45BL";
        case UNIT_TYPEID::DESTRUCTIBLEWALLCORNER90TR :
            return "DESTRUCTIBLEWALLCORNER90TR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLDIAGONALBLUR :
            return "DESTRUCTIBLEWALLDIAGONALBLUR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLDIAGONALBLURLF :
            return "DESTRUCTIBLEWALLDIAGONALBLURLF";
        case UNIT_TYPEID::DESTRUCTIBLEWALLDIAGONALULBR :
            return "DESTRUCTIBLEWALLDIAGONALULBR";
        case UNIT_TYPEID::DESTRUCTIBLEWALLDIAGONALULBRLF :
            return "DESTRUCTIBLEWALLDIAGONALULBRLF";
        case UNIT_TYPEID::DESTRUCTIBLEWALLSTRAIGHTHORIZONTAL :
            return "DESTRUCTIBLEWALLSTRAIGHTHORIZONTAL";
        case UNIT_TYPEID::DESTRUCTIBLEWALLSTRAIGHTHORIZONTALBF :
            return "DESTRUCTIBLEWALLSTRAIGHTHORIZONTALBF";
        case UNIT_TYPEID::DESTRUCTIBLEWALLSTRAIGHTVERTICAL :
            return "DESTRUCTIBLEWALLSTRAIGHTVERTICAL";
        case UNIT_TYPEID::DESTRUCTIBLEWALLVERTICALLF :
            return "DESTRUCTIBLEWALLVERTICALLF";
        case UNIT_TYPEID::DESTRUCTIBLEZERGINFESTATION3X3 :
            return "DESTRUCTIBLEZERGINFESTATION3X3";
        case UNIT_TYPEID::DEVASTATORMISSILEWEAPON :
            return "DEVASTATORMISSILEWEAPON";
        case UNIT_TYPEID::DEVILDOG         : return "DEVILDOG";
        case UNIT_TYPEID::DEVOURERCOCOONMP : return "DEVOURERCOCOONMP";
        case UNIT_TYPEID::DEVOURERMP       : return "DEVOURERMP";
        case UNIT_TYPEID::DEVOURERMPWEAPONMISSILE :
            return "DEVOURERMPWEAPONMISSILE";
        case UNIT_TYPEID::DEVOURERTISSUEDOODAD : return "DEVOURERTISSUEDOODAD";
        case UNIT_TYPEID::DEVOURERTISSUEMISSILE :
            return "DEVOURERTISSUEMISSILE";
        case UNIT_TYPEID::DEVOURERTISSUESAMPLE : return "DEVOURERTISSUESAMPLE";
        case UNIT_TYPEID::DEVOURERTISSUESAMPLETUBE :
            return "DEVOURERTISSUESAMPLETUBE";
        case UNIT_TYPEID::DIAMONDBACK : return "DIAMONDBACK";
        case UNIT_TYPEID::DIGESTERCREEPSPRAYTARGETUNIT :
            return "DIGESTERCREEPSPRAYTARGETUNIT";
        case UNIT_TYPEID::DIGESTERCREEPSPRAYUNIT :
            return "DIGESTERCREEPSPRAYUNIT";
        case UNIT_TYPEID::DOG              : return "DOG";
        case UNIT_TYPEID::DOMINIONKILLTEAM : return "DOMINIONKILLTEAM";
        case UNIT_TYPEID::DOMINIONKILLTEAMLMWEAPON :
            return "DOMINIONKILLTEAMLMWEAPON";
        case UNIT_TYPEID::DRAKKENLASERDRILL : return "DRAKKENLASERDRILL";
        case UNIT_TYPEID::DRBATTLECRUISERALMWEAPON :
            return "DRBATTLECRUISERALMWEAPON";
        case UNIT_TYPEID::DRBATTLECRUISERGLMWEAPON :
            return "DRBATTLECRUISERGLMWEAPON";
        case UNIT_TYPEID::DUKESREVENGE    : return "DUKESREVENGE";
        case UNIT_TYPEID::DUMPTRUCK       : return "DUMPTRUCK";
        case UNIT_TYPEID::DUSKWING        : return "DUSKWING";
        case UNIT_TYPEID::DUSKWINGWEAPON  : return "DUSKWINGWEAPON";
        case UNIT_TYPEID::EGGPURPLE       : return "EGGPURPLE";
        case UNIT_TYPEID::ELEVATORBLOCKER : return "ELEVATORBLOCKER";
        case UNIT_TYPEID::ELSECARO_COLONIST_HUT :
            return "ELSECARO_COLONIST_HUT";
        case UNIT_TYPEID::EMP2WEAPON : return "EMP2WEAPON";
        case UNIT_TYPEID::ENEMYPATHINGBLOCKER16X16 :
            return "ENEMYPATHINGBLOCKER16X16";
        case UNIT_TYPEID::ENEMYPATHINGBLOCKER1X1 :
            return "ENEMYPATHINGBLOCKER1X1";
        case UNIT_TYPEID::ENEMYPATHINGBLOCKER2X2 :
            return "ENEMYPATHINGBLOCKER2X2";
        case UNIT_TYPEID::ENEMYPATHINGBLOCKER4X4 :
            return "ENEMYPATHINGBLOCKER4X4";
        case UNIT_TYPEID::ENEMYPATHINGBLOCKER8X8 :
            return "ENEMYPATHINGBLOCKER8X8";
        case UNIT_TYPEID::EXPERIMENTALPLASMAGUNWEAPON :
            return "EXPERIMENTALPLASMAGUNWEAPON";
        case UNIT_TYPEID::EXPLODINGBARRELLARGE : return "EXPLODINGBARRELLARGE";
        case UNIT_TYPEID::EXTENDINGBRIDGENEWIDE10 :
            return "EXTENDINGBRIDGENEWIDE10";
        case UNIT_TYPEID::EXTENDINGBRIDGENEWIDE10OUT :
            return "EXTENDINGBRIDGENEWIDE10OUT";
        case UNIT_TYPEID::EXTENDINGBRIDGENEWIDE12 :
            return "EXTENDINGBRIDGENEWIDE12";
        case UNIT_TYPEID::EXTENDINGBRIDGENEWIDE12OUT :
            return "EXTENDINGBRIDGENEWIDE12OUT";
        case UNIT_TYPEID::EXTENDINGBRIDGENEWIDE8 :
            return "EXTENDINGBRIDGENEWIDE8";
        case UNIT_TYPEID::EXTENDINGBRIDGENEWIDE8OUT :
            return "EXTENDINGBRIDGENEWIDE8OUT";
        case UNIT_TYPEID::EXTENDINGBRIDGENWWIDE10 :
            return "EXTENDINGBRIDGENWWIDE10";
        case UNIT_TYPEID::EXTENDINGBRIDGENWWIDE10OUT :
            return "EXTENDINGBRIDGENWWIDE10OUT";
        case UNIT_TYPEID::EXTENDINGBRIDGENWWIDE12 :
            return "EXTENDINGBRIDGENWWIDE12";
        case UNIT_TYPEID::EXTENDINGBRIDGENWWIDE12OUT :
            return "EXTENDINGBRIDGENWWIDE12OUT";
        case UNIT_TYPEID::EXTENDINGBRIDGENWWIDE8 :
            return "EXTENDINGBRIDGENWWIDE8";
        case UNIT_TYPEID::EXTENDINGBRIDGENWWIDE8OUT :
            return "EXTENDINGBRIDGENWWIDE8OUT";
        case UNIT_TYPEID::EYESTALKWEAPON      : return "EYESTALKWEAPON";
        case UNIT_TYPEID::FACTORYTECHREACTOR  : return "FACTORYTECHREACTOR";
        case UNIT_TYPEID::FEEDERLING          : return "FEEDERLING";
        case UNIT_TYPEID::FIREBAT             : return "FIREBAT";
        case UNIT_TYPEID::FIREWORKSBLUE       : return "FIREWORKSBLUE";
        case UNIT_TYPEID::FIREWORKSRED        : return "FIREWORKSRED";
        case UNIT_TYPEID::FIREWORKSYELLOW     : return "FIREWORKSYELLOW";
        case UNIT_TYPEID::FLAMINGBETTY        : return "FLAMINGBETTY";
        case UNIT_TYPEID::FLATBEDTRUCK        : return "FLATBEDTRUCK";
        case UNIT_TYPEID::FLYOVERUNIT         : return "FLYOVERUNIT";
        case UNIT_TYPEID::FOOD1000            : return "FOOD1000";
        case UNIT_TYPEID::FREIGHTCAR          : return "FREIGHTCAR";
        case UNIT_TYPEID::FRENZYWEAPON        : return "FRENZYWEAPON";
        case UNIT_TYPEID::FUNGALGROWTHMISSILE : return "FUNGALGROWTHMISSILE";
        case UNIT_TYPEID::FUSIONREACTOR       : return "FUSIONREACTOR";
        case UNIT_TYPEID::G4CHARGEWEAPON      : return "G4CHARGEWEAPON";
        case UNIT_TYPEID::GASCANISTER         : return "GASCANISTER";
        case UNIT_TYPEID::GASCANISTERPROTOSS  : return "GASCANISTERPROTOSS";
        case UNIT_TYPEID::GASCANISTERZERG     : return "GASCANISTERZERG";
        case UNIT_TYPEID::GATECONTROLUNIT     : return "GATECONTROLUNIT";
        case UNIT_TYPEID::GHOSTALTERNATE      : return "GHOSTALTERNATE";
        case UNIT_TYPEID::GHOSTLASERLINES     : return "GHOSTLASERLINES";
        case UNIT_TYPEID::GHOSTNOVA           : return "GHOSTNOVA";
        case UNIT_TYPEID::GLAIVEWURMBOUNCEWEAPON :
            return "GLAIVEWURMBOUNCEWEAPON";
        case UNIT_TYPEID::GLAIVEWURMM2WEAPON : return "GLAIVEWURMM2WEAPON";
        case UNIT_TYPEID::GLAIVEWURMM3WEAPON : return "GLAIVEWURMM3WEAPON";
        case UNIT_TYPEID::GLAIVEWURMWEAPON   : return "GLAIVEWURMWEAPON";
        case UNIT_TYPEID::GLOBESTATUE        : return "GLOBESTATUE";
        case UNIT_TYPEID::GOLIATH            : return "GOLIATH";
        case UNIT_TYPEID::GOLIATHAWEAPON     : return "GOLIATHAWEAPON";
        case UNIT_TYPEID::GRAPPLEWEAPON      : return "GRAPPLEWEAPON";
        case UNIT_TYPEID::GUARDIANCOCOONMP   : return "GUARDIANCOCOONMP";
        case UNIT_TYPEID::GUARDIANMP         : return "GUARDIANMP";
        case UNIT_TYPEID::GUARDIANMPWEAPON   : return "GUARDIANMPWEAPON";
        case UNIT_TYPEID::HAILSTORMMISSILESWEAPON :
            return "HAILSTORMMISSILESWEAPON";
        case UNIT_TYPEID::HAMMERSECURITY : return "HAMMERSECURITY";
        case UNIT_TYPEID::HAMMERSECURITYLMWEAPON :
            return "HAMMERSECURITYLMWEAPON";
        case UNIT_TYPEID::HEALINGPOTIONTESTINSTANT :
            return "HEALINGPOTIONTESTINSTANT";
        case UNIT_TYPEID::HEALINGPOTIONTESTTARGET :
            return "HEALINGPOTIONTESTTARGET";
        case UNIT_TYPEID::HELPEREMITTERSELECTIONARROW :
            return "HELPEREMITTERSELECTIONARROW";
        case UNIT_TYPEID::HELSANGELASSAULT : return "HELSANGELASSAULT";
        case UNIT_TYPEID::HELSANGELFIGHTER : return "HELSANGELFIGHTER";
        case UNIT_TYPEID::HELSANGELFIGHTERWEAPON :
            return "HELSANGELFIGHTERWEAPON";
        case UNIT_TYPEID::HERC                 : return "HERC";
        case UNIT_TYPEID::HERCPLACEMENT        : return "HERCPLACEMENT";
        case UNIT_TYPEID::HERCULES             : return "HERCULES";
        case UNIT_TYPEID::HERCULESLANDER       : return "HERCULESLANDER";
        case UNIT_TYPEID::HERCULESLANDERFLYING : return "HERCULESLANDERFLYING";
        case UNIT_TYPEID::HERONUKE             : return "HERONUKE";
        case UNIT_TYPEID::HIGHTEMPLARSKINPREVIEW :
            return "HIGHTEMPLARSKINPREVIEW";
        case UNIT_TYPEID::HIGHTEMPLARWEAPONMISSILE :
            return "HIGHTEMPLARWEAPONMISSILE";
        case UNIT_TYPEID::HIVEMINDEMULATOR     : return "HIVEMINDEMULATOR";
        case UNIT_TYPEID::HOLDINGPEN           : return "HOLDINGPEN";
        case UNIT_TYPEID::HOMELARGE            : return "HOMELARGE";
        case UNIT_TYPEID::HOMESMALL            : return "HOMESMALL";
        case UNIT_TYPEID::HUNTERKILLER         : return "HUNTERKILLER";
        case UNIT_TYPEID::HUNTERKILLERBURROWED : return "HUNTERKILLERBURROWED";
        case UNIT_TYPEID::HUNTERKILLERWEAPON   : return "HUNTERKILLERWEAPON";
        case UNIT_TYPEID::HUNTERSEEKERWEAPON   : return "HUNTERSEEKERWEAPON";
        case UNIT_TYPEID::HURRICANEMISSILELEFT : return "HURRICANEMISSILELEFT";
        case UNIT_TYPEID::HURRICANEMISSILERIGHT :
            return "HURRICANEMISSILERIGHT";
        case UNIT_TYPEID::HUT                 : return "HUT";
        case UNIT_TYPEID::HYBRID              : return "HYBRID";
        case UNIT_TYPEID::HYBRIDCPLASMAWEAPON : return "HYBRIDCPLASMAWEAPON";
        case UNIT_TYPEID::HYBRIDDESTROYER     : return "HYBRIDDESTROYER";
        case UNIT_TYPEID::HYBRIDREAVER        : return "HYBRIDREAVER";
        case UNIT_TYPEID::HYBRIDSINGULARITYFEEDBACKWEAPON :
            return "HYBRIDSINGULARITYFEEDBACKWEAPON";
        case UNIT_TYPEID::HYDRALISKIMPALEMISSILE :
            return "HYDRALISKIMPALEMISSILE";
        case UNIT_TYPEID::HYPERION          : return "HYPERION";
        case UNIT_TYPEID::HYPERIONALMWEAPON : return "HYPERIONALMWEAPON";
        case UNIT_TYPEID::HYPERIONLMWEAPON  : return "HYPERIONLMWEAPON";
        case UNIT_TYPEID::HYPERIONYAMATOSPECIALWEAPON :
            return "HYPERIONYAMATOSPECIALWEAPON";
        case UNIT_TYPEID::ICE2X2NONCONJOINED : return "ICE2X2NONCONJOINED";
        case UNIT_TYPEID::ICEPROTOSSCRATES   : return "ICEPROTOSSCRATES";
        case UNIT_TYPEID::INFESTABLEBIODOME  : return "INFESTABLEBIODOME";
        case UNIT_TYPEID::INFESTABLECOLONISTBIODOME :
            return "INFESTABLECOLONISTBIODOME";
        case UNIT_TYPEID::INFESTABLECOLONISTHUT :
            return "INFESTABLECOLONISTHUT";
        case UNIT_TYPEID::INFESTABLEHUT       : return "INFESTABLEHUT";
        case UNIT_TYPEID::INFESTATIONSPIRE    : return "INFESTATIONSPIRE";
        case UNIT_TYPEID::INFESTEDABOMINATION : return "INFESTEDABOMINATION";
        case UNIT_TYPEID::INFESTEDABOMINATIONBURROWED :
            return "INFESTEDABOMINATIONBURROWED";
        case UNIT_TYPEID::INFESTEDACIDSPINESWEAPON :
            return "INFESTEDACIDSPINESWEAPON";
        case UNIT_TYPEID::INFESTEDARMORY   : return "INFESTEDARMORY";
        case UNIT_TYPEID::INFESTEDBARRACKS : return "INFESTEDBARRACKS";
        case UNIT_TYPEID::INFESTEDBUNKER   : return "INFESTEDBUNKER";
        case UNIT_TYPEID::INFESTEDCC       : return "INFESTEDCC";
        case UNIT_TYPEID::INFESTEDCIVILIAN : return "INFESTEDCIVILIAN";
        case UNIT_TYPEID::INFESTEDCIVILIANBURROWED :
            return "INFESTEDCIVILIANBURROWED";
        case UNIT_TYPEID::INFESTEDCOCOON       : return "INFESTEDCOCOON";
        case UNIT_TYPEID::INFESTEDCOLONISTSHIP : return "INFESTEDCOLONISTSHIP";
        case UNIT_TYPEID::INFESTEDENGBAY       : return "INFESTEDENGBAY";
        case UNIT_TYPEID::INFESTEDFACTORY      : return "INFESTEDFACTORY";
        case UNIT_TYPEID::INFESTEDMERCHAVEN    : return "INFESTEDMERCHAVEN";
        case UNIT_TYPEID::INFESTEDMISSILETURRET :
            return "INFESTEDMISSILETURRET";
        case UNIT_TYPEID::INFESTEDREFINERY : return "INFESTEDREFINERY";
        case UNIT_TYPEID::INFESTEDSTARPORT : return "INFESTEDSTARPORT";
        case UNIT_TYPEID::INFESTEDSUPPLY   : return "INFESTEDSUPPLY";
        case UNIT_TYPEID::INFESTEDTERRAN   : return "INFESTEDTERRAN";
        case UNIT_TYPEID::INFESTEDTERRANCAMPAIGN :
            return "INFESTEDTERRANCAMPAIGN";
        case UNIT_TYPEID::INFESTEDTERRANCAMPAIGNBURROWED :
            return "INFESTEDTERRANCAMPAIGNBURROWED";
        case UNIT_TYPEID::INFESTEDTERRANSEGGPLACEMENT :
            return "INFESTEDTERRANSEGGPLACEMENT";
        case UNIT_TYPEID::INFESTEDTERRANSWEAPON :
            return "INFESTEDTERRANSWEAPON";
        case UNIT_TYPEID::INFESTEDVENTBROODLORDEGG :
            return "INFESTEDVENTBROODLORDEGG";
        case UNIT_TYPEID::INFESTEDVENTCORRUPTOREGG :
            return "INFESTEDVENTCORRUPTOREGG";
        case UNIT_TYPEID::INFESTEDVENTEGGMISSILE :
            return "INFESTEDVENTEGGMISSILE";
        case UNIT_TYPEID::INFESTEDVENTMUTALISKEGG :
            return "INFESTEDVENTMUTALISKEGG";
        case UNIT_TYPEID::INFESTORENSNAREATTACKMISSILE :
            return "INFESTORENSNAREATTACKMISSILE";
        case UNIT_TYPEID::INFESTORTERRANBURROWED :
            return "INFESTORTERRANBURROWED";
        case UNIT_TYPEID::INFESTORTERRANSWEAPON :
            return "INFESTORTERRANSWEAPON";
        case UNIT_TYPEID::INHIBITORZONEFLYINGLARGE :
            return "INHIBITORZONEFLYINGLARGE";
        case UNIT_TYPEID::INHIBITORZONEFLYINGMEDIUM :
            return "INHIBITORZONEFLYINGMEDIUM";
        case UNIT_TYPEID::INHIBITORZONEFLYINGSMALL :
            return "INHIBITORZONEFLYINGSMALL";
        case UNIT_TYPEID::INHIBITORZONELARGE  : return "INHIBITORZONELARGE";
        case UNIT_TYPEID::INHIBITORZONEMEDIUM : return "INHIBITORZONEMEDIUM";
        case UNIT_TYPEID::INHIBITORZONESMALL  : return "INHIBITORZONESMALL";
        case UNIT_TYPEID::INVALID             : return "INVALID";
        case UNIT_TYPEID::INVISIBLEPYLON      : return "INVISIBLEPYLON";
        case UNIT_TYPEID::IONCANNONSWEAPON    : return "IONCANNONSWEAPON";
        case UNIT_TYPEID::IPISTOLAD           : return "IPISTOLAD";
        case UNIT_TYPEID::ITEMGRAVITYBOMBS    : return "ITEMGRAVITYBOMBS";
        case UNIT_TYPEID::ITEMGRAVITYBOMBSWEAPON :
            return "ITEMGRAVITYBOMBSWEAPON";
        case UNIT_TYPEID::ITEMGRENADES         : return "ITEMGRENADES";
        case UNIT_TYPEID::ITEMGRENADESWEAPON   : return "ITEMGRENADESWEAPON";
        case UNIT_TYPEID::ITEMMEDKIT           : return "ITEMMEDKIT";
        case UNIT_TYPEID::ITEMMINES            : return "ITEMMINES";
        case UNIT_TYPEID::JORIUMSTOCKPILE      : return "JORIUMSTOCKPILE";
        case UNIT_TYPEID::KARAKMALE            : return "KARAKMALE";
        case UNIT_TYPEID::KARASS               : return "KARASS";
        case UNIT_TYPEID::KARASSWEAPON         : return "KARASSWEAPON";
        case UNIT_TYPEID::KD8CHARGEWEAPON      : return "KD8CHARGEWEAPON";
        case UNIT_TYPEID::KERRIGAN             : return "KERRIGAN";
        case UNIT_TYPEID::KERRIGANCHAR         : return "KERRIGANCHAR";
        case UNIT_TYPEID::KERRIGANCHARBURROWED : return "KERRIGANCHARBURROWED";
        case UNIT_TYPEID::KERRIGANCHARWEAPON   : return "KERRIGANCHARWEAPON";
        case UNIT_TYPEID::KERRIGANEGG          : return "KERRIGANEGG";
        case UNIT_TYPEID::KERRIGANWEAPON       : return "KERRIGANWEAPON";
        case UNIT_TYPEID::L800ETC_AD           : return "L800ETC_AD";
        case UNIT_TYPEID::LABBOT               : return "LABBOT";
        case UNIT_TYPEID::LARVARELEASEMISSILE  : return "LARVARELEASEMISSILE";
        case UNIT_TYPEID::LEVIATHAN            : return "LEVIATHAN";
        case UNIT_TYPEID::LEVIATHANSCOURGEMISSILE :
            return "LEVIATHANSCOURGEMISSILE";
        case UNIT_TYPEID::LIBERATORAGMISSILE : return "LIBERATORAGMISSILE";
        case UNIT_TYPEID::LIBERATORDAMAGEMISSILE :
            return "LIBERATORDAMAGEMISSILE";
        case UNIT_TYPEID::LIBERATORMISSILE     : return "LIBERATORMISSILE";
        case UNIT_TYPEID::LIBERATORSKINPREVIEW : return "LIBERATORSKINPREVIEW";
        case UNIT_TYPEID::LIGHTNINGBOMBWEAPON  : return "LIGHTNINGBOMBWEAPON";
        case UNIT_TYPEID::LOADOUTSPRAY_1       : return "LOADOUTSPRAY_1";
        case UNIT_TYPEID::LOADOUTSPRAY_10      : return "LOADOUTSPRAY_10";
        case UNIT_TYPEID::LOADOUTSPRAY_11      : return "LOADOUTSPRAY_11";
        case UNIT_TYPEID::LOADOUTSPRAY_12      : return "LOADOUTSPRAY_12";
        case UNIT_TYPEID::LOADOUTSPRAY_13      : return "LOADOUTSPRAY_13";
        case UNIT_TYPEID::LOADOUTSPRAY_14      : return "LOADOUTSPRAY_14";
        case UNIT_TYPEID::LOADOUTSPRAY_2       : return "LOADOUTSPRAY_2";
        case UNIT_TYPEID::LOADOUTSPRAY_3       : return "LOADOUTSPRAY_3";
        case UNIT_TYPEID::LOADOUTSPRAY_4       : return "LOADOUTSPRAY_4";
        case UNIT_TYPEID::LOADOUTSPRAY_5       : return "LOADOUTSPRAY_5";
        case UNIT_TYPEID::LOADOUTSPRAY_6       : return "LOADOUTSPRAY_6";
        case UNIT_TYPEID::LOADOUTSPRAY_7       : return "LOADOUTSPRAY_7";
        case UNIT_TYPEID::LOADOUTSPRAY_8       : return "LOADOUTSPRAY_8";
        case UNIT_TYPEID::LOADOUTSPRAY_9       : return "LOADOUTSPRAY_9";
        case UNIT_TYPEID::LOCUSTMPEGGAMISSILEWEAPON :
            return "LOCUSTMPEGGAMISSILEWEAPON";
        case UNIT_TYPEID::LOCUSTMPEGGBMISSILEWEAPON :
            return "LOCUSTMPEGGBMISSILEWEAPON";
        case UNIT_TYPEID::LOCUSTMPPRECURSOR : return "LOCUSTMPPRECURSOR";
        case UNIT_TYPEID::LOCUSTMPWEAPON    : return "LOCUSTMPWEAPON";
        case UNIT_TYPEID::LOGISTICSHEADQUARTERS :
            return "LOGISTICSHEADQUARTERS";
        case UNIT_TYPEID::LOKI : return "LOKI";
        case UNIT_TYPEID::LOKIHURRICANEMISSILELEFT :
            return "LOKIHURRICANEMISSILELEFT";
        case UNIT_TYPEID::LOKIHURRICANEMISSILERIGHT :
            return "LOKIHURRICANEMISSILERIGHT";
        case UNIT_TYPEID::LOKIYAMATOWEAPON : return "LOKIYAMATOWEAPON";
        case UNIT_TYPEID::LONGBOLTMISSILEWEAPON :
            return "LONGBOLTMISSILEWEAPON";
        case UNIT_TYPEID::LURKER            : return "LURKER";
        case UNIT_TYPEID::LURKERBURROWED    : return "LURKERBURROWED";
        case UNIT_TYPEID::LURKERDEN         : return "LURKERDEN";
        case UNIT_TYPEID::LURKEREGG         : return "LURKEREGG";
        case UNIT_TYPEID::LYOTE             : return "LYOTE";
        case UNIT_TYPEID::MAAR              : return "MAAR";
        case UNIT_TYPEID::MAARWARPINUNIT    : return "MAARWARPINUNIT";
        case UNIT_TYPEID::MAINCELLBLOCK     : return "MAINCELLBLOCK";
        case UNIT_TYPEID::MARSARABRIDGEBLUR : return "MARSARABRIDGEBLUR";
        case UNIT_TYPEID::MARSARABRIDGEBRUL : return "MARSARABRIDGEBRUL";
        case UNIT_TYPEID::MEDIC             : return "MEDIC";
        case UNIT_TYPEID::MENGSKHOLOGRAMBILLBOARD :
            return "MENGSKHOLOGRAMBILLBOARD";
        case UNIT_TYPEID::MENGSKSTATUE      : return "MENGSKSTATUE";
        case UNIT_TYPEID::MENGSKSTATUEALONE : return "MENGSKSTATUEALONE";
        case UNIT_TYPEID::MERCCOMPOUND      : return "MERCCOMPOUND";
        case UNIT_TYPEID::MERCENARYFORTRESS : return "MERCENARYFORTRESS";
        case UNIT_TYPEID::METALGATEDIAGONALBLUR :
            return "METALGATEDIAGONALBLUR";
        case UNIT_TYPEID::METALGATEDIAGONALBLURLOWERED :
            return "METALGATEDIAGONALBLURLOWERED";
        case UNIT_TYPEID::METALGATEDIAGONALULBR :
            return "METALGATEDIAGONALULBR";
        case UNIT_TYPEID::METALGATEDIAGONALULBRLOWERED :
            return "METALGATEDIAGONALULBRLOWERED";
        case UNIT_TYPEID::METALGATESTRAIGHTHORIZONTAL :
            return "METALGATESTRAIGHTHORIZONTAL";
        case UNIT_TYPEID::METALGATESTRAIGHTHORIZONTALBF :
            return "METALGATESTRAIGHTHORIZONTALBF";
        case UNIT_TYPEID::METALGATESTRAIGHTHORIZONTALBFLOWERED :
            return "METALGATESTRAIGHTHORIZONTALBFLOWERED";
        case UNIT_TYPEID::METALGATESTRAIGHTHORIZONTALLOWERED :
            return "METALGATESTRAIGHTHORIZONTALLOWERED";
        case UNIT_TYPEID::METALGATESTRAIGHTVERTICAL :
            return "METALGATESTRAIGHTVERTICAL";
        case UNIT_TYPEID::METALGATESTRAIGHTVERTICALLF :
            return "METALGATESTRAIGHTVERTICALLF";
        case UNIT_TYPEID::METALGATESTRAIGHTVERTICALLFLOWERED :
            return "METALGATESTRAIGHTVERTICALLFLOWERED";
        case UNIT_TYPEID::METALGATESTRAIGHTVERTICALLOWERED :
            return "METALGATESTRAIGHTVERTICALLOWERED";
        case UNIT_TYPEID::MINDSIPHONRETURNWEAPON :
            return "MINDSIPHONRETURNWEAPON";
        case UNIT_TYPEID::MINDSIPHONWEAPON   : return "MINDSIPHONWEAPON";
        case UNIT_TYPEID::MINERALCRYSTAL     : return "MINERALCRYSTAL";
        case UNIT_TYPEID::MINERALFIELDOPAQUE : return "MINERALFIELDOPAQUE";
        case UNIT_TYPEID::MINERALFIELDOPAQUE900 :
            return "MINERALFIELDOPAQUE900";
        case UNIT_TYPEID::MINERMALE : return "MINERMALE";
        case UNIT_TYPEID::MOHANDAR  : return "MOHANDAR";
        case UNIT_TYPEID::MONLYTHARTIFACTFORCEFIELD :
            return "MONLYTHARTIFACTFORCEFIELD";
        case UNIT_TYPEID::MONLYTHFORCEFIELDSTATUE :
            return "MONLYTHFORCEFIELDSTATUE";
        case UNIT_TYPEID::MONOLITH : return "MONOLITH";
        case UNIT_TYPEID::MOOPY    : return "MOOPY";
        case UNIT_TYPEID::MOTHERSHIPCOREWEAPONWEAPON :
            return "MOTHERSHIPCOREWEAPONWEAPON";
        case UNIT_TYPEID::MULTIKILLOBJECT    : return "MULTIKILLOBJECT";
        case UNIT_TYPEID::MURLOCMARINE       : return "MURLOCMARINE";
        case UNIT_TYPEID::MUTALISKEGG        : return "MUTALISKEGG";
        case UNIT_TYPEID::MUTALISKEGGMISSILE : return "MUTALISKEGGMISSILE";
        case UNIT_TYPEID::NATURALGAS         : return "NATURALGAS";
        case UNIT_TYPEID::NATURALMINERALS    : return "NATURALMINERALS";
        case UNIT_TYPEID::NATURALMINERALSRED : return "NATURALMINERALSRED";
        case UNIT_TYPEID::NEEDLESPINESWEAPON : return "NEEDLESPINESWEAPON";
        case UNIT_TYPEID::NEURALPARASITETENTACLEMISSILE :
            return "NEURALPARASITETENTACLEMISSILE";
        case UNIT_TYPEID::NEURALPARASITEWEAPON : return "NEURALPARASITEWEAPON";
        case UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD :
            return "NEUTRAL_BATTLESTATIONMINERALFIELD";
        case UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD750 :
            return "NEUTRAL_BATTLESTATIONMINERALFIELD750";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLEROCKTOWERDEBRIS :
            return "NEUTRAL_COLLAPSIBLEROCKTOWERDEBRIS";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLEROCKTOWERDIAGONAL :
            return "NEUTRAL_COLLAPSIBLEROCKTOWERDIAGONAL";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLEROCKTOWERPUSHUNIT :
            return "NEUTRAL_COLLAPSIBLEROCKTOWERPUSHUNIT";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERDEBRIS :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERDEBRIS";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERDIAGONAL :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERDIAGONAL";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNIT :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNIT";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPLEFT :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPLEFT";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPRIGHT :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPRIGHT";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERRAMPLEFT :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERRAMPLEFT";
        case UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERRAMPRIGHT :
            return "NEUTRAL_COLLAPSIBLETERRANTOWERRAMPRIGHT";
        case UNIT_TYPEID::NEUTRAL_DEBRISRAMPLEFT :
            return "NEUTRAL_DEBRISRAMPLEFT";
        case UNIT_TYPEID::NEUTRAL_DEBRISRAMPRIGHT :
            return "NEUTRAL_DEBRISRAMPRIGHT";
        case UNIT_TYPEID::NEUTRAL_DESTRUCTIBLECITYDEBRIS6X6 :
            return "NEUTRAL_DESTRUCTIBLECITYDEBRIS6X6";
        case UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEDEBRIS6X6 :
            return "NEUTRAL_DESTRUCTIBLEDEBRIS6X6";
        case UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEBLUR :
            return "NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEBLUR";
        case UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEULBR :
            return "NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEULBR";
        case UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEROCK6X6 :
            return "NEUTRAL_DESTRUCTIBLEROCK6X6";
        case UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEROCKEX1DIAGONALHUGEBLUR :
            return "NEUTRAL_DESTRUCTIBLEROCKEX1DIAGONALHUGEBLUR";
        case UNIT_TYPEID::NEUTRAL_FORCEFIELD  : return "NEUTRAL_FORCEFIELD";
        case UNIT_TYPEID::NEUTRAL_KARAKFEMALE : return "NEUTRAL_KARAKFEMALE";
        case UNIT_TYPEID::NEUTRAL_LABMINERALFIELD :
            return "NEUTRAL_LABMINERALFIELD";
        case UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750 :
            return "NEUTRAL_LABMINERALFIELD750";
        case UNIT_TYPEID::NEUTRAL_MINERALFIELD : return "NEUTRAL_MINERALFIELD";
        case UNIT_TYPEID::NEUTRAL_MINERALFIELD450 :
            return "NEUTRAL_MINERALFIELD450";
        case UNIT_TYPEID::NEUTRAL_MINERALFIELD750 :
            return "NEUTRAL_MINERALFIELD750";
        case UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER :
            return "NEUTRAL_PROTOSSVESPENEGEYSER";
        case UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD :
            return "NEUTRAL_PURIFIERMINERALFIELD";
        case UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD750 :
            return "NEUTRAL_PURIFIERMINERALFIELD750";
        case UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD :
            return "NEUTRAL_PURIFIERRICHMINERALFIELD";
        case UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD750 :
            return "NEUTRAL_PURIFIERRICHMINERALFIELD750";
        case UNIT_TYPEID::NEUTRAL_PURIFIERVESPENEGEYSER :
            return "NEUTRAL_PURIFIERVESPENEGEYSER";
        case UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD :
            return "NEUTRAL_RICHMINERALFIELD";
        case UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750 :
            return "NEUTRAL_RICHMINERALFIELD750";
        case UNIT_TYPEID::NEUTRAL_RICHVESPENEGEYSER :
            return "NEUTRAL_RICHVESPENEGEYSER";
        case UNIT_TYPEID::NEUTRAL_SCANTIPEDE : return "NEUTRAL_SCANTIPEDE";
        case UNIT_TYPEID::NEUTRAL_SHAKURASVESPENEGEYSER :
            return "NEUTRAL_SHAKURASVESPENEGEYSER";
        case UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER :
            return "NEUTRAL_SPACEPLATFORMGEYSER";
        case UNIT_TYPEID::NEUTRAL_UNBUILDABLEBRICKSDESTRUCTIBLE :
            return "NEUTRAL_UNBUILDABLEBRICKSDESTRUCTIBLE";
        case UNIT_TYPEID::NEUTRAL_UNBUILDABLEPLATESDESTRUCTIBLE :
            return "NEUTRAL_UNBUILDABLEPLATESDESTRUCTIBLE";
        case UNIT_TYPEID::NEUTRAL_UTILITYBOT : return "NEUTRAL_UTILITYBOT";
        case UNIT_TYPEID::NEUTRAL_VESPENEGEYSER :
            return "NEUTRAL_VESPENEGEYSER";
        case UNIT_TYPEID::NEUTRAL_XELNAGATOWER : return "NEUTRAL_XELNAGATOWER";
        case UNIT_TYPEID::NEWFOLSOMPRISONENTRANCE :
            return "NEWFOLSOMPRISONENTRANCE";
        case UNIT_TYPEID::NEWSARCTURUSINTERVIEWSET :
            return "NEWSARCTURUSINTERVIEWSET";
        case UNIT_TYPEID::NEWSARCTURUSPRESSROOM :
            return "NEWSARCTURUSPRESSROOM";
        case UNIT_TYPEID::NEWSMEINHOFFREFUGEECENTER :
            return "NEWSMEINHOFFREFUGEECENTER";
        case UNIT_TYPEID::NEWSRAYNORLOGO : return "NEWSRAYNORLOGO";
        case UNIT_TYPEID::NEWSTVEFFECT   : return "NEWSTVEFFECT";
        case UNIT_TYPEID::NOVA           : return "NOVA";
        case UNIT_TYPEID::NUKENOODLESCOMMERCIAL :
            return "NUKENOODLESCOMMERCIAL";
        case UNIT_TYPEID::NUKEPACK           : return "NUKEPACK";
        case UNIT_TYPEID::NUKESILONOVA       : return "NUKESILONOVA";
        case UNIT_TYPEID::NYDUSCANALATTACKER : return "NYDUSCANALATTACKER";
        case UNIT_TYPEID::NYDUSCANALATTACKERWEAPON :
            return "NYDUSCANALATTACKERWEAPON";
        case UNIT_TYPEID::NYDUSCANALCREEPER  : return "NYDUSCANALCREEPER";
        case UNIT_TYPEID::NYDUSWORMLAVADEATH : return "NYDUSWORMLAVADEATH";
        case UNIT_TYPEID::OBELISK            : return "OBELISK";
        case UNIT_TYPEID::ODIN               : return "ODIN";
        case UNIT_TYPEID::ODINAAWEAPON       : return "ODINAAWEAPON";
        case UNIT_TYPEID::ODINBUILD          : return "ODINBUILD";
        case UNIT_TYPEID::ODINWRECKAGE       : return "ODINWRECKAGE";
        case UNIT_TYPEID::OMEGALISK          : return "OMEGALISK";
        case UNIT_TYPEID::OMEGALISKBURROWED  : return "OMEGALISKBURROWED";
        case UNIT_TYPEID::ORACLEWEAPON       : return "ORACLEWEAPON";
        case UNIT_TYPEID::OVERLORDGENERATECREEPKEYBIND :
            return "OVERLORDGENERATECREEPKEYBIND";
        case UNIT_TYPEID::OVERMIND             : return "OVERMIND";
        case UNIT_TYPEID::OVERMINDREMAINS      : return "OVERMINDREMAINS";
        case UNIT_TYPEID::PALLETGAS            : return "PALLETGAS";
        case UNIT_TYPEID::PALLETMINERALS       : return "PALLETMINERALS";
        case UNIT_TYPEID::PARASITESPOREWEAPON  : return "PARASITESPOREWEAPON";
        case UNIT_TYPEID::PARASITICBOMBMISSILE : return "PARASITICBOMBMISSILE";
        case UNIT_TYPEID::PATHINGBLOCKER1X1    : return "PATHINGBLOCKER1X1";
        case UNIT_TYPEID::PATHINGBLOCKER2X2    : return "PATHINGBLOCKER2X2";
        case UNIT_TYPEID::PATHINGBLOCKERRADIUS1 :
            return "PATHINGBLOCKERRADIUS1";
        case UNIT_TYPEID::PERDITIONTURRET : return "PERDITIONTURRET";
        case UNIT_TYPEID::PERDITIONTURRETUNDERGROUND :
            return "PERDITIONTURRETUNDERGROUND";
        case UNIT_TYPEID::PERMANENTCREEPBLOCKER1X1 :
            return "PERMANENTCREEPBLOCKER1X1";
        case UNIT_TYPEID::PHOTONCANNONWEAPON : return "PHOTONCANNONWEAPON";
        case UNIT_TYPEID::PHYSICSCAPSULE     : return "PHYSICSCAPSULE";
        case UNIT_TYPEID::PHYSICSCUBE        : return "PHYSICSCUBE";
        case UNIT_TYPEID::PHYSICSCYLINDER    : return "PHYSICSCYLINDER";
        case UNIT_TYPEID::PHYSICSKNOT        : return "PHYSICSKNOT";
        case UNIT_TYPEID::PHYSICSL           : return "PHYSICSL";
        case UNIT_TYPEID::PHYSICSPRIMITIVES  : return "PHYSICSPRIMITIVES";
        case UNIT_TYPEID::PHYSICSSPHERE      : return "PHYSICSSPHERE";
        case UNIT_TYPEID::PHYSICSSTAR        : return "PHYSICSSTAR";
        case UNIT_TYPEID::PICKUPCHRONORIFTCHARGE :
            return "PICKUPCHRONORIFTCHARGE";
        case UNIT_TYPEID::PICKUPCHRONORIFTDEVICE :
            return "PICKUPCHRONORIFTDEVICE";
        case UNIT_TYPEID::PICKUPENERGY100      : return "PICKUPENERGY100";
        case UNIT_TYPEID::PICKUPENERGY25       : return "PICKUPENERGY25";
        case UNIT_TYPEID::PICKUPENERGY50       : return "PICKUPENERGY50";
        case UNIT_TYPEID::PICKUPENERGYFULL     : return "PICKUPENERGYFULL";
        case UNIT_TYPEID::PICKUPGRENADES       : return "PICKUPGRENADES";
        case UNIT_TYPEID::PICKUPHEALTH100      : return "PICKUPHEALTH100";
        case UNIT_TYPEID::PICKUPHEALTH25       : return "PICKUPHEALTH25";
        case UNIT_TYPEID::PICKUPHEALTH50       : return "PICKUPHEALTH50";
        case UNIT_TYPEID::PICKUPHEALTHFULL     : return "PICKUPHEALTHFULL";
        case UNIT_TYPEID::PICKUPMANARECHARGE   : return "PICKUPMANARECHARGE";
        case UNIT_TYPEID::PICKUPMEDICRECHARGE  : return "PICKUPMEDICRECHARGE";
        case UNIT_TYPEID::PICKUPMINES          : return "PICKUPMINES";
        case UNIT_TYPEID::PICKUPPALLETGAS      : return "PICKUPPALLETGAS";
        case UNIT_TYPEID::PICKUPPALLETMINERALS : return "PICKUPPALLETMINERALS";
        case UNIT_TYPEID::PICKUPPLASMAGUN      : return "PICKUPPLASMAGUN";
        case UNIT_TYPEID::PICKUPPLASMAROUNDS   : return "PICKUPPLASMAROUNDS";
        case UNIT_TYPEID::PICKUPPSISTORM       : return "PICKUPPSISTORM";
        case UNIT_TYPEID::PICKUPRESTORATIONCHARGE :
            return "PICKUPRESTORATIONCHARGE";
        case UNIT_TYPEID::PICKUPSCRAPSALVAGE1X1 :
            return "PICKUPSCRAPSALVAGE1X1";
        case UNIT_TYPEID::PICKUPSCRAPSALVAGE2X2 :
            return "PICKUPSCRAPSALVAGE2X2";
        case UNIT_TYPEID::PICKUPSCRAPSALVAGE3X3 :
            return "PICKUPSCRAPSALVAGE3X3";
        case UNIT_TYPEID::PLASMATORPEDOESWEAPON :
            return "PLASMATORPEDOESWEAPON";
        case UNIT_TYPEID::PLATFORMCONNECTOR : return "PLATFORMCONNECTOR";
        case UNIT_TYPEID::POINTDEFENSEDRONERELEASEWEAPON :
            return "POINTDEFENSEDRONERELEASEWEAPON";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITE10 :
            return "PORTCITY_BRIDGE_UNITE10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITE10OUT :
            return "PORTCITY_BRIDGE_UNITE10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITE12 :
            return "PORTCITY_BRIDGE_UNITE12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITE12OUT :
            return "PORTCITY_BRIDGE_UNITE12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITE8 :
            return "PORTCITY_BRIDGE_UNITE8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITE8OUT :
            return "PORTCITY_BRIDGE_UNITE8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITN10 :
            return "PORTCITY_BRIDGE_UNITN10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITN10OUT :
            return "PORTCITY_BRIDGE_UNITN10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITN12 :
            return "PORTCITY_BRIDGE_UNITN12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITN12OUT :
            return "PORTCITY_BRIDGE_UNITN12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITN8 :
            return "PORTCITY_BRIDGE_UNITN8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITN8OUT :
            return "PORTCITY_BRIDGE_UNITN8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNE10 :
            return "PORTCITY_BRIDGE_UNITNE10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNE10OUT :
            return "PORTCITY_BRIDGE_UNITNE10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNE12 :
            return "PORTCITY_BRIDGE_UNITNE12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNE12OUT :
            return "PORTCITY_BRIDGE_UNITNE12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNE8 :
            return "PORTCITY_BRIDGE_UNITNE8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNE8OUT :
            return "PORTCITY_BRIDGE_UNITNE8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNW10 :
            return "PORTCITY_BRIDGE_UNITNW10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNW10OUT :
            return "PORTCITY_BRIDGE_UNITNW10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNW12 :
            return "PORTCITY_BRIDGE_UNITNW12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNW12OUT :
            return "PORTCITY_BRIDGE_UNITNW12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNW8 :
            return "PORTCITY_BRIDGE_UNITNW8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITNW8OUT :
            return "PORTCITY_BRIDGE_UNITNW8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITS10 :
            return "PORTCITY_BRIDGE_UNITS10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITS10OUT :
            return "PORTCITY_BRIDGE_UNITS10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITS12 :
            return "PORTCITY_BRIDGE_UNITS12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITS12OUT :
            return "PORTCITY_BRIDGE_UNITS12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITS8 :
            return "PORTCITY_BRIDGE_UNITS8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITS8OUT :
            return "PORTCITY_BRIDGE_UNITS8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSE10 :
            return "PORTCITY_BRIDGE_UNITSE10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSE10OUT :
            return "PORTCITY_BRIDGE_UNITSE10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSE12 :
            return "PORTCITY_BRIDGE_UNITSE12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSE12OUT :
            return "PORTCITY_BRIDGE_UNITSE12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSE8 :
            return "PORTCITY_BRIDGE_UNITSE8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSE8OUT :
            return "PORTCITY_BRIDGE_UNITSE8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSW10 :
            return "PORTCITY_BRIDGE_UNITSW10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSW10OUT :
            return "PORTCITY_BRIDGE_UNITSW10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSW12 :
            return "PORTCITY_BRIDGE_UNITSW12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSW12OUT :
            return "PORTCITY_BRIDGE_UNITSW12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSW8 :
            return "PORTCITY_BRIDGE_UNITSW8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITSW8OUT :
            return "PORTCITY_BRIDGE_UNITSW8OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITW10 :
            return "PORTCITY_BRIDGE_UNITW10";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITW10OUT :
            return "PORTCITY_BRIDGE_UNITW10OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITW12 :
            return "PORTCITY_BRIDGE_UNITW12";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITW12OUT :
            return "PORTCITY_BRIDGE_UNITW12OUT";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITW8 :
            return "PORTCITY_BRIDGE_UNITW8";
        case UNIT_TYPEID::PORTCITY_BRIDGE_UNITW8OUT :
            return "PORTCITY_BRIDGE_UNITW8OUT";
        case UNIT_TYPEID::PORTJUNKER         : return "PORTJUNKER";
        case UNIT_TYPEID::PREDATOR           : return "PREDATOR";
        case UNIT_TYPEID::PRESERVERA         : return "PRESERVERA";
        case UNIT_TYPEID::PRESERVERB         : return "PRESERVERB";
        case UNIT_TYPEID::PRESERVERBASE      : return "PRESERVERBASE";
        case UNIT_TYPEID::PRESERVERC         : return "PRESERVERC";
        case UNIT_TYPEID::PRESERVERPRISON    : return "PRESERVERPRISON";
        case UNIT_TYPEID::PRISONERCIVILIAN   : return "PRISONERCIVILIAN";
        case UNIT_TYPEID::PRISONERSPECTRE    : return "PRISONERSPECTRE";
        case UNIT_TYPEID::PRISONZEALOT       : return "PRISONZEALOT";
        case UNIT_TYPEID::PROTOSSCRATES      : return "PROTOSSCRATES";
        case UNIT_TYPEID::PROTOSSPSIELEMENTS : return "PROTOSSPSIELEMENTS";
        case UNIT_TYPEID::PROTOSSRELIC       : return "PROTOSSRELIC";
        case UNIT_TYPEID::PROTOSSSNAKESEGMENTDEMO :
            return "PROTOSSSNAKESEGMENTDEMO";
        case UNIT_TYPEID::PROTOSS_ADEPT : return "PROTOSS_ADEPT";
        case UNIT_TYPEID::PROTOSS_ADEPTPHASESHIFT :
            return "PROTOSS_ADEPTPHASESHIFT";
        case UNIT_TYPEID::PROTOSS_ARCHON      : return "PROTOSS_ARCHON";
        case UNIT_TYPEID::PROTOSS_ASSIMILATOR : return "PROTOSS_ASSIMILATOR";
        case UNIT_TYPEID::PROTOSS_ASSIMILATORRICH :
            return "PROTOSS_ASSIMILATORRICH";
        case UNIT_TYPEID::PROTOSS_CARRIER  : return "PROTOSS_CARRIER";
        case UNIT_TYPEID::PROTOSS_COLOSSUS : return "PROTOSS_COLOSSUS";
        case UNIT_TYPEID::PROTOSS_CYBERNETICSCORE :
            return "PROTOSS_CYBERNETICSCORE";
        case UNIT_TYPEID::PROTOSS_DARKSHRINE  : return "PROTOSS_DARKSHRINE";
        case UNIT_TYPEID::PROTOSS_DARKTEMPLAR : return "PROTOSS_DARKTEMPLAR";
        case UNIT_TYPEID::PROTOSS_DISRUPTOR   : return "PROTOSS_DISRUPTOR";
        case UNIT_TYPEID::PROTOSS_DISRUPTORPHASED :
            return "PROTOSS_DISRUPTORPHASED";
        case UNIT_TYPEID::PROTOSS_FLEETBEACON : return "PROTOSS_FLEETBEACON";
        case UNIT_TYPEID::PROTOSS_FORGE       : return "PROTOSS_FORGE";
        case UNIT_TYPEID::PROTOSS_GATEWAY     : return "PROTOSS_GATEWAY";
        case UNIT_TYPEID::PROTOSS_HIGHTEMPLAR : return "PROTOSS_HIGHTEMPLAR";
        case UNIT_TYPEID::PROTOSS_IMMORTAL    : return "PROTOSS_IMMORTAL";
        case UNIT_TYPEID::PROTOSS_INTERCEPTOR : return "PROTOSS_INTERCEPTOR";
        case UNIT_TYPEID::PROTOSS_MOTHERSHIP  : return "PROTOSS_MOTHERSHIP";
        case UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE :
            return "PROTOSS_MOTHERSHIPCORE";
        case UNIT_TYPEID::PROTOSS_NEXUS    : return "PROTOSS_NEXUS";
        case UNIT_TYPEID::PROTOSS_OBSERVER : return "PROTOSS_OBSERVER";
        case UNIT_TYPEID::PROTOSS_OBSERVERSIEGEMODE :
            return "PROTOSS_OBSERVERSIEGEMODE";
        case UNIT_TYPEID::PROTOSS_ORACLE : return "PROTOSS_ORACLE";
        case UNIT_TYPEID::PROTOSS_ORACLESTASISTRAP :
            return "PROTOSS_ORACLESTASISTRAP";
        case UNIT_TYPEID::PROTOSS_PHOENIX      : return "PROTOSS_PHOENIX";
        case UNIT_TYPEID::PROTOSS_PHOTONCANNON : return "PROTOSS_PHOTONCANNON";
        case UNIT_TYPEID::PROTOSS_PROBE        : return "PROTOSS_PROBE";
        case UNIT_TYPEID::PROTOSS_PYLON        : return "PROTOSS_PYLON";
        case UNIT_TYPEID::PROTOSS_PYLONOVERCHARGED :
            return "PROTOSS_PYLONOVERCHARGED";
        case UNIT_TYPEID::PROTOSS_ROBOTICSBAY : return "PROTOSS_ROBOTICSBAY";
        case UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY :
            return "PROTOSS_ROBOTICSFACILITY";
        case UNIT_TYPEID::PROTOSS_SENTRY : return "PROTOSS_SENTRY";
        case UNIT_TYPEID::PROTOSS_SHIELDBATTERY :
            return "PROTOSS_SHIELDBATTERY";
        case UNIT_TYPEID::PROTOSS_STALKER  : return "PROTOSS_STALKER";
        case UNIT_TYPEID::PROTOSS_STARGATE : return "PROTOSS_STARGATE";
        case UNIT_TYPEID::PROTOSS_TEMPEST  : return "PROTOSS_TEMPEST";
        case UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE :
            return "PROTOSS_TEMPLARARCHIVE";
        case UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL :
            return "PROTOSS_TWILIGHTCOUNCIL";
        case UNIT_TYPEID::PROTOSS_VOIDRAY   : return "PROTOSS_VOIDRAY";
        case UNIT_TYPEID::PROTOSS_WARPGATE  : return "PROTOSS_WARPGATE";
        case UNIT_TYPEID::PROTOSS_WARPPRISM : return "PROTOSS_WARPPRISM";
        case UNIT_TYPEID::PROTOSS_WARPPRISMPHASING :
            return "PROTOSS_WARPPRISMPHASING";
        case UNIT_TYPEID::PROTOSS_ZEALOT   : return "PROTOSS_ZEALOT";
        case UNIT_TYPEID::PSIDISRUPTOR     : return "PSIDISRUPTOR";
        case UNIT_TYPEID::PSIINDOCTRINATOR : return "PSIINDOCTRINATOR";
        case UNIT_TYPEID::PSIOPSCOMMERCIAL : return "PSIOPSCOMMERCIAL";
        case UNIT_TYPEID::PSISHOCKWEAPON   : return "PSISHOCKWEAPON";
        case UNIT_TYPEID::PUNISHERGRENADESLMWEAPON :
            return "PUNISHERGRENADESLMWEAPON";
        case UNIT_TYPEID::PURIFIER : return "PURIFIER";
        case UNIT_TYPEID::PURIFIERBLASTMARKUNIT :
            return "PURIFIERBLASTMARKUNIT";
        case UNIT_TYPEID::PYGALISK       : return "PYGALISK";
        case UNIT_TYPEID::PYGALISKCOCOON : return "PYGALISKCOCOON";
        case UNIT_TYPEID::QUEENMP        : return "QUEENMP";
        case UNIT_TYPEID::QUEENMPENSNAREMISSILE :
            return "QUEENMPENSNAREMISSILE";
        case UNIT_TYPEID::QUEENMPSPAWNBROODLINGSMISSILE :
            return "QUEENMPSPAWNBROODLINGSMISSILE";
        case UNIT_TYPEID::QUESTIONMARK    : return "QUESTIONMARK";
        case UNIT_TYPEID::RAVAGERBURROWED : return "RAVAGERBURROWED";
        case UNIT_TYPEID::RAVAGERCORROSIVEBILEMISSILE :
            return "RAVAGERCORROSIVEBILEMISSILE";
        case UNIT_TYPEID::RAVAGERWEAPONMISSILE : return "RAVAGERWEAPONMISSILE";
        case UNIT_TYPEID::RAVENREPAIRDRONE     : return "RAVENREPAIRDRONE";
        case UNIT_TYPEID::RAVENREPAIRDRONERELEASEWEAPON :
            return "RAVENREPAIRDRONERELEASEWEAPON";
        case UNIT_TYPEID::RAVENSCRAMBLERMISSILE :
            return "RAVENSCRAMBLERMISSILE";
        case UNIT_TYPEID::RAVENSHREDDERMISSILEWEAPON :
            return "RAVENSHREDDERMISSILEWEAPON";
        case UNIT_TYPEID::RAYNOR              : return "RAYNOR";
        case UNIT_TYPEID::RAYNOR01            : return "RAYNOR01";
        case UNIT_TYPEID::RAYNORCOMMANDO      : return "RAYNORCOMMANDO";
        case UNIT_TYPEID::REAPERPLACEHOLDER   : return "REAPERPLACEHOLDER";
        case UNIT_TYPEID::REAPERPLACEMENT     : return "REAPERPLACEMENT";
        case UNIT_TYPEID::REDSTONELAVACRITTER : return "REDSTONELAVACRITTER";
        case UNIT_TYPEID::REDSTONELAVACRITTERBURROWED :
            return "REDSTONELAVACRITTERBURROWED";
        case UNIT_TYPEID::REDSTONELAVACRITTERINJURED :
            return "REDSTONELAVACRITTERINJURED";
        case UNIT_TYPEID::REDSTONELAVACRITTERINJUREDBURROWED :
            return "REDSTONELAVACRITTERINJUREDBURROWED";
        case UNIT_TYPEID::RELEASEINTERCEPTORSBEACON :
            return "RELEASEINTERCEPTORSBEACON";
        case UNIT_TYPEID::RENEGADELONGBOLTMISSILEWEAPON :
            return "RENEGADELONGBOLTMISSILEWEAPON";
        case UNIT_TYPEID::RENEGADEMISSILETURRET :
            return "RENEGADEMISSILETURRET";
        case UNIT_TYPEID::REPLICANT            : return "REPLICANT";
        case UNIT_TYPEID::REPTILECRATE         : return "REPTILECRATE";
        case UNIT_TYPEID::REPULSERFIELD10      : return "REPULSERFIELD10";
        case UNIT_TYPEID::REPULSERFIELD12      : return "REPULSERFIELD12";
        case UNIT_TYPEID::REPULSERFIELD6       : return "REPULSERFIELD6";
        case UNIT_TYPEID::REPULSERFIELD8       : return "REPULSERFIELD8";
        case UNIT_TYPEID::REPULSORCANNONWEAPON : return "REPULSORCANNONWEAPON";
        case UNIT_TYPEID::RESOURCEBLOCKER      : return "RESOURCEBLOCKER";
        case UNIT_TYPEID::RIPFIELDGENERATOR    : return "RIPFIELDGENERATOR";
        case UNIT_TYPEID::RIPFIELDGENERATORSMALL :
            return "RIPFIELDGENERATORSMALL";
        case UNIT_TYPEID::ROCKS2X2NONCONJOINED : return "ROCKS2X2NONCONJOINED";
        case UNIT_TYPEID::ROUGHTERRAIN         : return "ROUGHTERRAIN";
        case UNIT_TYPEID::SCIENCEFACILITY      : return "SCIENCEFACILITY";
        case UNIT_TYPEID::SCIENCEVESSEL        : return "SCIENCEVESSEL";
        case UNIT_TYPEID::SCIENTIST            : return "SCIENTIST";
        case UNIT_TYPEID::SCOPETEST            : return "SCOPETEST";
        case UNIT_TYPEID::SCOURGE              : return "SCOURGE";
        case UNIT_TYPEID::SCOURGEMP            : return "SCOURGEMP";
        case UNIT_TYPEID::SCOUT                : return "SCOUT";
        case UNIT_TYPEID::SCOUTAIRWEAPONLEFT   : return "SCOUTAIRWEAPONLEFT";
        case UNIT_TYPEID::SCOUTAIRWEAPONRIGHT  : return "SCOUTAIRWEAPONRIGHT";
        case UNIT_TYPEID::SCOUTMP              : return "SCOUTMP";
        case UNIT_TYPEID::SCOUTMPAIRWEAPONLEFT : return "SCOUTMPAIRWEAPONLEFT";
        case UNIT_TYPEID::SCOUTMPAIRWEAPONRIGHT :
            return "SCOUTMPAIRWEAPONRIGHT";
        case UNIT_TYPEID::SCRAPHUGE       : return "SCRAPHUGE";
        case UNIT_TYPEID::SCRAPSALVAGE1X1 : return "SCRAPSALVAGE1X1";
        case UNIT_TYPEID::SCRAPSALVAGE2X2 : return "SCRAPSALVAGE2X2";
        case UNIT_TYPEID::SCRAPSALVAGE3X3 : return "SCRAPSALVAGE3X3";
        case UNIT_TYPEID::SECRETDOCUMENTS : return "SECRETDOCUMENTS";
        case UNIT_TYPEID::SECURITYGATEDIAGONALBLUR :
            return "SECURITYGATEDIAGONALBLUR";
        case UNIT_TYPEID::SECURITYGATEDIAGONALBLURLOWERED :
            return "SECURITYGATEDIAGONALBLURLOWERED";
        case UNIT_TYPEID::SECURITYGATEDIAGONALULBR :
            return "SECURITYGATEDIAGONALULBR";
        case UNIT_TYPEID::SECURITYGATEDIAGONALULBRLOWERED :
            return "SECURITYGATEDIAGONALULBRLOWERED";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTHORIZONTAL :
            return "SECURITYGATESTRAIGHTHORIZONTAL";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTHORIZONTALBF :
            return "SECURITYGATESTRAIGHTHORIZONTALBF";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTHORIZONTALBFLOWERED :
            return "SECURITYGATESTRAIGHTHORIZONTALBFLOWERED";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTHORIZONTALLOWERED :
            return "SECURITYGATESTRAIGHTHORIZONTALLOWERED";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTVERTICAL :
            return "SECURITYGATESTRAIGHTVERTICAL";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTVERTICALLF :
            return "SECURITYGATESTRAIGHTVERTICALLF";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTVERTICALLFLOWERED :
            return "SECURITYGATESTRAIGHTVERTICALLFLOWERED";
        case UNIT_TYPEID::SECURITYGATESTRAIGHTVERTICALLOWERED :
            return "SECURITYGATESTRAIGHTVERTICALLOWERED";
        case UNIT_TYPEID::SEEKERMISSILE        : return "SEEKERMISSILE";
        case UNIT_TYPEID::SELENDIS             : return "SELENDIS";
        case UNIT_TYPEID::SELENDISINTERCEPTOR  : return "SELENDISINTERCEPTOR";
        case UNIT_TYPEID::SENTRYGUN            : return "SENTRYGUN";
        case UNIT_TYPEID::SENTRYGUNUNDERGROUND : return "SENTRYGUNUNDERGROUND";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENE10 :
            return "SHAKURASLIGHTBRIDGENE10";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENE10OUT :
            return "SHAKURASLIGHTBRIDGENE10OUT";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENE12 :
            return "SHAKURASLIGHTBRIDGENE12";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENE12OUT :
            return "SHAKURASLIGHTBRIDGENE12OUT";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENE8 :
            return "SHAKURASLIGHTBRIDGENE8";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENE8OUT :
            return "SHAKURASLIGHTBRIDGENE8OUT";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENW10 :
            return "SHAKURASLIGHTBRIDGENW10";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENW10OUT :
            return "SHAKURASLIGHTBRIDGENW10OUT";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENW12 :
            return "SHAKURASLIGHTBRIDGENW12";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENW12OUT :
            return "SHAKURASLIGHTBRIDGENW12OUT";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENW8 :
            return "SHAKURASLIGHTBRIDGENW8";
        case UNIT_TYPEID::SHAKURASLIGHTBRIDGENW8OUT :
            return "SHAKURASLIGHTBRIDGENW8OUT";
        case UNIT_TYPEID::SHAPE4POINTSTAR      : return "SHAPE4POINTSTAR";
        case UNIT_TYPEID::SHAPE5POINTSTAR      : return "SHAPE5POINTSTAR";
        case UNIT_TYPEID::SHAPE6POINTSTAR      : return "SHAPE6POINTSTAR";
        case UNIT_TYPEID::SHAPE8POINTSTAR      : return "SHAPE8POINTSTAR";
        case UNIT_TYPEID::SHAPEAPPLE           : return "SHAPEAPPLE";
        case UNIT_TYPEID::SHAPEARROWPOINTER    : return "SHAPEARROWPOINTER";
        case UNIT_TYPEID::SHAPEBANANA          : return "SHAPEBANANA";
        case UNIT_TYPEID::SHAPEBASEBALL        : return "SHAPEBASEBALL";
        case UNIT_TYPEID::SHAPEBASEBALLBAT     : return "SHAPEBASEBALLBAT";
        case UNIT_TYPEID::SHAPEBASKETBALL      : return "SHAPEBASKETBALL";
        case UNIT_TYPEID::SHAPEBOWL            : return "SHAPEBOWL";
        case UNIT_TYPEID::SHAPEBOX             : return "SHAPEBOX";
        case UNIT_TYPEID::SHAPECAPSULE         : return "SHAPECAPSULE";
        case UNIT_TYPEID::SHAPECARROT          : return "SHAPECARROT";
        case UNIT_TYPEID::SHAPECASHLARGE       : return "SHAPECASHLARGE";
        case UNIT_TYPEID::SHAPECASHMEDIUM      : return "SHAPECASHMEDIUM";
        case UNIT_TYPEID::SHAPECASHSMALL       : return "SHAPECASHSMALL";
        case UNIT_TYPEID::SHAPECHERRY          : return "SHAPECHERRY";
        case UNIT_TYPEID::SHAPECONE            : return "SHAPECONE";
        case UNIT_TYPEID::SHAPECRESCENTMOON    : return "SHAPECRESCENTMOON";
        case UNIT_TYPEID::SHAPECUBE            : return "SHAPECUBE";
        case UNIT_TYPEID::SHAPECYLINDER        : return "SHAPECYLINDER";
        case UNIT_TYPEID::SHAPEDECAHEDRON      : return "SHAPEDECAHEDRON";
        case UNIT_TYPEID::SHAPEDIAMOND         : return "SHAPEDIAMOND";
        case UNIT_TYPEID::SHAPEDODECAHEDRON    : return "SHAPEDODECAHEDRON";
        case UNIT_TYPEID::SHAPEDOLLARSIGN      : return "SHAPEDOLLARSIGN";
        case UNIT_TYPEID::SHAPEEGG             : return "SHAPEEGG";
        case UNIT_TYPEID::SHAPEEUROSIGN        : return "SHAPEEUROSIGN";
        case UNIT_TYPEID::SHAPEFOOTBALL        : return "SHAPEFOOTBALL";
        case UNIT_TYPEID::SHAPEFOOTBALLCOLORED : return "SHAPEFOOTBALLCOLORED";
        case UNIT_TYPEID::SHAPEGEMSTONE        : return "SHAPEGEMSTONE";
        case UNIT_TYPEID::SHAPEGOLFBALL        : return "SHAPEGOLFBALL";
        case UNIT_TYPEID::SHAPEGOLFCLUB        : return "SHAPEGOLFCLUB";
        case UNIT_TYPEID::SHAPEGRAPE           : return "SHAPEGRAPE";
        case UNIT_TYPEID::SHAPEHAND            : return "SHAPEHAND";
        case UNIT_TYPEID::SHAPEHEART           : return "SHAPEHEART";
        case UNIT_TYPEID::SHAPEHOCKEYPUCK      : return "SHAPEHOCKEYPUCK";
        case UNIT_TYPEID::SHAPEHOCKEYSTICK     : return "SHAPEHOCKEYSTICK";
        case UNIT_TYPEID::SHAPEHORSESHOE       : return "SHAPEHORSESHOE";
        case UNIT_TYPEID::SHAPEICOSAHEDRON     : return "SHAPEICOSAHEDRON";
        case UNIT_TYPEID::SHAPEJACK            : return "SHAPEJACK";
        case UNIT_TYPEID::SHAPELEMON           : return "SHAPELEMON";
        case UNIT_TYPEID::SHAPELEMONSMALL      : return "SHAPELEMONSMALL";
        case UNIT_TYPEID::SHAPEMONEYBAG        : return "SHAPEMONEYBAG";
        case UNIT_TYPEID::SHAPEO               : return "SHAPEO";
        case UNIT_TYPEID::SHAPEOCTAHEDRON      : return "SHAPEOCTAHEDRON";
        case UNIT_TYPEID::SHAPEORANGE          : return "SHAPEORANGE";
        case UNIT_TYPEID::SHAPEORANGESMALL     : return "SHAPEORANGESMALL";
        case UNIT_TYPEID::SHAPEPEANUT          : return "SHAPEPEANUT";
        case UNIT_TYPEID::SHAPEPEAR            : return "SHAPEPEAR";
        case UNIT_TYPEID::SHAPEPINEAPPLE       : return "SHAPEPINEAPPLE";
        case UNIT_TYPEID::SHAPEPLUSSIGN        : return "SHAPEPLUSSIGN";
        case UNIT_TYPEID::SHAPEPOUNDSIGN       : return "SHAPEPOUNDSIGN";
        case UNIT_TYPEID::SHAPEPYRAMID         : return "SHAPEPYRAMID";
        case UNIT_TYPEID::SHAPERAINBOW         : return "SHAPERAINBOW";
        case UNIT_TYPEID::SHAPEROUNDEDCUBE     : return "SHAPEROUNDEDCUBE";
        case UNIT_TYPEID::SHAPESADFACE         : return "SHAPESADFACE";
        case UNIT_TYPEID::SHAPESHAMROCK        : return "SHAPESHAMROCK";
        case UNIT_TYPEID::SHAPESMILEYFACE      : return "SHAPESMILEYFACE";
        case UNIT_TYPEID::SHAPESOCCERBALL      : return "SHAPESOCCERBALL";
        case UNIT_TYPEID::SHAPESPADE           : return "SHAPESPADE";
        case UNIT_TYPEID::SHAPESPHERE          : return "SHAPESPHERE";
        case UNIT_TYPEID::SHAPESTRAWBERRY      : return "SHAPESTRAWBERRY";
        case UNIT_TYPEID::SHAPETENNISBALL      : return "SHAPETENNISBALL";
        case UNIT_TYPEID::SHAPETETRAHEDRON     : return "SHAPETETRAHEDRON";
        case UNIT_TYPEID::SHAPETHICKTORUS      : return "SHAPETHICKTORUS";
        case UNIT_TYPEID::SHAPETHINTORUS       : return "SHAPETHINTORUS";
        case UNIT_TYPEID::SHAPETORUS           : return "SHAPETORUS";
        case UNIT_TYPEID::SHAPETREASURECHESTCLOSED :
            return "SHAPETREASURECHESTCLOSED";
        case UNIT_TYPEID::SHAPETREASURECHESTOPEN :
            return "SHAPETREASURECHESTOPEN";
        case UNIT_TYPEID::SHAPETUBE            : return "SHAPETUBE";
        case UNIT_TYPEID::SHAPEWATERMELON      : return "SHAPEWATERMELON";
        case UNIT_TYPEID::SHAPEWATERMELONSMALL : return "SHAPEWATERMELONSMALL";
        case UNIT_TYPEID::SHAPEWONSIGN         : return "SHAPEWONSIGN";
        case UNIT_TYPEID::SHAPEX               : return "SHAPEX";
        case UNIT_TYPEID::SHAPEYENSIGN         : return "SHAPEYENSIGN";
        case UNIT_TYPEID::SHEEP                : return "SHEEP";
        case UNIT_TYPEID::SHIPALARM            : return "SHIPALARM";
        case UNIT_TYPEID::SHORTBRIDGEHORIZONTAL :
            return "SHORTBRIDGEHORIZONTAL";
        case UNIT_TYPEID::SHORTBRIDGEVERTICAL  : return "SHORTBRIDGEVERTICAL";
        case UNIT_TYPEID::SIEGEBREAKER         : return "SIEGEBREAKER";
        case UNIT_TYPEID::SIEGEBREAKERSIEGED   : return "SIEGEBREAKERSIEGED";
        case UNIT_TYPEID::SIEGETANKSKINPREVIEW : return "SIEGETANKSKINPREVIEW";
        case UNIT_TYPEID::SLAYNELEMENTAL       : return "SLAYNELEMENTAL";
        case UNIT_TYPEID::SLAYNELEMENTALGRABAIRUNIT :
            return "SLAYNELEMENTALGRABAIRUNIT";
        case UNIT_TYPEID::SLAYNELEMENTALGRABGROUNDUNIT :
            return "SLAYNELEMENTALGRABGROUNDUNIT";
        case UNIT_TYPEID::SLAYNELEMENTALGRABWEAPON :
            return "SLAYNELEMENTALGRABWEAPON";
        case UNIT_TYPEID::SLAYNELEMENTALWEAPON : return "SLAYNELEMENTALWEAPON";
        case UNIT_TYPEID::SLAYNSWARMHOSTSPAWNFLYER :
            return "SLAYNSWARMHOSTSPAWNFLYER";
        case UNIT_TYPEID::SMADJUTANT         : return "SMADJUTANT";
        case UNIT_TYPEID::SMADJUTANTHOLOGRAM : return "SMADJUTANTHOLOGRAM";
        case UNIT_TYPEID::SMANNABELLE        : return "SMANNABELLE";
        case UNIT_TYPEID::SMARCTURUSHOLOGRAM : return "SMARCTURUSHOLOGRAM";
        case UNIT_TYPEID::SMARCTURUSMENGSK   : return "SMARCTURUSMENGSK";
        case UNIT_TYPEID::SMARMORYBANSHEE    : return "SMARMORYBANSHEE";
        case UNIT_TYPEID::SMARMORYBANSHEEPHCRATE :
            return "SMARMORYBANSHEEPHCRATE";
        case UNIT_TYPEID::SMARMORYDROPSHIP : return "SMARMORYDROPSHIP";
        case UNIT_TYPEID::SMARMORYDROPSHIPPHCRATE :
            return "SMARMORYDROPSHIPPHCRATE";
        case UNIT_TYPEID::SMARMORYGHOSTCRATE : return "SMARMORYGHOSTCRATE";
        case UNIT_TYPEID::SMARMORYGHOSTCRATEPHCRATE :
            return "SMARMORYGHOSTCRATEPHCRATE";
        case UNIT_TYPEID::SMARMORYRIFLE        : return "SMARMORYRIFLE";
        case UNIT_TYPEID::SMARMORYSPECTRECRATE : return "SMARMORYSPECTRECRATE";
        case UNIT_TYPEID::SMARMORYSPECTRECRATEPHCRATE :
            return "SMARMORYSPECTRECRATEPHCRATE";
        case UNIT_TYPEID::SMARMORYSPIDERMINE : return "SMARMORYSPIDERMINE";
        case UNIT_TYPEID::SMARMORYSPIDERMINEPHCRATE :
            return "SMARMORYSPIDERMINEPHCRATE";
        case UNIT_TYPEID::SMARMORYTANK        : return "SMARMORYTANK";
        case UNIT_TYPEID::SMARMORYTANKPHCRATE : return "SMARMORYTANKPHCRATE";
        case UNIT_TYPEID::SMARMORYVIKING      : return "SMARMORYVIKING";
        case UNIT_TYPEID::SMARMORYVIKINGPHCRATE :
            return "SMARMORYVIKINGPHCRATE";
        case UNIT_TYPEID::SMBANSHEE           : return "SMBANSHEE";
        case UNIT_TYPEID::SMBOUNTYHUNTER      : return "SMBOUNTYHUNTER";
        case UNIT_TYPEID::SMBRALIK            : return "SMBRALIK";
        case UNIT_TYPEID::SMBRIDGEPLANETAGRIA : return "SMBRIDGEPLANETAGRIA";
        case UNIT_TYPEID::SMBRIDGEPLANETAIUR  : return "SMBRIDGEPLANETAIUR";
        case UNIT_TYPEID::SMBRIDGEPLANETAVERNUS :
            return "SMBRIDGEPLANETAVERNUS";
        case UNIT_TYPEID::SMBRIDGEPLANETBELSHIR :
            return "SMBRIDGEPLANETBELSHIR";
        case UNIT_TYPEID::SMBRIDGEPLANETCASTANAR :
            return "SMBRIDGEPLANETCASTANAR";
        case UNIT_TYPEID::SMBRIDGEPLANETCHAR   : return "SMBRIDGEPLANETCHAR";
        case UNIT_TYPEID::SMBRIDGEPLANETHAVEN  : return "SMBRIDGEPLANETHAVEN";
        case UNIT_TYPEID::SMBRIDGEPLANETKORHAL : return "SMBRIDGEPLANETKORHAL";
        case UNIT_TYPEID::SMBRIDGEPLANETMEINHOFF :
            return "SMBRIDGEPLANETMEINHOFF";
        case UNIT_TYPEID::SMBRIDGEPLANETMONLYTH :
            return "SMBRIDGEPLANETMONLYTH";
        case UNIT_TYPEID::SMBRIDGEPLANETNEWFOLSOM :
            return "SMBRIDGEPLANETNEWFOLSOM";
        case UNIT_TYPEID::SMBRIDGEPLANETPORTZION :
            return "SMBRIDGEPLANETPORTZION";
        case UNIT_TYPEID::SMBRIDGEPLANETREDSTONE :
            return "SMBRIDGEPLANETREDSTONE";
        case UNIT_TYPEID::SMBRIDGEPLANETSHAKURAS :
            return "SMBRIDGEPLANETSHAKURAS";
        case UNIT_TYPEID::SMBRIDGEPLANETSPACE : return "SMBRIDGEPLANETSPACE";
        case UNIT_TYPEID::SMBRIDGEPLANETSPACEASTEROIDS :
            return "SMBRIDGEPLANETSPACEASTEROIDS";
        case UNIT_TYPEID::SMBRIDGEPLANETTARSONIS :
            return "SMBRIDGEPLANETTARSONIS";
        case UNIT_TYPEID::SMBRIDGEPLANETTYPHON : return "SMBRIDGEPLANETTYPHON";
        case UNIT_TYPEID::SMBRIDGEPLANETTYRADOR :
            return "SMBRIDGEPLANETTYRADOR";
        case UNIT_TYPEID::SMBRIDGEPLANETULAAN : return "SMBRIDGEPLANETULAAN";
        case UNIT_TYPEID::SMBRIDGEPLANETULNAR : return "SMBRIDGEPLANETULNAR";
        case UNIT_TYPEID::SMBRIDGEPLANETVALHALLA :
            return "SMBRIDGEPLANETVALHALLA";
        case UNIT_TYPEID::SMBRIDGEPLANETXIL : return "SMBRIDGEPLANETXIL";
        case UNIT_TYPEID::SMBRIDGEPLANETZHAKULDAS :
            return "SMBRIDGEPLANETZHAKULDAS";
        case UNIT_TYPEID::SMBRIDGEWINDOWSPACE : return "SMBRIDGEWINDOWSPACE";
        case UNIT_TYPEID::SMCADE              : return "SMCADE";
        case UNIT_TYPEID::SMCAMERABRIDGE      : return "SMCAMERABRIDGE";
        case UNIT_TYPEID::SMCAMERATERRAN01    : return "SMCAMERATERRAN01";
        case UNIT_TYPEID::SMCAMERATERRAN02A   : return "SMCAMERATERRAN02A";
        case UNIT_TYPEID::SMCAMERATERRAN02B   : return "SMCAMERATERRAN02B";
        case UNIT_TYPEID::SMCAMERATERRAN03    : return "SMCAMERATERRAN03";
        case UNIT_TYPEID::SMCAMERATERRAN04    : return "SMCAMERATERRAN04";
        case UNIT_TYPEID::SMCAMERATERRAN04A   : return "SMCAMERATERRAN04A";
        case UNIT_TYPEID::SMCAMERATERRAN04B   : return "SMCAMERATERRAN04B";
        case UNIT_TYPEID::SMCAMERATERRAN05    : return "SMCAMERATERRAN05";
        case UNIT_TYPEID::SMCAMERATERRAN06A   : return "SMCAMERATERRAN06A";
        case UNIT_TYPEID::SMCAMERATERRAN06B   : return "SMCAMERATERRAN06B";
        case UNIT_TYPEID::SMCAMERATERRAN06C   : return "SMCAMERATERRAN06C";
        case UNIT_TYPEID::SMCAMERATERRAN07    : return "SMCAMERATERRAN07";
        case UNIT_TYPEID::SMCAMERATERRAN08    : return "SMCAMERATERRAN08";
        case UNIT_TYPEID::SMCAMERATERRAN09    : return "SMCAMERATERRAN09";
        case UNIT_TYPEID::SMCAMERATERRAN10    : return "SMCAMERATERRAN10";
        case UNIT_TYPEID::SMCAMERATERRAN11    : return "SMCAMERATERRAN11";
        case UNIT_TYPEID::SMCAMERATERRAN12    : return "SMCAMERATERRAN12";
        case UNIT_TYPEID::SMCAMERATERRAN13    : return "SMCAMERATERRAN13";
        case UNIT_TYPEID::SMCAMERATERRAN14    : return "SMCAMERATERRAN14";
        case UNIT_TYPEID::SMCAMERATERRAN15    : return "SMCAMERATERRAN15";
        case UNIT_TYPEID::SMCAMERATERRAN16    : return "SMCAMERATERRAN16";
        case UNIT_TYPEID::SMCAMERATERRAN17    : return "SMCAMERATERRAN17";
        case UNIT_TYPEID::SMCAMERATERRAN20    : return "SMCAMERATERRAN20";
        case UNIT_TYPEID::SMCHARBATTLEFIELDENDPROPS :
            return "SMCHARBATTLEFIELDENDPROPS";
        case UNIT_TYPEID::SMCHARBATTLEZONEARTIFACTHS :
            return "SMCHARBATTLEZONEARTIFACTHS";
        case UNIT_TYPEID::SMCHARBATTLEZONEBRIEFCASEHS :
            return "SMCHARBATTLEZONEBRIEFCASEHS";
        case UNIT_TYPEID::SMCHARBATTLEZONEBRIEFINGSET :
            return "SMCHARBATTLEZONEBRIEFINGSET";
        case UNIT_TYPEID::SMCHARBATTLEZONEBRIEFINGSET2 :
            return "SMCHARBATTLEZONEBRIEFINGSET2";
        case UNIT_TYPEID::SMCHARBATTLEZONEBRIEFINGSETLEFT :
            return "SMCHARBATTLEZONEBRIEFINGSETLEFT";
        case UNIT_TYPEID::SMCHARBATTLEZONEBRIEFINGSETRIGHT :
            return "SMCHARBATTLEZONEBRIEFINGSETRIGHT";
        case UNIT_TYPEID::SMCHARBATTLEZONEDROPSHIPHS :
            return "SMCHARBATTLEZONEDROPSHIPHS";
        case UNIT_TYPEID::SMCHARBATTLEZONEFLAG : return "SMCHARBATTLEZONEFLAG";
        case UNIT_TYPEID::SMCHARBATTLEZONERADIOHS :
            return "SMCHARBATTLEZONERADIOHS";
        case UNIT_TYPEID::SMCHARBATTLEZONESET  : return "SMCHARBATTLEZONESET";
        case UNIT_TYPEID::SMCHARBATTLEZONESET2 : return "SMCHARBATTLEZONESET2";
        case UNIT_TYPEID::SMCHARBATTLEZONESET3 : return "SMCHARBATTLEZONESET3";
        case UNIT_TYPEID::SMCHARBATTLEZONESET4 : return "SMCHARBATTLEZONESET4";
        case UNIT_TYPEID::SMCHARBATTLEZONESET5 : return "SMCHARBATTLEZONESET5";
        case UNIT_TYPEID::SMCHARBATTLEZONESHADOWBOX :
            return "SMCHARBATTLEZONESHADOWBOX";
        case UNIT_TYPEID::SMCHARBATTLEZONETURRET :
            return "SMCHARBATTLEZONETURRET";
        case UNIT_TYPEID::SMCHARCUTSCENES00 : return "SMCHARCUTSCENES00";
        case UNIT_TYPEID::SMCHARCUTSCENES01 : return "SMCHARCUTSCENES01";
        case UNIT_TYPEID::SMCHARCUTSCENES02 : return "SMCHARCUTSCENES02";
        case UNIT_TYPEID::SMCHARCUTSCENES03 : return "SMCHARCUTSCENES03";
        case UNIT_TYPEID::SMCHARGATLINGGUN  : return "SMCHARGATLINGGUN";
        case UNIT_TYPEID::SMCHARINTERACTIVE02SKYPARALLAX :
            return "SMCHARINTERACTIVE02SKYPARALLAX";
        case UNIT_TYPEID::SMCHARINTERACTIVESKYPARALLAX :
            return "SMCHARINTERACTIVESKYPARALLAX";
        case UNIT_TYPEID::SMCIVILIAN        : return "SMCIVILIAN";
        case UNIT_TYPEID::SMCOOPER          : return "SMCOOPER";
        case UNIT_TYPEID::SMDONNYVERMILLION : return "SMDONNYVERMILLION";
        case UNIT_TYPEID::SMDONNYVERMILLIONDEATH :
            return "SMDONNYVERMILLIONDEATH";
        case UNIT_TYPEID::SMDONNYVERMILLIONSET : return "SMDONNYVERMILLIONSET";
        case UNIT_TYPEID::SMDROPSHIP           : return "SMDROPSHIP";
        case UNIT_TYPEID::SMDROPSHIPBLUE       : return "SMDROPSHIPBLUE";
        case UNIT_TYPEID::SMEARL               : return "SMEARL";
        case UNIT_TYPEID::SMFIREBAT            : return "SMFIREBAT";
        case UNIT_TYPEID::SMFIREBATPHCRATE     : return "SMFIREBATPHCRATE";
        case UNIT_TYPEID::SMFIRSTOFFICER       : return "SMFIRSTOFFICER";
        case UNIT_TYPEID::SMFLY                : return "SMFLY";
        case UNIT_TYPEID::SMGENERICMALEGREASEMONKEY01 :
            return "SMGENERICMALEGREASEMONKEY01";
        case UNIT_TYPEID::SMGENERICMALEGREASEMONKEY02 :
            return "SMGENERICMALEGREASEMONKEY02";
        case UNIT_TYPEID::SMGENERICMALEOFFICER01 :
            return "SMGENERICMALEOFFICER01";
        case UNIT_TYPEID::SMGENERICMALEOFFICER02 :
            return "SMGENERICMALEOFFICER02";
        case UNIT_TYPEID::SMHALL            : return "SMHALL";
        case UNIT_TYPEID::SMHAVENPLANET     : return "SMHAVENPLANET";
        case UNIT_TYPEID::SMHILL            : return "SMHILL";
        case UNIT_TYPEID::SMHYDRALISK       : return "SMHYDRALISK";
        case UNIT_TYPEID::SMHYDRALISKDEAD   : return "SMHYDRALISKDEAD";
        case UNIT_TYPEID::SMHYPERIONARMORER : return "SMHYPERIONARMORER";
        case UNIT_TYPEID::SMHYPERIONARMORYSPACELIGHTING :
            return "SMHYPERIONARMORYSPACELIGHTING";
        case UNIT_TYPEID::SMHYPERIONARMORYSTAGE1SET :
            return "SMHYPERIONARMORYSTAGE1SET";
        case UNIT_TYPEID::SMHYPERIONARMORYSTAGE1SET01 :
            return "SMHYPERIONARMORYSTAGE1SET01";
        case UNIT_TYPEID::SMHYPERIONARMORYSTAGE1SET02 :
            return "SMHYPERIONARMORYSTAGE1SET02";
        case UNIT_TYPEID::SMHYPERIONARMORYSTAGE1SET03 :
            return "SMHYPERIONARMORYSTAGE1SET03";
        case UNIT_TYPEID::SMHYPERIONARMORYSTAGE1SWANNCAMERAS :
            return "SMHYPERIONARMORYSTAGE1SWANNCAMERAS";
        case UNIT_TYPEID::SMHYPERIONARMORYSTAGE1TECHNOLOGYCONSOLEHS :
            return "SMHYPERIONARMORYSTAGE1TECHNOLOGYCONSOLEHS";
        case UNIT_TYPEID::SMHYPERIONARMORYVIKING :
            return "SMHYPERIONARMORYVIKING";
        case UNIT_TYPEID::SMHYPERIONBRIDGEBRIEFING :
            return "SMHYPERIONBRIDGEBRIEFING";
        case UNIT_TYPEID::SMHYPERIONBRIDGEBRIEFINGCENTER :
            return "SMHYPERIONBRIDGEBRIEFINGCENTER";
        case UNIT_TYPEID::SMHYPERIONBRIDGEBRIEFINGLEFT :
            return "SMHYPERIONBRIDGEBRIEFINGLEFT";
        case UNIT_TYPEID::SMHYPERIONBRIDGEBRIEFINGRIGHT :
            return "SMHYPERIONBRIDGEBRIEFINGRIGHT";
        case UNIT_TYPEID::SMHYPERIONBRIDGEHOLOMAP :
            return "SMHYPERIONBRIDGEHOLOMAP";
        case UNIT_TYPEID::SMHYPERIONBRIDGEPROPS :
            return "SMHYPERIONBRIDGEPROPS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1BATTLECOMMANDHS :
            return "SMHYPERIONBRIDGESTAGE1BATTLECOMMANDHS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1BATTLEREPORTSHS :
            return "SMHYPERIONBRIDGESTAGE1BATTLEREPORTSHS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1BOW :
            return "SMHYPERIONBRIDGESTAGE1BOW";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1CANTINAHS :
            return "SMHYPERIONBRIDGESTAGE1CANTINAHS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1CENTERCONSOLEHS :
            return "SMHYPERIONBRIDGESTAGE1CENTERCONSOLEHS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1HANSONCAMERAS :
            return "SMHYPERIONBRIDGESTAGE1HANSONCAMERAS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1HORNERCAMERAS :
            return "SMHYPERIONBRIDGESTAGE1HORNERCAMERAS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1SET :
            return "SMHYPERIONBRIDGESTAGE1SET";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1SET2 :
            return "SMHYPERIONBRIDGESTAGE1SET2";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1SET3 :
            return "SMHYPERIONBRIDGESTAGE1SET3";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1TOSHCAMERAS :
            return "SMHYPERIONBRIDGESTAGE1TOSHCAMERAS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1TYCHUSCAMERAS :
            return "SMHYPERIONBRIDGESTAGE1TYCHUSCAMERAS";
        case UNIT_TYPEID::SMHYPERIONBRIDGESTAGE1WINDOWHS :
            return "SMHYPERIONBRIDGESTAGE1WINDOWHS";
        case UNIT_TYPEID::SMHYPERIONBRIDGETRAYNOR03BRIEFINGCAMERA :
            return "SMHYPERIONBRIDGETRAYNOR03BRIEFINGCAMERA";
        case UNIT_TYPEID::SMHYPERIONCANTINABADGEHS :
            return "SMHYPERIONCANTINABADGEHS";
        case UNIT_TYPEID::SMHYPERIONCANTINAHYDRACLAWSHS :
            return "SMHYPERIONCANTINAHYDRACLAWSHS";
        case UNIT_TYPEID::SMHYPERIONCANTINAMERCCOMPUTERHS :
            return "SMHYPERIONCANTINAMERCCOMPUTERHS";
        case UNIT_TYPEID::SMHYPERIONCANTINAPOSTER1HS :
            return "SMHYPERIONCANTINAPOSTER1HS";
        case UNIT_TYPEID::SMHYPERIONCANTINAPOSTER2HS :
            return "SMHYPERIONCANTINAPOSTER2HS";
        case UNIT_TYPEID::SMHYPERIONCANTINAPOSTER3HS :
            return "SMHYPERIONCANTINAPOSTER3HS";
        case UNIT_TYPEID::SMHYPERIONCANTINAPOSTER4HS :
            return "SMHYPERIONCANTINAPOSTER4HS";
        case UNIT_TYPEID::SMHYPERIONCANTINAPOSTER5HS :
            return "SMHYPERIONCANTINAPOSTER5HS";
        case UNIT_TYPEID::SMHYPERIONCANTINAPROGRESSFRAME :
            return "SMHYPERIONCANTINAPROGRESSFRAME";
        case UNIT_TYPEID::SMHYPERIONCANTINAPROPS :
            return "SMHYPERIONCANTINAPROPS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1ARCADEGAMEHS :
            return "SMHYPERIONCANTINASTAGE1ARCADEGAMEHS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1CORKBOARDHS :
            return "SMHYPERIONCANTINASTAGE1CORKBOARDHS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1EXITHS :
            return "SMHYPERIONCANTINASTAGE1EXITHS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1JUKEBOXHS :
            return "SMHYPERIONCANTINASTAGE1JUKEBOXHS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1PROGRESS1HS :
            return "SMHYPERIONCANTINASTAGE1PROGRESS1HS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1PROGRESS2HS :
            return "SMHYPERIONCANTINASTAGE1PROGRESS2HS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1PROGRESS3HS :
            return "SMHYPERIONCANTINASTAGE1PROGRESS3HS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1PROGRESS4HS :
            return "SMHYPERIONCANTINASTAGE1PROGRESS4HS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1PROGRESS5HS :
            return "SMHYPERIONCANTINASTAGE1PROGRESS5HS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1PROGRESS6HS :
            return "SMHYPERIONCANTINASTAGE1PROGRESS6HS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1SET :
            return "SMHYPERIONCANTINASTAGE1SET";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1SET2 :
            return "SMHYPERIONCANTINASTAGE1SET2";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1STAIRCASEHS :
            return "SMHYPERIONCANTINASTAGE1STAIRCASEHS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1TVHS :
            return "SMHYPERIONCANTINASTAGE1TVHS";
        case UNIT_TYPEID::SMHYPERIONCANTINASTAGE1WALLPIECE :
            return "SMHYPERIONCANTINASTAGE1WALLPIECE";
        case UNIT_TYPEID::SMHYPERIONCANTINATOSHCAMERAS :
            return "SMHYPERIONCANTINATOSHCAMERAS";
        case UNIT_TYPEID::SMHYPERIONCANTINATYCHUSCAMERAS :
            return "SMHYPERIONCANTINATYCHUSCAMERAS";
        case UNIT_TYPEID::SMHYPERIONCANTINAYBARRACAMERAS :
            return "SMHYPERIONCANTINAYBARRACAMERAS";
        case UNIT_TYPEID::SMHYPERIONCORRIDORPROPS :
            return "SMHYPERIONCORRIDORPROPS";
        case UNIT_TYPEID::SMHYPERIONCORRIDORSET :
            return "SMHYPERIONCORRIDORSET";
        case UNIT_TYPEID::SMHYPERIONEXTERIOR : return "SMHYPERIONEXTERIOR";
        case UNIT_TYPEID::SMHYPERIONEXTERIORHOLOGRAM :
            return "SMHYPERIONEXTERIORHOLOGRAM";
        case UNIT_TYPEID::SMHYPERIONEXTERIORLOW :
            return "SMHYPERIONEXTERIORLOW";
        case UNIT_TYPEID::SMHYPERIONLABADJUTANTCAMERAS :
            return "SMHYPERIONLABADJUTANTCAMERAS";
        case UNIT_TYPEID::SMHYPERIONLABARTIFACTBASEHS :
            return "SMHYPERIONLABARTIFACTBASEHS";
        case UNIT_TYPEID::SMHYPERIONLABARTIFACTPART1HS :
            return "SMHYPERIONLABARTIFACTPART1HS";
        case UNIT_TYPEID::SMHYPERIONLABARTIFACTPART2HS :
            return "SMHYPERIONLABARTIFACTPART2HS";
        case UNIT_TYPEID::SMHYPERIONLABARTIFACTPART3HS :
            return "SMHYPERIONLABARTIFACTPART3HS";
        case UNIT_TYPEID::SMHYPERIONLABARTIFACTPART4HS :
            return "SMHYPERIONLABARTIFACTPART4HS";
        case UNIT_TYPEID::SMHYPERIONLABCOWINCAMERAS :
            return "SMHYPERIONLABCOWINCAMERAS";
        case UNIT_TYPEID::SMHYPERIONLABHANSONCAMERAS :
            return "SMHYPERIONLABHANSONCAMERAS";
        case UNIT_TYPEID::SMHYPERIONMEDLABBRIEFING :
            return "SMHYPERIONMEDLABBRIEFING";
        case UNIT_TYPEID::SMHYPERIONMEDLABBRIEFINGCENTER :
            return "SMHYPERIONMEDLABBRIEFINGCENTER";
        case UNIT_TYPEID::SMHYPERIONMEDLABBRIEFINGLEFT :
            return "SMHYPERIONMEDLABBRIEFINGLEFT";
        case UNIT_TYPEID::SMHYPERIONMEDLABBRIEFINGRIGHT :
            return "SMHYPERIONMEDLABBRIEFINGRIGHT";
        case UNIT_TYPEID::SMHYPERIONMEDLABCRYOTUBEA :
            return "SMHYPERIONMEDLABCRYOTUBEA";
        case UNIT_TYPEID::SMHYPERIONMEDLABCRYOTUBEB :
            return "SMHYPERIONMEDLABCRYOTUBEB";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROPS :
            return "SMHYPERIONMEDLABPROPS";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROTOSSCRYOTUBE0HS :
            return "SMHYPERIONMEDLABPROTOSSCRYOTUBE0HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROTOSSCRYOTUBE1HS :
            return "SMHYPERIONMEDLABPROTOSSCRYOTUBE1HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROTOSSCRYOTUBE2HS :
            return "SMHYPERIONMEDLABPROTOSSCRYOTUBE2HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROTOSSCRYOTUBE3HS :
            return "SMHYPERIONMEDLABPROTOSSCRYOTUBE3HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROTOSSCRYOTUBE4HS :
            return "SMHYPERIONMEDLABPROTOSSCRYOTUBE4HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABPROTOSSCRYOTUBE5HS :
            return "SMHYPERIONMEDLABPROTOSSCRYOTUBE5HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1ARTIFACTHS :
            return "SMHYPERIONMEDLABSTAGE1ARTIFACTHS";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1CONSOLEHS :
            return "SMHYPERIONMEDLABSTAGE1CONSOLEHS";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1CRYSTALHS :
            return "SMHYPERIONMEDLABSTAGE1CRYSTALHS";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1DOORHS :
            return "SMHYPERIONMEDLABSTAGE1DOORHS";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1SET :
            return "SMHYPERIONMEDLABSTAGE1SET";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1SET2 :
            return "SMHYPERIONMEDLABSTAGE1SET2";
        case UNIT_TYPEID::SMHYPERIONMEDLABSTAGE1SETLIGHTS :
            return "SMHYPERIONMEDLABSTAGE1SETLIGHTS";
        case UNIT_TYPEID::SMHYPERIONMEDLABZERGCRYOTUBE0HS :
            return "SMHYPERIONMEDLABZERGCRYOTUBE0HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABZERGCRYOTUBE1HS :
            return "SMHYPERIONMEDLABZERGCRYOTUBE1HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABZERGCRYOTUBE2HS :
            return "SMHYPERIONMEDLABZERGCRYOTUBE2HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABZERGCRYOTUBE3HS :
            return "SMHYPERIONMEDLABZERGCRYOTUBE3HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABZERGCRYOTUBE4HS :
            return "SMHYPERIONMEDLABZERGCRYOTUBE4HS";
        case UNIT_TYPEID::SMHYPERIONMEDLABZERGCRYOTUBE5HS :
            return "SMHYPERIONMEDLABZERGCRYOTUBE5HS";
        case UNIT_TYPEID::SMKACHINSKY         : return "SMKACHINSKY";
        case UNIT_TYPEID::SMKATELOCKWELL      : return "SMKATELOCKWELL";
        case UNIT_TYPEID::SMKERRIGANPHOTO     : return "SMKERRIGANPHOTO";
        case UNIT_TYPEID::SMLABASSISTANT      : return "SMLABASSISTANT";
        case UNIT_TYPEID::SMLEEKENO           : return "SMLEEKENO";
        case UNIT_TYPEID::SMLEEKENOSET        : return "SMLEEKENOSET";
        case UNIT_TYPEID::SMMARAUDER          : return "SMMARAUDER";
        case UNIT_TYPEID::SMMARAUDERPHCRATE   : return "SMMARAUDERPHCRATE";
        case UNIT_TYPEID::SMMARINE01          : return "SMMARINE01";
        case UNIT_TYPEID::SMMARINE02          : return "SMMARINE02";
        case UNIT_TYPEID::SMMARINE02AOD       : return "SMMARINE02AOD";
        case UNIT_TYPEID::SMMARINE03          : return "SMMARINE03";
        case UNIT_TYPEID::SMMARINE04          : return "SMMARINE04";
        case UNIT_TYPEID::SMMARINERIFLE       : return "SMMARINERIFLE";
        case UNIT_TYPEID::SMMARSARABARBADGEHS : return "SMMARSARABARBADGEHS";
        case UNIT_TYPEID::SMMARSARABARBOTTLESHS :
            return "SMMARSARABARBOTTLESHS";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGSET :
            return "SMMARSARABARBRIEFINGSET";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGSET2 :
            return "SMMARSARABARBRIEFINGSET2";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGSETLEFT :
            return "SMMARSARABARBRIEFINGSETLEFT";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGSETRIGHT :
            return "SMMARSARABARBRIEFINGSETRIGHT";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVMAIN :
            return "SMMARSARABARBRIEFINGTVMAIN";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVMAIN2 :
            return "SMMARSARABARBRIEFINGTVMAIN2";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVMAIN3 :
            return "SMMARSARABARBRIEFINGTVMAIN3";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVPORTRAIT1 :
            return "SMMARSARABARBRIEFINGTVPORTRAIT1";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVPORTRAIT2 :
            return "SMMARSARABARBRIEFINGTVPORTRAIT2";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVPORTRAIT3 :
            return "SMMARSARABARBRIEFINGTVPORTRAIT3";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVPORTRAIT4 :
            return "SMMARSARABARBRIEFINGTVPORTRAIT4";
        case UNIT_TYPEID::SMMARSARABARBRIEFINGTVPORTRAIT5 :
            return "SMMARSARABARBRIEFINGTVPORTRAIT5";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDBACKGROUND :
            return "SMMARSARABARCORKBOARDBACKGROUND";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDHS :
            return "SMMARSARABARCORKBOARDHS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM1HS :
            return "SMMARSARABARCORKBOARDITEM1HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM2HS :
            return "SMMARSARABARCORKBOARDITEM2HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM3HS :
            return "SMMARSARABARCORKBOARDITEM3HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM4HS :
            return "SMMARSARABARCORKBOARDITEM4HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM5HS :
            return "SMMARSARABARCORKBOARDITEM5HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM6HS :
            return "SMMARSARABARCORKBOARDITEM6HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM7HS :
            return "SMMARSARABARCORKBOARDITEM7HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM8HS :
            return "SMMARSARABARCORKBOARDITEM8HS";
        case UNIT_TYPEID::SMMARSARABARCORKBOARDITEM9HS :
            return "SMMARSARABARCORKBOARDITEM9HS";
        case UNIT_TYPEID::SMMARSARABARHYDRALISKSKULLHS :
            return "SMMARSARABARHYDRALISKSKULLHS";
        case UNIT_TYPEID::SMMARSARABARJUKEBOXHS :
            return "SMMARSARABARJUKEBOXHS";
        case UNIT_TYPEID::SMMARSARABARKERRIGANPHOTOHS :
            return "SMMARSARABARKERRIGANPHOTOHS";
        case UNIT_TYPEID::SMMARSARABARPROPS : return "SMMARSARABARPROPS";
        case UNIT_TYPEID::SMMARSARABARSET   : return "SMMARSARABARSET";
        case UNIT_TYPEID::SMMARSARABARSET2  : return "SMMARSARABARSET2";
        case UNIT_TYPEID::SMMARSARABARSTARMAPHS :
            return "SMMARSARABARSTARMAPHS";
        case UNIT_TYPEID::SMMARSARABARTVHS : return "SMMARSARABARTVHS";
        case UNIT_TYPEID::SMMARSARABARTYCHUSCAMERAS :
            return "SMMARSARABARTYCHUSCAMERAS";
        case UNIT_TYPEID::SMMARSARAPLANET   : return "SMMARSARAPLANET";
        case UNIT_TYPEID::SMMIKELIBERTY     : return "SMMIKELIBERTY";
        case UNIT_TYPEID::SMMUTALISK        : return "SMMUTALISK";
        case UNIT_TYPEID::SMNOVA            : return "SMNOVA";
        case UNIT_TYPEID::SMPRESSROOMPROPS  : return "SMPRESSROOMPROPS";
        case UNIT_TYPEID::SMRAYNORCOMMANDER : return "SMRAYNORCOMMANDER";
        case UNIT_TYPEID::SMRAYNORGUN       : return "SMRAYNORGUN";
        case UNIT_TYPEID::SMRAYNORHANDS     : return "SMRAYNORHANDS";
        case UNIT_TYPEID::SMRAYNORMARINE    : return "SMRAYNORMARINE";
        case UNIT_TYPEID::SMSHADOWBOX       : return "SMSHADOWBOX";
        case UNIT_TYPEID::SMSTETMANN        : return "SMSTETMANN";
        case UNIT_TYPEID::SMTERRAN01FX      : return "SMTERRAN01FX";
        case UNIT_TYPEID::SMTERRAN03FX      : return "SMTERRAN03FX";
        case UNIT_TYPEID::SMTERRAN05FX      : return "SMTERRAN05FX";
        case UNIT_TYPEID::SMTERRAN05FXMUTALISKS :
            return "SMTERRAN05FXMUTALISKS";
        case UNIT_TYPEID::SMTERRAN05PROPS     : return "SMTERRAN05PROPS";
        case UNIT_TYPEID::SMTERRAN06AFX       : return "SMTERRAN06AFX";
        case UNIT_TYPEID::SMTERRAN06APROPS    : return "SMTERRAN06APROPS";
        case UNIT_TYPEID::SMTERRAN06BFX       : return "SMTERRAN06BFX";
        case UNIT_TYPEID::SMTERRAN06BPROPS    : return "SMTERRAN06BPROPS";
        case UNIT_TYPEID::SMTERRAN06CFX       : return "SMTERRAN06CFX";
        case UNIT_TYPEID::SMTERRAN07FX        : return "SMTERRAN07FX";
        case UNIT_TYPEID::SMTERRAN07PROPS     : return "SMTERRAN07PROPS";
        case UNIT_TYPEID::SMTERRAN08PROPS     : return "SMTERRAN08PROPS";
        case UNIT_TYPEID::SMTERRAN09FX        : return "SMTERRAN09FX";
        case UNIT_TYPEID::SMTERRAN09PROPS     : return "SMTERRAN09PROPS";
        case UNIT_TYPEID::SMTERRAN11FX        : return "SMTERRAN11FX";
        case UNIT_TYPEID::SMTERRAN11FXBLOOD   : return "SMTERRAN11FXBLOOD";
        case UNIT_TYPEID::SMTERRAN11FXDEBRIS  : return "SMTERRAN11FXDEBRIS";
        case UNIT_TYPEID::SMTERRAN11FXDEBRIS1 : return "SMTERRAN11FXDEBRIS1";
        case UNIT_TYPEID::SMTERRAN11FXDEBRIS2 : return "SMTERRAN11FXDEBRIS2";
        case UNIT_TYPEID::SMTERRAN11FXEXPLOSIONS :
            return "SMTERRAN11FXEXPLOSIONS";
        case UNIT_TYPEID::SMTERRAN11FXMISSILES : return "SMTERRAN11FXMISSILES";
        case UNIT_TYPEID::SMTERRAN11PROPS      : return "SMTERRAN11PROPS";
        case UNIT_TYPEID::SMTERRAN11PROPSBURROWROCKS :
            return "SMTERRAN11PROPSBURROWROCKS";
        case UNIT_TYPEID::SMTERRAN11PROPSRIFLESHELLS :
            return "SMTERRAN11PROPSRIFLESHELLS";
        case UNIT_TYPEID::SMTERRAN12FX     : return "SMTERRAN12FX";
        case UNIT_TYPEID::SMTERRAN12PROPS  : return "SMTERRAN12PROPS";
        case UNIT_TYPEID::SMTERRAN13PROPS  : return "SMTERRAN13PROPS";
        case UNIT_TYPEID::SMTERRAN14FX     : return "SMTERRAN14FX";
        case UNIT_TYPEID::SMTERRAN14PROPS  : return "SMTERRAN14PROPS";
        case UNIT_TYPEID::SMTERRAN15FX     : return "SMTERRAN15FX";
        case UNIT_TYPEID::SMTERRAN15PROPS  : return "SMTERRAN15PROPS";
        case UNIT_TYPEID::SMTERRAN16FX     : return "SMTERRAN16FX";
        case UNIT_TYPEID::SMTERRAN16FXFLAK : return "SMTERRAN16FXFLAK";
        case UNIT_TYPEID::SMTERRAN17FX     : return "SMTERRAN17FX";
        case UNIT_TYPEID::SMTERRAN17PROPS  : return "SMTERRAN17PROPS";
        case UNIT_TYPEID::SMTERRANREADYROOMLEFTTV :
            return "SMTERRANREADYROOMLEFTTV";
        case UNIT_TYPEID::SMTERRANREADYROOMMAINTV :
            return "SMTERRANREADYROOMMAINTV";
        case UNIT_TYPEID::SMTERRANREADYROOMRIGHTTV :
            return "SMTERRANREADYROOMRIGHTTV";
        case UNIT_TYPEID::SMTERRANREADYROOMSET : return "SMTERRANREADYROOMSET";
        case UNIT_TYPEID::SMTESTCAMERA         : return "SMTESTCAMERA";
        case UNIT_TYPEID::SMTOSHKNIFE          : return "SMTOSHKNIFE";
        case UNIT_TYPEID::SMTOSHSHUTTLEPROPS   : return "SMTOSHSHUTTLEPROPS";
        case UNIT_TYPEID::SMTOSHSHUTTLESET     : return "SMTOSHSHUTTLESET";
        case UNIT_TYPEID::SMTOSHSHUTTLESET2    : return "SMTOSHSHUTTLESET2";
        case UNIT_TYPEID::SMTVSTATIC           : return "SMTVSTATIC";
        case UNIT_TYPEID::SMUNNCAMERA          : return "SMUNNCAMERA";
        case UNIT_TYPEID::SMUNNSCREEN          : return "SMUNNSCREEN";
        case UNIT_TYPEID::SMUNNSET             : return "SMUNNSET";
        case UNIT_TYPEID::SMVALERIANFLAGSHIPCORRIDORSSET :
            return "SMVALERIANFLAGSHIPCORRIDORSSET";
        case UNIT_TYPEID::SMVALERIANFLAGSHIPCORRIDORSSET2 :
            return "SMVALERIANFLAGSHIPCORRIDORSSET2";
        case UNIT_TYPEID::SMVALERIANFLAGSHIPCORRIDORSSET3 :
            return "SMVALERIANFLAGSHIPCORRIDORSSET3";
        case UNIT_TYPEID::SMVALERIANFLAGSHIPCORRIDORSSET4 :
            return "SMVALERIANFLAGSHIPCORRIDORSSET4";
        case UNIT_TYPEID::SMVALERIANMENGSK : return "SMVALERIANMENGSK";
        case UNIT_TYPEID::SMVALERIANOBSERVATORYPAINTINGHS :
            return "SMVALERIANOBSERVATORYPAINTINGHS";
        case UNIT_TYPEID::SMVALERIANOBSERVATORYPROPS :
            return "SMVALERIANOBSERVATORYPROPS";
        case UNIT_TYPEID::SMVALERIANOBSERVATORYSET :
            return "SMVALERIANOBSERVATORYSET";
        case UNIT_TYPEID::SMVALERIANOBSERVATORYSET2 :
            return "SMVALERIANOBSERVATORYSET2";
        case UNIT_TYPEID::SMVALERIANOBSERVATORYSET3 :
            return "SMVALERIANOBSERVATORYSET3";
        case UNIT_TYPEID::SMVALERIANOBSERVATORYSTARMAP :
            return "SMVALERIANOBSERVATORYSTARMAP";
        case UNIT_TYPEID::SMVIKING           : return "SMVIKING";
        case UNIT_TYPEID::SMYBARRA           : return "SMYBARRA";
        case UNIT_TYPEID::SMZERATUL          : return "SMZERATUL";
        case UNIT_TYPEID::SMZERGEDHANSON     : return "SMZERGEDHANSON";
        case UNIT_TYPEID::SMZERGLING         : return "SMZERGLING";
        case UNIT_TYPEID::SNARE_PLACEHOLDER  : return "SNARE_PLACEHOLDER";
        case UNIT_TYPEID::SNOWGLAZESTARTERMP : return "SNOWGLAZESTARTERMP";
        case UNIT_TYPEID::SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8 :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8";
        case UNIT_TYPEID::SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT";
        case UNIT_TYPEID::SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8 :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8";
        case UNIT_TYPEID::SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT :
            return "SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT";
        case UNIT_TYPEID::SPACEDIABLO : return "SPACEDIABLO";
        case UNIT_TYPEID::SPACEPLATFORMCLIFFDOOR0 :
            return "SPACEPLATFORMCLIFFDOOR0";
        case UNIT_TYPEID::SPACEPLATFORMCLIFFDOOR1 :
            return "SPACEPLATFORMCLIFFDOOR1";
        case UNIT_TYPEID::SPACEPLATFORMCLIFFDOOROPEN0 :
            return "SPACEPLATFORMCLIFFDOOROPEN0";
        case UNIT_TYPEID::SPACEPLATFORMCLIFFDOOROPEN1 :
            return "SPACEPLATFORMCLIFFDOOROPEN1";
        case UNIT_TYPEID::SPACEPLATFORMDESTRUCTIBLEJUMBOBLOCKER :
            return "SPACEPLATFORMDESTRUCTIBLEJUMBOBLOCKER";
        case UNIT_TYPEID::SPACEPLATFORMDESTRUCTIBLELARGEBLOCKER :
            return "SPACEPLATFORMDESTRUCTIBLELARGEBLOCKER";
        case UNIT_TYPEID::SPACEPLATFORMDESTRUCTIBLEMEDIUMBLOCKER :
            return "SPACEPLATFORMDESTRUCTIBLEMEDIUMBLOCKER";
        case UNIT_TYPEID::SPACEPLATFORMDESTRUCTIBLESMALLBLOCKER :
            return "SPACEPLATFORMDESTRUCTIBLESMALLBLOCKER";
        case UNIT_TYPEID::SPACEPLATFORMREACTORPATHINGBLOCKER :
            return "SPACEPLATFORMREACTORPATHINGBLOCKER";
        case UNIT_TYPEID::SPACEPLATFORMVENTSUNIT :
            return "SPACEPLATFORMVENTSUNIT";
        case UNIT_TYPEID::SPARTANCOMPANY : return "SPARTANCOMPANY";
        case UNIT_TYPEID::SPARTANCOMPANYAWEAPON :
            return "SPARTANCOMPANYAWEAPON";
        case UNIT_TYPEID::SPECIALOPSDROPSHIP : return "SPECIALOPSDROPSHIP";
        case UNIT_TYPEID::SPECTRE            : return "SPECTRE";
        case UNIT_TYPEID::SPECTRENUKE        : return "SPECTRENUKE";
        case UNIT_TYPEID::SPIDERMINE         : return "SPIDERMINE";
        case UNIT_TYPEID::SPIDERMINEBURROWED : return "SPIDERMINEBURROWED";
        case UNIT_TYPEID::SPINECRAWLERWEAPON : return "SPINECRAWLERWEAPON";
        case UNIT_TYPEID::SPORECANNON        : return "SPORECANNON";
        case UNIT_TYPEID::SPORECANNONFIREMISSILE :
            return "SPORECANNONFIREMISSILE";
        case UNIT_TYPEID::SPORECRAWLERWEAPON   : return "SPORECRAWLERWEAPON";
        case UNIT_TYPEID::SS_BACKGROUNDSPACE00 : return "SS_BACKGROUNDSPACE00";
        case UNIT_TYPEID::SS_BACKGROUNDSPACE01 : return "SS_BACKGROUNDSPACE01";
        case UNIT_TYPEID::SS_BACKGROUNDSPACE02 : return "SS_BACKGROUNDSPACE02";
        case UNIT_TYPEID::SS_BACKGROUNDSPACELARGE :
            return "SS_BACKGROUNDSPACELARGE";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEPROT00 :
            return "SS_BACKGROUNDSPACEPROT00";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEPROT01 :
            return "SS_BACKGROUNDSPACEPROT01";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEPROT02 :
            return "SS_BACKGROUNDSPACEPROT02";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEPROT03 :
            return "SS_BACKGROUNDSPACEPROT03";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEPROT04 :
            return "SS_BACKGROUNDSPACEPROT04";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEPROTOSSLARGE :
            return "SS_BACKGROUNDSPACEPROTOSSLARGE";
        case UNIT_TYPEID::SS_BACKGROUNDSPACETERRAN00 :
            return "SS_BACKGROUNDSPACETERRAN00";
        case UNIT_TYPEID::SS_BACKGROUNDSPACETERRAN01 :
            return "SS_BACKGROUNDSPACETERRAN01";
        case UNIT_TYPEID::SS_BACKGROUNDSPACETERRAN02 :
            return "SS_BACKGROUNDSPACETERRAN02";
        case UNIT_TYPEID::SS_BACKGROUNDSPACETERRANLARGE :
            return "SS_BACKGROUNDSPACETERRANLARGE";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEZERG00 :
            return "SS_BACKGROUNDSPACEZERG00";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEZERG01 :
            return "SS_BACKGROUNDSPACEZERG01";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEZERG02 :
            return "SS_BACKGROUNDSPACEZERG02";
        case UNIT_TYPEID::SS_BACKGROUNDSPACEZERGLARGE :
            return "SS_BACKGROUNDSPACEZERGLARGE";
        case UNIT_TYPEID::SS_BACKGROUNDZERG01 : return "SS_BACKGROUNDZERG01";
        case UNIT_TYPEID::SS_BATTLECRUISER    : return "SS_BATTLECRUISER";
        case UNIT_TYPEID::SS_BATTLECRUISERHUNTERSEEKERMISSILE :
            return "SS_BATTLECRUISERHUNTERSEEKERMISSILE";
        case UNIT_TYPEID::SS_BATTLECRUISERMISSILE :
            return "SS_BATTLECRUISERMISSILE";
        case UNIT_TYPEID::SS_BATTLECRUISERMISSILELAUNCHER :
            return "SS_BATTLECRUISERMISSILELAUNCHER";
        case UNIT_TYPEID::SS_BLACKEDGEBORDER : return "SS_BLACKEDGEBORDER";
        case UNIT_TYPEID::SS_CARRIER         : return "SS_CARRIER";
        case UNIT_TYPEID::SS_CARRIERBOSS     : return "SS_CARRIERBOSS";
        case UNIT_TYPEID::SS_CARRIERBOSSMISSILE :
            return "SS_CARRIERBOSSMISSILE";
        case UNIT_TYPEID::SS_CORRUPTOR        : return "SS_CORRUPTOR";
        case UNIT_TYPEID::SS_CORRUPTORMISSILE : return "SS_CORRUPTORMISSILE";
        case UNIT_TYPEID::SS_FIGHTER          : return "SS_FIGHTER";
        case UNIT_TYPEID::SS_FIGHTERDRONEMISSILE :
            return "SS_FIGHTERDRONEMISSILE";
        case UNIT_TYPEID::SS_FIGHTERMISSILELEFT :
            return "SS_FIGHTERMISSILELEFT";
        case UNIT_TYPEID::SS_FIGHTERMISSILERIGHT :
            return "SS_FIGHTERMISSILERIGHT";
        case UNIT_TYPEID::SS_INTERCEPTOR : return "SS_INTERCEPTOR";
        case UNIT_TYPEID::SS_INTERCEPTORMISSILE :
            return "SS_INTERCEPTORMISSILE";
        case UNIT_TYPEID::SS_INTERCEPTORSPAWNMISSILE :
            return "SS_INTERCEPTORSPAWNMISSILE";
        case UNIT_TYPEID::SS_LEVIATHAN     : return "SS_LEVIATHAN";
        case UNIT_TYPEID::SS_LEVIATHANBOMB : return "SS_LEVIATHANBOMB";
        case UNIT_TYPEID::SS_LEVIATHANBOMBMISSILE :
            return "SS_LEVIATHANBOMBMISSILE";
        case UNIT_TYPEID::SS_LEVIATHANSPAWNBOMBMISSILE :
            return "SS_LEVIATHANSPAWNBOMBMISSILE";
        case UNIT_TYPEID::SS_LEVIATHANTENTACLEL1MISSILE :
            return "SS_LEVIATHANTENTACLEL1MISSILE";
        case UNIT_TYPEID::SS_LEVIATHANTENTACLEL2MISSILE :
            return "SS_LEVIATHANTENTACLEL2MISSILE";
        case UNIT_TYPEID::SS_LEVIATHANTENTACLER1MISSILE :
            return "SS_LEVIATHANTENTACLER1MISSILE";
        case UNIT_TYPEID::SS_LEVIATHANTENTACLER2MISSILE :
            return "SS_LEVIATHANTENTACLER2MISSILE";
        case UNIT_TYPEID::SS_LEVIATHANTENTACLETARGET :
            return "SS_LEVIATHANTENTACLETARGET";
        case UNIT_TYPEID::SS_LIGHTNINGPROJECTORFACELEFT :
            return "SS_LIGHTNINGPROJECTORFACELEFT";
        case UNIT_TYPEID::SS_LIGHTNINGPROJECTORFACERIGHT :
            return "SS_LIGHTNINGPROJECTORFACERIGHT";
        case UNIT_TYPEID::SS_PHOENIX        : return "SS_PHOENIX";
        case UNIT_TYPEID::SS_PHOENIXMISSILE : return "SS_PHOENIXMISSILE";
        case UNIT_TYPEID::SS_POWERUPBOMB    : return "SS_POWERUPBOMB";
        case UNIT_TYPEID::SS_POWERUPHEALTH  : return "SS_POWERUPHEALTH";
        case UNIT_TYPEID::SS_POWERUPSIDEMISSILES :
            return "SS_POWERUPSIDEMISSILES";
        case UNIT_TYPEID::SS_POWERUPSTRONGERMISSILES :
            return "SS_POWERUPSTRONGERMISSILES";
        case UNIT_TYPEID::SS_SCIENCEVESSEL : return "SS_SCIENCEVESSEL";
        case UNIT_TYPEID::SS_SCIENCEVESSELMISSILE :
            return "SS_SCIENCEVESSELMISSILE";
        case UNIT_TYPEID::SS_SCOURGE        : return "SS_SCOURGE";
        case UNIT_TYPEID::SS_SCOURGEMISSILE : return "SS_SCOURGEMISSILE";
        case UNIT_TYPEID::SS_SCOUT          : return "SS_SCOUT";
        case UNIT_TYPEID::SS_SCOUTMISSILE   : return "SS_SCOUTMISSILE";
        case UNIT_TYPEID::SS_STRONGMISSILE1 : return "SS_STRONGMISSILE1";
        case UNIT_TYPEID::SS_STRONGMISSILE2 : return "SS_STRONGMISSILE2";
        case UNIT_TYPEID::SS_SWARMGUARDIAN  : return "SS_SWARMGUARDIAN";
        case UNIT_TYPEID::SS_SWARMGUARDIANMISSILE :
            return "SS_SWARMGUARDIANMISSILE";
        case UNIT_TYPEID::SS_TERRATRON : return "SS_TERRATRON";
        case UNIT_TYPEID::SS_TERRATRONBEAMTARGET :
            return "SS_TERRATRONBEAMTARGET";
        case UNIT_TYPEID::SS_TERRATRONMISSILE : return "SS_TERRATRONMISSILE";
        case UNIT_TYPEID::SS_TERRATRONMISSILELAUNCHER :
            return "SS_TERRATRONMISSILELAUNCHER";
        case UNIT_TYPEID::SS_TERRATRONMISSILESPINNER :
            return "SS_TERRATRONMISSILESPINNER";
        case UNIT_TYPEID::SS_TERRATRONMISSILESPINNERLAUNCHER :
            return "SS_TERRATRONMISSILESPINNERLAUNCHER";
        case UNIT_TYPEID::SS_TERRATRONMISSILESPINNERMISSILE :
            return "SS_TERRATRONMISSILESPINNERMISSILE";
        case UNIT_TYPEID::SS_TERRATRONSAW     : return "SS_TERRATRONSAW";
        case UNIT_TYPEID::SS_WRAITH           : return "SS_WRAITH";
        case UNIT_TYPEID::SS_WRAITHMISSILE    : return "SS_WRAITHMISSILE";
        case UNIT_TYPEID::STALKERWEAPON       : return "STALKERWEAPON";
        case UNIT_TYPEID::STARPORTTECHREACTOR : return "STARPORTTECHREACTOR";
        case UNIT_TYPEID::STEREOSCOPICOPTIONSUNIT :
            return "STEREOSCOPICOPTIONSUNIT";
        case UNIT_TYPEID::STETMANN           : return "STETMANN";
        case UNIT_TYPEID::STONEZEALOT        : return "STONEZEALOT";
        case UNIT_TYPEID::SUPERWARPGATE      : return "SUPERWARPGATE";
        case UNIT_TYPEID::SUPPLYDEPOTDROP    : return "SUPPLYDEPOTDROP";
        case UNIT_TYPEID::SWANN              : return "SWANN";
        case UNIT_TYPEID::SWANNWEAPON        : return "SWANNWEAPON";
        case UNIT_TYPEID::SWARMLING          : return "SWARMLING";
        case UNIT_TYPEID::TALDARIMMOTHERSHIP : return "TALDARIMMOTHERSHIP";
        case UNIT_TYPEID::TALDARIMPRISON     : return "TALDARIMPRISON";
        case UNIT_TYPEID::TALDARIMPRISONCRYSTAL :
            return "TALDARIMPRISONCRYSTAL";
        case UNIT_TYPEID::TALONSMISSILEWEAPON : return "TALONSMISSILEWEAPON";
        case UNIT_TYPEID::TANKERTRUCK         : return "TANKERTRUCK";
        case UNIT_TYPEID::TARSONISENGINE      : return "TARSONISENGINE";
        case UNIT_TYPEID::TARSONISENGINEFAST  : return "TARSONISENGINEFAST";
        case UNIT_TYPEID::TARSONIS_DOORE      : return "TARSONIS_DOORE";
        case UNIT_TYPEID::TARSONIS_DOORELOWERED :
            return "TARSONIS_DOORELOWERED";
        case UNIT_TYPEID::TARSONIS_DOORN  : return "TARSONIS_DOORN";
        case UNIT_TYPEID::TARSONIS_DOORNE : return "TARSONIS_DOORNE";
        case UNIT_TYPEID::TARSONIS_DOORNELOWERED :
            return "TARSONIS_DOORNELOWERED";
        case UNIT_TYPEID::TARSONIS_DOORNLOWERED :
            return "TARSONIS_DOORNLOWERED";
        case UNIT_TYPEID::TARSONIS_DOORNW : return "TARSONIS_DOORNW";
        case UNIT_TYPEID::TARSONIS_DOORNWLOWERED :
            return "TARSONIS_DOORNWLOWERED";
        case UNIT_TYPEID::TASSADAR            : return "TASSADAR";
        case UNIT_TYPEID::TAURENOUTHOUSE      : return "TAURENOUTHOUSE";
        case UNIT_TYPEID::TAURENSPACEMARINE   : return "TAURENSPACEMARINE";
        case UNIT_TYPEID::TECHREACTOR         : return "TECHREACTOR";
        case UNIT_TYPEID::TEMPESTWEAPON       : return "TEMPESTWEAPON";
        case UNIT_TYPEID::TEMPESTWEAPONGROUND : return "TEMPESTWEAPONGROUND";
        case UNIT_TYPEID::TENTACLEAMISSILE    : return "TENTACLEAMISSILE";
        case UNIT_TYPEID::TENTACLEBMISSILE    : return "TENTACLEBMISSILE";
        case UNIT_TYPEID::TENTACLECMISSILE    : return "TENTACLECMISSILE";
        case UNIT_TYPEID::TENTACLEDMISSILE    : return "TENTACLEDMISSILE";
        case UNIT_TYPEID::TERRANBUGGY         : return "TERRANBUGGY";
        case UNIT_TYPEID::TERRANDROPPOD       : return "TERRANDROPPOD";
        case UNIT_TYPEID::TERRAN_ARMORY       : return "TERRAN_ARMORY";
        case UNIT_TYPEID::TERRAN_AUTOTURRET   : return "TERRAN_AUTOTURRET";
        case UNIT_TYPEID::TERRAN_BANSHEE      : return "TERRAN_BANSHEE";
        case UNIT_TYPEID::TERRAN_BARRACKS     : return "TERRAN_BARRACKS";
        case UNIT_TYPEID::TERRAN_BARRACKSFLYING :
            return "TERRAN_BARRACKSFLYING";
        case UNIT_TYPEID::TERRAN_BARRACKSREACTOR :
            return "TERRAN_BARRACKSREACTOR";
        case UNIT_TYPEID::TERRAN_BARRACKSTECHLAB :
            return "TERRAN_BARRACKSTECHLAB";
        case UNIT_TYPEID::TERRAN_BATTLECRUISER : return "TERRAN_BATTLECRUISER";
        case UNIT_TYPEID::TERRAN_BUNKER        : return "TERRAN_BUNKER";
        case UNIT_TYPEID::TERRAN_COMMANDCENTER : return "TERRAN_COMMANDCENTER";
        case UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING :
            return "TERRAN_COMMANDCENTERFLYING";
        case UNIT_TYPEID::TERRAN_CYCLONE : return "TERRAN_CYCLONE";
        case UNIT_TYPEID::TERRAN_ENGINEERINGBAY :
            return "TERRAN_ENGINEERINGBAY";
        case UNIT_TYPEID::TERRAN_FACTORY       : return "TERRAN_FACTORY";
        case UNIT_TYPEID::TERRAN_FACTORYFLYING : return "TERRAN_FACTORYFLYING";
        case UNIT_TYPEID::TERRAN_FACTORYREACTOR :
            return "TERRAN_FACTORYREACTOR";
        case UNIT_TYPEID::TERRAN_FACTORYTECHLAB :
            return "TERRAN_FACTORYTECHLAB";
        case UNIT_TYPEID::TERRAN_FUSIONCORE    : return "TERRAN_FUSIONCORE";
        case UNIT_TYPEID::TERRAN_GHOST         : return "TERRAN_GHOST";
        case UNIT_TYPEID::TERRAN_GHOSTACADEMY  : return "TERRAN_GHOSTACADEMY";
        case UNIT_TYPEID::TERRAN_HELLION       : return "TERRAN_HELLION";
        case UNIT_TYPEID::TERRAN_HELLIONTANK   : return "TERRAN_HELLIONTANK";
        case UNIT_TYPEID::TERRAN_KD8CHARGE     : return "TERRAN_KD8CHARGE";
        case UNIT_TYPEID::TERRAN_LIBERATOR     : return "TERRAN_LIBERATOR";
        case UNIT_TYPEID::TERRAN_LIBERATORAG   : return "TERRAN_LIBERATORAG";
        case UNIT_TYPEID::TERRAN_MARAUDER      : return "TERRAN_MARAUDER";
        case UNIT_TYPEID::TERRAN_MARINE        : return "TERRAN_MARINE";
        case UNIT_TYPEID::TERRAN_MEDIVAC       : return "TERRAN_MEDIVAC";
        case UNIT_TYPEID::TERRAN_MISSILETURRET : return "TERRAN_MISSILETURRET";
        case UNIT_TYPEID::TERRAN_MULE          : return "TERRAN_MULE";
        case UNIT_TYPEID::TERRAN_NUKE          : return "TERRAN_NUKE";
        case UNIT_TYPEID::TERRAN_ORBITALCOMMAND :
            return "TERRAN_ORBITALCOMMAND";
        case UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING :
            return "TERRAN_ORBITALCOMMANDFLYING";
        case UNIT_TYPEID::TERRAN_PLANETARYFORTRESS :
            return "TERRAN_PLANETARYFORTRESS";
        case UNIT_TYPEID::TERRAN_POINTDEFENSEDRONE :
            return "TERRAN_POINTDEFENSEDRONE";
        case UNIT_TYPEID::TERRAN_PREVIEWBUNKERUPGRADED :
            return "TERRAN_PREVIEWBUNKERUPGRADED";
        case UNIT_TYPEID::TERRAN_RAVEN        : return "TERRAN_RAVEN";
        case UNIT_TYPEID::TERRAN_REACTOR      : return "TERRAN_REACTOR";
        case UNIT_TYPEID::TERRAN_REAPER       : return "TERRAN_REAPER";
        case UNIT_TYPEID::TERRAN_REFINERY     : return "TERRAN_REFINERY";
        case UNIT_TYPEID::TERRAN_REFINERYRICH : return "TERRAN_REFINERYRICH";
        case UNIT_TYPEID::TERRAN_SCV          : return "TERRAN_SCV";
        case UNIT_TYPEID::TERRAN_SENSORTOWER  : return "TERRAN_SENSORTOWER";
        case UNIT_TYPEID::TERRAN_SIEGETANK    : return "TERRAN_SIEGETANK";
        case UNIT_TYPEID::TERRAN_SIEGETANKSIEGED :
            return "TERRAN_SIEGETANKSIEGED";
        case UNIT_TYPEID::TERRAN_STARPORT : return "TERRAN_STARPORT";
        case UNIT_TYPEID::TERRAN_STARPORTFLYING :
            return "TERRAN_STARPORTFLYING";
        case UNIT_TYPEID::TERRAN_STARPORTREACTOR :
            return "TERRAN_STARPORTREACTOR";
        case UNIT_TYPEID::TERRAN_STARPORTTECHLAB :
            return "TERRAN_STARPORTTECHLAB";
        case UNIT_TYPEID::TERRAN_SUPPLYDEPOT : return "TERRAN_SUPPLYDEPOT";
        case UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED :
            return "TERRAN_SUPPLYDEPOTLOWERED";
        case UNIT_TYPEID::TERRAN_TECHLAB       : return "TERRAN_TECHLAB";
        case UNIT_TYPEID::TERRAN_THOR          : return "TERRAN_THOR";
        case UNIT_TYPEID::TERRAN_THORAP        : return "TERRAN_THORAP";
        case UNIT_TYPEID::TERRAN_VIKINGASSAULT : return "TERRAN_VIKINGASSAULT";
        case UNIT_TYPEID::TERRAN_VIKINGFIGHTER : return "TERRAN_VIKINGFIGHTER";
        case UNIT_TYPEID::TERRAN_WIDOWMINE     : return "TERRAN_WIDOWMINE";
        case UNIT_TYPEID::TERRAN_WIDOWMINEBURROWED :
            return "TERRAN_WIDOWMINEBURROWED";
        case UNIT_TYPEID::TERRAZINECANISTER : return "TERRAZINECANISTER";
        case UNIT_TYPEID::TERRAZINENODE     : return "TERRAZINENODE";
        case UNIT_TYPEID::TERRAZINENODEDEADTERRAN :
            return "TERRAZINENODEDEADTERRAN";
        case UNIT_TYPEID::TERRAZINENODEHAPPYPROTOSS :
            return "TERRAZINENODEHAPPYPROTOSS";
        case UNIT_TYPEID::TERRAZINETANK : return "TERRAZINETANK";
        case UNIT_TYPEID::TESTHERO      : return "TESTHERO";
        case UNIT_TYPEID::TESTHERODEBUGMISSILEABILITY1WEAPON :
            return "TESTHERODEBUGMISSILEABILITY1WEAPON";
        case UNIT_TYPEID::TESTHERODEBUGMISSILEABILITY2WEAPON :
            return "TESTHERODEBUGMISSILEABILITY2WEAPON";
        case UNIT_TYPEID::TESTHEROTHROWMISSILE : return "TESTHEROTHROWMISSILE";
        case UNIT_TYPEID::TESTSHOP             : return "TESTSHOP";
        case UNIT_TYPEID::TESTZERG             : return "TESTZERG";
        case UNIT_TYPEID::THORAALANCE          : return "THORAALANCE";
        case UNIT_TYPEID::THORAAWEAPON         : return "THORAAWEAPON";
        case UNIT_TYPEID::THORNLIZARD          : return "THORNLIZARD";
        case UNIT_TYPEID::THORWRECKAGE         : return "THORWRECKAGE";
        case UNIT_TYPEID::TORNADOMISSILEDUMMYWEAPON :
            return "TORNADOMISSILEDUMMYWEAPON";
        case UNIT_TYPEID::TORNADOMISSILEWEAPON : return "TORNADOMISSILEWEAPON";
        case UNIT_TYPEID::TOSH                 : return "TOSH";
        case UNIT_TYPEID::TOSSGRENADEWEAPON    : return "TOSSGRENADEWEAPON";
        case UNIT_TYPEID::TOWERMINE            : return "TOWERMINE";
        case UNIT_TYPEID::TRAFFICSIGNAL        : return "TRAFFICSIGNAL";
        case UNIT_TYPEID::TRANSPORTTRUCK       : return "TRANSPORTTRUCK";
        case UNIT_TYPEID::TRAYNOR01SIGNSDESTRUCTIBLE1 :
            return "TRAYNOR01SIGNSDESTRUCTIBLE1";
        case UNIT_TYPEID::TRUCKFLATBEDUNIT    : return "TRUCKFLATBEDUNIT";
        case UNIT_TYPEID::TRUCKSEMIUNIT       : return "TRUCKSEMIUNIT";
        case UNIT_TYPEID::TRUCKUTILITYUNIT    : return "TRUCKUTILITYUNIT";
        case UNIT_TYPEID::TYCHUSCHAINGUN      : return "TYCHUSCHAINGUN";
        case UNIT_TYPEID::TYCHUSCOMMANDO      : return "TYCHUSCOMMANDO";
        case UNIT_TYPEID::TYCHUSEJECTMISSILE  : return "TYCHUSEJECTMISSILE";
        case UNIT_TYPEID::TYCHUSGRENADEWEAPON : return "TYCHUSGRENADEWEAPON";
        case UNIT_TYPEID::ULAANSMOKEBRIDGE    : return "ULAANSMOKEBRIDGE";
        case UNIT_TYPEID::ULTRASONICPULSEWEAPON :
            return "ULTRASONICPULSEWEAPON";
        case UNIT_TYPEID::UNBUILDABLEBRICKSSMALLUNIT :
            return "UNBUILDABLEBRICKSSMALLUNIT";
        case UNIT_TYPEID::UNBUILDABLEBRICKSUNIT :
            return "UNBUILDABLEBRICKSUNIT";
        case UNIT_TYPEID::UNBUILDABLEPLATESSMALLUNIT :
            return "UNBUILDABLEPLATESSMALLUNIT";
        case UNIT_TYPEID::UNBUILDABLEPLATESUNIT :
            return "UNBUILDABLEPLATESUNIT";
        case UNIT_TYPEID::UNBUILDABLEROCKSDESTRUCTIBLE :
            return "UNBUILDABLEROCKSDESTRUCTIBLE";
        case UNIT_TYPEID::UNBUILDABLEROCKSSMALLUNIT :
            return "UNBUILDABLEROCKSSMALLUNIT";
        case UNIT_TYPEID::UNBUILDABLEROCKSUNIT : return "UNBUILDABLEROCKSUNIT";
        case UNIT_TYPEID::URSADAKCALF          : return "URSADAKCALF";
        case UNIT_TYPEID::URSADAKFEMALE        : return "URSADAKFEMALE";
        case UNIT_TYPEID::URSADAKFEMALEEXOTIC  : return "URSADAKFEMALEEXOTIC";
        case UNIT_TYPEID::URSADAKMALE          : return "URSADAKMALE";
        case UNIT_TYPEID::URSADAKMALEEXOTIC    : return "URSADAKMALEEXOTIC";
        case UNIT_TYPEID::URSADON              : return "URSADON";
        case UNIT_TYPEID::URSULA               : return "URSULA";
        case UNIT_TYPEID::URUN                 : return "URUN";
        case UNIT_TYPEID::URUNWEAPONLEFT       : return "URUNWEAPONLEFT";
        case UNIT_TYPEID::URUNWEAPONRIGHT      : return "URUNWEAPONRIGHT";
        case UNIT_TYPEID::VALHALLABASEDESTRUCTIBLEDOOR :
            return "VALHALLABASEDESTRUCTIBLEDOOR";
        case UNIT_TYPEID::VALHALLABASEDESTRUCTIBLEDOORDEAD :
            return "VALHALLABASEDESTRUCTIBLEDOORDEAD";
        case UNIT_TYPEID::VALHALLADESTRUCTIBLEWALL :
            return "VALHALLADESTRUCTIBLEWALL";
        case UNIT_TYPEID::VIKING              : return "VIKING";
        case UNIT_TYPEID::VIKINGFIGHTERWEAPON : return "VIKINGFIGHTERWEAPON";
        case UNIT_TYPEID::VIKINGSKINPREVIEW   : return "VIKINGSKINPREVIEW";
        case UNIT_TYPEID::VIKINGSKY_UNIT      : return "VIKINGSKY_UNIT";
        case UNIT_TYPEID::VILESTREAMWEAPON    : return "VILESTREAMWEAPON";
        case UNIT_TYPEID::VIPERCONSUMESTRUCTUREWEAPON :
            return "VIPERCONSUMESTRUCTUREWEAPON";
        case UNIT_TYPEID::VIROPHAGE : return "VIROPHAGE";
        case UNIT_TYPEID::VOIDMPIMMORTALREVIVECORPSE :
            return "VOIDMPIMMORTALREVIVECORPSE";
        case UNIT_TYPEID::VOIDSEEKER : return "VOIDSEEKER";
        case UNIT_TYPEID::VOIDSEEKERPHASEMINEBLASTSECONDARYWEAPON :
            return "VOIDSEEKERPHASEMINEBLASTSECONDARYWEAPON";
        case UNIT_TYPEID::VOIDSEEKERPHASEMINEBLASTWEAPON :
            return "VOIDSEEKERPHASEMINEBLASTWEAPON";
        case UNIT_TYPEID::VOIDSEEKERWEAPON     : return "VOIDSEEKERWEAPON";
        case UNIT_TYPEID::VULTURE              : return "VULTURE";
        case UNIT_TYPEID::VULTUREWEAPON        : return "VULTUREWEAPON";
        case UNIT_TYPEID::WALLOFFIRE           : return "WALLOFFIRE";
        case UNIT_TYPEID::WARBOT               : return "WARBOT";
        case UNIT_TYPEID::WARBOTBMISSILE       : return "WARBOTBMISSILE";
        case UNIT_TYPEID::WARHOUND             : return "WARHOUND";
        case UNIT_TYPEID::WARHOUNDWEAPON       : return "WARHOUNDWEAPON";
        case UNIT_TYPEID::WARPIG               : return "WARPIG";
        case UNIT_TYPEID::WARPPRISMSKINPREVIEW : return "WARPPRISMSKINPREVIEW";
        case UNIT_TYPEID::WEAPON               : return "WEAPON";
        case UNIT_TYPEID::WEAPONHYBRIDC        : return "WEAPONHYBRIDC";
        case UNIT_TYPEID::WEAPONHYBRIDD        : return "WEAPONHYBRIDD";
        case UNIT_TYPEID::WIDOWMINEAIRWEAPON   : return "WIDOWMINEAIRWEAPON";
        case UNIT_TYPEID::WIDOWMINEWEAPON      : return "WIDOWMINEWEAPON";
        case UNIT_TYPEID::WOLFSTATUE           : return "WOLFSTATUE";
        case UNIT_TYPEID::WRAITH               : return "WRAITH";
        case UNIT_TYPEID::WRAITHAIRWEAPONLEFT  : return "WRAITHAIRWEAPONLEFT";
        case UNIT_TYPEID::WRAITHAIRWEAPONRIGHT : return "WRAITHAIRWEAPONRIGHT";
        case UNIT_TYPEID::WRAITHGROUNDWEAPON   : return "WRAITHGROUNDWEAPON";
        case UNIT_TYPEID::WRECKEDBATTLECRUISERHELIOSFINAL :
            return "WRECKEDBATTLECRUISERHELIOSFINAL";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6E :
            return "XELNAGADESTRUCTIBLEBLOCKER6E";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6N :
            return "XELNAGADESTRUCTIBLEBLOCKER6N";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6NE :
            return "XELNAGADESTRUCTIBLEBLOCKER6NE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6NW :
            return "XELNAGADESTRUCTIBLEBLOCKER6NW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6S :
            return "XELNAGADESTRUCTIBLEBLOCKER6S";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6SE :
            return "XELNAGADESTRUCTIBLEBLOCKER6SE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6SW :
            return "XELNAGADESTRUCTIBLEBLOCKER6SW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER6W :
            return "XELNAGADESTRUCTIBLEBLOCKER6W";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8E :
            return "XELNAGADESTRUCTIBLEBLOCKER8E";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8N :
            return "XELNAGADESTRUCTIBLEBLOCKER8N";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8NE :
            return "XELNAGADESTRUCTIBLEBLOCKER8NE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8NW :
            return "XELNAGADESTRUCTIBLEBLOCKER8NW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8S :
            return "XELNAGADESTRUCTIBLEBLOCKER8S";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8SE :
            return "XELNAGADESTRUCTIBLEBLOCKER8SE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8SW :
            return "XELNAGADESTRUCTIBLEBLOCKER8SW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLEBLOCKER8W :
            return "XELNAGADESTRUCTIBLEBLOCKER8W";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6E :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6E";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6N :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6N";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6NE :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6NE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6NW :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6NW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6S :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6S";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6SE :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6SE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6SW :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6SW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER6W :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER6W";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8E :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8E";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8N :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8N";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8NE :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8NE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8NW :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8NW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8S :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8S";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8SE :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8SE";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8SW :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8SW";
        case UNIT_TYPEID::XELNAGADESTRUCTIBLERAMPBLOCKER8W :
            return "XELNAGADESTRUCTIBLERAMPBLOCKER8W";
        case UNIT_TYPEID::XELNAGAHEALINGSHRINE : return "XELNAGAHEALINGSHRINE";
        case UNIT_TYPEID::XELNAGAPRISON        : return "XELNAGAPRISON";
        case UNIT_TYPEID::XELNAGAPRISONCONSOLE : return "XELNAGAPRISONCONSOLE";
        case UNIT_TYPEID::XELNAGAPRISONHEIGHT2 : return "XELNAGAPRISONHEIGHT2";
        case UNIT_TYPEID::XELNAGAPRISONNORTH   : return "XELNAGAPRISONNORTH";
        case UNIT_TYPEID::XELNAGAPRISONNORTHHEIGHT2 :
            return "XELNAGAPRISONNORTHHEIGHT2";
        case UNIT_TYPEID::XELNAGASHRINE     : return "XELNAGASHRINE";
        case UNIT_TYPEID::XELNAGASHRINEXIL  : return "XELNAGASHRINEXIL";
        case UNIT_TYPEID::XELNAGATEMPLE     : return "XELNAGATEMPLE";
        case UNIT_TYPEID::XELNAGATEMPLEDOOR : return "XELNAGATEMPLEDOOR";
        case UNIT_TYPEID::XELNAGATEMPLEDOORBURROWED :
            return "XELNAGATEMPLEDOORBURROWED";
        case UNIT_TYPEID::XELNAGATEMPLEDOORURDL :
            return "XELNAGATEMPLEDOORURDL";
        case UNIT_TYPEID::XELNAGATEMPLEDOORURDLBURROWED :
            return "XELNAGATEMPLEDOORURDLBURROWED";
        case UNIT_TYPEID::XELNAGAVAULT : return "XELNAGAVAULT";
        case UNIT_TYPEID::XELNAGAWORLDSHIPVAULT :
            return "XELNAGAWORLDSHIPVAULT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORE :
            return "XELNAGA_CAVERNS_DOORE";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOOREOPENED :
            return "XELNAGA_CAVERNS_DOOREOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORN :
            return "XELNAGA_CAVERNS_DOORN";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORNE :
            return "XELNAGA_CAVERNS_DOORNE";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORNEOPENED :
            return "XELNAGA_CAVERNS_DOORNEOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORNOPENED :
            return "XELNAGA_CAVERNS_DOORNOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORNW :
            return "XELNAGA_CAVERNS_DOORNW";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORNWOPENED :
            return "XELNAGA_CAVERNS_DOORNWOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORS :
            return "XELNAGA_CAVERNS_DOORS";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORSE :
            return "XELNAGA_CAVERNS_DOORSE";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORSEOPENED :
            return "XELNAGA_CAVERNS_DOORSEOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORSOPENED :
            return "XELNAGA_CAVERNS_DOORSOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORSW :
            return "XELNAGA_CAVERNS_DOORSW";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORSWOPENED :
            return "XELNAGA_CAVERNS_DOORSWOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORW :
            return "XELNAGA_CAVERNS_DOORW";
        case UNIT_TYPEID::XELNAGA_CAVERNS_DOORWOPENED :
            return "XELNAGA_CAVERNS_DOORWOPENED";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEH10 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH10";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEH12 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH12";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEH8 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH8";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENE10 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE10";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENE12 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE12";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENE8 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE8";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENW10 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW10";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENW12 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW12";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENW8 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW8";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEV10 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV10";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEV12 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV12";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEV8 :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV8";
        case UNIT_TYPEID::XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT :
            return "XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT";
        case UNIT_TYPEID::YAMATOWEAPON : return "YAMATOWEAPON";
        case UNIT_TYPEID::YOINKMISSILE : return "YOINKMISSILE";
        case UNIT_TYPEID::YOINKSIEGETANKMISSILE :
            return "YOINKSIEGETANKMISSILE";
        case UNIT_TYPEID::YOINKVIKINGAIRMISSILE :
            return "YOINKVIKINGAIRMISSILE";
        case UNIT_TYPEID::YOINKVIKINGGROUNDMISSILE :
            return "YOINKVIKINGGROUNDMISSILE";
        case UNIT_TYPEID::ZERATUL              : return "ZERATUL";
        case UNIT_TYPEID::ZERATULCRYSTALCHARGE : return "ZERATULCRYSTALCHARGE";
        case UNIT_TYPEID::ZERGDROPPOD          : return "ZERGDROPPOD";
        case UNIT_TYPEID::ZERGDROPPODCREEP     : return "ZERGDROPPODCREEP";
        case UNIT_TYPEID::ZERG_BANELING        : return "ZERG_BANELING";
        case UNIT_TYPEID::ZERG_BANELINGBURROWED :
            return "ZERG_BANELINGBURROWED";
        case UNIT_TYPEID::ZERG_BANELINGCOCOON  : return "ZERG_BANELINGCOCOON";
        case UNIT_TYPEID::ZERG_BANELINGNEST    : return "ZERG_BANELINGNEST";
        case UNIT_TYPEID::ZERG_BROODLING       : return "ZERG_BROODLING";
        case UNIT_TYPEID::ZERG_BROODLORD       : return "ZERG_BROODLORD";
        case UNIT_TYPEID::ZERG_BROODLORDCOCOON : return "ZERG_BROODLORDCOCOON";
        case UNIT_TYPEID::ZERG_CHANGELING      : return "ZERG_CHANGELING";
        case UNIT_TYPEID::ZERG_CHANGELINGMARINE :
            return "ZERG_CHANGELINGMARINE";
        case UNIT_TYPEID::ZERG_CHANGELINGMARINESHIELD :
            return "ZERG_CHANGELINGMARINESHIELD";
        case UNIT_TYPEID::ZERG_CHANGELINGZEALOT :
            return "ZERG_CHANGELINGZEALOT";
        case UNIT_TYPEID::ZERG_CHANGELINGZERGLING :
            return "ZERG_CHANGELINGZERGLING";
        case UNIT_TYPEID::ZERG_CHANGELINGZERGLINGWINGS :
            return "ZERG_CHANGELINGZERGLINGWINGS";
        case UNIT_TYPEID::ZERG_CORRUPTOR  : return "ZERG_CORRUPTOR";
        case UNIT_TYPEID::ZERG_CREEPTUMOR : return "ZERG_CREEPTUMOR";
        case UNIT_TYPEID::ZERG_CREEPTUMORBURROWED :
            return "ZERG_CREEPTUMORBURROWED";
        case UNIT_TYPEID::ZERG_CREEPTUMORQUEEN : return "ZERG_CREEPTUMORQUEEN";
        case UNIT_TYPEID::ZERG_DRONE           : return "ZERG_DRONE";
        case UNIT_TYPEID::ZERG_DRONEBURROWED   : return "ZERG_DRONEBURROWED";
        case UNIT_TYPEID::ZERG_EGG             : return "ZERG_EGG";
        case UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER :
            return "ZERG_EVOLUTIONCHAMBER";
        case UNIT_TYPEID::ZERG_EXTRACTOR     : return "ZERG_EXTRACTOR";
        case UNIT_TYPEID::ZERG_EXTRACTORRICH : return "ZERG_EXTRACTORRICH";
        case UNIT_TYPEID::ZERG_GREATERSPIRE  : return "ZERG_GREATERSPIRE";
        case UNIT_TYPEID::ZERG_HATCHERY      : return "ZERG_HATCHERY";
        case UNIT_TYPEID::ZERG_HIVE          : return "ZERG_HIVE";
        case UNIT_TYPEID::ZERG_HYDRALISK     : return "ZERG_HYDRALISK";
        case UNIT_TYPEID::ZERG_HYDRALISKBURROWED :
            return "ZERG_HYDRALISKBURROWED";
        case UNIT_TYPEID::ZERG_HYDRALISKDEN   : return "ZERG_HYDRALISKDEN";
        case UNIT_TYPEID::ZERG_INFESTATIONPIT : return "ZERG_INFESTATIONPIT";
        case UNIT_TYPEID::ZERG_INFESTEDTERRANSEGG :
            return "ZERG_INFESTEDTERRANSEGG";
        case UNIT_TYPEID::ZERG_INFESTOR : return "ZERG_INFESTOR";
        case UNIT_TYPEID::ZERG_INFESTORBURROWED :
            return "ZERG_INFESTORBURROWED";
        case UNIT_TYPEID::ZERG_INFESTORTERRAN : return "ZERG_INFESTORTERRAN";
        case UNIT_TYPEID::ZERG_LAIR           : return "ZERG_LAIR";
        case UNIT_TYPEID::ZERG_LARVA          : return "ZERG_LARVA";
        case UNIT_TYPEID::ZERG_LOCUSTMP       : return "ZERG_LOCUSTMP";
        case UNIT_TYPEID::ZERG_LOCUSTMPFLYING : return "ZERG_LOCUSTMPFLYING";
        case UNIT_TYPEID::ZERG_LURKERDENMP    : return "ZERG_LURKERDENMP";
        case UNIT_TYPEID::ZERG_LURKERMP       : return "ZERG_LURKERMP";
        case UNIT_TYPEID::ZERG_LURKERMPBURROWED :
            return "ZERG_LURKERMPBURROWED";
        case UNIT_TYPEID::ZERG_LURKERMPEGG    : return "ZERG_LURKERMPEGG";
        case UNIT_TYPEID::ZERG_MUTALISK       : return "ZERG_MUTALISK";
        case UNIT_TYPEID::ZERG_NYDUSCANAL     : return "ZERG_NYDUSCANAL";
        case UNIT_TYPEID::ZERG_NYDUSNETWORK   : return "ZERG_NYDUSNETWORK";
        case UNIT_TYPEID::ZERG_OVERLORD       : return "ZERG_OVERLORD";
        case UNIT_TYPEID::ZERG_OVERLORDCOCOON : return "ZERG_OVERLORDCOCOON";
        case UNIT_TYPEID::ZERG_OVERLORDTRANSPORT :
            return "ZERG_OVERLORDTRANSPORT";
        case UNIT_TYPEID::ZERG_OVERSEER : return "ZERG_OVERSEER";
        case UNIT_TYPEID::ZERG_OVERSEERSIEGEMODE :
            return "ZERG_OVERSEERSIEGEMODE";
        case UNIT_TYPEID::ZERG_PARASITICBOMBDUMMY :
            return "ZERG_PARASITICBOMBDUMMY";
        case UNIT_TYPEID::ZERG_QUEEN         : return "ZERG_QUEEN";
        case UNIT_TYPEID::ZERG_QUEENBURROWED : return "ZERG_QUEENBURROWED";
        case UNIT_TYPEID::ZERG_RAVAGER       : return "ZERG_RAVAGER";
        case UNIT_TYPEID::ZERG_RAVAGERCOCOON : return "ZERG_RAVAGERCOCOON";
        case UNIT_TYPEID::ZERG_ROACH         : return "ZERG_ROACH";
        case UNIT_TYPEID::ZERG_ROACHBURROWED : return "ZERG_ROACHBURROWED";
        case UNIT_TYPEID::ZERG_ROACHWARREN   : return "ZERG_ROACHWARREN";
        case UNIT_TYPEID::ZERG_SPAWNINGPOOL  : return "ZERG_SPAWNINGPOOL";
        case UNIT_TYPEID::ZERG_SPINECRAWLER  : return "ZERG_SPINECRAWLER";
        case UNIT_TYPEID::ZERG_SPINECRAWLERUPROOTED :
            return "ZERG_SPINECRAWLERUPROOTED";
        case UNIT_TYPEID::ZERG_SPIRE        : return "ZERG_SPIRE";
        case UNIT_TYPEID::ZERG_SPORECRAWLER : return "ZERG_SPORECRAWLER";
        case UNIT_TYPEID::ZERG_SPORECRAWLERUPROOTED :
            return "ZERG_SPORECRAWLERUPROOTED";
        case UNIT_TYPEID::ZERG_SWARMHOSTBURROWEDMP :
            return "ZERG_SWARMHOSTBURROWEDMP";
        case UNIT_TYPEID::ZERG_SWARMHOSTMP : return "ZERG_SWARMHOSTMP";
        case UNIT_TYPEID::ZERG_TRANSPORTOVERLORDCOCOON :
            return "ZERG_TRANSPORTOVERLORDCOCOON";
        case UNIT_TYPEID::ZERG_ULTRALISK : return "ZERG_ULTRALISK";
        case UNIT_TYPEID::ZERG_ULTRALISKBURROWED :
            return "ZERG_ULTRALISKBURROWED";
        case UNIT_TYPEID::ZERG_ULTRALISKCAVERN : return "ZERG_ULTRALISKCAVERN";
        case UNIT_TYPEID::ZERG_VIPER           : return "ZERG_VIPER";
        case UNIT_TYPEID::ZERG_ZERGLING        : return "ZERG_ZERGLING";
        case UNIT_TYPEID::ZERG_ZERGLINGBURROWED :
            return "ZERG_ZERGLINGBURROWED";
        case UNIT_TYPEID::ZERUSDESTRUCTIBLEARCH :
            return "ZERUSDESTRUCTIBLEARCH";
        case UNIT_TYPEID::ZHAKULDASLIBRARYUNIT : return "ZHAKULDASLIBRARYUNIT";
        case UNIT_TYPEID::ZHAKULDASLIBRARYUNITBURROWED :
            return "ZHAKULDASLIBRARYUNITBURROWED";
        case UNIT_TYPEID::ZHAKULDASLIGHTBRIDGE : return "ZHAKULDASLIGHTBRIDGE";
        case UNIT_TYPEID::ZHAKULDASLIGHTBRIDGEOFF :
            return "ZHAKULDASLIGHTBRIDGEOFF";
        case UNIT_TYPEID::ZHAKULDASLIGHTBRIDGEOFFTOPRIGHT :
            return "ZHAKULDASLIGHTBRIDGEOFFTOPRIGHT";
        case UNIT_TYPEID::ZHAKULDASLIGHTBRIDGETOPRIGHT :
            return "ZHAKULDASLIGHTBRIDGETOPRIGHT";
        case UNIT_TYPEID::_10SLOTBAG : return "_10SLOTBAG";
        case UNIT_TYPEID::_12SLOTBAG : return "_12SLOTBAG";
        case UNIT_TYPEID::_14SLOTBAG : return "_14SLOTBAG";
        case UNIT_TYPEID::_16SLOTBAG : return "_16SLOTBAG";
        case UNIT_TYPEID::_18SLOTBAG : return "_18SLOTBAG";
        case UNIT_TYPEID::_20SLOTBAG : return "_20SLOTBAG";
        case UNIT_TYPEID::_22SLOTBAG : return "_22SLOTBAG";
        case UNIT_TYPEID::_24SLOTBAG : return "_24SLOTBAG";
        case UNIT_TYPEID::_4SLOTBAG  : return "_4SLOTBAG";
        case UNIT_TYPEID::_6SLOTBAG  : return "_6SLOTBAG";
        case UNIT_TYPEID::_8SLOTBAG  : return "_8SLOTBAG";
        default                      : return "UNKNOWN";
    }
}

}