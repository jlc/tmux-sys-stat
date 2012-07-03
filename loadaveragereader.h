/*
 * loadaveragereader.h
 *
 * Base class for load average stats gathering.
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

#ifndef __LOADAVERAGELOADER_H__
#define __LOADAVERAGELOADER_H__

#include <inttypes.h>

#include "base.h"

class LoadAverageReader : public Reader {
public:
  LoadAverageReader();
  virtual ~LoadAverageReader();

  virtual void accept(Visitor*);

protected:
  double loadAverage_[3];

public:
  inline double loadAverage1() { return loadAverage_[0]; }
  inline double loadAverage5() { return loadAverage_[1]; }
  inline double loadAverage15() { return loadAverage_[2]; }
};

#endif // __LOADAVERAGELOADER_H__
