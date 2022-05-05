#include "CarController.h"

static const std::map<std::string, Commands> commands = {
        {"Info", Commands::INFO},
        { "EngineOn", Commands::ENGINE_ON },
        { "EngineOff", Commands::ENGINE_OFF },
        { "SetGear", Commands::SET_GEAR },
        { "SetSpeed", Commands::SET_SPEED },
};

static const int MIN_GEAR = -1;
static const int MAX_GEAR = 5;

static const int REVERSE_GEAR = -1;
static const int NEUTRAL_GEAR = 0;
static const int FIRST_GEAR = 1;

static const int DIRECTION_BACKWARD = -1;
static const int NO_DIRECTION = 0;

static const std::string ENGINE = "Engine: ";
static const std::string DIRECTION = "Direction: ";
static const std::string SPEED = "Speed: ";
static const std::string GEAR = "GEAR: ";
static const std::string ON = "On\n";
static const std::string OFF = "Off\n";
static const std::string BACKWARD = "Backward\n";
static const std::string WITHOUT_DIRECTION = "Without direction\n";
static const std::string FORWARD = "Forward\n";

static const std::string SUCCESS_TURNED_ON = "The engine is turned on successfully!\n\n";
static const std::string FAILED_TURNED_ON = "The engine is alredy tirned on!\n\n";
static const std::string SUCCESS_TURNED_OFF = "The engine is turned off successfully!\n\n";
static const std::string SHUTDOWN_ERROR = "shutdown error!\n\n";
static const std::string GEAR_CANNOT_SET = " gear can\'t be set\n";
static const std::string GEAR_SET = " gear set\n\n";
static const std::string SPEED_CANNOT_SET = " speed can\'t be set\n";
static const std::string SPEED_SET = " speed set\n\n";
static const std::string ENGINE_OFF = "engine turned off\n\n";

static const std::string COMMAND_NOT_EXIST= "This command does not exist\n\n";
static const std::string INCORRECT_GEAR_FORMAT = "Incorrect gear parameter format\n\n";
static const std::string INCORRECT_SPEED_FORMAT = "Incorrect speed parameter format\n\n";
static const std::string CANNOT_SHUTDOWN_ENGINE_WHEN_SPEED_GEAR_NULL = "can\'t shutdown engine when speed or gear are not at 0\n\n ";
static const std::string GEAR_NOT_EXIST = "this gear does not exist in the car\n\n";
static const std::string CANNOT_SET_NON_NEUTRAL_GEAR_WHEN_ENGINE_OFF = "impossible to switch to a non-neutral gear when the engine is off\n\n";
static const std::string CANNOT_SET_FORWARD_GEAR_WHEN_DRIVING_BACKWARD = "impossible to switch to forward gear when driving backward\n\n";
static const std::string CANNOT_SET_REVERSE_GEAR_WHEN_NOT_REST = "Switch to reverse gear allowed after stop\n\n";
static const std::string GEAR_NOT_SUPPORT_SPEED = "the gear doesn\'t support the current speed\n\n";
static const std::string CANNOT_INCREASE_SPEED_IN_NEUTRAL_GEAR = "can't increase the speed in neutral gear\n\n";
static const std::string SPEED_OUT_OF_RANGE_OF_GEAR = "the speed is out of the range of gear\n\n";

CarController::CarController() = default;

void CarController::ProcessCommand(Car& car, const std::string& userCommand)
{
    std::stringstream stringAppeal(userCommand);
    Commands command;
    if (CarController::GetCommand(stringAppeal, command))
    {
        switch (command)
        {
            case Commands::INFO:
                CarController::getCarInfo(car);
                break;

            case Commands::ENGINE_ON:
                CarController::TurnOnEngine(car);
                break;

            case Commands::ENGINE_OFF:
                CarController::TurnOffEngine(car);
                break;

            case Commands::SET_GEAR:
                int gear;
                if (stringAppeal >> gear)
                {
                    CarController::SetGear(car, gear);
                    break;
                }
                std::cout << INCORRECT_GEAR_FORMAT;
                break;

            case Commands::SET_SPEED:
                int speed;
                if (stringAppeal >> speed)
                {
                    CarController::SetSpeed(car, speed);
                    break;
                }
                std::cout << INCORRECT_SPEED_FORMAT;
                break;
            default:
                break;
        }
    }
    else
    {
        std::cout << COMMAND_NOT_EXIST;
    }
}

bool CarController::GetCommand(std::stringstream& commandLine, Commands& command)
{
    std::string stringCommand;
    commandLine >> stringCommand;
    if (commands.find(stringCommand) != commands.end())
    {
        command = commands.at(stringCommand);
        return true;
    }
    return false;
}

void CarController::PrintEngineInfo(Car& car) const
{
    std::cout << ENGINE;
    if (car.IsTurnedOn())
    {
        std::cout << ON;
    }
    else
    {
        std::cout << OFF;
    }
}

void CarController::PrintDirectionInfo(Car& car) const
{
    std::cout << DIRECTION;
    switch (car.GetDirection())
    {
        case -1:
            std::cout << BACKWARD;
            break;
        case 0:
            std::cout << WITHOUT_DIRECTION;
            break;
        case 1:
            std::cout << FORWARD;
            break;
        default:
            break;
    }
}

void CarController::PrintSpeedInfo(Car& car) const
{
    std::cout << SPEED;
    std::cout << car.GetSpeed() << std::endl;
}

void CarController::PrintGearInfo(Car& car) const
{
    std::cout << GEAR;
    std::cout << car.GetGear() << std::endl;
}

void CarController::getCarInfo(Car& car) const
{
    CarController::PrintEngineInfo(car);
    CarController::PrintDirectionInfo(car);
    CarController::PrintSpeedInfo(car);
    CarController::PrintGearInfo(car);
    std::cout << std::endl;
}

bool CarController::TurnOnEngine(Car& car) 
{
    if (car.TurnOnEngine()) {
        std::cout << SUCCESS_TURNED_ON;
        return true;
    };
    std::cout << FAILED_TURNED_ON;
    return false;
}

bool CarController::TurnOffEngine(Car& car)
{
    if (!car.IsTurnedOn())
    {
        std::cout << SUCCESS_TURNED_OFF;
        return true;
    }
    if (car.GetSpeed() == 0 && car.GetGear() == 0)
    {
        car.TurnOffEngine();
        std::cout << SUCCESS_TURNED_OFF;
        return true;
    }
    std::cout << SHUTDOWN_ERROR << CANNOT_SHUTDOWN_ENGINE_WHEN_SPEED_GEAR_NULL;
    return false;
}

bool CarController::SetGear(Car& car, int gear)
{
    if (gear < MIN_GEAR || gear > MAX_GEAR)
    {
        std::cout << gear << GEAR_CANNOT_SET << GEAR_NOT_EXIST;
        return false;
    }
    if (!car.IsTurnedOn() && gear != NEUTRAL_GEAR)
    {
        std::cout << gear << GEAR_CANNOT_SET << CANNOT_SET_NON_NEUTRAL_GEAR_WHEN_ENGINE_OFF;
        return false;
    }
    if (gear == FIRST_GEAR && car.GetDirection() == DIRECTION_BACKWARD)
    {
        std::cout << gear << GEAR_CANNOT_SET << CANNOT_SET_FORWARD_GEAR_WHEN_DRIVING_BACKWARD;
        return false;
    }
    if (gear == REVERSE_GEAR && car.GetDirection() != NO_DIRECTION)
    {
        std::cout << gear << GEAR_CANNOT_SET << CANNOT_SET_REVERSE_GEAR_WHEN_NOT_REST;
        return false;
    }

    if (car.SetGear(gear))
    {
        std::cout << gear << GEAR_SET;
        return true;
    }
    std::cout << gear << GEAR_CANNOT_SET << GEAR_NOT_SUPPORT_SPEED;
    return false;
}

bool CarController::SetSpeed(Car& car, int speed)
{
    if (!car.IsTurnedOn())
    {
        std::cout << speed << SPEED_CANNOT_SET << ENGINE_OFF;
        return false;
    }
    if ((car.GetGear() == NEUTRAL_GEAR && speed > car.GetSpeed()) || speed < 0)
    {
        std::cout << speed << SPEED_CANNOT_SET << CANNOT_INCREASE_SPEED_IN_NEUTRAL_GEAR;
        return false;
    }
    if (!car.SetSpeed(speed))
    {
        std::cout << speed << SPEED_CANNOT_SET << SPEED_OUT_OF_RANGE_OF_GEAR;
        return false;
    }

    std::cout << speed << SPEED_SET;
    return true;
}
