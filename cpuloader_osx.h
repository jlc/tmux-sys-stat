/*
 * cpuloader_osx.h
 *
 * MacOSX Cpu stat gathering.
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

#ifndef __CPULOADER_OSX__
#define __CPULOADER_OSX__

#include "cpuloader.h"

#include <mach/mach_types.h>

class CpuLoaderOSX : public CpuLoader {
public:
  CpuLoaderOSX();
  virtual ~CpuLoaderOSX();

  virtual bool init();

  virtual void fini();

  virtual void update();

private:
  bool initClockSpeed();

  bool initCpuCount();

  bool initCpuTicks();

  bool readCpuTicks();

  bool readLoadAverage();

private:
  mach_port_t machHost_;
};

#endif // __CPULOADER_OSX__
