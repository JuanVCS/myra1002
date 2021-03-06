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

#include "frontend_context.h"
#include <string.h>

static const frontend_ctx_driver_t *frontend_ctx_drivers[] = {
   &frontend_ctx_gx,
   NULL // zero length array is not valid
};

const frontend_ctx_driver_t *frontend_ctx_find_driver(const char *ident)
{
   unsigned i;
   for (i = 0; frontend_ctx_drivers[i]; i++)
   {
      if (strcmp(frontend_ctx_drivers[i]->ident, ident) == 0)
         return frontend_ctx_drivers[i];
   }

   return NULL;
}

const frontend_ctx_driver_t *frontend_ctx_init_first(void)
{
   unsigned i;
   for (i = 0; frontend_ctx_drivers[i]; i++)
      return frontend_ctx_drivers[i];

   return NULL;
}
