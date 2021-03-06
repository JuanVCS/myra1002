#include <gctypes.h>
#include "string.h"
#include "dolloader.h"
#include "sync.h"

#define ARENA1_HI_LIMIT 0x81800000

typedef struct _dolheader {
	uint32_t text_pos[7];
	uint32_t data_pos[11];
	uint32_t text_start[7];
	uint32_t data_start[11];
	uint32_t text_size[7];
	uint32_t data_size[11];
	uint32_t bss_start;
	uint32_t bss_size;
	uint32_t entry_point;
} dolheader;

uint32_t load_dol_image(const void *dolstart)
{
	if(!dolstart)
		return 0;

	uint32_t i;
	dolheader *dolfile = (dolheader *) dolstart;

/* 	if (dolfile->bss_start > 0 && dolfile->bss_start < ARENA1_HI_LIMIT) {
		uint32_t bss_size = dolfile->bss_size;
		if (dolfile->bss_start + bss_size > ARENA1_HI_LIMIT) {
			bss_size = ARENA1_HI_LIMIT - dolfile->bss_start;
		}
		memset((void *) dolfile->bss_start, 0, bss_size);
		sync_before_exec((void *) dolfile->bss_start, bss_size);
	} */

	for (i = 0; i < 7; i++)
	{
		if ((!dolfile->text_size[i]) || (dolfile->text_start[i] < 0x100))
			continue;

		memcpy((void *) dolfile->text_start[i], dolstart + dolfile->text_pos[i], dolfile->text_size[i]);
		sync_before_exec((void *) dolfile->text_start[i], dolfile->text_size[i]);
	}

	for (i = 0; i < 11; i++)
	{
		if ((!dolfile->data_size[i]) || (dolfile->data_start[i] < 0x100))
			continue;

		memcpy((void *) dolfile->data_start[i], dolstart + dolfile->data_pos[i], dolfile->data_size[i]);
		sync_before_exec((void *) dolfile->data_start[i], dolfile->data_size[i]);
	}

	return dolfile->entry_point;
}
