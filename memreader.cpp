/*
 * memreader.cpp
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

#include "memreader.h"

MemReader::MemReader() :
  totalMB_(0), activeMB_(0), inactiveMB_(0), wiredMB_(0), freeMB_(0),
  total_(0), active_(0), inactive_(0), wired_(0), free_(0) {
}

MemReader::~MemReader() {
}

void MemReader::accept(Visitor* v) {
  v->visit(this);
}
