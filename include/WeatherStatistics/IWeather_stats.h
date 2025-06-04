#pragma once

namespace weather_stats
{

class IWeather_stats
{
public:
    virtual void run() = 0;
    virtual ~IWeather_stats() = default;
};
} // weather_stats