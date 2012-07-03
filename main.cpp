/*
 * main.cpp
 *
 * Main.
 *
 * Copyright (C) 2012 Jeanluc Chasseriau <jeanluc.chasseriau@crossing-tech.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdio.h>
#include <unistd.h>

#include "base.h"
#include "constants.h"
#include "status.h"

#ifdef __MACOSX__
#include "cpureader_osx.h"
#include "memreader_osx.h"
#include "loadaveragereader_osx.h"
#endif // __MACOSX__

int main(int argc, char** argv) {

#ifdef __MACOSX__
  CpuReaderOSX cpu;
  MemReaderOSX mem;
  LoadAverageReaderOSX lavg;
#endif // __MACOSX__

  Reader** cmp = NULL;
  Reader* components[] = {&cpu, &mem, &lavg, NULL};

  StatusVisitor status;

  cmp = components;
  while(*cmp) { 
    if(!(*cmp)->init())
      return -1;

    (*cmp)->update();

    cmp++;
  }

  usleep(1*SECONDS);

  cmp = components;
  while(*cmp) { 
    (*cmp)->update();

    (*cmp)->accept(&status);

    (*cmp)->fini();

    cmp++;
  }

  status.printStatus();

  return 0;
}
