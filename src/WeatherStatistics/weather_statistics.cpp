#include "WeatherStatistics/weather_statistics.h"
#include <iostream>
#include <fstream>

namespace weather_stats
{
using namespace std;

void Weather_stats::run() {
    // param1 -> starting date and time
    // param2 -> ending date and time
    // return -> coefficient of the barometric pressure

    cout << "Running : Weather Statistics" << endl;

    getDates();

    cout << "Slope coefficent: " << calculate() << endl;


    cout << "End : Weather Statistics" << endl;
}

void Weather_stats::getDates() {
    cout << "Enter the starting date :" << endl;
    cin >> m_starting_date;
    cout << "Enter the starting date :" << endl;
    cin >> m_ending_date;
}

void Weather_stats::readDb() {

    // Open file
    std::string data_file{"data1.txt"};
    std::fstream data(data_file);

    // if (!data) {
    //     std::cerr << "Could not open file.";
    //     return 1;
    // }

    std::string line;
    // while (std::getline(data, line)) {
    //     std::istringstream iss(line);
    //     std::string date;
    //     std::string time;
    //     std::string a;

    //     iss >> date >> time >> a;
    //     // parse data from line
    //     // considering 
    // }

    // Read data and dump it in vector
}

float Weather_stats::calculate() {
    // Slope coefficient Calculation
    return 0.0;
}

}   // weather_stats