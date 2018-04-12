//
// Created by tic-tac on 4/12/18.
//

#include "Lidar.h"

Lidar::Lidar() : driver(RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT)){
    node.reserve(8192);
}

Lidar::~Lidar() {
    //Retirer ça pour mettre sur la UDOO
    //RPlidarDriver::DisposeDriver(driver);
}

bool Lidar::connect(const char *path, int baudrate) {
    bool status=driver->connect("/dev/ttyUSB0", 115200) == RESULT_OK;
    if(!status){
        std::cout<<"Erreur RPLidar: Echec grabScanData"<<std::endl;
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
        std::cout<<"Erreur RPLidar : Echec printDeviceHealth"<<std::endl;
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
        std::cout<<"Erreur RPLidar : Echec printDeviceInfo"<<std::endl;
    }
}




