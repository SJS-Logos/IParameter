#include "IParameter.h"

/* This class can be used for building structures of parameters
   In a typical use case the configuration will be defined in a system independent file:
   
   // Configuration: A structure with public IParameterRef fields
    struct Configuration {
      IParameterRef<int> id;
      IParameterRef<std::string> name;
      std::vector<IParameterRef<amount_t> > priceList;

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
      config.id.emplace(StaticParameter<int>, 101);
      config.name.emplace(StaticParameter<std::string>, "Test_User");
      for (size_t i=0; i < 10; i++) {
        priceList.emplace_back( IParameterRef<amount_t> ).emplace( StaticParameter<amount_t>, 2500 );
      }
    }
*/
template <typename T>
class IParameterRef {
public:
    explicit IParameterRef() : _ownedParameter(nullptr) {}

private:
    IParameterRef(const IParameterRef&);
    IParameterRef& operator=(const IParameterRef&);

public:
    template <typename Type, typename P1>
    IParameterRef& emplace(Type type, P1 p1) {
        if (_ownedParameter) delete _ownedParameter;
        _ownedParameter = new type(p1);
        return *this;
    }    
    
    template <typename Type, typename P1, typename P2>
    IParameterRef& emplace(Type type, P1 p1, P2 p2) {
        if (_ownedParameter) delete _ownedParameter;
        _ownedParameter = new type(p1,p2);
        return *this;
    }    

    operator T() const { return *_ownedParameter; }

    IParameterRef& operator=(const T& other) {
        if (_ownedParameter) *_ownedParameter = other;
        return *this;
    }
    
    ~IParameterRef() { delete _ownedParameter; }

private:
    IParameter<T>* _ownedParameter;
};