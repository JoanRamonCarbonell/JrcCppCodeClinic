#include <iostream>
#include "WeatherStatistics/weather_statistics.h"
#include "EightQueens/EightQueens.h"

#include <memory>

int main() {
    std::cout << "C++ : Code Clinic" << std::endl;
//    std::unique_ptr<weather_stats::Weather_stats> weather_stats = std::make_unique<weather_stats::Weather_stats>();
    std::unique_ptr<eight_queens::EightQueens> eight_queens = std::make_unique<eight_queens::EightQueens>();

    return 0;
}