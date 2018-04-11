#include <iostream>
#include <zconf.h>
#include "RPLidar/sdk/include/rplidar.h"

using namespace rp::standalone::rplidar;
int main()
{
    RPlidarDriver* driver=RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);                    //L'interface avec le LiDAR

    if(driver->connect("/dev/ttyUSB0", 115200) == RESULT_OK) {               //Connection au LiDAR sur le port serie /dev/ttyUSB0 a 115200 bauds
        //  GESTION DU STATUS DU LIDAR
        std::cout<<"RPLIDAR: lidar connecte"<<std::endl;
        rplidar_response_device_health_t health_response;
        driver->getHealth(health_response);
        rplidar_response_device_info_t device_info;
        driver->getDeviceInfo(device_info);
        std::cout<<"Device: 0x"<<std::hex<<(unsigned int)device_info.model<<std::endl;
        std::cout<<"Serial Num.: ";
        for(int i=0;i<16;i++){
            std::cout<<"0x"<<(unsigned int) device_info.serialnum[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"Hardware Ver.: "<<(unsigned int)device_info.hardware_version<<" Firmware Ver.: "<<(unsigned int)device_info.firmware_version<<std::endl;
        std::cout<<"Status: "<<std::hex<<(unsigned int)health_response.status<<" Error code: "<<std::hex<<(unsigned int)health_response.error_code<<std::endl;
        std::cout<<"Codes de status: 0=OK, 1=WARNING, 2=ERREUR"<<std::endl;

//        driver->setMotorPWM(500); //Permet de demarrer le moteur
//        usleep(1000000);          //Delais en microsecondes




//        driver->stopMotor();  //Toujours arreter le moteur avant de terminer
        driver->disconnect();
    }
    else{
        std::cout<<"Erreur rplidar_wrapper: connection echouee"<<std::endl;
    }


    // SEGFAULT si le lidar est détruit,
    //RPlidarDriver::DisposeDriver(driver);
    return 0;
}