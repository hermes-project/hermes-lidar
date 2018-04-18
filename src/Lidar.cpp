//
// Created by tic-tac on 4/12/18.
//

#include "Lidar.h"

Lidar::Lidar() : driver(RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT)){}

//TODO: Decommenter ça sur la UDOO/Raspi
//Lidar::~Lidar() {
//    RPlidarDriver::DisposeDriver(driver);
//}

bool Lidar::connect(const char *path, int baudrate) {
    bool status=driver->connect("/dev/ttyUSB0", 115200) == RESULT_OK;
    if(!status){
        std::cout<<"Erreur RPLidar: connect"<<std::endl;
    }
    return status;
}

void Lidar::disconnect(){
    driver->disconnect();
}

void Lidar::printDeviceHealth() {
    rplidar_response_device_health_t health_response;
    u_result operation_status;
    operation_status = driver->getHealth(health_response);
    if(IS_OK(operation_status)) {
        std::cout << "Status: " << std::hex << (unsigned int) health_response.status << " Error code: " << std::hex
                  << (unsigned int) health_response.error_code << std::endl;
        std::cout << "Codes de status: 0=OK, 1=WARNING, 2=ERREUR" << std::endl;
    }
    else{
        std::cout<<"Erreur RPLidar : printDeviceHealth"<<std::endl;
    }
}

void Lidar::printDeviceInfo() {
    rplidar_response_device_info_t device_info;
    u_result operation_status;
    operation_status = driver->getDeviceInfo(device_info);
    if(IS_OK(operation_status)) {
        std::cout << "Device: 0x" << std::hex << (unsigned int) device_info.model << std::endl;
        std::cout << "Serial Num.: ";
        for (int i = 0; i < 16; i++) {
            std::cout << "0x" << (unsigned int) device_info.serialnum[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Hardware Ver.: " << (unsigned int) device_info.hardware_version << " Firmware Ver.: "
                  << (unsigned int) device_info.firmware_version << std::endl;
    }
    else{
        std::cout<<"Erreur RPLidar : printDeviceInfo"<<std::endl;
    }
}


bool Lidar::startMotor(uint16_t pwm) {
    if(!IS_OK(driver->setMotorPWM(pwm))){
        std::cout<<"Erreur RPLidar : startMotor"<<std::endl;
        return false;
    }
    return true;
}

bool Lidar::stopMotor() {
    if(!IS_OK(driver->stopMotor())){
        std::cout<<"Erreur RPLidar : stopMotor"<<std::endl;
        return false;
    }
    return true;
}


bool Lidar::startScans() {
    if(!IS_OK(driver->startScan(false, true))){
        std::cout<<"Erreur RPLidar : startScans"<<std::endl;
        return false;
    }
    return true;
}

bool Lidar::stopScans() {
    if(!IS_OK(driver->startScan(false, true))){
        std::cout<<"Erreur RPLidar : startScans"<<std::endl;
        return false;
    }
    return true;
}

const std::shared_ptr<ScanData> Lidar::getScanData() {
    RawMeasuresVector rawMeasureVector;
    rawMeasureVector.reserve(8192);
    size_t count=8192;
    if(IS_OK(driver->grabScanData(rawMeasureVector.data(),count))){
        driver->ascendScanData(rawMeasureVector.data(),count);

        //Preparation of the measures with format {new_turn, quality, angle distance}
        std::vector<measure> measures;
        for(auto rawMeasure : rawMeasureVector){
            measures.emplace_back((rawMeasure.sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) != 0,
                      rawMeasure.sync_quality>>RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT,
                      (rawMeasure.angle_q6_checkbit>>RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
                      rawMeasure.distance_q2/4.0f);
        }

        //Timestamp
        using namespace std::chrono;
        long timestamp=time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();

        return std::make_shared<ScanData>(measures,timestamp);

    }
    else{
        std::cout<<"Erreur RPLidar : getScanData\nReturning old values"<<std::endl;
        return std::make_shared<ScanData>();
    }
}
