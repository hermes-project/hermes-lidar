//
// Created by tic-tac on 4/12/18.
//

#ifndef HERMES_LIDAR_LIDAR_H
#define HERMES_LIDAR_LIDAR_H

#include <iostream>
#include <vector>

#include "RPLidar/sdk/include/rplidar.h"

using namespace rp::standalone::rplidar;

typedef std::vector<rplidar_response_measurement_node_t> MeasuresVector;

class Lidar {


    RPlidarDriver *driver;
    MeasuresVector measures;

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
    bool startMotor(uint16_t pwm);
    bool stopMotor();

    bool startScan();
    bool stopScan();

    const MeasuresVector& getScanData();
};


#endif //HERMES_LIDAR_LIDAR_H
