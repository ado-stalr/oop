#ifndef LW3_CAR_H
#define LW3_CAR_H
#endif//LW3_CAR_H
#pragma once
#include <array>
#include <climits>
#include <map>

class Car {
public:
    Car();
    bool IsTurnedOn() const;
    int GetDirection() const;
    int GetSpeed() const;
    int GetGear() const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);

private:
    bool m_isEngineWorking = false;
    int m_speed = 0;
    int m_gear = 0;
    int m_direction = 0;
    std::map<int, std::array<int, 2>> m_gearRanges =
    {
        {-1, {0, 20}},
        {0, {0, INT_MAX}},
        {1, {0, 30}},
        {2, {20, 50}},
        {3, {30, 60}},
        {4, {40, 90}},
        {5, {50, 150}}
    };
};
