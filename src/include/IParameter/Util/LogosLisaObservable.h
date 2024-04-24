#ifndef LOGOS_LISA_OBSERVABLE_H
#define LOGOS_LISA_OBSERVABLE_H

#include "ObserverHelper.h"

class LisaVariant;
class Lisa2_Facade;

class LogosLisaObservable : public LogosObservable  {
  public:
  
  LogosLisaObservable();
  void bind( Lisa2_Facade& facade, int parameterIndex );
  
  private:
  
  static void updateStatic(void* ThisContext, int ParameterIndex, LisaVariant* Parameter);
};

#endif // LOGOS_LISA_OBSERVABLE_H
