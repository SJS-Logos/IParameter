#ifndef IPARAMETER_H
#define IPARAMETER_H

#include "OsUtil/Observable.h"
#include "OsUtil/Observer.h"
#include "IParameter/IParameter.h"

template <typename T>
class IParameterObservable : public Observable< IParameter<T> >, IParameter<T> {
};

template <typename T>
class IParameterRefObservable {
public:
    explicit IParameterRefObservable() : _ownedParameter(nullptr) {}

private:
    IParameterRefObservable(const IParameterRefObservable&);
    IParameterRefObservable& operator=(const IParameterRefObservable&);

public:
    template <typename Type, typename P1>
    IParameterRefObservable& emplace(Type type, P1 p1) {
        if (_ownedParameter) delete _ownedParameter;
        _ownedParameter = new type(p1);
        return *this;
    }    
    
    template <typename Type, typename P1, typename P2>
    IParameterRefObservable& emplace(Type type, P1 p1, P2 p2) {
        if (_ownedParameter) delete _ownedParameter;
        _ownedParameter = new type(p1,p2);
        return *this;
    }    
    

    operator T() const { return *_ownedParameter; }

    IParameterRefObservable& operator=(const T& other) {
        if (_ownedParameter) *_ownedParameter = other;
        return *this;
    }
    
    void attach(Observer< IParameter<T> >* observer) {
        _ownedParameter.attach( observer );
    }

    void detach(Observer< IParameter<T> >* observer) {
        _ownedParameter->detach(observer);
    }    

    ~IParameterRefObservable() { delete _ownedParameter; }

private:
    IParameterObservable<T>* _ownedParameter;
};

#endif // IPARAMETER_H