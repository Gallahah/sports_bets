#ifndef SPORTS_BETS_EVENTS_H
#define SPORTS_BETS_EVENTS_H
#include <string>

using namespace std;

struct SportsEvent {
    string name; // may be redundant
    string sport; // the sport of the event
    string team1; // name of the first team
    string team2; // name of the second team
    float coeff_win_team1; // coefficient for if team 1 wins
    float coeff_win_team2; // coefficient for if team 2 wins
    float coeff_draw; // coefficient for if the match ends in a draw

    bool ended; // true = match has ended | false = match has not yet been played
    int result; // 0 if draw, 1 if team1 wins, 2 if team2 wins
};

#endif //SPORTS_BETS_EVENTS_H