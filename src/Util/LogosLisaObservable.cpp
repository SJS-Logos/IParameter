#include "Util/LogosLisaObservable.h"
#include "Lisa2/CLisa2_Facade.h"

LogosLisaObservable::LogosLisaObservable() : LogosObservable() {
  
}
void LogosLisaObservable::bind( Lisa2_Facade& facade,int parameterIndex )
{  
  facade.AddChangeEvent(parameterIndex, this, updateStatic);  
}

void LogosLisaObservable::updateStatic(void* ThisContext, int /*ParameterIndex*/, LisaVariant* /*Parameter*/)
{
  ((LogosObservable*)ThisContext)->update();
}

