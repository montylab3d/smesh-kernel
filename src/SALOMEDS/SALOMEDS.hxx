//  SALOME SALOMEDS : data structure of SALOME and sources of Salome data server 
//
//  Copyright (C) 2003  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS 
// 
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public 
//  License as published by the Free Software Foundation; either 
//  version 2.1 of the License. 
// 
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free Software 
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA 
// 
//  See http://www.opencascade.org/SALOME/ or email : webmaster.salome@opencascade.org 
//
//
//
//  File   : SALOMEDS.hxx
//  Author : Sergey ANIKIN
//  Module : SALOME
//  $Header$


#ifndef SALOMEDS_HeaderFile
#define SALOMEDS_HeaderFile

#include <Utils_Mutex.hxx>

namespace SALOMEDS
{
  // PAL8065: san -- Implementation of convenient locker based on simple recursive 
  // mutex for POSIX platforms.
  // This class is to protect SALOMEDS CORBA methods which deal with OCC calls from 
  // parallel access by several threads
  // To protect some method, an instance of Locker class should be created
  // on the stack at the beginning of guarded code:
  //
  //    Locker lock;
  //
  class Locker : public Utils_Locker
  {
  public:
    Locker();
    virtual ~Locker();

  private:
    static Utils_Mutex MutexDS;

    friend void lock();
    friend void unlock();
  };

  // Convenient functions to lock/unlock the global SALOMEDS mutex temporarily.
  // In particular, "unlock-dosomething-lock" scheme should be used, when some non-SALOMEDS
  // CORBA interface is called (component's engine), to avoid deadlocks in case of 
  // indirect recursion.
  void lock();
  void unlock();
};

#endif