//
// Created by aeols on 2025-01-23.
//

#include <cmath>
#include "Geodetic_utility.h"

namespace Utility {

    const double PI = 3.14159265358979323846;
    const double WGS84_A = 6378137.0;  // Halvaksen til WGS84
    const double WGS84_F = 1.0 / 298.257223563;  // Flattening til WGS84
    const double WGS84_E2 = 2 * WGS84_F - WGS84_F * WGS84_F;  // Eccentricity

// Soneinnstillinger for UTM
    const int UTM_ZONE = 32;  // Eksempel på sone 33
    const double UTM_ZONE_OFFSET = 500000.0;  // Øst-verdi for UTM
    const double UTM_SCALE_FACTOR = 0.9996;   // Skaleringsfaktor for UTM

// Funksjoner for å konvertere fra WGS84 til UTM
    double degToRad(double deg) {
        return deg * PI / 180.0;
    }

    void Geodetic_utility::WGS84_to_UTM(double latitude, double longitude, double &utmEast, double &utmNorth) {
        double latRad = degToRad(latitude);  // Breddegrad i radianer
        double lonRad = degToRad(longitude); // Lengdegrad i radianer

        // Beregn de nødvendige parameterne
        double N = WGS84_A / sqrt(1.0 - WGS84_E2 * sin(latRad) * sin(latRad));  // Krumningsradius
        double T = tan(latRad) * tan(latRad);
        double C = WGS84_E2 * cos(latRad) * cos(latRad);
        double A = cos(latRad) * (lonRad - degToRad((UTM_ZONE - 1) * 6 - 180 + 3));  // Sone-senteret

        // Beregn koordinatene
        double M = WGS84_A * ((1 - WGS84_E2 / 4 - 3 * WGS84_E2 * WGS84_E2 / 64 - 5 * WGS84_E2 * WGS84_E2 * WGS84_E2 / 256) * latRad
                              - (3 * WGS84_E2 / 8 + 3 * WGS84_E2 * WGS84_E2 / 32 + 45 * WGS84_E2 * WGS84_E2 * WGS84_E2 / 1024) *
                                sin(2 * latRad)
                              + (15 * WGS84_E2 * WGS84_E2 / 256 + 45 * WGS84_E2 * WGS84_E2 * WGS84_E2 / 1024) * sin(4 * latRad)
                              - (35 * WGS84_E2 * WGS84_E2 * WGS84_E2 / 3072) * sin(6 * latRad));

        // UTM Easting (X)
        utmEast = UTM_ZONE_OFFSET + UTM_SCALE_FACTOR * N * (A + (1 - T + C) * A * A * A / 6.0
                                                            +
                                                            (5 - 18 * T + T * T + 72 * C - 58 * WGS84_E2) * A * A * A * A * A /
                                                            120.0);

        // UTM Northing (Y)
        utmNorth = UTM_SCALE_FACTOR * (M + N * tan(latRad) * (A * A / 2.0
                                                              + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24.0
                                                              +
                                                              (61 - 58 * T + T * T + 600 * C - 330 * WGS84_E2) * A * A * A * A * A *
                                                              A /
                                                              720.0));

        // Hvis vi er i den sørlige halvkule, legg til 10 000 000 for å unngå negative verdier
        if (latitude < 0) {
            utmNorth += 10000000.0;
        }
    }
} // Utility
