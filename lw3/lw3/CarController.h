#ifndef LW3_CARCONTROLLER_H
#define LW3_CARCONTROLLER_H
#endif//LW3_CARCONTROLLER_H

#include "Car.h"
#include <sstream>
#include <iostream>
#include <string>

enum class Commands
{
    INFO,
    ENGINE_ON,
    ENGINE_OFF,
    SET_GEAR,
    SET_SPEED
};

class CarController
{
public:
    CarController();
    void ProcessCommand(Car& car, const std::string& userAppeal);
    bool GetCommand(std::stringstream& stringAppeal, Commands& command);
    void PrintEngineInfo(Car& car) const;
    void PrintDirectionInfo(Car& car) const;
    void PrintSpeedInfo(Car& car) const;
    void PrintGearInfo(Car& car) const;
    void getCarInfo(Car& car) const;
    bool TurnOnEngine(Car& car);
    bool TurnOffEngine(Car& car);
    bool SetGear(Car& car, int gear);
    bool SetSpeed(Car& car, int speed);
};
