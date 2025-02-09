#ifndef IPARAMETER_LISA2_H
#define IPARAMETER_LISA2_H

class Lisa2_Facade;

template <typename T, class Converter = StringHelper, class Facade = Lisa2_Facade>
class IParameterLisa2Helper : public IParameter<T>, public LogosLisaObservable {
public:
  explicit IParameterLisa2Helper( Facade& facadeInstance = *Facade::GetInstance() ) :
        facadeInstance_( facadeInstance ), parameterIndex_(0)
  {
  }

  static void updateStatic(void* ThisContext, int /*ParameterIndex*/, LisaVariant* /*Parameter*/ ) {
    
    ((IParameterLisa2Helper)ThisContext)->Update();
  }

  void bind(int parameterIndex, bool isObservable = false)
  {
    parameterIndex_ = parameterIndex;
    if ( isObservable ) {
      LogosLisaObservable::bind( facadeInstance_, parameterIndex );
    }
  }
  
  virtual T get() const
  {
    char buffer[ 2048 ];
    int returnValue = facadeInstance_.GetParameterValue(parameterIndex_, buffer, sizeof(buffer));
    T result;
    if ( returnValue != 0 ) {
      // Log Critical error. Parameter does not exist
      Converter::from_string( &result, std::string("") );
    }
    else {
      Converter::from_string( &result, std::string( buffer ) );
    }
    return result;
  }	

  virtual void set( const T value ) 
  {
    int returnValue = facadeInstance_.SetParameterValue(parameterIndex_, Converter::to_string(value).c_str());
    if (returnValue != 0) {
      // Log Critical error. Parameter does not exist
    }
  }
	
private:
  Facade& facadeInstance_;
  int parameterIndex_;
  Converter cnv;
};

#endif // IPARAMETER_LISA2_H
