#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Car.h"
#include "../CarController.h"

TEST_CASE("Testing class Car")
{
    std::cout << "Function: IsTurnedOn" << std::endl;
    SECTION("Engine is working after TurnOnEngine")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Engine is not working after creating Car")
    {
        Car car;
        REQUIRE(car.IsTurnedOn() == false);
    }

    std::cout << "Function: TurnOnEngine" << std::endl;
    SECTION("Engine turn on if was turned off")
    {
        Car car;
        REQUIRE(car.TurnOnEngine() == true);
    }

    SECTION("Engine turning on failed if was already turned on")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.TurnOnEngine() == false);
    }

    std::cout << "Function: TurnOffEngine" << std::endl;
    SECTION("Engine is not turned off when car is moving on neitral gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(car.TurnOffEngine() == false);
    }

    SECTION("Engine is not turned off when car is on neitral gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(car.TurnOffEngine() == false);
    }

    SECTION("Engine is turned off when car is not moving and on neitral gear")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.TurnOffEngine() == true);
    }

    SECTION("Engine turning off success if was already turned off")
    {
        Car car;
        REQUIRE(car.TurnOffEngine() == true);
    }

    std::cout << "Function: GetDirection" << std::endl;
    SECTION("Direction 0 if speed 0 after SetGear -1")
    {
        Car car;
        car.SetGear(-1);
        REQUIRE(car.GetDirection() == 0);
    }
    
    SECTION("Direction 0 if speed 0 after SetGear 1")
    {
        Car car;
        car.SetGear(1);
        REQUIRE(car.GetDirection() == 0);
    }

    SECTION("Direction -1 after start moving backward")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(11);
        REQUIRE(car.GetDirection() == -1);
    }

    std::cout << "Function: SetSpeed" << std::endl;
    SECTION("Setting Speed up failed on neitral gear when car is not moving")
    {
        Car car;
        car.TurnOnEngine();
        REQUIRE(car.SetSpeed(10) == false);
    }

    SECTION("Setting Speed up failed on neitral gear when car is moving")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(car.SetSpeed(11) == false);
    }

    SECTION("Setting Speed failed when speed not in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(car.SetSpeed(500) == false);
    }

    SECTION("Setting Speed success when speed in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(car.SetSpeed(10) == true);
    }
    
    std::cout << "Function: SetGear" << std::endl;
    SECTION("Setting gear failing after creating car")
    {
        Car car;
        REQUIRE(car.SetGear(-1) == false);
    }

    SECTION("Setting gear success when speed is in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(2) == true);
    }

    SECTION("Setting gear failed when speed is not in range of gear")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE(car.SetGear(2) == false);
    }

    SECTION("Setting gear failed when opposite direction")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(car.SetGear(1) == false);
    }
}


TEST_CASE("Testing class CarController")
{
    std::cout << "Function: GetCommand" << std::endl;
    SECTION("Command = Info")
    {
        CarController controller;
        std::stringstream stringCommand("Info");
        Commands command;
        REQUIRE(controller.GetCommand(stringCommand, command) == true);
        REQUIRE(command == Commands::INFO);
    }

    SECTION("Uncorrect command = SetGear1")
    {
        CarController controller;
        std::stringstream stringCommand("SetGear1");
        Commands command;
        REQUIRE(controller.GetCommand(stringCommand, command) == false);
    }

    SECTION("Correct command = SetGear 1")
    {
        CarController controller;
        std::stringstream stringCommand("SetGear 1");
        Commands command;
        REQUIRE(controller.GetCommand(stringCommand, command) == true);
        REQUIRE(command == Commands::SET_GEAR);
    }

    std::cout << "Function: TurnOnEngine" << std::endl;
    SECTION("Engine turn on if was turned off")
    {
        CarController controller;
        Car car;
        REQUIRE(controller.TurnOnEngine(car) == true);
    }

    SECTION("Engine turning on failed if was already turned on")
    {
        CarController controller;
        Car car;
        controller.TurnOnEngine(car);
        REQUIRE(controller.TurnOnEngine(car) == false);
    }

    std::cout << "Function: TurnOffEngine" << std::endl;
    SECTION("Engine is turned off when car is not moving and on neitral gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(controller.TurnOffEngine(car) == false);
    }

    SECTION("Engine is not turned off when car is not on neitral gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(controller.TurnOffEngine(car) == false);
    }

    SECTION("Engine is turned off when car is not moving and on neitral gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        REQUIRE(controller.TurnOffEngine(car) == true);
    }

    SECTION("Engine turning off success if was already turned off")
    {
        CarController controller;
        Car car;
        REQUIRE(controller.TurnOffEngine(car) == true);
    }

    std::cout << "Function: SetSpeed" << std::endl;
    SECTION("Setting Speed up failed on neitral gear when car is not moving")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        REQUIRE(controller.SetSpeed(car, 10) == false);
    }

    SECTION("Setting Speed up failed on neitral gear when car is moving")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(controller.SetSpeed(car, 11) == false);
    }

    SECTION("Setting Speed failed when speed not in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(controller.SetSpeed(car, 500) == false);
    }

    SECTION("Setting Speed success when speed in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE(controller.SetSpeed(car, 10) == true);
    }

    std::cout << "Function: SetGear" << std::endl;
    SECTION("Setting gear failing after creating car")
    {
        CarController controller;
        Car car;
        REQUIRE(controller.SetGear(car, -1) == false);
    }

    SECTION("Setting gear success when speed is in range of gear")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(controller.SetGear(car, 2) == true);
    }

    SECTION("Setting gear failed when speed is not in range of gea")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE(controller.SetGear(car, 2) == false);
    }

    SECTION("Setting gear failed when opposite direction")
    {
        CarController controller;
        Car car;
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE(controller.SetGear(car, 1) == false);
    }
}
