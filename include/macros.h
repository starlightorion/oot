#ifndef MACROS_H
#define MACROS_H

#ifndef AVOID_UB
#define BAD_RETURN(type) type
#else
#define BAD_RETURN(type) void
#endif

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define PHYSICAL_TO_VIRTUAL(addr) (void*)((uintptr_t)(addr) + 0x80000000)
#define VIRTUAL_TO_PHYSICAL(addr) (uintptr_t)((u8*)(addr) - 0x80000000)
#define SEGMENTED_TO_VIRTUAL(addr) PHYSICAL_TO_VIRTUAL(gSegments[SEGMENT_NUMBER(addr)] + SEGMENT_OFFSET(addr))

#define SQ(x) ((x)*(x))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define DECR(x) ((x) == 0 ? 0 : --(x))
#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define RGBA8(r, g, b, a) ((((r) & 0xFF) << 24) | (((g) & 0xFF) << 16) | (((b) & 0xFF) << 8) | (((a) & 0xFF) << 0))

#define GET_PLAYER(play) ((Player*)(play)->actorCtx.actorLists[ACTORCAT_PLAYER].head)

#define GET_ACTIVE_CAM(play) ((play)->cameraPtrs[(play)->activeCamId])

#define LINK_IS_ADULT (gSaveContext.save.linkAge == LINK_AGE_ADULT)
#define LINK_IS_CHILD (gSaveContext.save.linkAge == LINK_AGE_CHILD)

#define YEARS_CHILD 5
#define YEARS_ADULT 17
#define LINK_AGE_IN_YEARS (!LINK_IS_ADULT ? YEARS_CHILD : YEARS_ADULT)

#define CLOCK_TIME(hr, min) ((s32)(((hr) * 60 + (min)) * (f32)0x10000 / (24 * 60) + 0.5f))

#define IS_DAY (gSaveContext.save.nightFlag == 0)
#define IS_NIGHT (gSaveContext.save.nightFlag == 1)

#define SLOT(item) gItemSlots[item]
#define INV_CONTENT(item) gSaveContext.save.info.inventory.items[SLOT(item)]
#define AMMO(item) gSaveContext.save.info.inventory.ammo[SLOT(item)]
#define BEANS_BOUGHT AMMO(ITEM_MAGIC_BEAN + 1)

#define ALL_EQUIP_VALUE(equip) ((s32)(gSaveContext.save.info.inventory.equipment & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_EQUIP_VALUE(equip) ((s32)(gSaveContext.save.info.equips.equipment & gEquipMasks[equip]) >> gEquipShifts[equip])
#define OWNED_EQUIP_FLAG(equip, value) (gBitFlags[value] << gEquipShifts[equip])
#define OWNED_EQUIP_FLAG_ALT(equip, value) ((1 << (value)) << gEquipShifts[equip])
#define CHECK_OWNED_EQUIP(equip, value) (OWNED_EQUIP_FLAG(equip, value) & gSaveContext.save.info.inventory.equipment)
#define CHECK_OWNED_EQUIP_ALT(equip, value) (gBitFlags[(value) + (equip) * 4] & gSaveContext.save.info.inventory.equipment)

#define SWORD_EQUIP_TO_PLAYER(swordEquip) (swordEquip)
#define SHIELD_EQUIP_TO_PLAYER(shieldEquip) (shieldEquip)
#define TUNIC_EQUIP_TO_PLAYER(tunicEquip) ((tunicEquip) - 1)
#define BOOTS_EQUIP_TO_PLAYER(bootsEquip) ((bootsEquip) - 1)

#define CUR_UPG_VALUE(upg) ((s32)(gSaveContext.save.info.inventory.upgrades & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])
#define CAPACITY(upg, value) gUpgradeCapacities[upg][value]
#define CUR_CAPACITY(upg) CAPACITY(upg, CUR_UPG_VALUE(upg))

#define CHECK_QUEST_ITEM(item) (gBitFlags[item] & gSaveContext.save.info.inventory.questItems)
#define CHECK_DUNGEON_ITEM(item, dungeonIndex) (gSaveContext.save.info.inventory.dungeonItems[dungeonIndex] & gBitFlags[item])

#define GET_GS_FLAGS(index) \
    ((gSaveContext.save.info.gsFlags[(index) >> 2] & gGsFlagsMasks[(index) & 3]) >> gGsFlagsShifts[(index) & 3])
#define SET_GS_FLAGS(index, value) \
    (gSaveContext.save.info.gsFlags[(index) >> 2] |= (value) << gGsFlagsShifts[(index) & 3])

#define HIGH_SCORE(score) (gSaveContext.save.info.highScores[score])

#define GET_EVENTCHKINF(flag) (gSaveContext.save.info.eventChkInf[(flag) >> 4] & (1 << ((flag) & 0xF)))
#define SET_EVENTCHKINF(flag) (gSaveContext.save.info.eventChkInf[(flag) >> 4] |= (1 << ((flag) & 0xF)))
#define CLEAR_EVENTCHKINF(flag) (gSaveContext.save.info.eventChkInf[(flag) >> 4] &= ~(1 << ((flag) & 0xF)))

#define GET_ITEMGETINF(flag) (gSaveContext.save.info.itemGetInf[(flag) >> 4] & (1 << ((flag) & 0xF)))
#define SET_ITEMGETINF(flag) (gSaveContext.save.info.itemGetInf[(flag) >> 4] |= (1 << ((flag) & 0xF)))

#define GET_INFTABLE(flag) (gSaveContext.save.info.infTable[(flag) >> 4] & (1 << ((flag) & 0xF)))
#define SET_INFTABLE(flag) (gSaveContext.save.info.infTable[(flag) >> 4] |= (1 << ((flag) & 0xF)))
#define CLEAR_INFTABLE(flag) (gSaveContext.save.info.infTable[(flag) >> 4] &= ~(1 << ((flag) & 0xF)))

#define GET_EVENTINF(flag) (gSaveContext.eventInf[(flag) >> 4] & (1 << ((flag) & 0xF)))
#define SET_EVENTINF(flag) (gSaveContext.eventInf[(flag) >> 4] |= (1 << ((flag) & 0xF)))
#define CLEAR_EVENTINF(flag) (gSaveContext.eventInf[(flag) >> 4] &= ~(1 << ((flag) & 0xF)))

#define B_BTN_ITEM ((gSaveContext.buttonStatus[0] == ITEM_NONE)                     \
                        ? ITEM_NONE                                                 \
                        : (gSaveContext.save.info.equips.buttonItems[0] == ITEM_GIANTS_KNIFE) \
                            ? ITEM_SWORD_BIGGORON                                   \
                            : gSaveContext.save.info.equips.buttonItems[0])

#define C_BTN_ITEM(button) ((gSaveContext.buttonStatus[(button) + 1] != BTN_DISABLED) \
                                ? gSaveContext.save.info.equips.buttonItems[(button) + 1]       \
                                : ITEM_NONE)

#define CHECK_BTN_ALL(state, combo) (~((state) | ~(combo)) == 0)
#define CHECK_BTN_ANY(state, combo) (((state) & (combo)) != 0)

#define CHECK_FLAG_ALL(flags, mask) (((flags) & (mask)) == (mask))

#ifdef OOT_DEBUG
#define PRINTF osSyncPrintf
#else
#ifdef __sgi /* IDO compiler */
// IDO doesn't support variadic macros, but it merely throws a warning for the
// number of arguments not matching the definition (warning 609) instead of
// throwing an error. We suppress this warning and rely on GCC to catch macro
// argument errors instead.
#define PRINTF(args) (void)0
#else
#define PRINTF(format, ...) (void)0
#endif
#endif

#ifdef OOT_DEBUG

#define LOG(exp, value, format, file, line)         \
    do {                                            \
        LogUtils_LogThreadId(file, line);           \
        osSyncPrintf(exp " = " format "\n", value); \
    } while (0)
#else
#define LOG(exp, value, format, file, line) (void)0
#endif

#define LOG_STRING(string, file, line) LOG(#string, string, "%s", file, line)
#define LOG_ADDRESS(exp, value, file, line) LOG(exp, value, "%08x", file, line)
#define LOG_TIME(exp, value, file, line) LOG(exp, value, "%lld", file, line)
#define LOG_NUM(exp, value, file, line) LOG(exp, value, "%d", file, line)
#define LOG_HEX(exp, value, file, line) LOG(exp, value, "%x", file, line)
#define LOG_HEX32(exp, value, file, line) LOG(exp, value, "%08x", file, line)
#define LOG_FLOAT(exp, value, file, line) LOG(exp, value, "%f", file, line)

#define SET_NEXT_GAMESTATE(curState, newInit, newStruct) \
    do {                                                 \
        (curState)->init = newInit;                      \
        (curState)->size = sizeof(newStruct);            \
    } while (0)

#define SET_FULLSCREEN_VIEWPORT(view)      \
    {                                      \
        Viewport viewport;                 \
        viewport.bottomY = SCREEN_HEIGHT;  \
        viewport.rightX = SCREEN_WIDTH;    \
        viewport.topY = 0;                 \
        viewport.leftX = 0;                \
        View_SetViewport(view, &viewport); \
    }                                      \
    (void)0

struct GraphicsContext;

extern struct GraphicsContext* __gfxCtx;

#define WORK_DISP       __gfxCtx->work.p
#define POLY_OPA_DISP   __gfxCtx->polyOpa.p
#define POLY_XLU_DISP   __gfxCtx->polyXlu.p
#define OVERLAY_DISP    __gfxCtx->overlay.p

#ifdef OOT_DEBUG

// __gfxCtx shouldn't be used directly.
// Use the DISP macros defined above when writing to display buffers.
#define OPEN_DISPS(gfxCtx, file, line) \
    {                                  \
        GraphicsContext* __gfxCtx;     \
        Gfx* dispRefs[4];              \
        __gfxCtx = gfxCtx;             \
        (void)__gfxCtx;                \
        Graph_OpenDisps(dispRefs, gfxCtx, file, line)

#define CLOSE_DISPS(gfxCtx, file, line)                 \
        Graph_CloseDisps(dispRefs, gfxCtx, file, line); \
    }                                                   \
    (void)0

#define GRAPH_ALLOC(gfxCtx, size) Graph_Alloc(gfxCtx, size)
#define MATRIX_TO_MTX(gfxCtx, file, line) Matrix_ToMtx(gfxCtx, file, line)
#define MATRIX_NEW(gfxCtx, file, line) Matrix_NewMtx(gfxCtx, file, line)
#define MATRIX_CHECK_FLOATS(mtx, file, line) Matrix_CheckFloats(mtx, file, line)
#define DMA_REQUEST_SYNC(ram, vrom, size, file, line) DmaMgr_RequestSyncDebug(ram, vrom, size, file, line)
#define DMA_REQUEST_ASYNC(req, ram, vrom, size, unk5, queue, msg, file, line) DmaMgr_RequestAsyncDebug(req, ram, vrom, size, unk5, queue, msg, file, line)
#define GAME_STATE_ALLOC(gameState, size, file, line) GameState_Alloc(gameState, size, file, line)
#define SYSTEM_ARENA_MALLOC(size, file, line) SystemArena_MallocDebug(size, file, line)
#define SYSTEM_ARENA_MALLOC_R(size, file, line) SystemArena_MallocRDebug(size, file, line)
#define SYSTEM_ARENA_FREE(size, file, line) SystemArena_FreeDebug(size, file, line)
#define ZELDA_ARENA_MALLOC(size, file, line) ZeldaArena_MallocDebug(size, file, line)
#define ZELDA_ARENA_MALLOC_R(size, file, line) ZeldaArena_MallocRDebug(size, file, line)
#define ZELDA_ARENA_FREE(size, file, line) ZeldaArena_FreeDebug(size, file, line)
#define LOG_UTILS_CHECK_NULL_POINTER(exp, ptr, file, line) LogUtils_CheckNullPointer(exp, ptr, file, line)
#define LOG_UTILS_CHECK_VALID_POINTER(exp, ptr, file, line) LogUtils_CheckValidPointer(exp, ptr, file, line)

#else

#define OPEN_DISPS(gfxCtx, file, line)      \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        s32 __dispPad

#define CLOSE_DISPS(gfxCtx, file, line) \
    (void)0;                            \
    }                                   \
    (void)0

#define GRAPH_ALLOC(gfxCtx, size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - ALIGN16(size))))
#define MATRIX_TO_MTX(gfxCtx, file, line) Matrix_ToMtx(gfxCtx)
#define MATRIX_NEW(gfxCtx, file, line) Matrix_NewMtx(gfxCtx)
#define MATRIX_CHECK_FLOATS(mtx, file, line) (mtx)
#define DMA_REQUEST_SYNC(ram, vrom, size, file, line) DmaMgr_RequestSync(ram, vrom, size)
#define DMA_REQUEST_ASYNC(req, ram, vrom, size, unk5, queue, msg, file, line) DmaMgr_RequestAsync(req, ram, vrom, size, unk5, queue, msg)
#define GAME_STATE_ALLOC(gameState, size, file, line) THA_AllocTailAlign16(&(gameState)->tha, size)
#define SYSTEM_ARENA_MALLOC(size, file, line) SystemArena_Malloc(size)
#define SYSTEM_ARENA_MALLOC_R(size, file, line) SystemArena_MallocR(size)
#define SYSTEM_ARENA_FREE(size, file, line) SystemArena_Free(size)
#define ZELDA_ARENA_MALLOC(size, file, line) ZeldaArena_Malloc(size)
#define ZELDA_ARENA_MALLOC_R(size, file, line) ZeldaArena_MallocR(size)
#define ZELDA_ARENA_FREE(size, file, line) ZeldaArena_Free(size)
#define LOG_UTILS_CHECK_NULL_POINTER(exp, ptr, file, line) (void)0
#define LOG_UTILS_CHECK_VALID_POINTER(exp, ptr, file, line) (void)0

#endif /* OOT_DEBUG */

/**
 * `x` vertex x
 * `y` vertex y
 * `z` vertex z
 * `s` texture s coordinate
 * `t` texture t coordinate
 * `crnx` red component of color vertex, or x component of normal vertex
 * `cgny` green component of color vertex, or y component of normal vertex
 * `cbnz` blue component of color vertex, or z component of normal vertex
 * `a` alpha
 */
#define VTX(x,y,z,s,t,crnx,cgny,cbnz,a) { { { x, y, z }, 0, { s, t }, { crnx, cgny, cbnz, a } } }

#define VTX_T(x,y,z,s,t,cr,cg,cb,a) { { x, y, z }, 0, { s, t }, { cr, cg, cb, a } }

#define gDPSetTileCustom(pkt, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                    \
    do {                                                                                                               \
        gDPPipeSync(pkt);                                                                                              \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, \
                   masks, shifts);                                                                                     \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,  \
                   cms, masks, shifts);                                                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    } while (0)

#endif
