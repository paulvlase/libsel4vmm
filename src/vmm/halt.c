/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

/*vm exits related with hlt'ing*/

#include <stdio.h>
#include <stdlib.h>

#include <sel4/sel4.h>

#include "vmm/vmm.h"

/* Handling EPT violation VMExit Events. */
int vmm_hlt_handler(vmm_t *vmm) {
    if (!(vmm_guest_state_get_rflags(&vmm->guest_state, vmm->guest_vcpu) & BIT(9))) {
        printf("Halted forever :(\n");
    }
    if (!vmm->plat_callbacks.has_interrupt()) {
        vmm->guest_state.virt.interrupt_halt = 1;
    }
    vmm_guest_exit_next_instruction(&vmm->guest_state);
    return 0;
}
