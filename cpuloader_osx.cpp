/*
 * cpuloader_osx.cpp
 *
 * MacOSX Cpu stat gathering.
 *
 * Copyright (C) 2002-2011 Alex Harper
 *   Author of MenuMeterCPUStats.m, part of MenuMeter (http://www.ragingmenace.com/software/menumeters/index.html).
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

#include "cpuloader_osx.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#include <mach/mach.h>
#include <mach/mach_error.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/processor.h>
#include <mach/processor_info.h>

#include "constants.h"

CpuLoaderOSX::CpuLoaderOSX() {
}

CpuLoaderOSX::~CpuLoaderOSX() {
  fini();
}

bool CpuLoaderOSX::init() {
  if (!initCpuCount()) {
    printf("Unable to initialized cpu count.\n");
    return false;
  }

  if (!initClockSpeed()) {
    printf("Unable to initialized clock speed.\n");
    return false;
  }

  if (!initCpuTicks()) {
    printf("Unable to initialized cpu ticks count.\n");
    return false;
  }

  return true;
}

void CpuLoaderOSX::fini() {
  if (prevCpuLoad_) {
    free(prevCpuLoad_);
    prevCpuLoad_ = NULL;
  }

  if (cpuStat_) {
    free(cpuStat_);
    cpuStat_ = NULL;
  }
}

void CpuLoaderOSX::update() {
  if (!readCpuTicks())
    printf("Error: unable to read cpu ticks.\n");
}

bool CpuLoaderOSX::initClockSpeed() {
  uint32_t clockRate = 0;
  int mib[2] = { CTL_HW, HW_CPU_FREQ };
  size_t sysctlLength = sizeof(clockRate);

  if (sysctl(mib, 2, &clockRate, &sysctlLength, NULL, 0)) {
    return false;
  }

  clockSpeed_ = (double)clockRate / GIGAHERTZ;

  return true;
}


bool CpuLoaderOSX::initCpuCount() {
  size_t sysctlLength = sizeof(cpuCount_);
  int mib[2] = { CTL_HW, HW_NCPU };
  if (sysctl(mib, 2, &cpuCount_, &sysctlLength, NULL, 0)) {
    return false;
  }

  return true;
}

bool CpuLoaderOSX::initCpuTicks() {
  processor_cpu_load_info_t cpuLoad;
  mach_msg_type_number_t processorMsgCount;
  natural_t processorCount;

  machHost_ = mach_host_self();

  kern_return_t err = host_processor_info(machHost_, PROCESSOR_CPU_LOAD_INFO, &processorCount, (processor_info_array_t *)&cpuLoad, &processorMsgCount);

  if (err != KERN_SUCCESS) {
    printf("ERROR: while executing host_processor_info()\n");
    return false;
  }

  prevCpuLoad_ = (processor_cpu_load_info*) malloc(processorCount * sizeof(struct processor_cpu_load_info));
  for (natural_t i = 0; i < processorCount; i++) {
    for (natural_t j = 0; j < CPU_STATE_MAX; j++) {
      prevCpuLoad_[i].cpu_ticks[j] = cpuLoad[i].cpu_ticks[j];
    }
  }

  vm_deallocate(mach_task_self(), (vm_address_t)cpuLoad, (vm_size_t)(processorCount * sizeof(*cpuLoad)));

  cpuStat_ = (CpuStat*) malloc(processorCount * sizeof(CpuStat));

  return true;
}

bool CpuLoaderOSX::readCpuTicks() {
  processor_cpu_load_info_t cpuLoad;
  mach_msg_type_number_t processorMsgCount;
  natural_t processorCount;

  kern_return_t err = host_processor_info(machHost_, PROCESSOR_CPU_LOAD_INFO, &processorCount, (processor_info_array_t *)&cpuLoad, &processorMsgCount);

  if (err != KERN_SUCCESS) {
    printf("ERROR: while executing host_processor_info()\n");
    return false;
  }

  for (natural_t i = 0; i < processorCount; i++) {

    // Calc load types and totals, with guards against 32-bit overflow
    // (values are natural_t)
    uint64_t system = 0, user = 0, idle = 0, total = 0;

    // system
    if (cpuLoad[i].cpu_ticks[CPU_STATE_SYSTEM] >= prevCpuLoad_[i].cpu_ticks[CPU_STATE_SYSTEM]) {
      system = cpuLoad[i].cpu_ticks[CPU_STATE_SYSTEM] - prevCpuLoad_[i].cpu_ticks[CPU_STATE_SYSTEM];
    } else {
      system = cpuLoad[i].cpu_ticks[CPU_STATE_SYSTEM] + (UINT_MAX - prevCpuLoad_[i].cpu_ticks[CPU_STATE_SYSTEM] + 1);
    }

    // user
    if (cpuLoad[i].cpu_ticks[CPU_STATE_USER] >= prevCpuLoad_[i].cpu_ticks[CPU_STATE_USER]) {
      user = cpuLoad[i].cpu_ticks[CPU_STATE_USER] - prevCpuLoad_[i].cpu_ticks[CPU_STATE_USER];
    } else {
      user = cpuLoad[i].cpu_ticks[CPU_STATE_USER] + (ULONG_MAX - prevCpuLoad_[i].cpu_ticks[CPU_STATE_USER] + 1);
    }
    // Count nice as user (nice slot non-zero only on  OS versions prior to 10.4)
    // Radar 5644966, duplicate 5555821. Apple says its intentional, so stop
    // pretending its going to get fixed.
    if (cpuLoad[i].cpu_ticks[CPU_STATE_NICE] >= prevCpuLoad_[i].cpu_ticks[CPU_STATE_NICE]) {
      user += cpuLoad[i].cpu_ticks[CPU_STATE_NICE] - prevCpuLoad_[i].cpu_ticks[CPU_STATE_NICE];
    } else {
      user += cpuLoad[i].cpu_ticks[CPU_STATE_NICE] + (ULONG_MAX - prevCpuLoad_[i].cpu_ticks[CPU_STATE_NICE] + 1);
    }

    // idle
    if (cpuLoad[i].cpu_ticks[CPU_STATE_IDLE] >= prevCpuLoad_[i].cpu_ticks[CPU_STATE_IDLE]) {
      idle = cpuLoad[i].cpu_ticks[CPU_STATE_IDLE] - prevCpuLoad_[i].cpu_ticks[CPU_STATE_IDLE];
    } else {
      idle = cpuLoad[i].cpu_ticks[CPU_STATE_IDLE] + (ULONG_MAX - prevCpuLoad_[i].cpu_ticks[CPU_STATE_IDLE] + 1);
    }

    total = system + user + idle;

    //printf("CpuLoader::readCpuTicks: system: %llu / user: %llu / idle: %llu = total: %llu\n", system, user, idle, total);

    // Sanity
    if (total < 1) {
      total = 1;
    }

    cpuStat_[i].system = (double)system / (double)total;
    cpuStat_[i].user = (double)user / (double)total;
    cpuStat_[i].idle = (double)idle / (double)total;
  }

  prevCpuLoad_ = (processor_cpu_load_info*) malloc(processorCount * sizeof(struct processor_cpu_load_info));
  for (natural_t i = 0; i < processorCount; i++) {
    for (natural_t j = 0; j < CPU_STATE_MAX; j++) {
      prevCpuLoad_[i].cpu_ticks[j] = cpuLoad[i].cpu_ticks[j];
    }
  }

  vm_deallocate(mach_task_self(), (vm_address_t)cpuLoad, (vm_size_t)(processorCount * sizeof(*cpuLoad)));
  return true;
}

