#pragma once

#include "types.h"

static constexpr u64 set_hook[] = {
    0x008202b0,
    0x00850ab4,
    0x0077b528,
    0x0085b4e4,
    0x0082cbcc,
    0x0080eb0c,
    0x00234380,
    0x000fc850,
    0x0017fe7c,
};
static constexpr u64 inline_1[] = {
    0x0194309c,
    0x0199bea0,
    0x019999dc,
    0x0198e89c,
    0x0197e614,
    0x0198c59c,
    0x01fdb870,
    0x01fcb930,
    0x01fca7bc,
};
static constexpr u64 inline_2[] = {
    0x01942f78,
    0x0199bd7c,
    0x019998b8,
    0x0198e9c0,
    0x0197e738,
    0x0198c6c0,
    0x01fdb9f4,
    0x01fcbab4,
    0x01fca940,
};
static constexpr u64 fix_hook[] = {
    0x0067390c,
    0x006d2330,
    0x009bb450,
    0x006c7ae4,
    0x00685ed4,
    0x0066589c,
    0x000aa98c,
    0x00519638,
    0x00538058,
};
static constexpr u64 charge_attack_hook[] = {
    0x01cf26e0,
    0x01d60f58,
    0x01d5b988,
    0x01d558b8,
    0x01d478e8,
    0x01d53d98,
    0x023e138c,
    0x023d26f0,
    0x023d3058,
};
static constexpr u64 spin_attack_hook[] = {
    0x01cf30bc,
    0x01d61934,
    0x01d5c364,
    0x01d56294,
    0x01d482c4,
    0x01d54774,
    0x023e1fe0,
    0x023d3344,
    0x023d39b8,
};
static constexpr u64 earthwake_hook[] = {
    0x01d23db8,
    0x01d92bc4,
    0x01d8d5e4,
    0x01d87748,
    0x01d795c4,
    0x01d85a64,
    0x02413d30,
    0x02405094,
    0x02405708,
};
static constexpr u64 check_hook[] = {
    0x0096ed58,
    0x007fb8fc,
    0x00746c08,
    0x0082c458,
    0x00bf37a8,
    0x009f1cb0,
    0x0043004c,
    0x00332620,
    0x00349394,
};
static constexpr u64 countup_hook[] = {
    0x007e9c18,
    0x00a26bb0,
    0x00a8900c,
    0x00a089d0,
    0x008166fc,
    0x00ec98cc,
    0x002c0bc8,
    0x005182b4,
    0x00536b6c,
};