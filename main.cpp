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

#include "cpuloader_osx.h"
#include "memloader_osx.h"
#include "base.h"
#include "constants.h"

using namespace std;

static int NB_BAR_MAX = 5;
static double PERCENT_PER_BAR = 100.0 / NB_BAR_MAX;

class StatusVisitor : public Visitor {
private:
  string cpuStatus_;
  string memStatus_;

  char tmpOutput[256];

public:
  StatusVisitor() {
    cpuStatus_ = "";
    memStatus_ = "";
  }

  ~StatusVisitor() {
  }

  void printStatus() {
    printf("%s %s\n", memStatus_.c_str(), cpuStatus_.c_str());
  }

  virtual void visit(CpuLoader* cpu) {
    double percentUsed = 0.0;
    double nbBar = 0.0;
    double nbEmptyBar = 0.0;

    char *cur = NULL;

    int i = cpu->cpuCount();
    int j = 0;

    const char *formatPercent         = "%02.0F%%";
    const char *formatPercentSpace    = "%02.0F%% ";

    while (--i) {
      percentUsed = (cpu->statSystem(i) + cpu->statUser(i)) * 100.0;
      nbBar = ceil(percentUsed / PERCENT_PER_BAR);
      nbEmptyBar = NB_BAR_MAX - (int)nbBar;

      cur = tmpOutput;
      j = 0;

      *cur++ = '[';
      j = nbBar;
      while (j--)   { *cur++ = '#'; }
      j = nbEmptyBar;
      while (j--)   { *cur++ = ' '; }
      *cur++ = ']';

      sprintf(cur, (i) ? formatPercentSpace : formatPercent, percentUsed);

      cpuStatus_ += tmpOutput;
    }
  }

  virtual void visit(MemLoader* mem) {
    double percentMemUsed = (100.0 * (mem->totalMB()-mem->freeMB())) / mem->totalMB();
    sprintf(tmpOutput, "%0.2F%% Mem", percentMemUsed);
    memStatus_ += tmpOutput;
  }

};



int main(int argc, char** argv) {

//#ifdef __MACOSX__
  CpuLoaderOSX cpu;
  MemLoaderOSX mem;
//#endif // __MACOSX__

  Loader** cmp = NULL;
  Loader* components[] = {&cpu, &mem, NULL};

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
