module;
// Avoiding use of "thread_local" as that isn't supported in older versions of
// Xcode.
#if defined( __clang__ ) || defined( __GNUC__ )
    #define TLS_OBJECT __thread
#else
    #define TLS_OBJECT __declspec ( thread )
#endif

#include <random>
// Avoiding use of "thread_local" as that isn't supported in older versions of
// Xcode.

export module math;
using namespace std;

struct RandomGenerator
{
    RandomGenerator ( )
        : mt ( rd( ) ) { }

    random_device rd;
    mt19937       mt;
};

static mt19937 &GetGenerator ( ) {
    TLS_OBJECT RandomGenerator *generator;
    if ( !generator )
        generator = new RandomGenerator( );
    return generator->mt;
}

float GetRandomScalar ( ) {
    static uniform_real_distribution<float> dist ( -1.0F, 1.0F );
    return dist ( GetGenerator( ) );
}

float GetRandomFraction ( ) {
    static uniform_real_distribution<float> dist ( 0.0F, 1.0F );
    return dist ( GetGenerator( ) );
}

int GetRandomInteger ( const int min, const int max ) {
    uniform_int_distribution<int> dist ( min, max );
    return dist ( GetGenerator( ) );
}
