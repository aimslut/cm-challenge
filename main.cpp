// 100 - 6cm challenge : aimslut
#include <iostream>

float round(float var) {
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

void sens_calc(){
    const int dpi = 1600;
    const float yaw = 0.006666;

    for (float cm = 100.0f; cm > 6.0f; cm -= (cm >= 24.0f ? 2.0f : cm >= 12.0f ? 1.0f : 0.5f)) {
        float sens = ((360 / (cm / 2.54 * dpi)) / yaw);
        std::cout << " " << round(sens) << "\t = " << cm << "cm" << std::endl;
    }
}

int main() {
    sens_calc();
    return 0;
}

