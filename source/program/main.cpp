#include "lib.hpp"

#include "nn.hpp"
#include "utils.hpp"
#include "structs.hpp"
#include "binaryoffsethelper.h"

#include <cstring>

int version;

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

using SetStructIntFunc = void (void*, int*, void*, u32);

SetStructIntFunc* setStructInt = nullptr;

static constexpr u32 extralife_hash = 0xee199c3a;

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

struct Component {
    char _00[0x18];
    GameActor* actor;
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

extern "C" void exl_main(void* x0, void* x1) {

    char buf[500];

    /* Setup hooking enviroment */
    exl::hook::Initialize();

    PRINT("Getting app version...");
    version = InitializeAppVersion();
    if (version == 0xffffffff || version > 5) {
        PRINT("Error getting version");
        return;
    }
    PRINT("Version index %d", version);

    setStructInt = reinterpret_cast<SetStructIntFunc*>(exl::util::modules::GetTargetOffset(set_hook[version]));

    PRINT("Hooking functions...");
    DuraFix::InstallAtOffset(inline_1[version]);
    DuraFix::InstallAtOffset(inline_2[version]);
    FixExtraLife::InstallAtOffset(fix_hook[version]);
    PRINT("Hook successful");

    return;
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}