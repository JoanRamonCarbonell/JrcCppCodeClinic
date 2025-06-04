#pragma once

#include "IWeather_stats.h"
#include <vector>
#include <string>

namespace weather_stats
{

class Weather_stats : public IWeather_stats
{
public:
    Weather_stats() { run(); }
    void run() override;

private:
    void getDates();
    void readDb();
    float calculate();

    std::string m_starting_date;
    std::string m_ending_date;
    std::vector<std::pair<double, double>> m_weather_data;

};
} // weather_stats