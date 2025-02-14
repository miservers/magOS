#ifndef OBJECT_REF_H
#define OBJECT_REF_H

#include <string>
#include <unordered_map>

#include "Types.h"
#include "JavaClass.h"
using namespace std;

class ObjectRef 
{
  public:
    u2 nameIndex;
    string className; // java name of this object
    
    JavaClass* clazz;
    unordered_map<FieldInfo*,j_int_t> fields; //map <FieldInfo*,value> 
    
    int refs; // how many times this object is referenced.
              // it may be garbage collected if refs=0
              // instructions that increment refs : new
              // instructions that decrement refs : 
    ObjectRef (u2 nameIndex, string className);
    ~ObjectRef ();
    void initFields ();
    void putField (FieldInfo*, j_int_t value);
};




#endif