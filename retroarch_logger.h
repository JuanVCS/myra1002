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

#ifndef __RARCH_LOGGER_H
#define __RARCH_LOGGER_H

#include <stdarg.h>

#if defined(HAVE_FILE_LOGGER) && !defined(IS_SALAMANDER)
#define LOG_FILE (g_extern.log_file)

#define LOG_FILENAME "/retroarch/retroarch.log"

#define RARCH_LOG(...) do { \
      fprintf(LOG_FILE, "RetroArch: " __VA_ARGS__); \
      fflush(LOG_FILE); \
   } while (0)
#define RARCH_LOG_V(tag, fmt, vp) do { \
      fprintf(LOG_FILE, "RetroArch: " tag); \
      vfprintf(LOG_FILE, fmt, vp); \
      fflush(LOG_FILE); \
   } while (0)

#define RARCH_LOG_OUTPUT(...) do { \
         fprintf(LOG_FILE, __VA_ARGS__); \
         fflush(LOG_FILE); \
   } while (0)
#define RARCH_LOG_OUTPUT_V(tag, fmt, vp) do { \
         fprintf(LOG_FILE, "RetroArch: " tag); \
         vfprintf(LOG_FILE, fmt, vp); \
         fflush(LOG_FILE); \
   } while (0)

#define RARCH_ERR(...) do { \
      fprintf(LOG_FILE, "RetroArch [ERROR] :: " __VA_ARGS__); \
      fflush(LOG_FILE); \
   } while (0)
#define RARCH_ERR_V(tag, fmt, vp) do { \
      fprintf(LOG_FILE, "RetroArch [ERROR] :: " tag); \
      vfprintf(LOG_FILE, fmt, vp); \
      fflush(LOG_FILE); \
   } while (0)

#define RARCH_WARN(...) do { \
      fprintf(LOG_FILE, "RetroArch [WARN] :: " __VA_ARGS__); \
      fflush(LOG_FILE); \
   } while (0)
#define RARCH_WARN_V(tag, fmt, vp) do { \
      fprintf(LOG_FILE, "RetroArch [WARN] :: " tag); \
      vfprintf(LOG_FILE, fmt, vp); \
      fflush(LOG_FILE); \
   } while (0)
#else
#define LOG_FILE stdout
#define RARCH_LOG(...)
#define RARCH_LOG_V(tag, fmt, vp)
#define RARCH_LOG_OUTPUT(...)
#define RARCH_LOG_OUTPUT_V(tag, fmt, vp)
#define RARCH_ERR(...)
#define RARCH_ERR_V(tag, fmt, vp)
#define RARCH_WARN(...)
#define RARCH_WARN_V(tag, fmt, vp)
#endif

#endif
