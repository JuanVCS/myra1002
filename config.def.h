/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2014 - Daniel De Matteis
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

/// Config header for RetroArch
//
//

#ifndef __CONFIG_DEF_H
#define __CONFIG_DEF_H

#include "boolean.h"
#include "libretro.h"
#include "driver.h"
#include "gfx/gfx_common.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HW_RVL
#include "gx/gx_input.h"
#include "gx/gx_hid_input.h"
#endif

enum
{
   VIDEO_GL = 0,
   VIDEO_XVIDEO,
   VIDEO_SDL,
   VIDEO_EXT,
   VIDEO_WII,
   VIDEO_D3D9,
   VIDEO_VG,
   VIDEO_NULL,

   AUDIO_OSS,
   AUDIO_ALSA,
   AUDIO_ALSATHREAD,
   AUDIO_ROAR,
   AUDIO_AL,
   AUDIO_JACK,
   AUDIO_SDL,
   AUDIO_XAUDIO,
   AUDIO_PULSE,
   AUDIO_EXT,
   AUDIO_DSOUND,
   AUDIO_COREAUDIO,
   AUDIO_WII,
   AUDIO_NULL,

   INPUT_SDL,
   INPUT_X,
   INPUT_DINPUT,
   INPUT_WII,
   INPUT_XINPUT,
   INPUT_UDEV,
   INPUT_LINUXRAW,
   INPUT_NULL,
};

#if defined(HAVE_OPENGL) || defined(HAVE_OPENGLES)
#define VIDEO_DEFAULT_DRIVER VIDEO_GL
#elif defined(GEKKO)
#define VIDEO_DEFAULT_DRIVER VIDEO_WII
#elif defined(HAVE_WIN32_D3D9)
#define VIDEO_DEFAULT_DRIVER VIDEO_D3D9
#elif defined(HAVE_VG)
#define VIDEO_DEFAULT_DRIVER VIDEO_VG
#elif defined(HAVE_XVIDEO)
#define VIDEO_DEFAULT_DRIVER VIDEO_XVIDEO
#elif defined(HAVE_SDL)
#define VIDEO_DEFAULT_DRIVER VIDEO_SDL
#elif defined(HAVE_DYLIB)
#define VIDEO_DEFAULT_DRIVER VIDEO_EXT
#else
#define VIDEO_DEFAULT_DRIVER VIDEO_NULL
#endif

#if defined(GEKKO)
#define AUDIO_DEFAULT_DRIVER AUDIO_WII
#elif defined(HAVE_ALSA) && defined(HAVE_VIDEOCORE)
#define AUDIO_DEFAULT_DRIVER AUDIO_ALSATHREAD
#elif defined(HAVE_ALSA)
#define AUDIO_DEFAULT_DRIVER AUDIO_ALSA
#elif defined(HAVE_PULSE)
#define AUDIO_DEFAULT_DRIVER AUDIO_PULSE
#elif defined(HAVE_OSS)
#define AUDIO_DEFAULT_DRIVER AUDIO_OSS
#elif defined(HAVE_JACK)
#define AUDIO_DEFAULT_DRIVER AUDIO_JACK
#elif defined(HAVE_COREAUDIO)
#define AUDIO_DEFAULT_DRIVER AUDIO_COREAUDIO
#elif defined(HAVE_AL)
#define AUDIO_DEFAULT_DRIVER AUDIO_AL
#elif defined(HAVE_DSOUND)
#define AUDIO_DEFAULT_DRIVER AUDIO_DSOUND
#elif defined(HAVE_SDL)
#define AUDIO_DEFAULT_DRIVER AUDIO_SDL
#elif defined(HAVE_XAUDIO)
#define AUDIO_DEFAULT_DRIVER AUDIO_XAUDIO
#elif defined(HAVE_ROAR)
#define AUDIO_DEFAULT_DRIVER AUDIO_ROAR
#elif defined(HAVE_DYLIB)
#define AUDIO_DEFAULT_DRIVER AUDIO_EXT
#else
#define AUDIO_DEFAULT_DRIVER AUDIO_NULL
#endif

#if defined(HAVE_XINPUT2) || defined(HAVE_XINPUT_XBOX1)
#define INPUT_DEFAULT_DRIVER INPUT_XINPUT
#elif defined(_WIN32)
#define INPUT_DEFAULT_DRIVER INPUT_DINPUT
#elif defined(GEKKO)
#define INPUT_DEFAULT_DRIVER INPUT_WII
#elif defined(HAVE_UDEV)
#define INPUT_DEFAULT_DRIVER INPUT_UDEV
#elif defined(__linux__)
#define INPUT_DEFAULT_DRIVER INPUT_LINUXRAW
#elif defined(HAVE_X11)
#define INPUT_DEFAULT_DRIVER INPUT_X
#elif defined(HAVE_SDL)
#define INPUT_DEFAULT_DRIVER INPUT_SDL
#else
#define INPUT_DEFAULT_DRIVER INPUT_NULL
#endif

#define DEFAULT_ASPECT_RATIO -1.0f

////////////////
// Video
////////////////

#define DEFAULT_GAMMA 0

// Windowed
static const float xscale = 3.0; // Real x res = aspect * base_size * xscale
static const float yscale = 3.0; // Real y res = base_size * yscale

// Fullscreen
static const bool fullscreen = true;  // To start in Fullscreen or not.
static const bool windowed_fullscreen = true;  // To use windowed mode or not when going fullscreen.
static const unsigned monitor_index = 0; // Which monitor to prefer. 0 is any monitor, 1 and up selects specific monitors, 1 being the first monitor.
static const unsigned fullscreen_x = 0; // Fullscreen resolution. A value of 0 uses the desktop resolution.
static const unsigned fullscreen_y = 0;

// Forcibly disable composition. Only valid on Windows Vista/7 for now.
static const bool disable_composition = false;

// Video VSYNC (recommended)
static const bool vsync = true;

// Uses a custom swap interval for VSync.
// Set this to effectively halve monitor refresh rate.
static unsigned swap_interval = 1;
// Threaded video. Will possibly increase performance significantly at cost of worse synchronization and latency.
static const bool video_threaded = false;

// Smooths picture
static const bool video_smooth = true;

// On resize and fullscreen, rendering area will stay 4:3
static const bool force_aspect = true;

// Enable use of shaders.
#ifdef RARCH_CONSOLE
static const bool shader_enable = true;
#else
static const bool shader_enable = false;
#endif

// Only scale in integer steps.
// The base size depends on system-reported geometry and aspect ratio.
// If video_force_aspect is not set, X/Y will be integer scaled independently.
static const bool scale_integer = false;

// Controls aspect ratio handling.
static const float aspect_ratio = DEFAULT_ASPECT_RATIO; // Automatic
static unsigned aspect_ratio_idx = ASPECT_RATIO_4_3;

// Save configuration file on exit
static bool config_save_on_exit = true;

#ifdef HAVE_OVERLAY
// Default overlay directory
static const char *default_overlay_dir = NULL;
#endif

static const char *default_shader_dir = NULL;
static const char *default_config_path = NULL;
static const char *default_libretro_info_path = NULL;

// Crop overscanned frames.
static const bool crop_overscan = true;

// Font size for on-screen messages.
static const float font_size = 48;

// Attempt to scale the font size.
// The scale factor will be window_size / desktop_size.
static const bool font_scale = true;

// Offset for where messages will be placed on-screen. Values are in range [0.0, 1.0].
static const float message_pos_offset_x = 0.05;
static const float message_pos_offset_y = 0.05;
// Color of the message.
static const uint32_t message_color = 0xffff00; // RGB hex value.

// Screenshots post-shaded GPU output if available.
static const bool gpu_screenshot = false;

// OSD-messages
static const bool font_enable = true;

// The accurate refresh rate of your monitor (Hz).
// This is used to calculate audio input rate with the formula:
// audio_input_rate = game_input_rate * display_refresh_rate / game_refresh_rate.
// If the implementation does not report any values,
// SNES NTSC defaults will be assumed for compatibility.
// This value should stay close to 60Hz to avoid large pitch changes.
// If your monitor does not run at 60Hz, or something close to it, disable VSync,
// and leave this at its default.
#if defined(RARCH_CONSOLE)
static const float refresh_rate = 60/1.001;
#else
static const float refresh_rate = 59.95;
#endif

// Allow games to set rotation. If false, rotation requests are honored, but ignored.
// Used for setups where one manually rotates the monitor.
static const bool allow_rotate = true;

////////////////
// Audio
////////////////

// Will enable audio or not.
static const bool audio_enable = true;

// Output samplerate
#ifdef GEKKO
static const unsigned out_rate = 32000;
#else
static const unsigned out_rate = 48000;
#endif

// Audio device (e.g. hw:0,0 or /dev/audio). If NULL, will use defaults.
static const char *audio_device = NULL;

// Desired audio latency in milliseconds. Might not be honored if driver can't provide given latency.
static const int out_latency = 64;

// Will sync audio. (recommended)
static const bool audio_sync = true;

// Default resampler
static const char *audio_resampler = "sinc";

// Experimental rate control
#if defined(GEKKO) || !defined(RARCH_CONSOLE)
static const bool rate_control = true;
#else
static const bool rate_control = false;
#endif

// Rate control delta. Defines how much rate_control is allowed to adjust input rate.
static const float rate_control_delta = 0.005;

// Default audio volume in dB. (0.0 dB == unity gain).
static const float audio_volume = 0.0;

//////////////
// Misc
//////////////

// Enables use of rewind. This will incur some memory footprint depending on the save state buffer.
static const bool rewind_enable = false;

// The buffer size for the rewind buffer. This needs to be about 15-20MB per minute. Very game dependant.
static const unsigned rewind_buffer_size = 20 << 20; // 20MiB

// How many frames to rewind at a time.
static const unsigned rewind_granularity = 1;

// Pause gameplay when gameplay loses focus.
static const bool pause_nonactive = false;

// Saves non-volatile SRAM at a regular interval. It is measured in seconds. A value of 0 disables autosave.
static const unsigned autosave_interval = 0;

// On save state load, block SRAM from being overwritten.
// This could potentially lead to buggy games.
static const bool block_sram_overwrite = false;

// When saving savestates, state index is automatically incremented before saving.
// When the ROM is loaded, state index will be set to the highest existing value.
static const bool savestate_auto_index = false;

// Automatically saves a savestate at the end of RetroArch's lifetime.
// The path is $SRAM_PATH.auto.
// RetroArch will automatically load any savestate with this path on startup if savestate_auto_load is set.
static const bool savestate_auto_save = false;
static const bool savestate_auto_load = true;

// Slowmotion ratio.
static const float slowmotion_ratio = 3.0;

// Maximum fast forward ratio (Negative => no limit).
static const float fastforward_ratio = -1.0;

// Enable stdin command interface
static const bool stdin_cmd_enable = false;

// Number of entries that will be kept in ROM history file.
static const unsigned game_history_size = 100;

// Log level for libretro cores (GET_LOG_INTERFACE).
static const unsigned libretro_log_level = 0;


////////////////////
// Keybinds, Joypad
////////////////////

// Axis threshold (between 0.0 and 1.0)
// How far an axis must be tilted to result in a button press
static const float axis_threshold = 0.5;

// Describes speed of which turbo-enabled buttons toggle.
static const unsigned turbo_period = 6;
static const unsigned turbo_duty_cycle = 3;

// Enable input debugging output.
static const bool input_debug_enable = false;

// Enable input auto-config gamepad buttons, plug-and-play style.
static const bool input_autoconf_buttons = true;

// Number of players to rotate using the quick swap controller feature.
// 1 means disabled.
static const unsigned quick_swap_players = 1;

/* Enable all players can control the menu */
static const bool menu_all_players_enable = false;

#ifndef IS_SALAMANDER

#define RETRO_DEF_JOYPAD_B NO_BTN
#define RETRO_DEF_JOYPAD_Y NO_BTN
#define RETRO_DEF_JOYPAD_SELECT NO_BTN
#define RETRO_DEF_JOYPAD_START NO_BTN
#define RETRO_DEF_JOYPAD_UP NO_BTN
#define RETRO_DEF_JOYPAD_DOWN NO_BTN
#define RETRO_DEF_JOYPAD_LEFT NO_BTN
#define RETRO_DEF_JOYPAD_RIGHT NO_BTN
#define RETRO_DEF_JOYPAD_A NO_BTN
#define RETRO_DEF_JOYPAD_X NO_BTN
#define RETRO_DEF_JOYPAD_L NO_BTN
#define RETRO_DEF_JOYPAD_R NO_BTN
#define RETRO_DEF_JOYPAD_L2 NO_BTN
#define RETRO_DEF_JOYPAD_R2 NO_BTN
#define RETRO_DEF_JOYPAD_L3 NO_BTN
#define RETRO_DEF_JOYPAD_R3 NO_BTN
#define RETRO_DEF_ANALOGL_DPAD_LEFT NO_BTN
#define RETRO_DEF_ANALOGL_DPAD_RIGHT NO_BTN
#define RETRO_DEF_ANALOGL_DPAD_UP NO_BTN
#define RETRO_DEF_ANALOGL_DPAD_DOWN NO_BTN
#define RETRO_DEF_ANALOGR_DPAD_LEFT NO_BTN
#define RETRO_DEF_ANALOGR_DPAD_RIGHT NO_BTN
#define RETRO_DEF_ANALOGR_DPAD_UP NO_BTN
#define RETRO_DEF_ANALOGR_DPAD_DOWN NO_BTN

#define RETRO_LBL_JOYPAD_B "RetroPad B Button"
#define RETRO_LBL_JOYPAD_Y "RetroPad Y Button"
#define RETRO_LBL_JOYPAD_SELECT "RetroPad Select Button"
#define RETRO_LBL_JOYPAD_START "RetroPad Start Button"
#define RETRO_LBL_JOYPAD_UP "RetroPad D-Pad Up"
#define RETRO_LBL_JOYPAD_DOWN "RetroPad D-Pad Down"
#define RETRO_LBL_JOYPAD_LEFT "RetroPad D-Pad Left"
#define RETRO_LBL_JOYPAD_RIGHT "RetroPad D-Pad Right"
#define RETRO_LBL_JOYPAD_A "RetroPad A Button"
#define RETRO_LBL_JOYPAD_X "RetroPad X Button"
#define RETRO_LBL_JOYPAD_L "RetroPad L Button"
#define RETRO_LBL_JOYPAD_R "RetroPad R Button"
#define RETRO_LBL_JOYPAD_L2 "RetroPad L2 Button"
#define RETRO_LBL_JOYPAD_R2 "RetroPad R2 Button"
#define RETRO_LBL_JOYPAD_L3 "RetroPad L3 Button"
#define RETRO_LBL_JOYPAD_R3 "RetroPad R3 Button"
#define RETRO_LBL_TURBO_ENABLE "Turbo Enable"
#define RETRO_LBL_ANALOG_LEFT_X_PLUS "Left Analog X +"
#define RETRO_LBL_ANALOG_LEFT_X_MINUS "Left Analog X -"
#define RETRO_LBL_ANALOG_LEFT_Y_PLUS "Left Analog Y +"
#define RETRO_LBL_ANALOG_LEFT_Y_MINUS "Left Analog Y -"
#define RETRO_LBL_ANALOG_RIGHT_X_PLUS "Right Analog X +"
#define RETRO_LBL_ANALOG_RIGHT_X_MINUS "Right Analog X -"
#define RETRO_LBL_ANALOG_RIGHT_Y_PLUS "Right Analog Y +"
#define RETRO_LBL_ANALOG_RIGHT_Y_MINUS "Right Analog Y -"
#define RETRO_LBL_FAST_FORWARD_KEY "Fast Forward"
#define RETRO_LBL_FAST_FORWARD_HOLD_KEY "Fast Forward Hold"
#define RETRO_LBL_LOAD_STATE_KEY "Load State"
#define RETRO_LBL_SAVE_STATE_KEY "Save State"
#define RETRO_LBL_QUIT_KEY "Quit Key"
#define RETRO_LBL_STATE_SLOT_PLUS "State Slot Plus"
#define RETRO_LBL_STATE_SLOT_MINUS "State Slot Minus"
#define RETRO_LBL_REWIND "Rewind"
#define RETRO_LBL_PAUSE_TOGGLE "Pause Toggle"
#define RETRO_LBL_FRAMEADVANCE "Frame Advance"
#define RETRO_LBL_RESET "Reset"
#define RETRO_LBL_SCREENSHOT "Screenshot"
#define RETRO_LBL_MUTE "Mute Audio"
#define RETRO_LBL_SLOWMOTION "Slowmotion"
#define RETRO_LBL_ENABLE_HOTKEY "Enable Hotkey"
#define RETRO_LBL_VOLUME_UP "Volume Up"
#define RETRO_LBL_VOLUME_DOWN "Volume Down"
#define RETRO_LBL_DISK_EJECT_TOGGLE "Disk Eject Toggle"
#define RETRO_LBL_DISK_NEXT "Disk Swap Next"
#define RETRO_LBL_QUICK_SWAP "Controller Quick Swap"
#ifndef RARCH_CONSOLE
#define RETRO_LBL_FULLSCREEN_TOGGLE_KEY "Fullscreen Toggle"
#define RETRO_LBL_SHADER_NEXT "Next Shader"
#define RETRO_LBL_SHADER_PREV "Previous Shader"
#define RETRO_LBL_OVERLAY_NEXT "Next Overlay"
#define RETRO_LBL_GRAB_MOUSE_TOGGLE "Grab mouse toggle"
#endif
#ifdef HAVE_MENU
#define RETRO_LBL_MENU_TOGGLE "Menu toggle"
#endif

// Player 1
static const struct retro_keybind retro_keybinds_1[] = {
    //     | RetroPad button            | desc                           | keyboard key  | js btn |     js axis   |
   { true, RETRO_DEVICE_ID_JOYPAD_B,      RETRO_LBL_JOYPAD_B,              RETROK_z,       RETRO_DEF_JOYPAD_B,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_Y,      RETRO_LBL_JOYPAD_Y,              RETROK_a,       RETRO_DEF_JOYPAD_Y,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_SELECT, RETRO_LBL_JOYPAD_SELECT,         RETROK_RSHIFT,  RETRO_DEF_JOYPAD_SELECT, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_START,  RETRO_LBL_JOYPAD_START,          RETROK_RETURN,  RETRO_DEF_JOYPAD_START,  0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_UP,     RETRO_LBL_JOYPAD_UP,             RETROK_UP,      RETRO_DEF_JOYPAD_UP,     0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_DOWN,   RETRO_LBL_JOYPAD_DOWN,           RETROK_DOWN,    RETRO_DEF_JOYPAD_DOWN,   0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_LEFT,   RETRO_LBL_JOYPAD_LEFT,           RETROK_LEFT,    RETRO_DEF_JOYPAD_LEFT,   0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_RIGHT,  RETRO_LBL_JOYPAD_RIGHT,          RETROK_RIGHT,   RETRO_DEF_JOYPAD_RIGHT,  0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_A,      RETRO_LBL_JOYPAD_A,              RETROK_x,       RETRO_DEF_JOYPAD_A,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_X,      RETRO_LBL_JOYPAD_X,              RETROK_s,       RETRO_DEF_JOYPAD_X,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L,      RETRO_LBL_JOYPAD_L,              RETROK_q,       RETRO_DEF_JOYPAD_L,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R,      RETRO_LBL_JOYPAD_R,              RETROK_w,       RETRO_DEF_JOYPAD_R,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L2,     RETRO_LBL_JOYPAD_L2,             RETROK_UNKNOWN, RETRO_DEF_JOYPAD_L2,     0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R2,     RETRO_LBL_JOYPAD_R2,             RETROK_UNKNOWN, RETRO_DEF_JOYPAD_R2,     0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L3,     RETRO_LBL_JOYPAD_L3,             RETROK_UNKNOWN, RETRO_DEF_JOYPAD_L3,     0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R3,     RETRO_LBL_JOYPAD_R3,             RETROK_UNKNOWN, RETRO_DEF_JOYPAD_R3,     0, AXIS_NONE },

   { true, RARCH_ANALOG_LEFT_X_PLUS,      RETRO_LBL_ANALOG_LEFT_X_PLUS,    RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_X_MINUS,     RETRO_LBL_ANALOG_LEFT_X_MINUS,   RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_Y_PLUS,      RETRO_LBL_ANALOG_LEFT_Y_PLUS,    RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_Y_MINUS,     RETRO_LBL_ANALOG_LEFT_Y_MINUS,   RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_X_PLUS,     RETRO_LBL_ANALOG_RIGHT_X_PLUS,   RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_X_MINUS,    RETRO_LBL_ANALOG_RIGHT_X_MINUS,  RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_Y_PLUS,     RETRO_LBL_ANALOG_RIGHT_Y_PLUS,   RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_Y_MINUS,    RETRO_LBL_ANALOG_RIGHT_Y_MINUS,  RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },

   { true, RARCH_TURBO_ENABLE,             RETRO_LBL_TURBO_ENABLE,         RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_FAST_FORWARD_KEY,         RETRO_LBL_FAST_FORWARD_KEY,     RETROK_SPACE,   NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_FAST_FORWARD_HOLD_KEY,    RETRO_LBL_FAST_FORWARD_HOLD_KEY,RETROK_l,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_LOAD_STATE_KEY,           RETRO_LBL_LOAD_STATE_KEY,       RETROK_F4,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_SAVE_STATE_KEY,           RETRO_LBL_SAVE_STATE_KEY,       RETROK_F2,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_QUIT_KEY,                 RETRO_LBL_QUIT_KEY,             RETROK_ESCAPE,  NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_STATE_SLOT_PLUS,          RETRO_LBL_STATE_SLOT_PLUS,      RETROK_F7,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_STATE_SLOT_MINUS,         RETRO_LBL_STATE_SLOT_MINUS,     RETROK_F6,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_REWIND,                   RETRO_LBL_REWIND,               RETROK_r,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_PAUSE_TOGGLE,             RETRO_LBL_PAUSE_TOGGLE,         RETROK_p,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_FRAMEADVANCE,             RETRO_LBL_FRAMEADVANCE,         RETROK_k,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_RESET,                    RETRO_LBL_RESET,                RETROK_h,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_SCREENSHOT,               RETRO_LBL_SCREENSHOT,           RETROK_F8,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_MUTE,                     RETRO_LBL_MUTE,                 RETROK_F9,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_SLOWMOTION,               RETRO_LBL_SLOWMOTION,           RETROK_e,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_ENABLE_HOTKEY,            RETRO_LBL_ENABLE_HOTKEY,        RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_VOLUME_UP,                RETRO_LBL_VOLUME_UP,            RETROK_KP_PLUS, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_VOLUME_DOWN,              RETRO_LBL_VOLUME_DOWN,          RETROK_KP_MINUS,NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_DISK_EJECT_TOGGLE,        RETRO_LBL_DISK_EJECT_TOGGLE,    RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_DISK_NEXT,                RETRO_LBL_DISK_NEXT,            RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_QUICK_SWAP,               RETRO_LBL_QUICK_SWAP,           RETROK_c,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
#ifndef RARCH_CONSOLE
   { true, RARCH_FULLSCREEN_TOGGLE_KEY,    RETRO_LBL_FULLSCREEN_TOGGLE_KEY,RETROK_f,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_SHADER_NEXT,              RETRO_LBL_SHADER_NEXT,          RETROK_m,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_SHADER_PREV,              RETRO_LBL_SHADER_PREV,          RETROK_n,       NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_OVERLAY_NEXT,             RETRO_LBL_OVERLAY_NEXT,         RETROK_UNKNOWN, NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
   { true, RARCH_GRAB_MOUSE_TOGGLE,        RETRO_LBL_GRAB_MOUSE_TOGGLE,    RETROK_F11,     NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
#endif
#ifdef HAVE_MENU
   { true, RARCH_MENU_TOGGLE,              RETRO_LBL_MENU_TOGGLE,          RETROK_F1,      NO_BTN, NO_BTN, AXIS_NONE, AXIS_NONE },
#endif
};

#ifdef RARCH_CONSOLE
static const struct retro_keybind retro_keybinds_menu[] = {
   { true, RETRO_DEVICE_ID_JOYPAD_B,      RETRO_LBL_JOYPAD_B,              RETROK_UNKNOWN, CONSOLE_MENU_B,          0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_Y,      RETRO_LBL_JOYPAD_Y,              RETROK_UNKNOWN, CONSOLE_MENU_Y,          0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_SELECT, RETRO_LBL_JOYPAD_SELECT,         RETROK_UNKNOWN, CONSOLE_MENU_SELECT,     0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_START,  RETRO_LBL_JOYPAD_START,          RETROK_UNKNOWN, CONSOLE_MENU_START,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_UP,     RETRO_LBL_JOYPAD_UP,             RETROK_UNKNOWN, CONSOLE_MENU_UP,         0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_DOWN,   RETRO_LBL_JOYPAD_DOWN,           RETROK_UNKNOWN, CONSOLE_MENU_DOWN,       0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_LEFT,   RETRO_LBL_JOYPAD_LEFT,           RETROK_UNKNOWN, CONSOLE_MENU_LEFT,       0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_RIGHT,  RETRO_LBL_JOYPAD_RIGHT,          RETROK_UNKNOWN, CONSOLE_MENU_RIGHT,      0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_A,      RETRO_LBL_JOYPAD_A,              RETROK_UNKNOWN, CONSOLE_MENU_A,          0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_X,      RETRO_LBL_JOYPAD_X,              RETROK_UNKNOWN, CONSOLE_MENU_X,          0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L,      RETRO_LBL_JOYPAD_L,              RETROK_UNKNOWN, CONSOLE_MENU_L,          0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R,      RETRO_LBL_JOYPAD_R,              RETROK_UNKNOWN, CONSOLE_MENU_R,          0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L2,     RETRO_LBL_JOYPAD_L2,             RETROK_UNKNOWN, CONSOLE_MENU_L2,         0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R2,     RETRO_LBL_JOYPAD_R2,             RETROK_UNKNOWN, CONSOLE_MENU_R2,         0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L3,     RETRO_LBL_JOYPAD_L3,             RETROK_UNKNOWN, CONSOLE_MENU_L3,         0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R3,     RETRO_LBL_JOYPAD_R3,             RETROK_UNKNOWN, CONSOLE_MENU_R3,         0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_X_PLUS,      RETRO_LBL_ANALOG_LEFT_X_PLUS,    RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_X_MINUS,     RETRO_LBL_ANALOG_LEFT_X_MINUS,   RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_Y_PLUS,      RETRO_LBL_ANALOG_LEFT_Y_PLUS,    RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_Y_MINUS,     RETRO_LBL_ANALOG_LEFT_Y_MINUS,   RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_X_PLUS,     RETRO_LBL_ANALOG_RIGHT_X_PLUS,   RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_X_MINUS,    RETRO_LBL_ANALOG_RIGHT_X_MINUS,  RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_Y_PLUS,     RETRO_LBL_ANALOG_RIGHT_Y_PLUS,   RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_Y_MINUS,    RETRO_LBL_ANALOG_RIGHT_Y_MINUS,  RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },

   { true, RARCH_TURBO_ENABLE,             RETRO_LBL_TURBO_ENABLE,         RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_FAST_FORWARD_KEY,         RETRO_LBL_FAST_FORWARD_KEY,     RETROK_SPACE,   NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_FAST_FORWARD_HOLD_KEY,    RETRO_LBL_FAST_FORWARD_HOLD_KEY,RETROK_l,       NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_LOAD_STATE_KEY,           RETRO_LBL_LOAD_STATE_KEY,       RETROK_F4,      NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_SAVE_STATE_KEY,           RETRO_LBL_SAVE_STATE_KEY,       RETROK_F2,      NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_QUIT_KEY,                 RETRO_LBL_QUIT_KEY,             RETROK_ESCAPE,  NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_STATE_SLOT_PLUS,          RETRO_LBL_STATE_SLOT_PLUS,      RETROK_F7,      NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_STATE_SLOT_MINUS,         RETRO_LBL_STATE_SLOT_MINUS,     RETROK_F6,      NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_REWIND,                   RETRO_LBL_REWIND,               RETROK_r,       NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_PAUSE_TOGGLE,             RETRO_LBL_PAUSE_TOGGLE,         RETROK_p,       NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_FRAMEADVANCE,             RETRO_LBL_FRAMEADVANCE,         RETROK_k,       NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_RESET,                    RETRO_LBL_RESET,                RETROK_h,       NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_SCREENSHOT,               RETRO_LBL_SCREENSHOT,           RETROK_F8,      NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_MUTE,                     RETRO_LBL_MUTE,                 RETROK_F9,      NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_SLOWMOTION,               RETRO_LBL_SLOWMOTION,           RETROK_e,       NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_ENABLE_HOTKEY,            RETRO_LBL_ENABLE_HOTKEY,        RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_VOLUME_UP,                RETRO_LBL_VOLUME_UP,            RETROK_KP_PLUS, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_VOLUME_DOWN,              RETRO_LBL_VOLUME_DOWN,          RETROK_KP_MINUS,NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_DISK_EJECT_TOGGLE,        RETRO_LBL_DISK_EJECT_TOGGLE,    RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_DISK_NEXT,                RETRO_LBL_DISK_NEXT,            RETROK_UNKNOWN, NO_BTN,                  0, AXIS_NONE },
   { true, RARCH_QUICK_SWAP,               RETRO_LBL_QUICK_SWAP,           RETROK_c,       NO_BTN,                  0, AXIS_NONE },
#ifdef HAVE_MENU
   { true, RARCH_MENU_TOGGLE,              RETRO_LBL_MENU_TOGGLE,          RETROK_UNKNOWN, CONSOLE_MENU_HOME,       0, AXIS_NONE },
#endif
};
#endif

// Player 2-5
static const struct retro_keybind retro_keybinds_rest[] = {
    //     | RetroPad button            | desc                           | keyboard key  | js btn |     js axis   |
   { true, RETRO_DEVICE_ID_JOYPAD_B,      RETRO_LBL_JOYPAD_B,              RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_Y,      RETRO_LBL_JOYPAD_Y,              RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_SELECT, RETRO_LBL_JOYPAD_SELECT,         RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_START,  RETRO_LBL_JOYPAD_START,          RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_UP,     RETRO_LBL_JOYPAD_UP,             RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_DOWN,   RETRO_LBL_JOYPAD_DOWN,           RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_LEFT,   RETRO_LBL_JOYPAD_LEFT,           RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_RIGHT,  RETRO_LBL_JOYPAD_RIGHT,          RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_A,      RETRO_LBL_JOYPAD_A,              RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_X,      RETRO_LBL_JOYPAD_X,              RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L,      RETRO_LBL_JOYPAD_L,              RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R,      RETRO_LBL_JOYPAD_R,              RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L2,     RETRO_LBL_JOYPAD_L2,             RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R2,     RETRO_LBL_JOYPAD_R2,             RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_L3,     RETRO_LBL_JOYPAD_L3,             RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RETRO_DEVICE_ID_JOYPAD_R3,     RETRO_LBL_JOYPAD_R3,             RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },

   { true, RARCH_ANALOG_LEFT_X_PLUS,      RETRO_LBL_ANALOG_LEFT_X_PLUS,    RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_X_MINUS,     RETRO_LBL_ANALOG_LEFT_X_MINUS,   RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_Y_PLUS,      RETRO_LBL_ANALOG_LEFT_Y_PLUS,    RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_LEFT_Y_MINUS,     RETRO_LBL_ANALOG_LEFT_Y_MINUS,   RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_X_PLUS,     RETRO_LBL_ANALOG_RIGHT_X_PLUS,   RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_X_MINUS,    RETRO_LBL_ANALOG_RIGHT_X_MINUS,  RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_Y_PLUS,     RETRO_LBL_ANALOG_RIGHT_Y_PLUS,   RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_ANALOG_RIGHT_Y_MINUS,    RETRO_LBL_ANALOG_RIGHT_Y_MINUS,  RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
   { true, RARCH_TURBO_ENABLE,            RETRO_LBL_TURBO_ENABLE,          RETROK_UNKNOWN, NO_BTN, 0, AXIS_NONE },
};

#endif

#endif

