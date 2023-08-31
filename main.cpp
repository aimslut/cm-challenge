// 100 - 6cm challenge : aimslut
#include <iostream>
#include <algorithm>
#include <vector>

// rounding calc
float round(float var) {
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

// struct for game yaw values
struct GameYaw {
    std::string game;
    double yaw;
};

// game yaw values
const std::vector<GameYaw> GAME_YAWS = {
        {"source", 0.022},
        {"apex", 0.022},
        {"quake", 0.022},
        {"cs", 0.022},
        {"q3a", 0.022},
        {"bf5", 0.022},
        {"battlefield5", 0.022},
        {"d2", 0.0066},
        {"destiny2", 0.0066},
        {"ow", 0.0066},
        {"overwatch", 0.0066},
        {"fn", 0.5715},
        {"fortnite", 0.5715},
        {"ql", 0.02105},
        {"quakelive", 0.02105},
        {"pubg", 2.22222},
        {"ow2", 0.006666},
        {"overwatch2", 0.006666},
        {"doom", 0.0439453125},
        {"qcde", 0.0439453125},
        {"val", 0.051097900390625},
        {"valorant", 0.051097900390625},
        {"siege", 0.00572957795130823},
        {"r6", 0.00572957795130823},
        {"reflex", 0.00572957795130823},
        {"ut", 0.596}
};

// determine game and return the corresponding yaw
double determine_game(const std::string& game) {
    auto identified_game = std::find_if(GAME_YAWS.begin(), GAME_YAWS.end(), [&](const GameYaw& game_yaw) {
        return game_yaw.game == game;
    });

    if (identified_game != GAME_YAWS.end()) {
        return identified_game->yaw;
    } else {
        // Convert the original string to a double (you might want to use a proper conversion method)
        try {
            return std::stod(game);
        } catch (const std::invalid_argument&) {
            // Conversion failed, return a default value
            return 0.0;
        }
    }
}

// 100 - 6cm calc
void sens_calc(int dpi, double yaw){
    for (double cm = 100; cm > 6; cm -= (cm >= 24 ? 2 : cm >= 12 ? 1 : 0.5)) {
        double sens = ((360 / (cm / 2.54 * dpi)) / yaw);
        std::cout << " " << round(sens) << "\t = " << cm << "cm" << std::endl;
    }
}

int main() {
    int dpi;
    double game_yaw{};

    std::string game;
    std::cout << "input dpi: ";
    std::cin >> dpi;
    std::cout << "input game ( or yaw ): ";
    std::cin >> game;
    game_yaw = determine_game( game );
    sens_calc(dpi, game_yaw);

    system("pause");
    return 0;
}
