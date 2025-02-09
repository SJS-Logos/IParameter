#include "IParameter.h"
#include "OsUtil/Observer.h"

/* This class can be used for building up structures of parameters
   In a typical use case the configuration will be defined in a system independant 
   
   file:
   // Configuration: A structure with public IParameterRef fields
    struct Configuration {
      IParameterRef<int> id;
      IParameterRef<std::string> name;

      Configuration() {}
    };
    
    And a system dependant function somewhere else will setup how to maintain values:
    
    // Concrete Implementations
    template <typename T>
    class StaticParameter : public IParameter<T> {
    public:
        explicit StaticParameter(const T& value) : _value(value) {}

        virtual operator T() const { return _value; }
        virtual T& operator=(const T& other) { _value = other; return _value; }

    private:
        T _value;
    };
    
    inline void initializeConfig(Configuration& config)
    {
      config.id.forward(new StaticParameter<int>(101));
      config.name.forward(new StaticParameter<std::string>("Test_User"));       
    }
*/
template <typename T>
class IParameterRef {
public:
    explicit IParameterRef() : _ownedParameter(NULL) {}

private:
    IParameterRef(const IParameterRef&);
    IParameterRef& operator=(const IParameterRef&);

public:
    IParameterRef& forward(IParameter<T>* rhs) {
        if (_ownedParameter) delete _ownedParameter;
        _ownedParameter = rhs;
        return *this;
    }

    operator T() const { return *_ownedParameter; }

    IParameterRef& operator=(const T& other) {
        if (_ownedParameter) *_ownedParameter = other;
        return *this;
    }
    
    void attach(Observer< IParameter<T> >* observer) {
        _ownedParameter.attach( observer );
    }

    void detach(Observer< IParameter<T> >* observer) {
        _ownedParameter->detach(observer);
    }    

    ~IParameterRef() { delete _ownedParameter; }

private:
    IParameter<T>* _ownedParameter;
};