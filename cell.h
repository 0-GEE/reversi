#ifndef CELL_H
#define CELL_H
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"
#include <cstddef>

class Cell : public Subject<Info, State>, public Observer<Info, State> {
  const size_t r, c;
  Colour colour = Colour::NoColour;

public:
  Cell(size_t r, size_t c);

  void setPiece(Colour colour); // Place a piece of given colour here.
  void toggle();                // Toggles my colour.

  void notify(
      Subject<Info, State> &whoFrom) override; // My neighbours will call this
                                               // when they've changed state
  Info getInfo() const override;
};
#endif
