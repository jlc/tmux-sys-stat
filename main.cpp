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

class Sleeper : public Updatable {
public:
  virtual void update() {
    usleep(1*SECONDS);
  }
  virtual void accept(Visitor*) {}
};

int main(int argc, char** argv) {

  try {
#ifdef __MACOSX__
    CpuReaderOSX cpu;
    MemReaderOSX mem;
    LoadAverageReaderOSX lavg;
#endif // __MACOSX__

    Sleeper sleeper;
    StatusVisitor status;

    Updatable** cmp = NULL;
    Updatable* components[] = { &sleeper,
                                &cpu, &mem, &lavg,
                                NULL };

    cmp = components;
    while(*cmp) {
      (*cmp)->update();

      (*cmp)->accept(&status);

      cmp++;
    }

    status.printStatus();
  }
  catch(ReaderException& exception) {
    printf("Exception: %s\n", exception.what());
    return -1;
  }

  return 0;
}
