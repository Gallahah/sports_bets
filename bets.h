#ifndef SPORTS_BETS_BETS_H
#define SPORTS_BETS_BETS_H
#include <string>

struct Bet {
    string user; // name of the person that is placing a bet
    string event; // name of the event
    char choice;
    float bet_amount; // amount of the bet
    float possible_winnings; // amount of possible winnings
};

#endif //SPORTS_BETS_BETS_H