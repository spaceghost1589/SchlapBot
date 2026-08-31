module;
#include "types.h"
export module type_enums:buff_enum;

export namespace sc2 {

enum class BUFF_ID : uint16_t {
    ACCELERATIONZONEFLYINGTEMPORALFIELD                 = 290,
    ACCELERATIONZONETEMPORALFIELD                       = 289,
    ADEPTDEATHCHECK                                     = 135,
    AGGRESSIVEMUTATION                                  = 131,
    AIDANGERBUFF                                        = 31,
    AMORPHOUSARMORCLOUD                                 = 297,
    ANTIAIRWEAPONSWITCHCOOLDOWN                         = 100,
    ARBITERMPCLOAKFIELDEFFECT                           = 110,
    ARBITERMPSTASISFIELD                                = 101,
    ARTANISCLOAKINGFIELDEFFECT                          = 222,
    ARTANISTEMPORALRIFTUNIT                             = 221,
    ARTANISVORTEXBEHAVIOR                               = 223,
    AUTOMATEDREPAIR                                     = 232,
    BANSHEECLOAK                                        = 7,
    BANSHEECLOAKCROSSSPECTRUMDAMPENERS                  = 154,
    BATTERYOVERCHARGE                                   = 301,
    BATTLECRUISERANTIAIRDISABLE                         = 70,
    BENIGN                                              = 79,
    BIOSTASIS                                           = 205,
    BLINDINGCLOUD                                       = 83,
    BLINDINGCLOUDSTRUCTURE                              = 38,
    BUILDINGSCARAB                                      = 249,
    BUILDINGSHIELD                                      = 66,
    BUILDINGSTASIS                                      = 71,
    BURROWCHARGE                                        = 86,
    BURSTCAPACITORSDAMAGEBUFF                           = 239,
    BYPASSARMORDEBUFFONE                                = 142,
    BYPASSARMORDEBUFFTHREE                              = 144,
    BYPASSARMORDEBUFFTWO                                = 143,
    CANNONRADAR                                         = 253,
    CAPRESOURCE                                         = 82,
    CARRYHARVESTABLEVESPENEGEYSERGAS                    = 273,
    CARRYHARVESTABLEVESPENEGEYSERGASPROTOSS             = 274,
    CARRYHARVESTABLEVESPENEGEYSERGASZERG                = 275,
    CARRYHIGHYIELDMINERALFIELDMINERALS                  = 272,
    CARRYMINERALFIELDMINERALS                           = 271,
    CHANNELSNIPECOMBAT                                  = 145,
    CHARGEUP                                            = 75,
    CHARGING                                            = 30,
    CHRONOBOOSTENERGYCOST                               = 281,
    CLOAKFIELD                                          = 294,
    CLOAKFIELDEFFECT                                    = 29,
    CLOAKINGFIELDTARGETED                               = 103,
    CLOAKUNIT                                           = 76,
    COLLAPSIBLEROCKTOWERCONJOINEDSEARCH                 = 39,
    COLLAPSIBLEROCKTOWERRAMPDIAGONALCONJOINEDSEARCH     = 40,
    COLLAPSIBLETERRANTOWERCONJOINEDSEARCH               = 41,
    COLLAPSIBLETERRANTOWERRAMPDIAGONALCONJOINEDSEARCH   = 42,
    COLONYINFESTATION                                   = 240,
    CONTAMINATED                                        = 36,
    CORRUPTION                                          = 10,
    CORRUPTIONBOMBDAMAGE                                = 112,
    CORRUPTORGROUNDATTACKDEBUFF                         = 69,
    CORRUPTORINFESTING                                  = 264,
    CORSAIRMPDISRUPTIONWEB                              = 113,
    DEFENSIVEMATRIX                                     = 260,
    DEFILERMPCONSUME                                    = 125,
    DEFILERMPDARKSWARM                                  = 126,
    DEFILERMPPLAGUE                                     = 127,
    DEVOURERMPACIDSPORES                                = 124,
    DIGESTERCREEPSPRAYVISION                            = 43,
    DISABLEABILS                                        = 3,
    DISABLEINTERCEPTORS                                 = 141,
    DISRUPTORPUSH                                       = 114,
    DOMINATION                                          = 241,
    DOOMDAMAGEDELAY                                     = 84,
    DUTCHMARAUDERSLOW                                   = 226,
    EMPBURST                                            = 242,
    EMPDECLOAK                                          = 16,
    EMPDRAIN                                            = 207,
    ENGAGE                                              = 81,
    ETHEREAL                                            = 21,
    EXTENDBRIDGEEXTENDINGBRIDGENEWIDE10OUT              = 92,
    EXTENDBRIDGEEXTENDINGBRIDGENEWIDE12OUT              = 94,
    EXTENDBRIDGEEXTENDINGBRIDGENEWIDE8OUT               = 90,
    EXTENDBRIDGEEXTENDINGBRIDGENWWIDE10OUT              = 93,
    EXTENDBRIDGEEXTENDINGBRIDGENWWIDE12OUT              = 95,
    EXTENDBRIDGEEXTENDINGBRIDGENWWIDE8OUT               = 91,
    EYESTALK                                            = 85,
    FUNGALGROWTH                                        = 17,
    GHOSTBLAST                                          = 251,
    GHOSTCLOAK                                          = 6,
    GHOSTHOLDFIRE                                       = 12,
    GHOSTHOLDFIREB                                      = 13,
    GHOSTSNIPEDOT                                       = 50,
    GRAVITONBEAM                                        = 5,
    GRAVITONPRISON                                      = 147,
    GUARDIANSHIELD                                      = 18,
    HEROICBUFF03                                        = 252,
    HIDDEN                                              = 87,
    HYBRIDCZERGYROOTS                                   = 243,
    HYBRIDFZERGYROOTS                                   = 244,
    IMMORTALOVERLOAD                                    = 102,
    INCAPACITATED                                       = 224,
    INFESTORDISEASE                                     = 148,
    INFESTORENSNARE                                     = 284,
    INFESTORENSNAREMAKEPRECURSORREHEIGHTSOURCE          = 285,
    INHIBITORZONEFLYINGTEMPORALFIELD                    = 291,
    INHIBITORZONETEMPORALFIELD                          = 293,
    INVALID                                             = 0,
    INVULNERABILITYSHIELD                               = 44,
    IRRADIATE                                           = 213,
    ITEMGRAVITYBOMBS                                    = 270,
    JUMPSTOMPFSTUN                                      = 228,
    JUMPSTOMPSTUN                                       = 227,
    KARASSPSISTORM                                      = 225,
    LASERSIGHT                                          = 67,
    LASERTARGETING                                      = 80,
    LEECH                                               = 14,
    LEECHDISABLEABILITIES                               = 15,
    LIGHTNINGBOMB                                       = 104,
    LIGHTOFAIUR                                         = 115,
    LOADOUTSPRAY_TRACKER                                = 292,
    LOCKDOWNB                                           = 245,
    LOCKON                                              = 116,
    LURKERHOLDFIRE                                      = 136,
    LURKERHOLDFIREB                                     = 137,
    MAXIMUMTHRUST                                       = 74,
    MEDIVACSPEEDBOOST                                   = 89,
    MERCAIRDROPDELAY                                    = 267,
    MERCENARYCYCLONEMISSILES                            = 61,
    MERCENARYSENSORDISH                                 = 62,
    MERCENARYSHIELD                                     = 63,
    MERCGROUNDDROP                                      = 266,
    MERCGROUNDDROPDELAY                                 = 265,
    MINDBLASTSTUN                                       = 208,
    MINDCONTROL                                         = 217,
    MINEDRONECOUNTDOWN                                  = 45,
    MINEDRONEDOT                                        = 88,
    MOTHERSHIPCOREENERGIZEVISUAL                        = 48,
    MOTHERSHIPSTASIS                                    = 46,
    MOTHERSHIPSTASISCASTER                              = 47,
    NAPALM                                              = 238,
    NEURALPARASITE                                      = 22,
    NEURALPARASITECHILDREN                              = 296,
    NEURALPARASITEWAIT                                  = 23,
    NEXUSINVULNERABILITY                                = 52,
    NEXUSPHASESHIFT                                     = 51,
    NEXUSSHIELDOVERCHARGE                               = 286,
    NEXUSSHIELDRECHARGEONPYLONBEHAVIOR                  = 282,
    NEXUSSHIELDRECHARGEONPYLONBEHAVIORSECONDARYONTARGET = 283,
    NULLFIELD                                           = 77,
    NYDUSWORMLAVAINSTANTDEATH                           = 214,
    ORACLECLOAKFIELD                                    = 55,
    ORACLECLOAKFIELDEFFECT                              = 56,
    ORACLEPHASESHIFT                                    = 105,
    ORACLEREVELATION                                    = 49,
    ORACLESTASISTRAPTARGET                              = 129,
    ORACLEWEAPON                                        = 99,
    OVERCHARGE                                          = 117,
    OVERCHARGEDAMAGE                                    = 118,
    OVERCHARGESPEEDBOOST                                = 119,
    PARASITICBOMB                                       = 132,
    PARASITICBOMBDELAYTIMEDLIFE                         = 287,
    PARASITICBOMBSECONDARYUNITSEARCH                    = 134,
    PARASITICBOMBUNITKU                                 = 133,
    PERMANENTLYCLOAKED                                  = 276,
    PERSONALCLOAKINGFREE                                = 206,
    PHASESHIELD                                         = 96,
    POWERUSERWARPABLE                                   = 8,
    PREDATORCLOAKING                                    = 215,
    PROTECTIVEBARRIER                                   = 68,
    PSIDISRUPTION                                       = 216,
    PSIONICSHOCKWAVEHEIGHTANDSTUN                       = 230,
    PSISTORM                                            = 28,
    PSYTROUSOXIDE                                       = 153,
    PURIFICATIONNOVA                                    = 111,
    PURIFICATIONNOVAPOST                                = 140,
    PURIFIERPLANETCRACKERCHARGE                         = 150,
    PURIFY                                              = 97,
    QUEENKNOCKDOWN                                      = 218,
    QUEENMPENSNARE                                      = 128,
    QUEENSPAWNLARVATIMER                                = 11,
    RADAR25                                             = 1,
    RAVENSCRAMBLERMISSILE                               = 277,
    RAVENSCRAMBLERMISSILECARRIER                        = 300,
    RAVENSHREDDERMISSILEARMORREDUCTION                  = 280,
    RAVENSHREDDERMISSILEARMORREDUCTIONUISUBTRUCT        = 298,
    RAVENSHREDDERMISSILETIMEOUT                         = 278,
    RAVENSHREDDERMISSILETINT                            = 279,
    RAYNORMISSILETIMEDLIFE                              = 229,
    RAYNORTIMEBOMBMISSILE                               = 234,
    RAYNORTIMEBOMBUNIT                                  = 235,
    RELEASEINTERCEPTORSBEACON                           = 109,
    RELEASEINTERCEPTORSCOOLDOWN                         = 106,
    RELEASEINTERCEPTORSTIMEDLIFEWARNING                 = 107,
    RELEASEINTERCEPTORSWANDERDELAY                      = 108,
    RESCUE                                              = 78,
    RESONATINGGLAIVESPHASESHIFT                         = 295,
    RESOURCESTUN                                        = 73,
    RESTORESHIELDS                                      = 60,
    ROUGHTERRAINSEARCH                                  = 53,
    ROUGHTERRAINSLOW                                    = 54,
    SCIENCEVESSELCLOAKFIELD                             = 219,
    SCRYER                                              = 64,
    SCRYERFRIENDLY                                      = 57,
    SEEKERMISSILE                                       = 120,
    SEEKERMISSILETIMEOUT                                = 19,
    SELFREPAIR                                          = 130,
    SHADOWCLONE                                         = 231,
    SHEEPBUSY                                           = 35,
    SHIFTDELAY                                          = 204,
    SHREDDERSWARMDAMAGEAPPLY                            = 263,
    SLAYNELEMENTALGRABSTUN                              = 139,
    SLIMED                                              = 233,
    SLOW                                                = 33,
    SPECTRECLOAKING                                     = 151,
    SPECTRECLOAKINGFREE                                 = 211,
    SPECTREHOLDFIRE                                     = 268,
    SPECTREHOLDFIREB                                    = 269,
    SPECTRELOCKDOWNB                                    = 246,
    SPECTRESHIELD                                       = 58,
    SPORECANNONMISSILE                                  = 220,
    SS_BATTLECRUISERCOLLISIONCHECK                      = 171,
    SS_BATTLECRUISERHUNTERSEEKERTIMEOUT                 = 155,
    SS_BATTLECRUISERMISSILELAUNCHER                     = 175,
    SS_CARRIERBOSSCOLLISIONCHECK                        = 163,
    SS_CARRIERCOLLISIONCHECK                            = 185,
    SS_CORRUPTORCOLLISIONCHECK                          = 196,
    SS_CORRUPTORMISSILETARGETCHECK                      = 164,
    SS_FIGHTERBOMBMISSILEDEATH                          = 182,
    SS_FIGHTERDRONEDAMAGERESPONSE                       = 183,
    SS_INTERCEPTORCOLLISIONCHECK                        = 184,
    SS_INVULNERABLE                                     = 165,
    SS_LEVIATHANBOMBCOLLISIONCHECK                      = 159,
    SS_LEVIATHANBOMBEXPLODETIMER                        = 160,
    SS_LEVIATHANBOMBMISSILETARGETCHECK                  = 161,
    SS_LEVIATHANCOLLISIONCHECK                          = 200,
    SS_LEVIATHANTENTACLEMISSILESCANSWAPDELAY            = 169,
    SS_LEVIATHANTENTACLEMISSILETARGETCHECK              = 166,
    SS_LEVIATHANTENTACLEMISSILETARGETCHECKINVERTED      = 167,
    SS_LEVIATHANTENTACLETARGETDEATHDELAY                = 168,
    SS_LIGHTNINGPROJECTOR                               = 149,
    SS_LIGHTNINGPROJECTORCOLLISIONCHECK                 = 203,
    SS_MAXACCELERATION                                  = 257,
    SS_MAXSPEED                                         = 256,
    SS_MISSILETARGETCHECK                               = 255,
    SS_MISSILETARGETCHECKVIKING                         = 254,
    SS_MISSILETARGETCHECKVIKINGDRONE                    = 186,
    SS_MISSILETARGETCHECKVIKINGSTRONG1                  = 187,
    SS_MISSILETARGETCHECKVIKINGSTRONG2                  = 188,
    SS_MISSILETIMEOUT                                   = 158,
    SS_PHOENIXCOLLISIONCHECK                            = 198,
    SS_POWERUPDIAGONAL1                                 = 258,
    SS_POWERUPDIAGONAL2                                 = 170,
    SS_POWERUPHEALTH1                                   = 189,
    SS_POWERUPHEALTH2                                   = 190,
    SS_POWERUPMORPHTOBOMB                               = 192,
    SS_POWERUPMORPHTOHEALTH                             = 193,
    SS_POWERUPMORPHTOSIDEMISSILES                       = 194,
    SS_POWERUPMORPHTOSTRONGERMISSILES                   = 195,
    SS_POWERUPSTRONG                                    = 191,
    SS_SCIENCEVESSELCOLLISIONCHECK                      = 201,
    SS_SCOURGECOLLISIONCHECK                            = 199,
    SS_SCOURGEDEATH                                     = 180,
    SS_SCOURGEMISSILETARGETCHECK                        = 179,
    SS_SCOUTCOLLISIONCHECK                              = 197,
    SS_STRONGERENEMYBUFF                                = 156,
    SS_SWARMGUARDIANCOLLISIONCHECK                      = 181,
    SS_TERRATRONARMMISSILETARGETCHECK                   = 157,
    SS_TERRATRONCOLLISIONCHECK                          = 162,
    SS_TERRATRONMISSILELAUNCHER                         = 174,
    SS_TERRATRONMISSILESPINNERCOLLISIONCHECK            = 173,
    SS_TERRATRONMISSILESPINNERMISSILELAUNCHER           = 172,
    SS_TERRATRONSAWCOLLISIONCHECK                       = 202,
    SS_TERRATRONSTUN                                    = 176,
    SS_VIKINGRESPAWN                                    = 177,
    SS_WRAITHCOLLISIONCHECK                             = 178,
    STASIS                                              = 72,
    STIMPACK                                            = 27,
    STIMPACKMARAUDER                                    = 24,
    STUNROUNDINITIALBEHAVIOR                            = 65,
    SUPPLYDROP                                          = 25,
    TAKENDAMAGE                                         = 299,
    TAUNTB                                              = 2,
    TEMPESTDISRUPTIONBLASTSTUNBEHAVIOR                  = 146,
    TEMPORALFIELD                                       = 121,
    TEMPORALRIFTUNIT                                    = 34,
    TESTATTRIBUTE                                       = 261,
    TESTVETERANCY                                       = 262,
    TIMESCALECONVERSIONBEHAVIOR                         = 37,
    TIMESTOPSTUN                                        = 138,
    TIMEWARPPRODUCTION                                  = 20,
    TRANSFUSION                                         = 288,
    TRANSIENTMORPH                                      = 4,
    TYCHUSCOMMANDOSTIMPACK                              = 236,
    ULTRASONICPULSESTUN                                 = 212,
    VIPERCONSUMESTRUCTURE                               = 59,
    VIRALPLASMA                                         = 237,
    VOIDMPIMMORTALREVIVESUPRESSED                       = 123,
    VOIDRAYSWARMDAMAGEBOOST                             = 122,
    VOIDSIPHON                                          = 98,
    VOODOOLOCKDOWN                                      = 247,
    VOODOOSHIELD                                        = 210,
    VORTEXBEHAVIOR                                      = 32,
    VORTEXBEHAVIORENEMY                                 = 9,
    VORTEXBEHAVIORERADICATOR                            = 250,
    WATER                                               = 259,
    WRAITHCLOAK                                         = 152,
    ZERATULSTUN                                         = 248,
    _250MMSTRIKECANNONS                                 = 26,
    _330MMBARRAGECANNONS                                = 209,
};

using BuffID = SC2Type<BUFF_ID>;

//! Converts a BUFF_ID into a string of the same name.
const char* BuffIDToName ( const BuffID id ) {
    switch ( static_cast<BUFF_ID> ( id ) ) {
        case BUFF_ID::ACCELERATIONZONEFLYINGTEMPORALFIELD :
            return "ACCELERATIONZONEFLYINGTEMPORALFIELD";
        case BUFF_ID::ACCELERATIONZONETEMPORALFIELD :
            return "ACCELERATIONZONETEMPORALFIELD";
        case BUFF_ID::ADEPTDEATHCHECK     : return "ADEPTDEATHCHECK";
        case BUFF_ID::AGGRESSIVEMUTATION  : return "AGGRESSIVEMUTATION";
        case BUFF_ID::AIDANGERBUFF        : return "AIDANGERBUFF";
        case BUFF_ID::AMORPHOUSARMORCLOUD : return "AMORPHOUSARMORCLOUD";
        case BUFF_ID::ANTIAIRWEAPONSWITCHCOOLDOWN :
            return "ANTIAIRWEAPONSWITCHCOOLDOWN";
        case BUFF_ID::ARBITERMPCLOAKFIELDEFFECT :
            return "ARBITERMPCLOAKFIELDEFFECT";
        case BUFF_ID::ARBITERMPSTASISFIELD : return "ARBITERMPSTASISFIELD";
        case BUFF_ID::ARTANISCLOAKINGFIELDEFFECT :
            return "ARTANISCLOAKINGFIELDEFFECT";
        case BUFF_ID::ARTANISTEMPORALRIFTUNIT :
            return "ARTANISTEMPORALRIFTUNIT";
        case BUFF_ID::ARTANISVORTEXBEHAVIOR : return "ARTANISVORTEXBEHAVIOR";
        case BUFF_ID::AUTOMATEDREPAIR       : return "AUTOMATEDREPAIR";
        case BUFF_ID::BANSHEECLOAK          : return "BANSHEECLOAK";
        case BUFF_ID::BANSHEECLOAKCROSSSPECTRUMDAMPENERS :
            return "BANSHEECLOAKCROSSSPECTRUMDAMPENERS";
        case BUFF_ID::BATTERYOVERCHARGE : return "BATTERYOVERCHARGE";
        case BUFF_ID::BATTLECRUISERANTIAIRDISABLE :
            return "BATTLECRUISERANTIAIRDISABLE";
        case BUFF_ID::BENIGN                 : return "BENIGN";
        case BUFF_ID::BIOSTASIS              : return "BIOSTASIS";
        case BUFF_ID::BLINDINGCLOUD          : return "BLINDINGCLOUD";
        case BUFF_ID::BLINDINGCLOUDSTRUCTURE : return "BLINDINGCLOUDSTRUCTURE";
        case BUFF_ID::BUILDINGSCARAB         : return "BUILDINGSCARAB";
        case BUFF_ID::BUILDINGSHIELD         : return "BUILDINGSHIELD";
        case BUFF_ID::BUILDINGSTASIS         : return "BUILDINGSTASIS";
        case BUFF_ID::BURROWCHARGE           : return "BURROWCHARGE";
        case BUFF_ID::BURSTCAPACITORSDAMAGEBUFF :
            return "BURSTCAPACITORSDAMAGEBUFF";
        case BUFF_ID::BYPASSARMORDEBUFFONE   : return "BYPASSARMORDEBUFFONE";
        case BUFF_ID::BYPASSARMORDEBUFFTHREE : return "BYPASSARMORDEBUFFTHREE";
        case BUFF_ID::BYPASSARMORDEBUFFTWO   : return "BYPASSARMORDEBUFFTWO";
        case BUFF_ID::CANNONRADAR            : return "CANNONRADAR";
        case BUFF_ID::CAPRESOURCE            : return "CAPRESOURCE";
        case BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGAS :
            return "CARRYHARVESTABLEVESPENEGEYSERGAS";
        case BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGASPROTOSS :
            return "CARRYHARVESTABLEVESPENEGEYSERGASPROTOSS";
        case BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGASZERG :
            return "CARRYHARVESTABLEVESPENEGEYSERGASZERG";
        case BUFF_ID::CARRYHIGHYIELDMINERALFIELDMINERALS :
            return "CARRYHIGHYIELDMINERALFIELDMINERALS";
        case BUFF_ID::CARRYMINERALFIELDMINERALS :
            return "CARRYMINERALFIELDMINERALS";
        case BUFF_ID::CHANNELSNIPECOMBAT    : return "CHANNELSNIPECOMBAT";
        case BUFF_ID::CHARGEUP              : return "CHARGEUP";
        case BUFF_ID::CHARGING              : return "CHARGING";
        case BUFF_ID::CHRONOBOOSTENERGYCOST : return "CHRONOBOOSTENERGYCOST";
        case BUFF_ID::CLOAKFIELD            : return "CLOAKFIELD";
        case BUFF_ID::CLOAKFIELDEFFECT      : return "CLOAKFIELDEFFECT";
        case BUFF_ID::CLOAKINGFIELDTARGETED : return "CLOAKINGFIELDTARGETED";
        case BUFF_ID::CLOAKUNIT             : return "CLOAKUNIT";
        case BUFF_ID::COLLAPSIBLEROCKTOWERCONJOINEDSEARCH :
            return "COLLAPSIBLEROCKTOWERCONJOINEDSEARCH";
        case BUFF_ID::COLLAPSIBLEROCKTOWERRAMPDIAGONALCONJOINEDSEARCH :
            return "COLLAPSIBLEROCKTOWERRAMPDIAGONALCONJOINEDSEARCH";
        case BUFF_ID::COLLAPSIBLETERRANTOWERCONJOINEDSEARCH :
            return "COLLAPSIBLETERRANTOWERCONJOINEDSEARCH";
        case BUFF_ID::COLLAPSIBLETERRANTOWERRAMPDIAGONALCONJOINEDSEARCH :
            return "COLLAPSIBLETERRANTOWERRAMPDIAGONALCONJOINEDSEARCH";
        case BUFF_ID::COLONYINFESTATION    : return "COLONYINFESTATION";
        case BUFF_ID::CONTAMINATED         : return "CONTAMINATED";
        case BUFF_ID::CORRUPTION           : return "CORRUPTION";
        case BUFF_ID::CORRUPTIONBOMBDAMAGE : return "CORRUPTIONBOMBDAMAGE";
        case BUFF_ID::CORRUPTORGROUNDATTACKDEBUFF :
            return "CORRUPTORGROUNDATTACKDEBUFF";
        case BUFF_ID::CORRUPTORINFESTING     : return "CORRUPTORINFESTING";
        case BUFF_ID::CORSAIRMPDISRUPTIONWEB : return "CORSAIRMPDISRUPTIONWEB";
        case BUFF_ID::DEFENSIVEMATRIX        : return "DEFENSIVEMATRIX";
        case BUFF_ID::DEFILERMPCONSUME       : return "DEFILERMPCONSUME";
        case BUFF_ID::DEFILERMPDARKSWARM     : return "DEFILERMPDARKSWARM";
        case BUFF_ID::DEFILERMPPLAGUE        : return "DEFILERMPPLAGUE";
        case BUFF_ID::DEVOURERMPACIDSPORES   : return "DEVOURERMPACIDSPORES";
        case BUFF_ID::DIGESTERCREEPSPRAYVISION :
            return "DIGESTERCREEPSPRAYVISION";
        case BUFF_ID::DISABLEABILS        : return "DISABLEABILS";
        case BUFF_ID::DISABLEINTERCEPTORS : return "DISABLEINTERCEPTORS";
        case BUFF_ID::DISRUPTORPUSH       : return "DISRUPTORPUSH";
        case BUFF_ID::DOMINATION          : return "DOMINATION";
        case BUFF_ID::DOOMDAMAGEDELAY     : return "DOOMDAMAGEDELAY";
        case BUFF_ID::DUTCHMARAUDERSLOW   : return "DUTCHMARAUDERSLOW";
        case BUFF_ID::EMPBURST            : return "EMPBURST";
        case BUFF_ID::EMPDECLOAK          : return "EMPDECLOAK";
        case BUFF_ID::EMPDRAIN            : return "EMPDRAIN";
        case BUFF_ID::ENGAGE              : return "ENGAGE";
        case BUFF_ID::ETHEREAL            : return "ETHEREAL";
        case BUFF_ID::EXTENDBRIDGEEXTENDINGBRIDGENEWIDE10OUT :
            return "EXTENDBRIDGEEXTENDINGBRIDGENEWIDE10OUT";
        case BUFF_ID::EXTENDBRIDGEEXTENDINGBRIDGENEWIDE12OUT :
            return "EXTENDBRIDGEEXTENDINGBRIDGENEWIDE12OUT";
        case BUFF_ID::EXTENDBRIDGEEXTENDINGBRIDGENEWIDE8OUT :
            return "EXTENDBRIDGEEXTENDINGBRIDGENEWIDE8OUT";
        case BUFF_ID::EXTENDBRIDGEEXTENDINGBRIDGENWWIDE10OUT :
            return "EXTENDBRIDGEEXTENDINGBRIDGENWWIDE10OUT";
        case BUFF_ID::EXTENDBRIDGEEXTENDINGBRIDGENWWIDE12OUT :
            return "EXTENDBRIDGEEXTENDINGBRIDGENWWIDE12OUT";
        case BUFF_ID::EXTENDBRIDGEEXTENDINGBRIDGENWWIDE8OUT :
            return "EXTENDBRIDGEEXTENDINGBRIDGENWWIDE8OUT";
        case BUFF_ID::EYESTALK          : return "EYESTALK";
        case BUFF_ID::FUNGALGROWTH      : return "FUNGALGROWTH";
        case BUFF_ID::GHOSTBLAST        : return "GHOSTBLAST";
        case BUFF_ID::GHOSTCLOAK        : return "GHOSTCLOAK";
        case BUFF_ID::GHOSTHOLDFIRE     : return "GHOSTHOLDFIRE";
        case BUFF_ID::GHOSTHOLDFIREB    : return "GHOSTHOLDFIREB";
        case BUFF_ID::GHOSTSNIPEDOT     : return "GHOSTSNIPEDOT";
        case BUFF_ID::GRAVITONBEAM      : return "GRAVITONBEAM";
        case BUFF_ID::GRAVITONPRISON    : return "GRAVITONPRISON";
        case BUFF_ID::GUARDIANSHIELD    : return "GUARDIANSHIELD";
        case BUFF_ID::HEROICBUFF03      : return "HEROICBUFF03";
        case BUFF_ID::HIDDEN            : return "HIDDEN";
        case BUFF_ID::HYBRIDCZERGYROOTS : return "HYBRIDCZERGYROOTS";
        case BUFF_ID::HYBRIDFZERGYROOTS : return "HYBRIDFZERGYROOTS";
        case BUFF_ID::IMMORTALOVERLOAD  : return "IMMORTALOVERLOAD";
        case BUFF_ID::INCAPACITATED     : return "INCAPACITATED";
        case BUFF_ID::INFESTORDISEASE   : return "INFESTORDISEASE";
        case BUFF_ID::INFESTORENSNARE   : return "INFESTORENSNARE";
        case BUFF_ID::INFESTORENSNAREMAKEPRECURSORREHEIGHTSOURCE :
            return "INFESTORENSNAREMAKEPRECURSORREHEIGHTSOURCE";
        case BUFF_ID::INHIBITORZONEFLYINGTEMPORALFIELD :
            return "INHIBITORZONEFLYINGTEMPORALFIELD";
        case BUFF_ID::INHIBITORZONETEMPORALFIELD :
            return "INHIBITORZONETEMPORALFIELD";
        case BUFF_ID::INVALID               : return "INVALID";
        case BUFF_ID::INVULNERABILITYSHIELD : return "INVULNERABILITYSHIELD";
        case BUFF_ID::IRRADIATE             : return "IRRADIATE";
        case BUFF_ID::ITEMGRAVITYBOMBS      : return "ITEMGRAVITYBOMBS";
        case BUFF_ID::JUMPSTOMPFSTUN        : return "JUMPSTOMPFSTUN";
        case BUFF_ID::JUMPSTOMPSTUN         : return "JUMPSTOMPSTUN";
        case BUFF_ID::KARASSPSISTORM        : return "KARASSPSISTORM";
        case BUFF_ID::LASERSIGHT            : return "LASERSIGHT";
        case BUFF_ID::LASERTARGETING        : return "LASERTARGETING";
        case BUFF_ID::LEECH                 : return "LEECH";
        case BUFF_ID::LEECHDISABLEABILITIES : return "LEECHDISABLEABILITIES";
        case BUFF_ID::LIGHTNINGBOMB         : return "LIGHTNINGBOMB";
        case BUFF_ID::LIGHTOFAIUR           : return "LIGHTOFAIUR";
        case BUFF_ID::LOADOUTSPRAY_TRACKER  : return "LOADOUTSPRAY_TRACKER";
        case BUFF_ID::LOCKDOWNB             : return "LOCKDOWNB";
        case BUFF_ID::LOCKON                : return "LOCKON";
        case BUFF_ID::LURKERHOLDFIRE        : return "LURKERHOLDFIRE";
        case BUFF_ID::LURKERHOLDFIREB       : return "LURKERHOLDFIREB";
        case BUFF_ID::MAXIMUMTHRUST         : return "MAXIMUMTHRUST";
        case BUFF_ID::MEDIVACSPEEDBOOST     : return "MEDIVACSPEEDBOOST";
        case BUFF_ID::MERCAIRDROPDELAY      : return "MERCAIRDROPDELAY";
        case BUFF_ID::MERCENARYCYCLONEMISSILES :
            return "MERCENARYCYCLONEMISSILES";
        case BUFF_ID::MERCENARYSENSORDISH : return "MERCENARYSENSORDISH";
        case BUFF_ID::MERCENARYSHIELD     : return "MERCENARYSHIELD";
        case BUFF_ID::MERCGROUNDDROP      : return "MERCGROUNDDROP";
        case BUFF_ID::MERCGROUNDDROPDELAY : return "MERCGROUNDDROPDELAY";
        case BUFF_ID::MINDBLASTSTUN       : return "MINDBLASTSTUN";
        case BUFF_ID::MINDCONTROL         : return "MINDCONTROL";
        case BUFF_ID::MINEDRONECOUNTDOWN  : return "MINEDRONECOUNTDOWN";
        case BUFF_ID::MINEDRONEDOT        : return "MINEDRONEDOT";
        case BUFF_ID::MOTHERSHIPCOREENERGIZEVISUAL :
            return "MOTHERSHIPCOREENERGIZEVISUAL";
        case BUFF_ID::MOTHERSHIPSTASIS       : return "MOTHERSHIPSTASIS";
        case BUFF_ID::MOTHERSHIPSTASISCASTER : return "MOTHERSHIPSTASISCASTER";
        case BUFF_ID::NAPALM                 : return "NAPALM";
        case BUFF_ID::NEURALPARASITE         : return "NEURALPARASITE";
        case BUFF_ID::NEURALPARASITECHILDREN : return "NEURALPARASITECHILDREN";
        case BUFF_ID::NEURALPARASITEWAIT     : return "NEURALPARASITEWAIT";
        case BUFF_ID::NEXUSINVULNERABILITY   : return "NEXUSINVULNERABILITY";
        case BUFF_ID::NEXUSPHASESHIFT        : return "NEXUSPHASESHIFT";
        case BUFF_ID::NEXUSSHIELDOVERCHARGE  : return "NEXUSSHIELDOVERCHARGE";
        case BUFF_ID::NEXUSSHIELDRECHARGEONPYLONBEHAVIOR :
            return "NEXUSSHIELDRECHARGEONPYLONBEHAVIOR";
        case BUFF_ID::NEXUSSHIELDRECHARGEONPYLONBEHAVIORSECONDARYONTARGET :
            return "NEXUSSHIELDRECHARGEONPYLONBEHAVIORSECONDARYONTARGET";
        case BUFF_ID::NULLFIELD : return "NULLFIELD";
        case BUFF_ID::NYDUSWORMLAVAINSTANTDEATH :
            return "NYDUSWORMLAVAINSTANTDEATH";
        case BUFF_ID::ORACLECLOAKFIELD       : return "ORACLECLOAKFIELD";
        case BUFF_ID::ORACLECLOAKFIELDEFFECT : return "ORACLECLOAKFIELDEFFECT";
        case BUFF_ID::ORACLEPHASESHIFT       : return "ORACLEPHASESHIFT";
        case BUFF_ID::ORACLEREVELATION       : return "ORACLEREVELATION";
        case BUFF_ID::ORACLESTASISTRAPTARGET : return "ORACLESTASISTRAPTARGET";
        case BUFF_ID::ORACLEWEAPON           : return "ORACLEWEAPON";
        case BUFF_ID::OVERCHARGE             : return "OVERCHARGE";
        case BUFF_ID::OVERCHARGEDAMAGE       : return "OVERCHARGEDAMAGE";
        case BUFF_ID::OVERCHARGESPEEDBOOST   : return "OVERCHARGESPEEDBOOST";
        case BUFF_ID::PARASITICBOMB          : return "PARASITICBOMB";
        case BUFF_ID::PARASITICBOMBDELAYTIMEDLIFE :
            return "PARASITICBOMBDELAYTIMEDLIFE";
        case BUFF_ID::PARASITICBOMBSECONDARYUNITSEARCH :
            return "PARASITICBOMBSECONDARYUNITSEARCH";
        case BUFF_ID::PARASITICBOMBUNITKU  : return "PARASITICBOMBUNITKU";
        case BUFF_ID::PERMANENTLYCLOAKED   : return "PERMANENTLYCLOAKED";
        case BUFF_ID::PERSONALCLOAKINGFREE : return "PERSONALCLOAKINGFREE";
        case BUFF_ID::PHASESHIELD          : return "PHASESHIELD";
        case BUFF_ID::POWERUSERWARPABLE    : return "POWERUSERWARPABLE";
        case BUFF_ID::PREDATORCLOAKING     : return "PREDATORCLOAKING";
        case BUFF_ID::PROTECTIVEBARRIER    : return "PROTECTIVEBARRIER";
        case BUFF_ID::PSIDISRUPTION        : return "PSIDISRUPTION";
        case BUFF_ID::PSIONICSHOCKWAVEHEIGHTANDSTUN :
            return "PSIONICSHOCKWAVEHEIGHTANDSTUN";
        case BUFF_ID::PSISTORM             : return "PSISTORM";
        case BUFF_ID::PSYTROUSOXIDE        : return "PSYTROUSOXIDE";
        case BUFF_ID::PURIFICATIONNOVA     : return "PURIFICATIONNOVA";
        case BUFF_ID::PURIFICATIONNOVAPOST : return "PURIFICATIONNOVAPOST";
        case BUFF_ID::PURIFIERPLANETCRACKERCHARGE :
            return "PURIFIERPLANETCRACKERCHARGE";
        case BUFF_ID::PURIFY                : return "PURIFY";
        case BUFF_ID::QUEENKNOCKDOWN        : return "QUEENKNOCKDOWN";
        case BUFF_ID::QUEENMPENSNARE        : return "QUEENMPENSNARE";
        case BUFF_ID::QUEENSPAWNLARVATIMER  : return "QUEENSPAWNLARVATIMER";
        case BUFF_ID::RADAR25               : return "RADAR25";
        case BUFF_ID::RAVENSCRAMBLERMISSILE : return "RAVENSCRAMBLERMISSILE";
        case BUFF_ID::RAVENSCRAMBLERMISSILECARRIER :
            return "RAVENSCRAMBLERMISSILECARRIER";
        case BUFF_ID::RAVENSHREDDERMISSILEARMORREDUCTION :
            return "RAVENSHREDDERMISSILEARMORREDUCTION";
        case BUFF_ID::RAVENSHREDDERMISSILEARMORREDUCTIONUISUBTRUCT :
            return "RAVENSHREDDERMISSILEARMORREDUCTIONUISUBTRUCT";
        case BUFF_ID::RAVENSHREDDERMISSILETIMEOUT :
            return "RAVENSHREDDERMISSILETIMEOUT";
        case BUFF_ID::RAVENSHREDDERMISSILETINT :
            return "RAVENSHREDDERMISSILETINT";
        case BUFF_ID::RAYNORMISSILETIMEDLIFE : return "RAYNORMISSILETIMEDLIFE";
        case BUFF_ID::RAYNORTIMEBOMBMISSILE  : return "RAYNORTIMEBOMBMISSILE";
        case BUFF_ID::RAYNORTIMEBOMBUNIT     : return "RAYNORTIMEBOMBUNIT";
        case BUFF_ID::RELEASEINTERCEPTORSBEACON :
            return "RELEASEINTERCEPTORSBEACON";
        case BUFF_ID::RELEASEINTERCEPTORSCOOLDOWN :
            return "RELEASEINTERCEPTORSCOOLDOWN";
        case BUFF_ID::RELEASEINTERCEPTORSTIMEDLIFEWARNING :
            return "RELEASEINTERCEPTORSTIMEDLIFEWARNING";
        case BUFF_ID::RELEASEINTERCEPTORSWANDERDELAY :
            return "RELEASEINTERCEPTORSWANDERDELAY";
        case BUFF_ID::RESCUE : return "RESCUE";
        case BUFF_ID::RESONATINGGLAIVESPHASESHIFT :
            return "RESONATINGGLAIVESPHASESHIFT";
        case BUFF_ID::RESOURCESTUN       : return "RESOURCESTUN";
        case BUFF_ID::RESTORESHIELDS     : return "RESTORESHIELDS";
        case BUFF_ID::ROUGHTERRAINSEARCH : return "ROUGHTERRAINSEARCH";
        case BUFF_ID::ROUGHTERRAINSLOW   : return "ROUGHTERRAINSLOW";
        case BUFF_ID::SCIENCEVESSELCLOAKFIELD :
            return "SCIENCEVESSELCLOAKFIELD";
        case BUFF_ID::SCRYER               : return "SCRYER";
        case BUFF_ID::SCRYERFRIENDLY       : return "SCRYERFRIENDLY";
        case BUFF_ID::SEEKERMISSILE        : return "SEEKERMISSILE";
        case BUFF_ID::SEEKERMISSILETIMEOUT : return "SEEKERMISSILETIMEOUT";
        case BUFF_ID::SELFREPAIR           : return "SELFREPAIR";
        case BUFF_ID::SHADOWCLONE          : return "SHADOWCLONE";
        case BUFF_ID::SHEEPBUSY            : return "SHEEPBUSY";
        case BUFF_ID::SHIFTDELAY           : return "SHIFTDELAY";
        case BUFF_ID::SHREDDERSWARMDAMAGEAPPLY :
            return "SHREDDERSWARMDAMAGEAPPLY";
        case BUFF_ID::SLAYNELEMENTALGRABSTUN : return "SLAYNELEMENTALGRABSTUN";
        case BUFF_ID::SLIMED                 : return "SLIMED";
        case BUFF_ID::SLOW                   : return "SLOW";
        case BUFF_ID::SPECTRECLOAKING        : return "SPECTRECLOAKING";
        case BUFF_ID::SPECTRECLOAKINGFREE    : return "SPECTRECLOAKINGFREE";
        case BUFF_ID::SPECTREHOLDFIRE        : return "SPECTREHOLDFIRE";
        case BUFF_ID::SPECTREHOLDFIREB       : return "SPECTREHOLDFIREB";
        case BUFF_ID::SPECTRELOCKDOWNB       : return "SPECTRELOCKDOWNB";
        case BUFF_ID::SPECTRESHIELD          : return "SPECTRESHIELD";
        case BUFF_ID::SPORECANNONMISSILE     : return "SPORECANNONMISSILE";
        case BUFF_ID::SS_BATTLECRUISERCOLLISIONCHECK :
            return "SS_BATTLECRUISERCOLLISIONCHECK";
        case BUFF_ID::SS_BATTLECRUISERHUNTERSEEKERTIMEOUT :
            return "SS_BATTLECRUISERHUNTERSEEKERTIMEOUT";
        case BUFF_ID::SS_BATTLECRUISERMISSILELAUNCHER :
            return "SS_BATTLECRUISERMISSILELAUNCHER";
        case BUFF_ID::SS_CARRIERBOSSCOLLISIONCHECK :
            return "SS_CARRIERBOSSCOLLISIONCHECK";
        case BUFF_ID::SS_CARRIERCOLLISIONCHECK :
            return "SS_CARRIERCOLLISIONCHECK";
        case BUFF_ID::SS_CORRUPTORCOLLISIONCHECK :
            return "SS_CORRUPTORCOLLISIONCHECK";
        case BUFF_ID::SS_CORRUPTORMISSILETARGETCHECK :
            return "SS_CORRUPTORMISSILETARGETCHECK";
        case BUFF_ID::SS_FIGHTERBOMBMISSILEDEATH :
            return "SS_FIGHTERBOMBMISSILEDEATH";
        case BUFF_ID::SS_FIGHTERDRONEDAMAGERESPONSE :
            return "SS_FIGHTERDRONEDAMAGERESPONSE";
        case BUFF_ID::SS_INTERCEPTORCOLLISIONCHECK :
            return "SS_INTERCEPTORCOLLISIONCHECK";
        case BUFF_ID::SS_INVULNERABLE : return "SS_INVULNERABLE";
        case BUFF_ID::SS_LEVIATHANBOMBCOLLISIONCHECK :
            return "SS_LEVIATHANBOMBCOLLISIONCHECK";
        case BUFF_ID::SS_LEVIATHANBOMBEXPLODETIMER :
            return "SS_LEVIATHANBOMBEXPLODETIMER";
        case BUFF_ID::SS_LEVIATHANBOMBMISSILETARGETCHECK :
            return "SS_LEVIATHANBOMBMISSILETARGETCHECK";
        case BUFF_ID::SS_LEVIATHANCOLLISIONCHECK :
            return "SS_LEVIATHANCOLLISIONCHECK";
        case BUFF_ID::SS_LEVIATHANTENTACLEMISSILESCANSWAPDELAY :
            return "SS_LEVIATHANTENTACLEMISSILESCANSWAPDELAY";
        case BUFF_ID::SS_LEVIATHANTENTACLEMISSILETARGETCHECK :
            return "SS_LEVIATHANTENTACLEMISSILETARGETCHECK";
        case BUFF_ID::SS_LEVIATHANTENTACLEMISSILETARGETCHECKINVERTED :
            return "SS_LEVIATHANTENTACLEMISSILETARGETCHECKINVERTED";
        case BUFF_ID::SS_LEVIATHANTENTACLETARGETDEATHDELAY :
            return "SS_LEVIATHANTENTACLETARGETDEATHDELAY";
        case BUFF_ID::SS_LIGHTNINGPROJECTOR : return "SS_LIGHTNINGPROJECTOR";
        case BUFF_ID::SS_LIGHTNINGPROJECTORCOLLISIONCHECK :
            return "SS_LIGHTNINGPROJECTORCOLLISIONCHECK";
        case BUFF_ID::SS_MAXACCELERATION    : return "SS_MAXACCELERATION";
        case BUFF_ID::SS_MAXSPEED           : return "SS_MAXSPEED";
        case BUFF_ID::SS_MISSILETARGETCHECK : return "SS_MISSILETARGETCHECK";
        case BUFF_ID::SS_MISSILETARGETCHECKVIKING :
            return "SS_MISSILETARGETCHECKVIKING";
        case BUFF_ID::SS_MISSILETARGETCHECKVIKINGDRONE :
            return "SS_MISSILETARGETCHECKVIKINGDRONE";
        case BUFF_ID::SS_MISSILETARGETCHECKVIKINGSTRONG1 :
            return "SS_MISSILETARGETCHECKVIKINGSTRONG1";
        case BUFF_ID::SS_MISSILETARGETCHECKVIKINGSTRONG2 :
            return "SS_MISSILETARGETCHECKVIKINGSTRONG2";
        case BUFF_ID::SS_MISSILETIMEOUT : return "SS_MISSILETIMEOUT";
        case BUFF_ID::SS_PHOENIXCOLLISIONCHECK :
            return "SS_PHOENIXCOLLISIONCHECK";
        case BUFF_ID::SS_POWERUPDIAGONAL1   : return "SS_POWERUPDIAGONAL1";
        case BUFF_ID::SS_POWERUPDIAGONAL2   : return "SS_POWERUPDIAGONAL2";
        case BUFF_ID::SS_POWERUPHEALTH1     : return "SS_POWERUPHEALTH1";
        case BUFF_ID::SS_POWERUPHEALTH2     : return "SS_POWERUPHEALTH2";
        case BUFF_ID::SS_POWERUPMORPHTOBOMB : return "SS_POWERUPMORPHTOBOMB";
        case BUFF_ID::SS_POWERUPMORPHTOHEALTH :
            return "SS_POWERUPMORPHTOHEALTH";
        case BUFF_ID::SS_POWERUPMORPHTOSIDEMISSILES :
            return "SS_POWERUPMORPHTOSIDEMISSILES";
        case BUFF_ID::SS_POWERUPMORPHTOSTRONGERMISSILES :
            return "SS_POWERUPMORPHTOSTRONGERMISSILES";
        case BUFF_ID::SS_POWERUPSTRONG : return "SS_POWERUPSTRONG";
        case BUFF_ID::SS_SCIENCEVESSELCOLLISIONCHECK :
            return "SS_SCIENCEVESSELCOLLISIONCHECK";
        case BUFF_ID::SS_SCOURGECOLLISIONCHECK :
            return "SS_SCOURGECOLLISIONCHECK";
        case BUFF_ID::SS_SCOURGEDEATH : return "SS_SCOURGEDEATH";
        case BUFF_ID::SS_SCOURGEMISSILETARGETCHECK :
            return "SS_SCOURGEMISSILETARGETCHECK";
        case BUFF_ID::SS_SCOUTCOLLISIONCHECK : return "SS_SCOUTCOLLISIONCHECK";
        case BUFF_ID::SS_STRONGERENEMYBUFF   : return "SS_STRONGERENEMYBUFF";
        case BUFF_ID::SS_SWARMGUARDIANCOLLISIONCHECK :
            return "SS_SWARMGUARDIANCOLLISIONCHECK";
        case BUFF_ID::SS_TERRATRONARMMISSILETARGETCHECK :
            return "SS_TERRATRONARMMISSILETARGETCHECK";
        case BUFF_ID::SS_TERRATRONCOLLISIONCHECK :
            return "SS_TERRATRONCOLLISIONCHECK";
        case BUFF_ID::SS_TERRATRONMISSILELAUNCHER :
            return "SS_TERRATRONMISSILELAUNCHER";
        case BUFF_ID::SS_TERRATRONMISSILESPINNERCOLLISIONCHECK :
            return "SS_TERRATRONMISSILESPINNERCOLLISIONCHECK";
        case BUFF_ID::SS_TERRATRONMISSILESPINNERMISSILELAUNCHER :
            return "SS_TERRATRONMISSILESPINNERMISSILELAUNCHER";
        case BUFF_ID::SS_TERRATRONSAWCOLLISIONCHECK :
            return "SS_TERRATRONSAWCOLLISIONCHECK";
        case BUFF_ID::SS_TERRATRONSTUN : return "SS_TERRATRONSTUN";
        case BUFF_ID::SS_VIKINGRESPAWN : return "SS_VIKINGRESPAWN";
        case BUFF_ID::SS_WRAITHCOLLISIONCHECK :
            return "SS_WRAITHCOLLISIONCHECK";
        case BUFF_ID::STASIS           : return "STASIS";
        case BUFF_ID::STIMPACK         : return "STIMPACK";
        case BUFF_ID::STIMPACKMARAUDER : return "STIMPACKMARAUDER";
        case BUFF_ID::STUNROUNDINITIALBEHAVIOR :
            return "STUNROUNDINITIALBEHAVIOR";
        case BUFF_ID::SUPPLYDROP  : return "SUPPLYDROP";
        case BUFF_ID::TAKENDAMAGE : return "TAKENDAMAGE";
        case BUFF_ID::TAUNTB      : return "TAUNTB";
        case BUFF_ID::TEMPESTDISRUPTIONBLASTSTUNBEHAVIOR :
            return "TEMPESTDISRUPTIONBLASTSTUNBEHAVIOR";
        case BUFF_ID::TEMPORALFIELD    : return "TEMPORALFIELD";
        case BUFF_ID::TEMPORALRIFTUNIT : return "TEMPORALRIFTUNIT";
        case BUFF_ID::TESTATTRIBUTE    : return "TESTATTRIBUTE";
        case BUFF_ID::TESTVETERANCY    : return "TESTVETERANCY";
        case BUFF_ID::TIMESCALECONVERSIONBEHAVIOR :
            return "TIMESCALECONVERSIONBEHAVIOR";
        case BUFF_ID::TIMESTOPSTUN           : return "TIMESTOPSTUN";
        case BUFF_ID::TIMEWARPPRODUCTION     : return "TIMEWARPPRODUCTION";
        case BUFF_ID::TRANSFUSION            : return "TRANSFUSION";
        case BUFF_ID::TRANSIENTMORPH         : return "TRANSIENTMORPH";
        case BUFF_ID::TYCHUSCOMMANDOSTIMPACK : return "TYCHUSCOMMANDOSTIMPACK";
        case BUFF_ID::ULTRASONICPULSESTUN    : return "ULTRASONICPULSESTUN";
        case BUFF_ID::VIPERCONSUMESTRUCTURE  : return "VIPERCONSUMESTRUCTURE";
        case BUFF_ID::VIRALPLASMA            : return "VIRALPLASMA";
        case BUFF_ID::VOIDMPIMMORTALREVIVESUPRESSED :
            return "VOIDMPIMMORTALREVIVESUPRESSED";
        case BUFF_ID::VOIDRAYSWARMDAMAGEBOOST :
            return "VOIDRAYSWARMDAMAGEBOOST";
        case BUFF_ID::VOIDSIPHON          : return "VOIDSIPHON";
        case BUFF_ID::VOODOOLOCKDOWN      : return "VOODOOLOCKDOWN";
        case BUFF_ID::VOODOOSHIELD        : return "VOODOOSHIELD";
        case BUFF_ID::VORTEXBEHAVIOR      : return "VORTEXBEHAVIOR";
        case BUFF_ID::VORTEXBEHAVIORENEMY : return "VORTEXBEHAVIORENEMY";
        case BUFF_ID::VORTEXBEHAVIORERADICATOR :
            return "VORTEXBEHAVIORERADICATOR";
        case BUFF_ID::WATER                : return "WATER";
        case BUFF_ID::WRAITHCLOAK          : return "WRAITHCLOAK";
        case BUFF_ID::ZERATULSTUN          : return "ZERATULSTUN";
        case BUFF_ID::_250MMSTRIKECANNONS  : return "_250MMSTRIKECANNONS";
        case BUFF_ID::_330MMBARRAGECANNONS : return "_330MMBARRAGECANNONS";
        default                            : return "UNKNOWN";
    }
}

}