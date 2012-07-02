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
#include <math.h>
#include <string>

#include "cpuloader.h"
#include "cpuloader_osx.h"
#include "memloader_osx.h"
#include "constants.h"

using namespace std;

string cpuAsciiStatus(const double system, const double user, const double idle) {
  const int NB_BAR_MAX = 5;
  const double PERCENT_PER_BAR = 100.0 / NB_BAR_MAX;

  double percentUsed = (system + user) * 100.0;

  double nbBar = ceil(percentUsed / PERCENT_PER_BAR);
  double nbEmptyBar = NB_BAR_MAX - (int)nbBar;

  char output[256];
  char *cur = output;
  int i = 0;

  *cur++ = '[';
  i = 0;
  while (i < nbBar)        { *cur++ = '#'; i++; }
  i = 0;
  while (i < nbEmptyBar)   { *cur++ = ' '; i++; }
  *cur++ = ']';
  sprintf(cur, "%02.0F%%", percentUsed);

  string sOutput = output;
  return sOutput;
}

int main(int argc, char** argv) {
  CpuLoaderOSX cpu;
  MemLoaderOSX mem;

  if (!cpu.init()) {
    return -1;
  }
  if (!mem.init()) {
    return -1;
  }

  cpu.update();
  mem.update();
 
  usleep(1*SECONDS);

  cpu.update();
  mem.update();

  string output = "";
  char tmp[1024];

  // memory
  double percentMemUsed = (100.0 * (mem.totalMB()-mem.freeMB())) / mem.totalMB();
  sprintf(tmp, "%0.2F%%", percentMemUsed);
  output += string(tmp) + " ";

  // cpus
  for (int i = 0; i < cpu.cpuCount(); i++) {
    output += cpuAsciiStatus(cpu.cpuStatSystem(i), cpu.cpuStatUser(i), cpu.cpuStatIdle(i)) + string(" ");
  }

  printf("%s\n", output.c_str());

  mem.fini();
  cpu.fini();

  return 0;
}
