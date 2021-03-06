/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __DRIVER__H
#define __DRIVER__H

#include <sys/types.h>
#include <stdbool.h>
#include "libretro_private.h"
#include <stdlib.h>
#include <stdint.h>
#include "gfx/image/image.h"
#include "input/overlay.h"
#ifdef HAVE_SCALERS_BUILTIN
#include "gfx/filters/softfilter.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AUDIO_CHUNK_SIZE_BLOCKING 512
#define AUDIO_CHUNK_SIZE_NONBLOCKING 2048 // So we don't get complete line-noise when fast-forwarding audio.
#define AUDIO_MAX_RATIO 16

// Specialized _POINTER that targets the full screen regardless of viewport.
// Should not be used by a libretro implementation as coordinates returned make no sense.
// It is only used internally for overlays.
#define RARCH_DEVICE_POINTER_SCREEN (RETRO_DEVICE_POINTER | 0x10000)

// libretro has 16 buttons from 0-15 (libretro.h)
// Analog binds use RETRO_DEVICE_ANALOG, but we follow the same scheme internally
// in RetroArch for simplicity,
// so they are mapped into [16, 23].
#define RARCH_FIRST_CUSTOM_BIND 16
#define RARCH_FIRST_META_KEY RARCH_CUSTOM_BIND_LIST_END
enum // RetroArch specific bind IDs.
{
   // Custom binds that extend the scope of RETRO_DEVICE_JOYPAD for RetroArch specifically.
   // Analogs (RETRO_DEVICE_ANALOG)
   RARCH_ANALOG_LEFT_X_PLUS = RARCH_FIRST_CUSTOM_BIND,
   RARCH_ANALOG_LEFT_X_MINUS,
   RARCH_ANALOG_LEFT_Y_PLUS,
   RARCH_ANALOG_LEFT_Y_MINUS,
   RARCH_ANALOG_RIGHT_X_PLUS,
   RARCH_ANALOG_RIGHT_X_MINUS,
   RARCH_ANALOG_RIGHT_Y_PLUS,
   RARCH_ANALOG_RIGHT_Y_MINUS,

   // Turbo
   RARCH_TURBO_ENABLE,

   RARCH_CUSTOM_BIND_LIST_END,

   // Command binds. Not related to game input, only usable for port 0.
   RARCH_FAST_FORWARD_KEY = RARCH_FIRST_META_KEY,
   RARCH_FAST_FORWARD_HOLD_KEY,
   RARCH_LOAD_STATE_KEY,
   RARCH_SAVE_STATE_KEY,
   RARCH_QUIT_KEY,
   RARCH_STATE_SLOT_PLUS,
   RARCH_STATE_SLOT_MINUS,
   RARCH_REWIND,
   RARCH_PAUSE_TOGGLE,
   RARCH_FRAMEADVANCE,
   RARCH_RESET,
   RARCH_SCREENSHOT,
   RARCH_MUTE,
   RARCH_SLOWMOTION,
   RARCH_ENABLE_HOTKEY,
   RARCH_VOLUME_UP,
   RARCH_VOLUME_DOWN,
   RARCH_DISK_EJECT_TOGGLE,
   RARCH_DISK_NEXT,
   RARCH_QUICK_SWAP,
   RARCH_MENU_TOGGLE,
   RARCH_BIND_LIST_END,
   RARCH_BIND_LIST_END_NULL
};

enum // Console specific menu bind IDs.
{
   CONSOLE_MENU_FIRST      = 61,
   CONSOLE_MENU_A          = CONSOLE_MENU_FIRST,
   CONSOLE_MENU_B          = 62,
   CONSOLE_MENU_X          = 63,
   CONSOLE_MENU_Y          = 64,
   CONSOLE_MENU_START      = 65,
   CONSOLE_MENU_SELECT     = 66,
   CONSOLE_MENU_UP         = 67,
   CONSOLE_MENU_DOWN       = 68,
   CONSOLE_MENU_LEFT       = 69,
   CONSOLE_MENU_RIGHT      = 70,
   CONSOLE_MENU_L          = 71,
   CONSOLE_MENU_R          = 72,
   CONSOLE_MENU_L2         = 73,
   CONSOLE_MENU_R2         = 74,
   CONSOLE_MENU_L3         = 75,
   CONSOLE_MENU_R3         = 76,
   CONSOLE_MENU_HOME       = 77,
   CONSOLE_MENU_LAST       = CONSOLE_MENU_HOME,
};

struct retro_keybind
{
   bool valid;
   unsigned id;
   const char *desc;

   // PC only uses lower 16-bits.
   // Full 64-bit can be used for port-specific purposes, like simplifying multiple binds, etc.
   uint64_t joykey;

   // Default key binding value - for resetting bind to default
   uint64_t def_joykey;

   uint32_t joyaxis;
   uint32_t def_joyaxis;

   uint32_t orig_joyaxis; // Used by input_{push,pop}_analog_dpad().
};

struct platform_bind
{
   uint64_t joykey;
   char desc[64];
};

typedef struct audio_driver
{
   void *(*init)(const char *device, unsigned rate, unsigned latency);
   ssize_t (*write)(void *data, const void *buf, size_t size);
   bool (*stop)(void *data);
   bool (*start)(void *data);
   void (*set_nonblock_state)(void *data, bool toggle);
   void (*free)(void *data);
   const char *ident;

   size_t (*write_avail)(void *data); // Optional
   size_t (*buffer_size)(void *data); // Optional
} audio_driver_t;

#define AXIS_NEG(x) (((uint32_t)(x) << 16) | UINT16_C(0xFFFF))
#define AXIS_POS(x) ((uint32_t)(x) | UINT32_C(0xFFFF0000))
#define AXIS_NONE UINT32_C(0xFFFFFFFF)
#define AXIS_DIR_NONE UINT16_C(0xFFFF)

#define AXIS_NEG_GET(x) (((uint32_t)(x) >> 16) & UINT16_C(0xFFFF))
#define AXIS_POS_GET(x) ((uint32_t)(x) & UINT16_C(0xFFFF))

#define NO_BTN UINT16_C(0xFFFF) // I hope no joypad will ever have this many buttons ... ;)

#define HAT_UP_SHIFT 15
#define HAT_DOWN_SHIFT 14
#define HAT_LEFT_SHIFT 13
#define HAT_RIGHT_SHIFT 12
#define HAT_UP_MASK (1 << HAT_UP_SHIFT)
#define HAT_DOWN_MASK (1 << HAT_DOWN_SHIFT)
#define HAT_LEFT_MASK (1 << HAT_LEFT_SHIFT)
#define HAT_RIGHT_MASK (1 << HAT_RIGHT_SHIFT)
#define HAT_MAP(x, hat) ((x & ((1 << 12) - 1)) | hat)

#define HAT_MASK (HAT_UP_MASK | HAT_DOWN_MASK | HAT_LEFT_MASK | HAT_RIGHT_MASK)
#define GET_HAT_DIR(x) (x & HAT_MASK)
#define GET_HAT(x) (x & (~HAT_MASK))

enum input_devices
{
   DEVICE_GXPAD = 1,
   DEVICE_LAST
};

enum analog_dpad_mode
{
   ANALOG_DPAD_NONE = 0,
   ANALOG_DPAD_LSTICK,
   ANALOG_DPAD_RSTICK,
   ANALOG_DPAD_DUALANALOG,
   ANALOG_DPAD_LAST
};

enum keybind_set_id
{
   KEYBINDS_ACTION_NONE = 0,
   KEYBINDS_ACTION_SET_DEFAULT_BIND,
   KEYBINDS_ACTION_SET_DEFAULT_BINDS,
   KEYBINDS_ACTION_SET_PAD_NAME,
   KEYBINDS_ACTION_GET_BIND_LABEL,
};

typedef struct rarch_joypad_driver rarch_joypad_driver_t;

typedef struct input_driver
{
   void *(*init)(void);
   void (*poll)(void *data);
   int16_t (*input_state)(void *data, const struct retro_keybind **retro_keybinds,
         unsigned port, unsigned device, unsigned index, unsigned id);
   bool (*key_pressed)(void *data, int key);
   void (*free)(void *data);
   void (*set_keybinds)(void *data, unsigned device, unsigned port, unsigned id, unsigned keybind_action);
   uint64_t (*get_capabilities)(void *data);
   const char *ident;
   bool (*set_rumble)(void *data, unsigned port, enum retro_rumble_effect effect, uint16_t state);
   const rarch_joypad_driver_t *(*get_joypad_driver)(void *data);
} input_driver_t;

struct rarch_viewport;

#ifdef HAVE_OVERLAY
typedef struct video_overlay_interface
{
   void (*enable)(void *data, bool state);
   bool (*load)(void *data, const struct texture_image *images, unsigned num_images);
   void (*tex_geom)(void *data, unsigned image, float x, float y, float w, float h);
   void (*vertex_geom)(void *data, unsigned image, float x, float y, float w, float h);
   void (*full_screen)(void *data, bool enable);
   void (*set_alpha)(void *data, unsigned image, float mod);
   void (*free)(void *data);
} video_overlay_interface_t;
#endif

// Optionally implemented interface to poke more deeply into video driver.
typedef struct video_poke_interface
{
   void (*force_viewport_refresh)(void *data);
   void (*set_aspect_ratio)(void *data, unsigned aspectratio_index);
   void (*apply_state_changes)(void *data);
   void (*set_texture_frame)(void *data, const void *frame, bool rgb32, unsigned width, unsigned height, float alpha);
   void (*set_texture_enable)(void *data, bool enable, bool full_screen); // Enable/disable rendering.
   void (*update_screen_config)(void *data, unsigned res_idx, unsigned aspect_idx, bool scale_integer, unsigned orientation);
   void (*get_resolution_info)(void *data, unsigned res_index, unsigned *width, unsigned *height, unsigned *type);
   void (*set_refresh_rate)(void *data, unsigned res_index);
   void (*match_resolution_auto)(unsigned fbWidth, unsigned fbLines);
} video_poke_interface_t;

typedef struct video_driver
{
   bool (*init)(void **data, unsigned scale, bool rgb32);
   bool (*frame)(void *data, const void *frame, unsigned width, unsigned height, unsigned pitch, const char *msg); // msg is for showing a message on the screen along with the video frame.
   void (*set_nonblock_state)(void *data, bool toggle); // Should we care about syncing to vblank? Fast forwarding.
   void (*free)(void *data);
   const char *ident;
   void (*set_rotation)(void *data, unsigned rotation);
   void (*viewport_info)(void *data, struct rarch_viewport *vp);
#ifdef HAVE_OVERLAY
   void (*overlay_interface)(void *data, const video_overlay_interface_t **iface);
#endif
   void (*poke_interface)(void *data, const video_poke_interface_t **iface);
} video_driver_t;

typedef struct driver
{
   const audio_driver_t *audio;
   const video_driver_t *video;
   const input_driver_t *input;
   void *audio_data;
   void *video_data;
   void *input_data;

  // Set if the respective handles are owned by RetroArch driver core.
   // Consoles upper logic will generally intialize the drivers before
   // the driver core initializes. It will then be up to upper logic
   // to finally free() up the driver handles.
   // Driver core will still call init() and free(), but in this case
   // these calls should be seen as "reinit() + ref_count++" and "ref_count--"
   // respectively.
   bool video_input_locked;
   bool block_hotkey;
   bool block_input;
   bool nonblock_state;

#ifdef HAVE_OVERLAY
   input_overlay_t *overlay;
#endif

   // Interface for "poking".
   const video_poke_interface_t *video_poke;

   // last message given to the video driver
   const char *current_msg;
} driver_t;

void init_drivers(void);
void find_drivers(void);
void uninit_drivers(void);

void global_init_drivers(void);
void global_uninit_drivers(void);

void init_video_input(void);
void uninit_video_input(void);
void init_audio(void);
void uninit_audio(void);

void find_prev_resampler_driver(void);
void find_prev_video_driver(void);
void find_prev_audio_driver(void);
void find_prev_input_driver(void);
void find_next_video_driver(void);
void find_next_audio_driver(void);
void find_next_input_driver(void);
void find_next_resampler_driver(void);

void driver_set_monitor_refresh_rate(float hz);
void driver_set_nonblock_state(bool nonblock);

// Used by RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE
bool driver_set_rumble_state(unsigned port, enum retro_rumble_effect effect, uint16_t strength);

// Used by RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO
bool driver_update_system_av_info(const struct retro_system_av_info *info);

extern driver_t driver;

//////////////////////////////////////////////// Backends
#ifdef HAVE_SCALERS_BUILTIN
extern const softfilter_implementation_t blargg_ntsc_rf_implementation;
extern const softfilter_implementation_t blargg_ntsc_composite_implementation;
extern const softfilter_implementation_t blargg_ntsc_monochrome_implementation;
extern const softfilter_implementation_t epx_implementation;
extern const softfilter_implementation_t epxsmooth_implementation;
extern const softfilter_implementation_t twoxsai_implementation;
extern const softfilter_implementation_t supereagle_implementation;
extern const softfilter_implementation_t supertwoxsai_implementation;
extern const softfilter_implementation_t hq2x_implementation;
extern const softfilter_implementation_t scanlines_implementation;
#ifdef HAVE_ALL_SCALERS
extern const softfilter_implementation_t lq2x_implementation;
extern const softfilter_implementation_t twoxbr_implementation;
extern const softfilter_implementation_t scale2x_implementation;
extern const softfilter_implementation_t darken_implementation;
extern const softfilter_implementation_t blargg_ntsc_rgb_implementation;
extern const softfilter_implementation_t blargg_ntsc_svideo_implementation;
extern const softfilter_implementation_t phosphor2x_implementation;
#endif
#endif

#include "driver_funcs.h"

#ifdef __cplusplus
}
#endif

#endif
