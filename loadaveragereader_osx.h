/*
 * loadaveragereader_osx.h
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

#ifndef __LOADAVERAGELOADER_OSX_H__
#define __LOADAVERAGELOADER_OSX_H__

#include "loadaveragereader.h"

class LoadAverageReaderOSX : public LoadAverageReader {
public:
  LoadAverageReaderOSX();
  virtual ~LoadAverageReaderOSX();

  virtual void init();

  virtual void fini();

  virtual void update();

private:
  bool readLoadAverage();

};

#endif // __LOADAVERAGELOADER_H__
