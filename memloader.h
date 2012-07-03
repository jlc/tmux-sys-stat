/*
 * memloader.h
 *
 * Memory stat gatherer.
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

#ifndef __MEMLOADER_H__
#define __MEMLOADER_H__

#include <inttypes.h>

#include "base.h"

class MemLoader : public Loader {
public:
  MemLoader();
  virtual ~MemLoader();

  virtual void accept(Visitor*);

  inline double totalMB() { return total_; }
  inline double activeMB() { return active_; }
  inline double inactiveMB() { return inactive_; }
  inline double wiredMB() { return wired_; }
  inline double freeMB() { return free_; }

  inline uint64_t total() { return total_; }
  inline uint64_t active() { return active_; }
  inline uint64_t inactive() { return inactive_; }
  inline uint64_t wired() { return wired_; }
  inline uint64_t free() { return free_; }

protected:
  double totalMB_;
  double activeMB_;
  double inactiveMB_;
  double wiredMB_;
  double freeMB_;

  uint64_t total_;
  uint64_t active_;
  uint64_t inactive_;
  uint64_t wired_;
  uint64_t free_;
};

#endif // __MEMLOADER_H__
