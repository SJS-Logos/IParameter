#ifndef IPARAMETER_H
#define IPARAMETER_H

#include "OsUtil/Observable.h"

template <typename T>
class IParameter : public Observable< IParameter<T> > {
public:
  virtual operator T() const = 0;
  virtual T& operator=(const T& other) = 0;
  virtual ~IParameter() {}
};

#endif // IPARAMETER_H