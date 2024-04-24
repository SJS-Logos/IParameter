#include "ObserverHelper.h"
#include <memory>

bool NotifiableBool::checkChangedAndClear()
{
  bool isChangedLocal = isChanged_;
  isChanged_ = false;
  return isChangedLocal;
}

void NotifiableBool::update()
{
  isChanged_ = true;
}

LogosNotifiable::~LogosNotifiable() 
{
  observer_->detach(this);
}

void LogosObservable::attach( LogosNotifiable* notifiable)
{
  LinkedElement* e = new LinkedElement;
  e->notifiable_ = notifiable;
  e->next_ = linked_list_;
  linked_list_ = e;
}

void LogosObservable::update()
{
  LinkedElement* i = linked_list_; 
  while (i != nullptr) {
    LinkedElement* next = i->next_;
    i->notifiable_->update();
    i = next;
  }
}


void LogosObservable::detach( LogosNotifiable* notifiable)
{
  LinkedElement* previous = nullptr;
  LinkedElement* i = linked_list_;
  while (i != nullptr && notifiable != i->notifiable_) {
    previous = i; 
    i = i->next_;
  }
  
  if ( i != nullptr) {
    if (previous != nullptr) {
      previous->next_ = i->next_;
    }
    else {
      linked_list_ = i->next_;
    }
    delete i;
  }
}

