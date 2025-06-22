#include "../../include/utils/constant.hpp"
#include <string>

using namespace std;

namespace Constants {
    // Transport mode factors
    const double TRAIN_SPEED = 80.0; // km/h
    const double BUS_SPEED = 40.0;
    const double TAXI_SPEED = 60.0;
    
    // Cost multipliers (per km)
    const double TRAIN_COST = 500.0; // Rp/km
    const double BUS_COST = 300.0;
    const double TAXI_COST = 4500.0;
    
    // Time penalties (minutes)
    const int TRANSFER_PENALTY = 15;
    const int WAITING_TIME = 10;
    
    // Algorithm parameters
    const int MAX_PATH_LENGTH = 20;
    const int MAX_TRANSFERS = 3;
    
    // File paths
    const string DEFAULT_LOCATIONS_FILE = "data/location.csv";
    const string DEFAULT_ROUTES_FILE = "data/route.csv";
    const string PREFERENCES_FILE = "data/preference.json";
    
    // Display constants
    const int CONSOLE_WIDTH = 80;
    const string DIVIDER = "========================================";
}