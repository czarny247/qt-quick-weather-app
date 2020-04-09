#pragma once

namespace backend
{

struct GPSCoordinates
{

GPSCoordinates(double latitude, double longitude)
: latitude_(latitude)
, longitude_(longitude)
{
}

double latitude_ {0.00000};
double longitude_ {0.00000};

};

}