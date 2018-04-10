#include <iostream>
#include "RPLidar/include/rplidar.h"

using namespace rp::standalone::rplidar;
int main()
{
    RPlidarDriver* driver=RPlidarDriver::CreateDriver();
    driver->connect()


    RPlidarDriver::DisposeDriver(driver);
}