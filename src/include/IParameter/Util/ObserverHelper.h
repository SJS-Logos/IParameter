#ifndef OBSERVER_HELPER_H
#define OBSERVER_HELPER_H

class LogosObservable;
class LisaVariant;

class LogosNotifiable {
public:
  virtual void update() = 0;
  virtual ~LogosNotifiable();
  
private:
  LogosObservable* observer_;
};

class NotifiableBool : public LogosNotifiable {
public:
  bool checkChangedAndClear();
  void update() override;
private:
  bool isChanged_;
};


class LogosObservable {
public:
  LogosObservable();
  void attach( LogosNotifiable* notifiable );
  void detach( LogosNotifiable* notifiable);

  void update();
private:
  struct LinkedElement {
    LogosNotifiable* notifiable_;
    LinkedElement* next_;
  } *linked_list_;
};

#endif // OBSERVER_HELPER_H
