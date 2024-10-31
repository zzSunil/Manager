#include <bits/stdc++.h>
#include "controller.hpp"
#include "dji_motor.hpp"
#include "io.hpp"
#include "pid.hpp"
#include "can.hpp"

using namespace std;

using fp32 = float;

constexpr Pid::PidConfig YAW_SPEED_PID_CONFIG{
    500.f,
    100.f,
    0.2f,
    30000.0f,
    15000.0f,
};

constexpr Pid::PidConfig POSITION_PID_CONFIG{
    7.f,
    0.01f,
    0.02f,
    30.0f,
    0.0f,
};

int main() {
    IO::io<CAN>.insert(*new IO::Can_interface{"can0"});

    Hardware::M6020 motor("can0", 1);
    motor.setCtrl(Pid::PidRad(POSITION_PID_CONFIG, motor.angle)
        >> Pid::PidPosition(YAW_SPEED_PID_CONFIG, motor.angular_velocity));
    motor.enable();
    Hardware::DJIMotorManager::start();

    std::thread output_thread([&]() {
        while (true) {
            cout << motor.angular_velocity << ' ' << motor.angle << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    while (true) {
        motor.set(5);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}