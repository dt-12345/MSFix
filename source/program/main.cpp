#include "lib.hpp"

#include "binaryoffsethelper.h"
#include "nn.hpp"
#include "offsets.h"
#include "utils.hpp"
#include "structs.hpp"

#include <cstring>

int version;

static VFRCounter s_CooldownTimer;

void** s_VFRMgrPtr = nullptr;

using SetStructIntFunc = void (void*, int*, void*, u32);
using CountUpFunc = void (VFRCounter*);

SetStructIntFunc* setStructInt = nullptr;
CountUpFunc* countUp = nullptr;

static constexpr u32 extralife_hash = 0xee199c3a;
static constexpr float cooldown_frames = 30.f * 3.f;

HOOK_DEFINE_INLINE(DuraFix) {
    static void Callback(exl::hook::InlineCtx *ctx) {
        // set RecordExtraLife to -1 on MS resurrection to signal that it has not yet gained its bonus fuse durability yet
        void* mgr = (void*)ctx->X[0];
        void* handle = (void*)ctx->X[2];
        s32 a = -1;
        s32* value = &a;
        u32 hash = extralife_hash;
        setStructInt(mgr, value, handle, hash);
    }
};

HOOK_DEFINE_INLINE(FixExtraLife) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        // fix the ExtraLife value in LifeComponent using the WeaponComponent value bc otherwise it's garbage data for some reason?
        GameActor* actor = ((Component*)ctx->X[19])->actor;
        if (!actor) return;
        if (version == 0) {
            // avert your eyes
            actor = reinterpret_cast<GameActor*>(reinterpret_cast<uintptr_t>(actor) - 0x8);
        }
        if (strncmp(actor->name, "Weapon_Sword_070", 18)) return;
        if (!(actor->components.array)) return;
        LifeComponent* life_comp = reinterpret_cast<LifeComponent*>(actor->components.array[0x5f]);
        if (life_comp && life_comp->extra_life) {
            life_comp->extra_life->life = ctx->W[8];
        }
    }
};

HOOK_DEFINE_INLINE(StartCooldown) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        s_CooldownTimer.set_time(cooldown_frames);
    }
};

HOOK_DEFINE_INLINE(CheckTimer) {
    static void Callback(exl::hook::InlineFloatCtx* ctx) {
        if (s_CooldownTimer.time <= 0.f) {
            s_CooldownTimer.set_time(0.f);
        } else {
            countUp(&s_CooldownTimer);
            
            ctx->S[version > 5 ? 0 : 1] = *reinterpret_cast<float*>(ctx->X[19] + 0x74);
        }
    }
};

extern "C" void exl_main(void* x0, void* x1) {

    char buf[500];

    /* Setup hooking enviroment */
    exl::hook::Initialize();

    PRINT("Getting app version...");
    version = InitializeAppVersion();
    if (version == -1 || version > 8) {
        PRINT("Error getting version");
        return;
    }
    PRINT("Version index %d", version);

    setStructInt = reinterpret_cast<SetStructIntFunc*>(exl::util::modules::GetTargetOffset(set_hook[version]));
    countUp = reinterpret_cast<CountUpFunc*>(exl::util::modules::GetTargetOffset(countup_hook[version]));

    PRINT("Hooking functions...");
    DuraFix::InstallAtOffset(inline_1[version]);
    DuraFix::InstallAtOffset(inline_2[version]);
    FixExtraLife::InstallAtOffset(fix_hook[version]);

    StartCooldown::InstallAtOffset(charge_attack_hook[version]);
    StartCooldown::InstallAtOffset(spin_attack_hook[version]);
    StartCooldown::InstallAtOffset(earthwake_hook[version]);
    CheckTimer::InstallAtOffset(check_hook[version]);
    PRINT("Hook successful");

    return;
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT("Default exception handler called!");
}