#include "Car.h"
#include "CarController.h"
#include <iostream>

int main()
{
    std::cout << "Commands:" << std::endl
              << "\"Info\"" << std::endl
              << "\"EngineOn\"" << std::endl
              << "\"EngineOff\"" << std::endl
              << "\"SetGear <n>\"" << std::endl
              << "\"SetSpeed <n>\"" << std::endl;

    Car car;
    CarController controller;

    std::string userCommand;
    while (getline(std::cin, userCommand))
    {
        controller.ProcessCommand(car, userCommand);
    }
    return 0;
}