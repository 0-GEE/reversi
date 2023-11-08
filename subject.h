#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

/*
   Info is for the parts of the subjject inherent to what it is:  its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications.
*/

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<Observer<InfoType, StateType> *> observers;
  StateType state;

protected:
  void setState(StateType newS);

public:
  void attach(Observer<InfoType, StateType> *o);
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
  StateType getState() const;
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
  for (auto &ob : observers)
    ob->notify(*this);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) {
  state = newS;
}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const {
  return state;
}
#endif
