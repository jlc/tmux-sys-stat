/*
 * memreader_osx.cpp
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

#include "memreader_osx.h"

#include <stdio.h>

#include <mach/mach.h>
#include <mach/mach_error.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/vm_statistics.h>

#include "constants.h"

MemReaderOSX::MemReaderOSX() {
  begin();
}

MemReaderOSX::~MemReaderOSX() {
  end();
}

void MemReaderOSX::init() {
	// Build the Mach host reference
	machHost_ = mach_host_self();
	if (!machHost_)
    throw ReaderException("Error: Unable to initialize mach host self.");
}

void MemReaderOSX::fini() {
}

void MemReaderOSX::update() {
  if (!readMemoryStat())
    throw ReaderException("Error: Unable to read memory statistics.");
}

bool MemReaderOSX::readMemoryStat() {

	// Get the data
	vm_statistics_data_t vmStats;
	mach_msg_type_number_t vmCount = HOST_VM_INFO_COUNT;

	if (host_statistics(machHost_, HOST_VM_INFO, (host_info_t)&vmStats, &vmCount) != KERN_SUCCESS) {
		return false;
	}

	// Build total RAM if needed (check everytime just in case we've had earlier
	// errors). Double casts prevent sign extension from applying to upsized
	// 32-bit signed.
	total_ = (
          (uint64_t)((natural_t)vmStats.free_count) +
					(uint64_t)((natural_t)vmStats.active_count) +
					(uint64_t)((natural_t)vmStats.inactive_count) +
					(uint64_t)((natural_t)vmStats.wire_count)
          ) * (uint64_t)vm_page_size;

  // total is varying but is closed to real total memory

	// The rest of the statistics
	active_ = (uint64_t)((natural_t)vmStats.active_count) * (uint64_t)((natural_t)vm_page_size);
	inactive_ = (uint64_t)((natural_t)vmStats.inactive_count) * (uint64_t)((natural_t)vm_page_size);
	wired_ = (uint64_t)((natural_t)vmStats.wire_count) * (uint64_t)((natural_t)vm_page_size);
	free_ = (uint64_t)((natural_t)vmStats.free_count) * (uint64_t)((natural_t)vm_page_size);

  totalMB_ = (double)total_ / MEGABYTE;
  activeMB_ = (double)active_ / MEGABYTE;
  inactiveMB_ = (double)inactive_ / MEGABYTE;
  wiredMB_ = (double)wired_ / MEGABYTE;
  freeMB_ = (double)free_ / MEGABYTE;

  return true;
}

