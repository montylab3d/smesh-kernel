//  Copyright (C) 2004  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
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
//  File   : TraceCollector_WaitForServerReadiness.cxx
//  Author : Paul RASCLE (EDF)
//  Module : KERNEL
//  $Header$

#include "TraceCollector_WaitForServerReadiness.hxx"
#include <iostream>
#include <ctime>

using namespace std;

// ============================================================================
/*!
 *  Wait until a server is registered in naming service.
 *  \param serverName name of the server to find.
 *  When SALOME_NamingService is available,
 *  use NamingService_WaitForServerReadiness instead.
 *  This function is needed when macro MESSAGE used by SALOME_NamingService
 *  is not available (inside LocalTrace methods, for instance !).
 *  Direct access to CORBA Name Service. Look for serverName at Name service
 *  Root without extensions.
 */
// ============================================================================

CORBA::Object_ptr TraceCollector_WaitForServerReadiness(CORBA::ORB_ptr orb,
							string serverName)
{
  long TIMESleep = 500000000;
  int NumberOfTries = 40;

  timespec ts_req;
  ts_req.tv_nsec=TIMESleep;
  ts_req.tv_sec=0;
  timespec ts_rem;
  ts_rem.tv_nsec=0;
  ts_rem.tv_sec=0;

  CORBA::Object_var obj;

  try
    {
      // NB. You can't use SALOME_NamingService class because
      // it uses MESSAGE macro
      // Otherwise, you will get segmentation fault.   

      CosNaming::NamingContext_var inc;
      CosNaming::Name name;
      name.length(1);
      name[0].id = CORBA::string_dup(serverName.c_str());
      CORBA::Object_var theObj=CORBA::Object::_nil();

      for (int itry=0; itry < NumberOfTries; itry++)
	{
	  try
	    { 
	      if(!CORBA::is_nil(orb)) 
		theObj = orb->resolve_initial_references("NameService");
	      if (!CORBA::is_nil(theObj))
		inc = CosNaming::NamingContext::_narrow(theObj);
	    }  
	  catch( CORBA::COMM_FAILURE& )
	    {
	      cout << "TraceCollector_WaitForServerReadiness: "
		   << "CORBA::COMM_FAILURE: "
		   << "Unable to contact the Naming Service" << endl;
	    }
          catch(...)
	    {
	      cout << "TraceCollector_WaitForServerReadiness: "
		   << "Unknown exception dealing with Naming Service" << endl;
	    }
	  
	  obj=CORBA::Object::_nil();
	  if(!CORBA::is_nil(inc))
	    {
	      try
		{
		  obj = inc->resolve(name);
		  if (!CORBA::is_nil(obj))
		    {
		      cout << "TraceCollector_WaitForServerReadiness: "
			   << serverName << " found in CORBA Name Service" << endl;
		      break;
		    }
		}
	      catch (const CosNaming::NamingContext::NotFound&)
		{
		  cout << "Caught exception: Naming Service can't found Logger";
		}
	    }
	  int a = nanosleep(&ts_req,&ts_rem);
	  cout << "TraceCollector_WaitForServerReadiness: retry look for"
	       << serverName << endl;
	}	   
    }
  catch (const CosNaming::NamingContext::NotFound&)
    {
      cout << "Caught exception: Naming Service can't found Logger";
    }
  catch (CORBA::COMM_FAILURE&)
    {
      cout << "Caught CORBA::SystemException CommFailure.";
    }
  catch (CORBA::SystemException&)
    {
      cout << "Caught CORBA::SystemException.";
    }
  catch (CORBA::Exception&)
    {
      cout << "Caught CORBA::Exception.";
    }
  catch (...)
    {
      cout << "Caught unknown exception.";
    }
  return obj._retn();
}
