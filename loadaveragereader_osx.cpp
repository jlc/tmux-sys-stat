/*
 * loadaveragereader_osx.cpp
 *
 * Base class for load average stats gathering for OSX.
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

#include "loadaveragereader_osx.h"

#include <stdio.h>
#include <stdlib.h>

LoadAverageReaderOSX::LoadAverageReaderOSX() {}

LoadAverageReaderOSX::~LoadAverageReaderOSX() {}

bool LoadAverageReaderOSX::init() {
  loadAverage_[0] = loadAverage_[1] = loadAverage_[2] = 0;
  return true;
}

void LoadAverageReaderOSX::fini() {
}

void LoadAverageReaderOSX::update() {
  if (!readLoadAverage())
    printf("Error: unable to read load average.\n");
}

bool LoadAverageReaderOSX::readLoadAverage() {
  if (getloadavg(loadAverage_, 3) != 3) {
    return false;
  }
  return true;
}

