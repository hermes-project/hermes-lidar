//
// Created by tic-tac on 4/16/18.
//

#ifndef HERMES_LIDAR_SCANDATA_H
#define HERMES_LIDAR_SCANDATA_H

#include <iostream>
#include <vector>
#include <memory>

#define RESOLUTION 0.5f


struct measure{
    bool newTurn;
    uint8_t quality;
    float angle;
    float distance;

    measure(bool s, uint8_t q, float a, float d): newTurn(s), quality(q), angle(a), distance(d){}
};

class ScanData {
    uint32_t measureTime;
    std::shared_ptr<std::vector<measure>> measures;

public:

    ScanData();
    ScanData(std::vector<measure> &measureVector, uint16_t currentTime);

    uint16_t getSize();
    const measure& getMeasureAtIndex(uint16_t index);
    float getDistanceAtIndex(uint16_t index);
};


#endif //HERMES_LIDAR_SCANDATA_H
