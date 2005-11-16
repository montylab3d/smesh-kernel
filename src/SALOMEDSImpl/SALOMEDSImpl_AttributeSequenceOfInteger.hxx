//  File   : SALOMEDSImpl_AttributeSequenceOfInteger.hxx
//  Author : Sergey RUIN
//  Module : SALOME

#ifndef _SALOMEDSImpl_AttributeSequenceOfInteger_HeaderFile
#define _SALOMEDSImpl_AttributeSequenceOfInteger_HeaderFile

#include <Standard_DefineHandle.hxx>
#include <TDF_Attribute.hxx>
#include <TColStd_HSequenceOfInteger.hxx>
#include <TDF_Label.hxx>       
#include <TCollection_AsciiString.hxx>
#include "SALOMEDSImpl_GenericAttribute.hxx"

class Standard_GUID;
class Handle(TDF_Attribute);
class Handle(TDF_RelocationTable);


DEFINE_STANDARD_HANDLE( SALOMEDSImpl_AttributeSequenceOfInteger, SALOMEDSImpl_GenericAttribute )

class SALOMEDSImpl_AttributeSequenceOfInteger : public SALOMEDSImpl_GenericAttribute 
{

public:

Standard_EXPORT virtual TCollection_AsciiString Save();
Standard_EXPORT virtual void Load(const TCollection_AsciiString&);
 
Standard_EXPORT static const Standard_GUID& GetID() ;
Standard_EXPORT static  Handle_SALOMEDSImpl_AttributeSequenceOfInteger Set(const TDF_Label& label) ;
Standard_EXPORT SALOMEDSImpl_AttributeSequenceOfInteger();
Standard_EXPORT   void Assign(const Handle(TColStd_HSequenceOfInteger)& other) ;
Standard_EXPORT   void ChangeValue(const Standard_Integer Index,const Standard_Integer Value) ;
Standard_EXPORT   void Add(const Standard_Integer value) ;
Standard_EXPORT   Standard_Integer Value(const Standard_Integer Index) ;
Standard_EXPORT   void Remove(const Standard_Integer Index) ;
Standard_EXPORT   Standard_Integer Length() ;
Standard_EXPORT  const Standard_GUID& ID() const;
Standard_EXPORT   void Restore(const Handle(TDF_Attribute)& with) ;
Standard_EXPORT   Handle_TDF_Attribute NewEmpty() const;
Standard_EXPORT   void Paste(const Handle(TDF_Attribute)& into,const Handle(TDF_RelocationTable)& RT) const;
Standard_EXPORT ~SALOMEDSImpl_AttributeSequenceOfInteger() {}

private: 

Handle_TColStd_HSequenceOfInteger myValue;

public:
  DEFINE_STANDARD_RTTI( SALOMEDSImpl_AttributeSequenceOfInteger )

};

#endif