/*
 * cpureader.cpp
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

#include "cpureader.h"

#include <stdio.h>

CpuReader::CpuReader() :
  prevCpuLoad_(NULL), clockSpeed_(0), cpuCount_(0), cpuStat_(NULL) {
}

CpuReader::~CpuReader() {}

void CpuReader::accept(Visitor* v) {
  v->visit(this);
}
