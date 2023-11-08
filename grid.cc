#include "grid.h"
using namespace std;

void assignObservers(vector<vector<Cell>> &grid, TextDisplay *td) {
  size_t maxRowIdx = grid.size() - 1;

  for (size_t currRow = 0; currRow < grid.size(); ++currRow) {

    vector<Cell> &rowData = grid[currRow];
    size_t maxColIdx = rowData.size() - 1;

    for (size_t currCol = 0; currCol < rowData.size(); ++currCol) {

      Cell &currCell = rowData[currCol];

      // We now (attempt to) add all of: NW, N, NE, E, SE, S, SW, W observers

      // NW observer
      if ((currRow > 0) && (currCol > 0)) {
        currCell.attach(&grid[currRow - 1][currCol - 1]);
      }

      // N observer
      if (currRow > 0) {
        currCell.attach(&grid[currRow - 1][currCol]);
      }

      // NE observer
      if ((currRow > 0) && (currCol < maxColIdx)) {
        currCell.attach(&grid[currRow - 1][currCol + 1]);
      }

      // E observer
      if (currCol < maxColIdx) {
        currCell.attach(&rowData[currCol + 1]);
      }

      // SE observer
      if ((currRow < maxRowIdx) && (currCol < maxColIdx)) {
        currCell.attach(&grid[currRow + 1][currCol + 1]);
      }

      // S observer
      if (currRow < maxRowIdx) {
        currCell.attach(&grid[currRow + 1][currCol]);
      }

      // SW observer
      if ((currRow < maxRowIdx) && (currCol > 0)) {
        currCell.attach(&grid[currRow + 1][currCol - 1]);
      }

      // W observer
      if (currCol > 0) {
        currCell.attach(&rowData[currCol - 1]);
      }

      // finally we hook up the TextDisplay
      currCell.attach(td);
    }
  }
}

bool validMove(const vector<vector<Cell>> &grid, const size_t r,
               const size_t c) {
  // check for out of bounds
  size_t max = grid.size();
  if ((r < 0) || (c < 0) || (r >= max) || (c >= max))
    return false;

  // check if cell already occupied
  Cell cellCandidate = grid[r][c];
  if (cellCandidate.getInfo().colour != Colour::NoColour)
    return false;
  return true;
}

Grid::~Grid() {
  delete td;
  delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) { this->ob = ob; }

bool Grid::isFull() const {
  for (auto row : theGrid) {
    for (auto cell : row) {
      if (cell.getInfo().colour == Colour::NoColour)
        return false;
    }
  }
  return true;
}

Colour Grid::whoWon() const {
  if (!isFull())
    return Colour::NoColour;

  int blackCount = 0;
  int whiteCount = 0;

  for (auto row : theGrid) {
    for (auto cell : row) {
      Colour currColour = cell.getInfo().colour;

      if (currColour == Colour::Black) {
        ++blackCount;
      } else if (currColour == Colour::White) {
        ++whiteCount;
      } else {
        continue;
      }
    }
  }

  if (blackCount > whiteCount)
    return Colour::Black;
  if (whiteCount > blackCount)
    return Colour::White;
  return Colour::NoColour;
}

void Grid::init(size_t n) {
  delete td;

  theGrid = vector<vector<Cell>>{};

  for (size_t row = 0; row < n; ++row) {
    vector<Cell> theRow = vector<Cell>{};

    for (size_t col = 0; col < n; ++col) {
      theRow.emplace_back(Cell{row, col});
    }

    theGrid.emplace_back(theRow);
  }

  td = new TextDisplay{(int)n};
  assignObservers(theGrid, td);

  // Initialize middle positions
  //    B W
  //    W B

  size_t halfIdx = n / 2;

  theGrid[halfIdx - 1][halfIdx - 1].setPiece(Colour::Black);
  theGrid[halfIdx - 1][halfIdx].setPiece(Colour::White);
  theGrid[halfIdx][halfIdx - 1].setPiece(Colour::White);
  theGrid[halfIdx][halfIdx].setPiece(Colour::Black);
}

bool Grid::setPiece(size_t r, size_t c, Colour colour) {
  if (!validMove(theGrid, r, c))
    return false;

  // the move is valid

  theGrid[r][c].setPiece(colour);
  return true;
}

void Grid::toggle(size_t r, size_t c) { theGrid[r][c].toggle(); }

ostream &operator<<(ostream &out, const Grid &g) {
  out << *g.td;

  return out;
}
