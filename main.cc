#include "grid.h"
#include "state.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit | ios::failbit);
  string cmd;
  Grid g;

  size_t ticker = 0;

  try {
    while (true) {
      cin >> cmd;
      if (cmd == "new") {
        int n;
        cin >> n;

        ticker = 0;
        g.init(n);
        cout << g;
      } else if (cmd == "play") {
        int r = 0, c = 0;
        cin >> r >> c;

        bool success;

        if ((ticker % 2) == 0) {
          // play black on even turns
          success = g.setPiece(r, c, Colour::Black);
        } else {
          success = g.setPiece(r, c, Colour::White);
        }

        if (success) {
          cout << g;

          // Does anyone win on this turn?
          if (g.isFull()) {
            Colour winner = g.whoWon();

            if (winner == Colour::White) {
              cout << "White wins!" << endl;
            } else if (winner == Colour::Black) {
              cout << "Black wins!" << endl;
            }
            break;
          }
          ++ticker;
        }
      }
    }
  } catch (ios::failure &) {
  } // Any I/O failure quits
}
