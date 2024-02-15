// cm challenge ( previously 6cm challenge ) : aimslut
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <unordered_map>

// rounding calc
float round( float var ) {
    float value = ( int ) ( var * 100 + .5 );
    return ( float ) value / 100;
}

// struct for game yaw values
struct GameYaw {
    std::string game;
    double yaw;
};

// game yaw values ( unordered map is faster than a vector )
const std::unordered_map<std::string, double> GAME_YAWS = {
        { "source",       0.022 },
        { "apex",         0.022 },
        { "quake",        0.022 },
        { "cs",           0.022 },
        { "q3a",          0.022 },
        { "bf5",          0.022 },
        { "battlefield5", 0.022 },
        { "ut",           0.596 },
        { "d2",           0.0066 },
        { "destiny2",     0.0066 },
        { "ow",           0.0066 },
        { "overwatch",    0.0066 },
        { "fn",           0.5715 },
        { "fortnite",     0.5715 },
        { "ql",           0.02105 },
        { "quakelive",    0.02105 },
        { "pubg",         2.22222 },
        { "ow2",          0.006666 },
        { "overwatch2",   0.006666 },
        { "doom",         0.0439453125 },
        { "qcde",         0.0439453125 },
        { "val",          0.051097900390625 },
        { "valorant",     0.051097900390625 },
        { "siege",        0.00572957795130823 },
        { "r6",           0.00572957795130823 },
        { "reflex",       0.00572957795130823 }
};

// determine game and return the corresponding yaw
double determine_game( const std::string& game ) {
    std::string game_lower = game; // make a copy of the game string
    std::transform( game_lower.begin(), game_lower.end(), game_lower.begin(), ::tolower ); // convert to lowercase

    auto it = GAME_YAWS.find(game_lower); // search case-insensitivity

    if ( it != GAME_YAWS.end() ) {
        return it->second;
    } else {
        // handle direct yaw input ( more robust conversion )
        try {
            // allow scientific notation ( 1e-4, etc. )
            return std::stod( game );
        } catch ( const std::invalid_argument& ) {
            std::cerr << "Invalid game or yaw value." << std::endl;
            return std::numeric_limits<double>::quiet_NaN(); // default to NaN
        }
    }
}

// cm calc with custom range
void sens_calc( int dpi, double yaw, double min_cm, double max_cm ) {
    // ensure min_cm is smaller than max_cm
    if ( min_cm >= max_cm ) {
        std::cerr << "invalid range: minimum cm must be less than maximum cm." << std::endl;
        return;
    }

    // calculate step size based on range and desired detail
    double step_size = ( max_cm - min_cm ) >= 20 ? 2.0 :
                       ( max_cm - min_cm ) >= 10 ? 1.0 : 0.5;

    for ( double cm = max_cm; cm >= min_cm; cm -= step_size ) {
        double sens = ( 360.0 / ( cm / 2.54 * dpi )) / yaw;
        std::cout << std::fixed << std::setprecision( 2 )
                  << " " << sens << "\t = " << cm << "cm" << std::endl;
    }
}

int main() {
    int dpi;
    std::string game;
    double game_yaw{}, min_cm, max_cm;

    std::cout << "input dpi: ";
    std::cin >> dpi;
    std::cout << "input game ( or yaw ): ";
    std::cin >> game;
    std::cout << "input minimum cm: ";
    std::cin >> min_cm;
    std::cout << "input maximum cm: ";
    std::cin >> max_cm;

    game_yaw = determine_game( game );
    if ( std::isnan( game_yaw )) {
        return 1; // indicate an error occurred
    }
    sens_calc( dpi, game_yaw, min_cm, max_cm );

    system( "pause" );
    return 0;
}
