#include <iostream>
#include "RPLidar/include/rplidar.h"

using namespace rp::standalone::rplidar;
int main()
{

    RPlidarDriver* driver=RPlidarDriver::CreateDriver();                    //L'interface avec le LiDAR

    if(driver->connect("/dev/ttyUSB0", 115200) == RESULT_OK) {               //Connection au LiDAR sur le port serie /dev/ttyUSB0 a 115200 bauds
        std::cout<<"rplidar: lidar connecte"<<std::endl;
        rplidar_response_device_health_t health_response;
        driver->getHealth(health_response);
        std::cout<<"status: "<<health_response.status<<" error code: "<<health_response.error_code<<std::endl;
        driver->disconnect();
    }
    else{
        std::cout<<"Erreur rplidar: connection echouee"<<std::endl;
    }
    RPlidarDriver::DisposeDriver(driver);
}