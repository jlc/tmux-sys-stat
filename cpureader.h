/*
 * cpureader.h
 *
 * Base class for cpu stats gathering.
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

#ifndef __CPULOADER_H__
#define __CPULOADER_H__

#include <inttypes.h>

#include "base.h"

class CpuReader : public Reader {
public:

  class CpuStat {
  public:
    CpuStat() { system = user = idle = 0; }
    double system;
    double user;
    double idle;
  };

protected:
  struct processor_cpu_load_info* prevCpuLoad_;

  double clockSpeed_;

  uint32_t cpuCount_;

  CpuStat* cpuStat_;

public:

  CpuReader();
  virtual ~CpuReader();

  virtual void accept(Visitor* v);

  inline double clockSpeed() { return clockSpeed_; }
  inline uint32_t cpuCount() { return cpuCount_; }

  inline double statSystem(int cpu) {
    if (cpu >= cpuCount_) return 0.0;
    return cpuStat_[cpu].system;
  }

  inline double statUser(int cpu) {
    if (cpu >= cpuCount_) return 0.0;
    return cpuStat_[cpu].user;
  }

  inline double statIdle(int cpu) {
    if (cpu >= cpuCount_) return 0.0;
    return cpuStat_[cpu].idle;
  }
};

#endif // __CPULOADER_H__

