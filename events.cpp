#include "events.h"
#include "bets.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

vector<Bet> bets; // storing the active bets
vector<SportsEvent> events; // storing the active events

// events
// function to add a new event
void addSportEvent() {
    SportsEvent event;

    cout << "Enter the name of the first team: ";
    getline(cin, event.team1);
    cout << "Enter the name of the second team: ";
    getline(cin, event.team2);
    event.name = event.team1 + " " + event.team2;

    cout << "Enter the name of the sport: ";
    getline(cin, event.sport);

    // input a coefficient and check if the input is valid
    while (true) {
        cout << "Enter the coefficient for " << event.team1 << ": ";
        if (cin >> event.coeff_win_team1) {
            break;  // valid float entered, exit loop
        } else {
            cout << "Please enter a valid coefficient." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "Enter the coefficient for " << event.team2 << ": ";
        if (cin >> event.coeff_win_team2) {
            break;
        } else {
            cout << "Please enter a valid coefficient." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "Enter coefficient for a draw: ";
        if (cin >> event.coeff_draw) {
            break;
        } else {
            cout << "Please enter a valid coefficient." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    event.ended = false; // the event is yet to be played
    events.push_back(event); // add to vector
}

// function to display all events
void displaySportEvents() {
    if (events.empty()) {
        cout << "There are no upcoming events." << endl;
        return;
    } else {
        cout << "List of all upcoming sport events:" << endl;
        for (auto &event: events) {
            cout << event.name << " | " << event.sport << ": " << event.team1 << ": " << event.coeff_win_team1 <<
                 " V " << event.team2 << ": " << event.coeff_win_team2 <<
                 " | Draw: " << event.coeff_draw << endl;
        }
    }
}

// function to filter events by sport
void filterEventsBySport() {
    if (events.empty()) {
        cout << "There are no upcoming events." << endl;
        return;
    } else {
        string sport;
        cout << "Enter the type of sport to filter: ";
        cin >> sport;
        cout << "List of upcoming sport events for " << sport << ":" << endl;
        for (auto &event: events) {
            if (event.sport == sport) {
                cout << event.name << " | " << event.sport << ": " << event.team1 << ": " << event.coeff_win_team1 <<
                     " V " << event.team2 << ": " << event.coeff_win_team2 <<
                     " | Draw: " << event.coeff_draw << endl;
            }
        }
    }
}

// function to filter events by coefficient
void filterEventsByCoeff() {
    if (events.empty()) {
        cout << "There are no upcoming events." << endl;
        return;
    } else {
        float coefficient;
        cout << "Enter the coefficient to filter: ";
        cin >> coefficient;
        cout << "List of upcoming events with coefficient " << coefficient << ":" << endl;
        for (auto &event: events) {
            if (event.coeff_win_team1 == coefficient || event.coeff_win_team2 == coefficient ||
                event.coeff_draw == coefficient) {
                cout << event.name << " | " << event.sport << ": " << event.team1 << ": " << event.coeff_win_team1 <<
                     " V " << event.team2 << ": " << event.coeff_win_team2 <<
                     " | Draw: " << event.coeff_draw << endl;
            }
        }
    }
}

// bets
// function to place a new bet
void placeBet() {
    Bet bet;
    cout << "Enter your name: ";
    getline(cin, bet.user);
    cout << "Enter the name of the event you want to bet on: ";
    getline(cin, bet.event);
    cout << "Enter bet amount: ";
    cin >> bet.bet_amount;

    // finding the event and calculating possible winnings
    for (auto& event : events) {
        if (event.name == bet.event) {
            cout << "Enter 1 to bet on " << event.team1 << ", 2 to bet on " << event.team2 <<
                 ", or X to bet on a draw: ";

            //char choice;
            cin >> bet.choice;

            switch (bet.choice) {
                case '1':
                    bet.possible_winnings = bet.bet_amount * event.coeff_win_team1;
                    break;
                case '2':
                    bet.possible_winnings = bet.bet_amount * event.coeff_win_team2;
                    break;
                case 'X':
                case 'x':
                    bet.possible_winnings = bet.bet_amount * event.coeff_draw;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    return;
            }
            bets.push_back(bet);
            cout << "Your bet has been placed!" << endl;
            return;
        }
    }

    cout << "Invalid event name. Please try again." << endl;
}

// function to end an event and process bets
void endEvent() {
    if (events.empty()) {
        cout << "There are no upcoming events." << endl;
        return;
    } else {
        string event_name;
        int result;

        cout << "Enter the name of the event that has ended: ";
        getline(cin, event_name);

        // rng
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 2);

        // generate a number between 0 and 2
        result = dist(gen);

        if (result == 0) {
            cout << "The result of " << event_name << " is: " << "Draw" << endl;
        } else if (result == 1) {
            cout << "The result of " << event_name << " is: " << result << endl;
        } else if (result == 2) {
            cout << "The result of " << event_name << " is: " << result << endl;
        }

        // finding the bets on the ended event and processing them based on the result
        for (auto &bet: bets) {
            if (bet.event == event_name) {
                float winnings = 0;
                SportsEvent event;

                for (auto &ended_event: events) {
                    if (ended_event.name == bet.event) {
                        event = ended_event;
                        break;
                    }
                }
                if (result == 0 && bet.choice == 'X') {
                    winnings = bet.bet_amount * event.coeff_draw;
                    cout << bet.user << " won $" << winnings << " from their bet on " << bet.event << endl;
                } else if (result == 1 && bet.choice == '1') {
                    winnings = bet.bet_amount * event.coeff_win_team1;
                    cout << bet.user << " won $" << winnings << " from their bet on " << bet.event << endl;
                } else if (result == 2 && bet.choice == '2') {
                    winnings = bet.bet_amount * event.coeff_win_team2;
                    cout << bet.user << " won $" << winnings << " from their bet on " << bet.event << endl;
                } else {
                    cout << bet.user << " lost their bet on " << bet.event << endl;
                }
            }
        }

        // removing the ended event from the list of events
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->name == event_name) {
                events.erase(it);
                break;
            }
        }

        // removing the bets on the ended event
        bets.erase(
                remove_if(bets.begin(), bets.end(),
                          [&](const Bet &bet) { return bet.event == event_name; }),
                bets.end()
        );

        cout << "The event has been processed and removed from the list of upcoming events." << endl;
    }
}