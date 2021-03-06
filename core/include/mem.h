/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Little Endian Kernel.
 * 
 * Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Little Endian Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALEK_MEM_H
#define ALEK_MEM_H

/* Arch-specific memory functions */
#if defined(__arm__)
#include "arch/mem.h"
#endif

#include "types.h"

volatile void put32(addr_t addr, u32 val);
volatile u32  get32(addr_t addr);

extern "C" inline void *memset(void *s, s32 c, u32 n)
{
  u8 *a = reinterpret_cast<u8*>(s);
  for(u32 i = 0; i < n ; i++)
    a[i] = c;
  return s;
}

/**
 * puts a 32 bit integer
 */
#define P32_I(addr, val) put32(reinterpret_cast<addr_t>(addr), val)
#define G32_I(addr) get32(reinterpret_cast<addr_t>(addr))

#endif /* ALEK_MEM_H */
