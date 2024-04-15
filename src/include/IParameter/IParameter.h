#ifndef IPARAMETER_H
#define IPARAMETER_H

template <typename T>
class IParameter {
public:
  virtual T get() const = 0;
  virtual void set( const T value ) = 0;
};


template <typename T, class Converter = StringHelper, class Facade = Lisa2_Facade>
class IParameterLisa2Helper : public IParameter<T> {
public:
  explicit IParameterLisa2Helper( int parameterIndex, const T& defaultValue, Facade& facadeInstance = *Facade::GetInstance()) :
        facadeInstance_( facadeInstance ), parameterIndex_(parameterIndex), defaultValue_(defaultValue)
  {
  }

  virtual T get() const
  {
    char buffer[ 2048 ];
    int returnValue = facadeInstance_.GetParameterValue(parameterIndex_, buffer, sizeof(buffer));
    if ( returnValue != 0 ) {
      // Log Critical error. Parameter does not exist
      return defaultValue_;
    }
    else {
      return Converter::from_string( std::string( buffer ), defaultValue_);
    }
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
  const int defaultValue_;
  Converter cnv;
};

#endif // IPARAMETER_H