/*
 * kahuna -- simple USBasp compatible isp programmer
 *
 *   by Alexander Neumann <alexander@lochraster.org>
 *
 * inspired by USBasp by Thomas Fischl,
 * see http://www.obdev.at/products/avrusb/usbasploader.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <avr/io.h>
#include <stdint.h>

/* implementation of http://www.rn-wissen.de/index.php/Zufallszahlen_mit_avr-gcc
 *
 * random_seed is an uint16_t which will be initialized by XORing all words in
 * memory before initialization.  this should ensure a different value for each
 * device, even after reset (previous value of random_seed is also XORed) */
uint16_t random_seed __attribute__ ((section (".noinit")));

/* NEVER CALL DIRECTLY, WILL BE CALLED BY STARTUP CODE! */
void __init_random (void) __attribute__ ((naked))
    __attribute__ ((section (".init3")));

/* NEVER CALL DIRECTLY, WILL BE CALLED BY STARTUP CODE! */
void __init_random (void)
{
    uint16_t seed = 0;
    extern uint16_t __noinit_start;
    uint16_t *ptr = &__noinit_start;

    do {
        seed ^= *(ptr++);
    } while (ptr < (uint16_t *)RAMEND);

    random_seed = seed;
}
