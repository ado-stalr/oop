#include "Car.h"

static const int REVERSE_GEAR = -1;
static const int NEUTRAL_GEAR = 0;
static const int FIRST_GEAR = 1;

static const int DIRECTION_BACK = -1;
static const int WITHOUT_DIRECTION = 0;

Car::Car() = default;

bool Car::IsTurnedOn() const
{
    return m_isEngineWorking;
}

int Car::GetDirection() const
{
    return m_direction;
}

int Car::GetSpeed() const
{
    return m_speed;
}

int Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    if (!m_isEngineWorking)
    {
        m_isEngineWorking = true;
        return true;
    }
    return false;
}

bool Car::TurnOffEngine()
{
    if (!m_isEngineWorking)
    {
        return true;
    }
    if (m_speed == 0 && m_gear == 0)
    {
        m_isEngineWorking = false;
        return true;
    }
    return false;
}

bool speedInGearRange(int speed, int gear, std::map<int, std::array<int, 2>> gearRanges)
{
    return (speed >= gearRanges[gear][0] && speed <= gearRanges[gear][1]);
}

bool Car::SetGear(int gear)
{
    if (m_gearRanges.find(gear) == m_gearRanges.end())
    {
        return false;
    }
    if (!m_isEngineWorking && gear != NEUTRAL_GEAR)
    {
        return false;
    }
    if (gear >= FIRST_GEAR && m_direction == DIRECTION_BACK)
    {
        return false;
    }
    if (gear == REVERSE_GEAR && m_direction != WITHOUT_DIRECTION)
    {
        return false;
    }

    if (speedInGearRange(m_speed, gear, m_gearRanges))
    {
        m_gear = gear;
        return true;
    }

    return false;
}

bool Car::SetSpeed(int speed)
{
    if (!m_isEngineWorking || (m_gear == NEUTRAL_GEAR && speed > m_speed) || speed < 0)
    {
        return false;
    }

    if (speedInGearRange(speed, m_gear, m_gearRanges))
    {
        if (speed == 0)
        {
            m_speed = 0;
            m_direction = 0;

            return true;
        }
        if (m_speed == 0)
        {
            if (m_gear > 0)
            {
                m_direction = 1;
            }
            else
            {
                m_direction = -1;
            }
        }
        m_speed = speed;

        return true;
    }
    return false;
}