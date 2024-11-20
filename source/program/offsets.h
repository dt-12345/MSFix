#pragma once

#include "types.h"

static constexpr u64 set_hook[] = {
    0x008202b0,
    0x00850ab4,
    0x0077b528,
    0x0085b4e4,
    0x0082cbcc,
    0x0080eb0c,
};
static constexpr u64 inline_1[] = {
    0x0194309c,
    0x0199bea0,
    0x019999dc,
    0x0198e89c,
    0x0197e614,
    0x0198c59c,
};
static constexpr u64 inline_2[] = {
    0x01942f78,
    0x0199bd7c,
    0x019998b8,
    0x0198e9c0,
    0x0197e738,
    0x0198c6c0,
};
static constexpr u64 fix_hook[] = {
    0x0067390c,
    0x006d2330,
    0x009bb450,
    0x006c7ae4,
    0x00685ed4,
    0x0066589c,
};
static constexpr u64 charge_attack_hook[] = {
    0x01cf26e0,
    0x01d60f58,
    0x01d5b988,
    0x01d558b8,
    0x01d478e8,
    0x01d53d98,
};
static constexpr u64 spin_attack_hook[] = {
    0x01cf30bc,
    0x01d61934,
    0x01d5c364,
    0x01d56294,
    0x01d482c4,
    0x01d54774,
};
static constexpr u64 earthwake_hook[] = {
    0x01d23db8,
    0x01d92bc4,
    0x01d8d5e4,
    0x01d87748,
    0x01d795c4,
    0x01d85a64,
};
static constexpr u64 check_hook[] = {
    0x0096ed58,
    0x007fb8fc,
    0x00746c08,
    0x0082c458,
    0x00bf37a8,
    0x009f1cb0,
};
static constexpr u64 countup_hook[] = {
    0x007e9c18,
    0x00a26bb0,
    0x00a8900c,
    0x00a089d0,
    0x008166fc,
    0x00ec98cc,
};