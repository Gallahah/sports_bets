#include <iostream>
#include <algorithm>

using namespace std;

void setSportEvents();
void getSportEvents();
void filterEventsBySport();
void filterEventsByCoeff();
void placeBet();
void endEvent();


int main() {
    int choice;
    do {
        cout << "--------------" << endl;
        cout << "Sports Betting" << endl;
        cout << "--------------" << endl;
        cout << "1. Add a new sport event" << endl;
        cout << "2. Display all upcoming sport events" << endl;
        cout << "3. Filter sport events by sport" << endl;
        cout << "4. Filter sport events by coefficient" << endl;
        cout << "5. Place a new bet" << endl;
        cout << "6. End a sport event" << endl;
        cout << "7. Quit" << endl;
        cout << "Enter your choice " << endl;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                setSportEvents();
                break;
            case 2:
                getSportEvents();
                break;
            case 3:
                filterEventsBySport();
                break;
            case 4:
                filterEventsByCoeff();
                break;
            case 5:
                placeBet();
                break;
            case 6:
                endEvent();
                break;
            case 7:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 7);
    return 0;
}
