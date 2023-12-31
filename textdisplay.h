#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"
#include <iostream>
#include <vector>

class Cell;

class TextDisplay : public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;

public:
  TextDisplay(int n);

  void notify(Subject<Info, State> &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
