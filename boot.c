#include "iapetus.h"
#include "satiator.h"
#include "cd.h"
#include "bios.h"
#define VDP2_REG_TVSTAT         (*(volatile u16 *)0x25F80004)

char statbuf[280];
//////////////////////////////////////////////////////////////////////////////

void vdp_wait_vblankin(void)
{
	while(!(VDP2_REG_TVSTAT & 8)) {}
}

//////////////////////////////////////////////////////////////////////////////

void vdp_wait_vblankout(void)
{
	while(VDP2_REG_TVSTAT & 8) {}
}

//////////////////////////////////////////////////////////////////////////////
void vdp_vsync(void)
{
   // Wait for Vblank-in
   while(!(VDP2_REG_TVSTAT & 8)) {
   }

   // Wait for Vblank-out
	vdp_wait_vblankout();
}
int boot_disc()
{
	int ret = bios_loadcd_init();
   	ret = bios_loadcd_read();
   do {
       ret = bios_loadcd_boot();
	   vdp_vsync();
   } while (ret == 1);
   return ret;
}
void try_boot_iso()
{
	debug_print("change dir");
	s_chdir("/");
	debug_print("stat boot.desc");
	// see if a desc file exists in this directory already
	s_stat_t *st = (s_stat_t*)statbuf;
	s_chdir("/");
	int stret = s_stat("boot.desc", st, sizeof(statbuf)-1);
	if (stret < 0)
	{
		debug_print("stat failed");
		return;
	} else
	{	
		debug_print("stat ok");
		//fadeout(0x20);

		satiator_zone_header_t *cart = s_find_cartridge();
		if (cart && cart->header_version >= 1)
			cart->install_soft_reset_hook();

		debug_print("reset hook");
		//restore_vdp_mem();

		s_emulate("boot.desc");
		while (is_cd_present());
		//while (!is_cd_present());
		debug_print("booting");
		s_mode(s_cdrom);
		if(boot_disc() < 0)
		{
			s_mode(s_api);   // failed, restore order
			s_emulate("");  // close the old file
			//fadein(0x20);
			return;
		}
	}
					
}