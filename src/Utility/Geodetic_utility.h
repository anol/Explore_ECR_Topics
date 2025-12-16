//
// Created by aeols on 2025-01-23.
//

#ifndef TARGET_GPS_CAN_NODE_GEODETIC_UTILITY_H
#define TARGET_GPS_CAN_NODE_GEODETIC_UTILITY_H

namespace Utility {

    class Geodetic_utility {
    public:
        static void WGS84_to_UTM(double latitude, double longitude, double &utmEast, double &utmNorth);
    };

} // Utility

#endif //TARGET_GPS_CAN_NODE_GEODETIC_UTILITY_H
