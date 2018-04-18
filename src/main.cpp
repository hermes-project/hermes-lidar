#include <zconf.h>
#include "Lidar.h"

int main()
{
    Lidar lidar;

    if(lidar.connect("/dev/ttyUSB0", 115200)) {
        //  GESTION DU STATUS DU LIDAR
        u_result operation_status;
        std::cout<<"RPLIDAR: lidar connecte"<<std::endl;

        lidar.printDeviceInfo();
        lidar.printDeviceHealth();

        lidar.startMotor(500);
        lidar.startScans();

        std::shared_ptr<ScanData> measures = lidar.getScanData();        //Rec

        lidar.stopScans();
        lidar.stopMotor();
        lidar.disconnect();

        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}