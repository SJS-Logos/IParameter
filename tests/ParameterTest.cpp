#include "gtest/gtest.h"

#include "IParameter/IParameterRef.h"

struct Configuration {
  IParameterRef<int> id;
  IParameterRef<std::string> name;

  Configuration() {}
};

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



TEST(IParameterTest, HelloWorld)
{
  Configuration config;
  config.id.emplace<StaticParameter<int> >(101);
  config.name.emplace<StaticParameter<std::string> >( std::string("Test_User"));

  EXPECT_EQ(config.id, 101);
  EXPECT_EQ(config.name, "Test_User" );
}