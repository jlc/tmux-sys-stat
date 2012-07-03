/*
 * status.h
 *
 * Statistics.
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

#ifndef __STATUS_H__
#define __STATUS_H__

#include <string>

#include "base.h"

static int NB_BAR_MAX = 5;
static double PERCENT_PER_BAR = 100.0 / NB_BAR_MAX;

class StatusVisitor : public Visitor {
private:
  std::string cpuStatus_;
  std::string memStatus_;
  std::string lavgStatus_;

  char tmpOutput[256];

public:
  StatusVisitor();
  ~StatusVisitor();

  void printStatus();

  virtual void visit(CpuReader* cpu);

  virtual void visit(MemReader* mem);

  virtual void visit(LoadAverageReader* lavg);
};

#endif // __STATUS_H__
