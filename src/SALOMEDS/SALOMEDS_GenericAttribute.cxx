//  File   : SALOMEDS_GenericAttribute.cxx
//  Author : Sergey RUIN
//  Module : SALOME



#include <string>
#include <TCollection_AsciiString.hxx> 

#include "SALOMEDS_GenericAttribute.hxx"
#include "SALOMEDSImpl_SObject.hxx"
#include "SALOMEDS_SObject.hxx"
#include "SALOMEDS_ClientAttributes.hxx"

#ifdef WIN32
#include <process.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

#include "OpUtil.hxx"

using namespace std; 

SALOMEDS_GenericAttribute::SALOMEDS_GenericAttribute(const Handle(SALOMEDSImpl_GenericAttribute)& theGA)
{
  _isLocal = true;
  _local_impl = theGA;
  _corba_impl = SALOMEDS::GenericAttribute::_nil();
}

SALOMEDS_GenericAttribute::SALOMEDS_GenericAttribute(SALOMEDS::GenericAttribute_ptr theGA)
{
#ifdef WIN32
  long pid =  (long)_getpid();
#else
  long pid =  (long)getpid();
#endif  

  long addr = theGA->GetLocalImpl(GetHostname().c_str(), pid, _isLocal);
  if(_isLocal) {
    _local_impl = ((SALOMEDSImpl_GenericAttribute*)(addr));
    _corba_impl = SALOMEDS::GenericAttribute::_nil();
  }
  else {
    _local_impl = NULL;
    _corba_impl = SALOMEDS::GenericAttribute::_duplicate(theGA);
  }
}

SALOMEDS_GenericAttribute::~SALOMEDS_GenericAttribute() 
{
  if (!_isLocal) {
    _corba_impl->Destroy();
  }
}

void SALOMEDS_GenericAttribute::CheckLocked() 
{
  if(_isLocal) {
    try {
      _local_impl->CheckLocked();
    }
    catch(...) {
      throw SALOMEDS::GenericAttribute::LockProtection();
    }
  }
  else {
    _corba_impl->CheckLocked();
  }
}

std::string SALOMEDS_GenericAttribute::Type()
{
  std::string aType;
  if(_isLocal) {
    aType = _local_impl->Type().ToCString();
  }
  else {
    aType = _corba_impl->Type();
  }
  return aType;
}

std::string SALOMEDS_GenericAttribute::GetClassType()
{
  std::string aType;
  if(_isLocal) {
    aType = _local_impl->GetClassType().ToCString();
  }
  else {
    aType = _corba_impl->GetClassType();
  }
  return aType;
}

_PTR(SObject) SALOMEDS_GenericAttribute::GetSObject()
{
  SALOMEDSClient_SObject* aSO = NULL;
  if(_isLocal) {
    aSO = new SALOMEDS_SObject(_local_impl->GetSObject());
  }
  else {
    aSO = new SALOMEDS_SObject(_corba_impl->GetSObject());
  }

  return _PTR(SObject)(aSO);
}


SALOMEDS_GenericAttribute* SALOMEDS_GenericAttribute::CreateAttribute(const Handle(SALOMEDSImpl_GenericAttribute)& theGA)
{
  SALOMEDS_GenericAttribute* aGA = NULL;
  std::string aTypeOfAttribute = theGA->GetClassType().ToCString();
  __CreateGenericClientAttributeLocal
  return aGA;  
}

SALOMEDS_GenericAttribute* SALOMEDS_GenericAttribute::CreateAttribute(SALOMEDS::GenericAttribute_ptr theGA)
{
  SALOMEDS_GenericAttribute* aGA = NULL;
  std::string aTypeOfAttribute = theGA->GetClassType();
  __CreateGenericClientAttributeCORBA
  return aGA;  
}
