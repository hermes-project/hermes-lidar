//
// Created by tic-tac on 4/12/18.
//

#ifndef HERMES_LIDAR_LIDAR_H
#define HERMES_LIDAR_LIDAR_H

#include <iostream>
#include <vector>

#include "RPLidar/sdk/include/rplidar.h"

using namespace rp::standalone::rplidar;

class Lidar {

    RPlidarDriver *driver;
    std::vector<rplidar_response_measurement_node_t> node;

public:
    Lidar();
    ~Lidar();

    /*
     * Connection
     */
    bool connect(const char* path, int baudrate);
    void disconnect();

    /*
     * Infos
     */
    void printDeviceHealth();
    void printDeviceInfo();

    /*
     * Scans
     */


};


#endif //HERMES_LIDAR_LIDAR_H
