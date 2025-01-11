#include <user_lib.hpp>
#include <bits/stdc++.h>
#include "controller.hpp"
#include "dji_motor.hpp"
#include "io.hpp"
#include "pid.hpp"
#include "can.hpp"

using namespace std;

constexpr Pid::PidConfig SPEED_PID_CONFIG{
    200.f,
    5.f,
    0.2f,
    30000.0f,
    15000.0f,
};

constexpr Pid::PidConfig M6020_SPEED_PID_CONFIG{
    500.f,
    100.f,
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

int main() {
    IO::io<CAN>.insert("can0");
    Hardware::DJIMotorManager::start();

    Hardware::DJIMotor motor(3508, "can0", 3);
    motor.enable();
    while (true) {
        motor.set(4000);
    }
}