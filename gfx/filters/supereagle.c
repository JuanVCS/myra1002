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

// Compile: gcc -o supereagle.so -shared supereagle.c -std=c99 -O3 -Wall -pedantic -fPIC

#include "softfilter.h"
#include <stdlib.h>

#ifdef RARCH_INTERNAL
#define filter_data supereagle_filter_data
#endif

#define SUPEREAGLE_SCALE 2

struct filter_data
{
   unsigned in_fmt;
};

static unsigned supereagle_generic_input_fmts(void)
{
   return SOFTFILTER_FMT_RGB565 | SOFTFILTER_FMT_XRGB8888;
}

static unsigned supereagle_generic_output_fmts(unsigned input_fmts)
{
   return input_fmts;
}

static void *supereagle_generic_create(unsigned in_fmt)
{
   struct filter_data *filt = (struct filter_data*)calloc(1, sizeof(*filt));
   if (!filt)
      return NULL;

   filt->in_fmt  = in_fmt;

   return filt;
}

static void supereagle_generic_output(void *data, unsigned *out_width, unsigned *out_height,
      unsigned width, unsigned height)
{
   *out_width = width * SUPEREAGLE_SCALE;
   *out_height = height * SUPEREAGLE_SCALE;
}

static void supereagle_generic_destroy(void *data)
{
   struct filter_data *filt = (struct filter_data*)data;
   free(filt);
}

#define supereagle_interpolate_xrgb8888(A, B) ((((A) & 0xFEFEFEFE) >> 1) + (((B) & 0xFEFEFEFE) >> 1) + ((A) & (B) & 0x01010101))

#define supereagle_interpolate2_xrgb8888(A, B, C, D) ((((A) & 0xFCFCFCFC) >> 2) + (((B) & 0xFCFCFCFC) >> 2) + (((C) & 0xFCFCFCFC) >> 2) + (((D) & 0xFCFCFCFC) >> 2) + (((((A) & 0x03030303) + ((B) & 0x03030303) + ((C) & 0x03030303) + ((D) & 0x03030303)) >> 2) & 0x03030303))

#define supereagle_interpolate_rgb565(A, B) ((((A) & 0xF7DE) >> 1) + (((B) & 0xF7DE) >> 1) + ((A) & (B) & 0x0821));

#define supereagle_interpolate2_rgb565(A, B, C, D) ((((A) & 0xE79C) >> 2) + (((B) & 0xE79C) >> 2) + (((C) & 0xE79C) >> 2) + (((D) & 0xE79C) >> 2)  + (((((A) & 0x1863) + ((B) & 0x1863) + ((C) & 0x1863) + ((D) & 0x1863)) >> 2) & 0x1863))

#define supereagle_result(A, B, C, D) (((A) != (C) || (A) != (D)) - ((B) != (C) || (B) != (D)));

#define supereagle_declare_variables(typename_t, in, nextline) \
         typename_t product1a, product1b, product2a, product2b; \
         const typename_t colorB1 = *(in - nextline + 0); \
         const typename_t colorB2 = *(in - nextline + 1); \
         const typename_t color4  = *(in - 1); \
         const typename_t color5  = *(in + 0); \
         const typename_t color6  = *(in + 1); \
         const typename_t colorS2 = *(in + 2); \
         const typename_t color1  = *(in + nextline - 1); \
         const typename_t color2  = *(in + nextline + 0); \
         const typename_t color3  = *(in + nextline + 1); \
         const typename_t colorS1 = *(in + nextline + 2); \
         const typename_t colorA1 = *(in + nextline + nextline + 0); \
         const typename_t colorA2 = *(in + nextline + nextline + 1)

#ifndef supereagle_function
#define supereagle_function(result_cb, interpolate_cb, interpolate2_cb) \
         if (color2 == color6 && color5 != color3) \
         { \
            product1b = product2a = color2; \
            if ((color1 == color2) || (color6 == colorB2)) \
            { \
               product1a = interpolate_cb(color2, color5); \
               product1a = interpolate_cb(color2, product1a); \
            } \
            else \
            { \
               product1a = interpolate_cb(color5, color6); \
            } \
            if ((color6 == colorS2) || (color2 == colorA1)) \
            { \
               product2b = interpolate_cb(color2, color3); \
               product2b = interpolate_cb(color2, product2b); \
            } \
            else \
            { \
               product2b = interpolate_cb(color2, color3); \
            } \
         } \
         else if (color5 == color3 && color2 != color6) \
         { \
            product2b = product1a = color5; \
            if ((colorB1 == color5) || (color3 == colorS1)) \
            { \
               product1b = interpolate_cb(color5, color6); \
               product1b = interpolate_cb(color5, product1b); \
            } \
            else \
            { \
               product1b = interpolate_cb(color5, color6); \
            } \
            if ((color3 == colorA2) || (color4 == color5)) \
            { \
               product2a = interpolate_cb(color5, color2); \
               product2a = interpolate_cb(color5, product2a); \
            } \
            else \
            { \
               product2a = interpolate_cb(color2, color3); \
            } \
         } \
         else if (color5 == color3 && color2 == color6) \
         { \
            int r = 0; \
            r += supereagle_result(color6, color5, color1, colorA1); \
            r += supereagle_result(color6, color5, color4, colorB1); \
            r += supereagle_result(color6, color5, colorA2, colorS1); \
            r += supereagle_result(color6, color5, colorB2, colorS2); \
            if (r > 0) \
            { \
               product1b = product2a = color2; \
               product1a = product2b = interpolate_cb(color5, color6); \
            } \
            else if (r < 0) \
            { \
               product2b = product1a = color5; \
               product1b = product2a = interpolate_cb(color5, color6); \
            } \
            else \
            { \
               product2b = product1a = color5; \
               product1b = product2a = color2; \
            } \
         } \
         else \
         { \
            product2b = product1a = interpolate_cb(color2, color6); \
            product2b = interpolate2_cb(color3, color3, color3, product2b); \
            product1a = interpolate2_cb(color5, color5, color5, product1a); \
            product2a = product1b = interpolate_cb(color5, color3); \
            product2a = interpolate2_cb(color2, color2, color2, product2a); \
            product1b = interpolate2_cb(color6, color6, color6, product1b); \
         } \
         out[0] = product1a; \
         out[1] = product1b; \
         out[dst_stride] = product2a; \
         out[dst_stride + 1] = product2b; \
         ++in; \
         out += 2
#endif

static void supereagle_generic_xrgb8888(unsigned width, unsigned height,
      uint32_t *src, unsigned src_stride, uint32_t *dst, unsigned dst_stride)
{
   unsigned finish, nextline;
   nextline = src_stride;

   for (; height; height--)
   {
      uint32_t *in  = (uint32_t*)src;
      uint32_t *out = (uint32_t*)dst;

      for (finish = width; finish; finish -= 1)
      {
         supereagle_declare_variables(uint32_t, in, nextline);

         supereagle_function(supereagle_result, supereagle_interpolate_xrgb8888, supereagle_interpolate2_xrgb8888);
      }

      src += src_stride;
      dst += 2 * dst_stride;
   }
}

static void supereagle_generic_rgb565(unsigned width, unsigned height,
      uint16_t *src, unsigned src_stride, uint16_t *dst, unsigned dst_stride)
{
   unsigned nextline, finish;
   nextline = src_stride;

   for (; height; height--)
   {
      uint16_t *in  = (uint16_t*)src;
      uint16_t *out = (uint16_t*)dst;

      for (finish = width; finish; finish -= 1)
      {
         supereagle_declare_variables(uint16_t, in, nextline);

         supereagle_function(supereagle_result, supereagle_interpolate_rgb565, supereagle_interpolate2_rgb565);
      }

      src += src_stride;
      dst += 2 * dst_stride;
   }
}

static void supereagle_generic_render(void *data,
      void *output, size_t output_stride,
      const void *input, unsigned width, unsigned height, size_t input_stride)
{
   struct filter_data *filt = (struct filter_data*)data;

   if (filt->in_fmt == SOFTFILTER_FMT_RGB565)
      supereagle_generic_rgb565(width, height,
         (uint16_t*)input, input_stride / SOFTFILTER_BPP_RGB565, 
         (uint16_t*)output, output_stride / SOFTFILTER_BPP_RGB565);
   else if (filt->in_fmt == SOFTFILTER_FMT_XRGB8888)
      supereagle_generic_xrgb8888(width, height,
         (uint32_t*)input, input_stride / SOFTFILTER_BPP_XRGB8888, 
         (uint32_t*)output, output_stride / SOFTFILTER_BPP_XRGB8888);
}

const softfilter_implementation_t supereagle_implementation = {
   supereagle_generic_input_fmts,
   supereagle_generic_output_fmts,

   supereagle_generic_create,
   supereagle_generic_destroy,

   supereagle_generic_output,
   NULL,
   
   supereagle_generic_render,
   "SuperEagle",
};

#ifdef RARCH_INTERNAL
#undef filter_data
#endif
