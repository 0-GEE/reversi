#include "cell.h"
#include "state.h"

enum Direction reverse(const enum Direction &d) {
    switch (d) {
        case Direction::E:
            return Direction::W;
        
        case Direction::N:
            return Direction::S;

        case Direction::NE:
            return Direction::SW;

        case Direction::NW:
            return Direction::SE;

        case Direction::S:
            return Direction::N;

        case Direction::SE:
            return Direction::NW;

        case Direction::SW:
            return Direction::NE;

        default:
            return Direction::E;
    
    }
}

enum Direction coordsToDirection(const Info &senderInfo, const Info &myInfo) {
    size_t r = myInfo.row;
    size_t c = myInfo.col;

    size_t nr = senderInfo.row;
    size_t nc = senderInfo.col;

    if ((r < nr) && (c == nc)) return Direction::S;
    if ((r == nr) && (c > nc)) return Direction::W;
    if ((r > nr) && (c == nc)) return Direction::N;
    if ((r == nr) && (c < nc)) return Direction::E;

    if ((r < nr) && (c > nc)) return Direction::SW;
    if ((r > nr) && (c > nc)) return Direction::NW;
    if ((r > nr) && (c < nc)) return Direction::NE;
    return Direction::SE;
}

Cell::Cell(size_t r, size_t c): Subject<Info, State>{}, Observer<Info, State>{}, 
    r{r}, c{c}, colour{Colour::NoColour} {}

void Cell::setPiece(Colour colour) {
    this->colour = colour;

    setState(State{StateType::NewPiece, colour, Direction::N});
    notifyObservers();
}

void Cell::toggle() {
    colour = colour == Colour::Black? Colour::White : Colour::Black;
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    if (colour == Colour::NoColour) return;

    State senderSignal = whoFrom.getState();
    Info senderInfo = whoFrom.getInfo();
    enum Direction fromDirection = coordsToDirection(senderInfo, getInfo());

    if (senderSignal.type == StateType::NewPiece) {
        // neighbour has new piece
        if (colour == senderSignal.colour) return;

        State myNewState = State{StateType::Relay, senderSignal.colour, fromDirection};
        setState(myNewState);

    } else if (senderSignal.type == StateType::Relay) {
        if (fromDirection != senderSignal.direction) return; // notif is not intended for us

        if (colour == senderSignal.colour) {
            State newState = State{StateType::Reply, colour, reverse(fromDirection)};
            setState(newState);
        } else {
            setState(senderSignal);
        }

    } else if (senderSignal.type == StateType::Reply) {
        if (fromDirection != senderSignal.direction) return;
        if (colour == senderSignal.colour) return;

        toggle();
        setState(senderSignal);

    } else {
        // this should never be reached
        return;
    }

    notifyObservers();

}

Info Cell::getInfo() const {
    return Info{r, c, colour};
}
