/* Copyright (C)
* 2017 - John Melton, G0ORX/N6LYT
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*/

#ifdef CLIENT_SERVER
#include "client_server.h"
#endif

//
// The following calls functions can be called usig g_idle_add
// Use these calls from within the rigclt daemon, or the GPIO or MIDI stuff
//

#ifdef CLIENT_SERVER
extern int ext_remote_command(void *data);
extern int ext_receiver_remote_update_display(void *data);
#endif

extern int ext_discovery(void *data);
extern int ext_vfo_update(void *data);
extern int ext_band_update(void *data);
extern int ext_bandstack_update(void *data);
extern int ext_mox_update(void *data);
extern int ext_tune_update(void *data);
extern int ext_vox_changed(void *data);
extern int ext_sliders_mode_changed(void *data);

extern int ext_ps_update(void *data);
extern int ext_two_tone(void *data);
extern int ext_nr_update(void *data);
extern int ext_nb_update(void *data);
extern int ext_snb_update(void *data);

extern int ext_band_plus(void *data);
extern int ext_band_minus(void *data);
extern int ext_bandstack_plus(void *data);
extern int ext_bandstack_minus(void *data);
extern int ext_lock_update(void *data);
extern int ext_rit_update(void *data);
extern int ext_rit_clear(void *data);
extern int ext_xit_update(void *data);
extern int ext_xit_clear(void *data);
extern int ext_filter_plus(void *data);
extern int ext_filter_minus(void *data);
extern int ext_mode_plus(void *data);
extern int ext_mode_minus(void *data);
extern int ext_ctun_update(void *data);
extern int ext_agc_update(void *data);
extern int ext_split_toggle(void *data);

extern int ext_sliders_update(void *data);
extern int ext_mode_update(void *data);
extern int ext_filter_update(void *data);
extern int ext_frequency_update(void *data);
extern int ext_memory_update(void *data);
extern int ext_function_update(void *data);

#ifdef PURESIGNAL
extern int ext_tx_set_ps(void *data);
#endif

extern int ext_vfo_a_swap_b(void *data);
extern int ext_vfo_a_to_b(void *data);
extern int ext_vfo_b_to_a(void *data);

extern int ext_start_rx(void *data);
extern int ext_start_tx(void *data);
extern int ext_diversity_update(void *data);
extern int ext_sat_update(void *data);
extern int ext_set_duplex(void *data);

extern int ext_update_noise(void *data);
extern int ext_update_eq(void *data);
#ifdef PURESIGNAL
extern int ext_start_ps(void *data);
#endif

extern int ext_mute_update(void *data);

extern int ext_zoom_update(void *data);
extern int ext_pan_update(void *data);

extern int ext_remote_set_zoom(void *data);
extern int ext_remote_set_pan(void *data);
extern int ext_set_title(void *data);


//
// Helper functions, will be moved elsewhere on the long run
//
extern void set_split(int val);
extern void set_frequency(int v,long long f);
extern void ctun_update(int id,int state);
extern void band_plus(int id);
extern void band_minus(int id);
extern void num_pad(int num);
extern void update_vfo_step(int direction);
