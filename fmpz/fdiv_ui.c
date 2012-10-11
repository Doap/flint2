/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

ulong
fmpz_fdiv_ui(const fmpz_t g, ulong h)
{
    fmpz c1 = *g;
    ulong r;

    if (h == 0UL)
    {
        printf("Exception (fmpz_fdiv_ui). Division by 0.\n");
        abort();
    }

    if (!COEFF_IS_MPZ(c1))      /* g is small */
    {
        if (c1 < 0L)
        {
            r = h - (-c1 % h);  /* C doesn't correctly handle negative mods */
            if (r == h)
                r = 0;
        }
        else
            r = c1 % h;

        return r;
    }
    else                        /* g is large */
    {
        return mpz_fdiv_ui(COEFF_TO_PTR(c1), h);
    }
}
