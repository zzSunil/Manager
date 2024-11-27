#include <user_lib.hpp>
#include <bits/stdc++.h>
#include "controller.hpp"
#include "dji_motor.hpp"
#include "io.hpp"
#include "pid.hpp"
#include "can.hpp"

using namespace std;

constexpr Pid::PidConfig YAW_SPEED_PID_CONFIG{
    200.f,
    5.f,
    0.2f,
    30000.0f,
    15000.0f,
};

constexpr Pid::PidConfig POSITION_PID_CONFIG{
    7.f,
    0.01f,
    0.0f,
    30.0f,
    0.0f,
};

class LOG final : public Controller {
public:
    string s;
    LOG(string msg) : s{msg} {};
    void set(float x) override {
        cout << s << ": " << x << endl;
        out = x;
    }
};

[[noreturn]] int main() {
    IO::io<CAN>.insert("can0");
    Hardware::DJIMotor motor(6020, "can0", 3);
    Hardware::DJIMotor motor_3508(Hardware::DJIMotorConfig{3508, "can0", 3});

    motor.enable();
    motor_3508.enable();
    Hardware::DJIMotorManager::start();
    Pid::PidPosition pid1(YAW_SPEED_PID_CONFIG, motor_3508.data_.output_angular_velocity);
    Pid::PidRad pid2(POSITION_PID_CONFIG, motor.data_.rotor_angle);
    std::thread output_thread([&]() {
        while (true) {
            cout << motor_3508.data_.rotor_angular_velocity << ' ' << motor_3508.data_.output_linear_velocity << endl;
            UserLib::sleep_ms(10);
        }
    });
    while(true) {
        30 >> pid1 >> motor_3508;
        UserLib::sleep_ms(1);
    }
}