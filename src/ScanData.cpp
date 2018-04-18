//
// Created by tic-tac on 4/16/18.
//

#include "ScanData.h"

/**
 * Empty scan, for when there is an error in the grabbed data from the lidar
 * Always check for measureTime!=0 and measures!=nullptr to see if there was an error
 */
ScanData::ScanData() {
    measureTime=0;
    measures=nullptr;
}

/**
 * Data from a scan, with the measures as {float angle, uint16_t distance} elements
 * @param measureVector vector containing the measures
 * @param currentTime timestamp of the scan
 */
ScanData::ScanData(std::vector<measure> &measureVector, uint16_t currentTime) {
    measures=std::make_shared<std::vector<measure>>(measureVector);
    measureTime=currentTime;
}

uint16_t ScanData::getSize() {
    return static_cast<uint16_t>(measures->size());
}

const measure &ScanData::getMeasureAtIndex(uint16_t index) {
    return measures->at(index);
}

float ScanData::getDistanceAtIndex(uint16_t index) {
    return measures->at(index).distance;
}
