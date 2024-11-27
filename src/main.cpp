#include <user_lib.hpp>
#include <bits/stdc++.h>
#include "controller.hpp"
#include "dji_motor.hpp"
#include "io.hpp"
#include "pid.hpp"
#include "can.hpp"

using namespace std;

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
    Hardware::M6020 motor("can0", 1);
    Hardware::M2006 motor1("can0", 1);
    auto pid1 = Pid::PidRad(POSITION_PID_CONFIG, motor.angle);
    auto pid2 = Pid::PidPosition(YAW_SPEED_PID_CONFIG, motor.angular_velocity);
    auto log = LOG("M6020");
    motor.enable();
    motor1.enable();
    Hardware::DJIMotorManager::start();
    while(true) {
        motor1.set(2000);
        5 >> pid1 >> pid2 >> motor;
        UserLib::sleep_ms(1);
    }
}