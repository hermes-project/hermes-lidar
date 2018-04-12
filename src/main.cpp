#include <zconf.h>
#include "Lidar.h"

int main()
{
    Lidar lidar;

    if(lidar.connect("/dev/ttyUSB0", 115200)) {               //Connection au LiDAR sur le port serie /dev/ttyUSB0 a 115200 bauds
        //  GESTION DU STATUS DU LIDAR
        u_result operation_status;
        std::cout<<"RPLIDAR: lidar connecte"<<std::endl;

        lidar.printDeviceInfo();
        lidar.printDeviceHealth();


        lidar.disconnect();
    }

    return 0;
}