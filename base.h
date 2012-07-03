/*
 * base.h
 *
 * Base classes.
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

#ifndef __BASE_H__
#define __BASE_H__

class CpuReader;
class MemReader;
class LoadAverageReader;

class Visitor {
public:
  virtual void visit(CpuReader*) = 0;
  virtual void visit(MemReader*) = 0;
  virtual void visit(LoadAverageReader*) = 0;
};

class Visitable {
public:
  virtual void accept(Visitor*) = 0;
};

class Reader : public Visitable {
public:
  virtual bool init() = 0;

  virtual void fini() = 0;

  virtual void update() = 0;
};

#endif // __BASE_H__
