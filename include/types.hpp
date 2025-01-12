#ifndef __TYPES__
#define __TYPES__
#include <linux/can.h>

#include <cstdint>

#include "string"

// NOTE: defines and type defines
typedef signed char int8_t;
typedef signed short int int16_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned char bool_t;
typedef float fp32;
typedef double fp64;

namespace Status
{
    const bool OK = true;
    const bool ERROR = false;
}  // namespace Status

struct Vec3d
{
    double x, y, z;
};

namespace Types
{
    typedef struct ReceivePacket
    {
        float yaw;
        float pitch;
        float roll;
        float yaw_v;
        float pitch_v;
        float roll_v;
        int16_t ch[5];
        char s[2];
    } __attribute__((packed)) ReceivePacket;

    typedef struct
    {
        fp32 input;         // 输入数据
        fp32 out;           // 滤波输出的数据
        fp32 num[1];        // 滤波参数
        fp32 frame_period;  // 滤波的时间间隔 单位 s
    } first_order_filter_type_t;

    enum Kb_event
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
        SPIN_R,
        SPIN_L,
        STOP_X,
        STOP_Y,
    };

    typedef struct
    {
        fp32 vx;
        fp32 vy;
        fp32 wz;
        fp32 wheel_speed[4];
        can_frame can_f;
        uint64_t pkg;
        bool err;
        std::string debuginfo1;
        std::string debuginfo2;
        std::string debuginfo3;

    } debug_info_t;

    typedef struct
    {
        struct
        {
            int16_t ch[5];
            char s[2];
        } rc;
        struct
        {
            int16_t x;
            int16_t y;
            int16_t z;
            uint8_t press_l;
            uint8_t press_r;
        } mouse;
        struct
        {
            bool q;  //  spin clock wise
            bool f;  //  spin counter clock wise
            fp32 speed_x;
            fp32 speed_y;
            int16_t v;
        } key;

    } RC_ctrl_t;
    enum ROBOT_MODE
    {
        ROBOT_NO_FORCE,
        ROBOT_FINISH_INIT,
        ROBOT_FOLLOW_GIMBAL,
        ROBOT_SEARCH,
        ROBOT_IDLE,
        ROBOT_NOT_FOLLOW
    };

    typedef struct
    {
        fp32 input;         // 输入数据
        fp32 out;           // 滤波输出的数据
        fp32 num;           // 滤波参数
        fp32 frame_period;  // 滤波的时间间隔 单位 s
    } fof_t;

    typedef struct
    {
    } ramp_t;
}  // namespace Types

#endif