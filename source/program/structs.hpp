#pragma once

struct PtrArray {
    int count;
    int max;
    void** array;
};

struct GameActor {
    char _[0x218];
    char* name;
    PtrArray components;
};

struct DamageCalculator {
    char _[0x18];
    int value;
};

struct LifeGameDataSync {
    void* __vftable;
    int life;
    unsigned int hash;
};

struct Component {
    char _00[0x18];
    GameActor* actor;
};

struct LifeComponent : public Component {
    char _0[0x170];
    DamageCalculator external_calc;
    char _1[0x106c];
    DamageCalculator internal_calc;
    char _2[0x5fc];
    LifeGameDataSync* life;
    LifeGameDataSync* max_life;
    LifeGameDataSync* extra_life;
    LifeGameDataSync* break_life;
    LifeGameDataSync* hard_break_life;
};
static_assert(offsetof(LifeComponent, external_calc) == 0x190);
static_assert(offsetof(LifeComponent, internal_calc) == 0x1218);
static_assert(offsetof(LifeComponent, extra_life) == 0x1840);

struct VFRCounter {
    float time;
    float last_time;
    float rate;

    VFRCounter(float duration, float step_rate = -1.f)
        : time{duration}, last_time{duration}, rate{step_rate} {}
    VFRCounter() : time{0.f}, last_time{0.f}, rate{-1.f} {}

    void set_time(float duration) { time = duration; last_time = duration; }
    void set_rate(float step_rate) { rate = step_rate; }
};