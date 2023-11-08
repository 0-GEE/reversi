#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(int n): theDisplay{vector<vector<char>>{}}, gridSize{n * n} {
    theDisplay.assign(n, vector<char>{});

    for (auto &row : theDisplay) {
        row.assign(n, '-');
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    State senderSignal = whoNotified.getState();
    Info senderInfo = whoNotified.getInfo();

    if (senderSignal.type == StateType::Relay) return;

    if (senderInfo.colour == Colour::Black) {

        theDisplay[senderInfo.row][senderInfo.col] = 'B';

    } else if (senderInfo.colour == Colour::White) {

        theDisplay[senderInfo.row][senderInfo.col] = 'W';


    } else {

        return;
    }
}


ostream &operator<<(ostream &out, const TextDisplay &td) {

    for (auto row : td.theDisplay) {
        for (auto chr : row) {
            out << chr;
        }
        out << endl;
    }

    return out;
}
