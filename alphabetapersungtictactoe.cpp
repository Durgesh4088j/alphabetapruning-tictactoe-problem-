#include <bits/stdc++.h>
using namespace std;

const char PLAYER = 'X';
const char OPP    = 'O';
const char EMPTY  = '.';

struct Move { int r, c; };

int evaluate(const array<array<char,3>,3>& b) {            // ye function decide krkenga ki koi jita hau ya nhi
    for(int i=0;i<3;i++){
        if (b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
            if (b[i][0] == PLAYER) return +10;                     // diagonal 
            if (b[i][0] == OPP)    return -10;
        }
        if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) {
            if (b[0][i] == PLAYER) return +10;
            if (b[0][i] == OPP)    return -10;
        }
    }
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == PLAYER) return +10;
        if (b[0][0] == OPP)    return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == PLAYER) return +10;
        if (b[0][2] == OPP)    return -10;
    }
    return 0;
}

bool movesLeft(const array<array<char,3>,3>& b) {
    for (auto &r : b) for (char c : r) if (c == EMPTY) return true;      // decide krta hai ki bord me koi space khali to nhi hai 
    return false;
}

int alphabeta(array<array<char,3>,3>& board, int depth, int alpha, int beta, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!movesLeft(board)) return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int val = alphabeta(board, depth+1, alpha, beta, false);
                    board[i][j] = EMPTY;
                    best = max(best, val);
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (board[i][j] == EMPTY) {
                    board[i][j] = OPP;
                    int val = alphabeta(board, depth+1, alpha, beta, true);
                    board[i][j] = EMPTY;
                    best = min(best, val);
                    beta = min(beta, best);
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
}

Move findBestMove(array<array<char,3>,3>& board) {
    int bestVal = INT_MIN;
    Move bestMove{-1,-1};
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER;
                int moveVal = alphabeta(board, 0, INT_MIN, INT_MAX, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove = {i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void printBoard(const array<array<char,3>,3>& b) {
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++) cout << b[i][j] << ' ';
        cout << '\n';
    }
}

int main(){
    array<array<char,3>,3> board;
    for(auto &r: board) for(auto &c: r) c = EMPTY;

    cout << "Tic-Tac-Toe: AI = X, Human = O\n";
    printBoard(board);

    bool humanTurn = true;
    while (true) {
        if (!movesLeft(board) || evaluate(board) != 0) break;
        if (humanTurn) {
            int r,c;
            cout << "Enter your move (row col: 0-based): ";
            if (!(cin >> r >> c)) return 0;
            if (r<0||r>2||c<0||c>2||board[r][c]!=EMPTY) {
                cout << "Invalid move, try again.\n";
                continue;
            }
            board[r][c] = OPP;
        } else {
            Move aiMove = findBestMove(board);
            if (aiMove.r == -1) {
                cout << "No moves left\n";
                break;
            }
            board[aiMove.r][aiMove.c] = PLAYER;
            cout << "AI plays: " << aiMove.r << ' ' << aiMove.c << '\n';
        }
        printBoard(board);
        humanTurn = !humanTurn;
    }

    int finalScore = evaluate(board);
    if (finalScore == 10) cout << "AI (X) wins!\n";
    else if (finalScore == -10) cout << "Human (O) wins!\n";
    else cout << "Draw.\n";
    return 0;
}
