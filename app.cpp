#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>
#include <random>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <vector>

using std::string;
using std::endl;
using std::cin;

void mainMenu(string& account) {
    // Main variables
    int main_menu;
    int gems = 0; // Primo gems starts at 0
    string ingame_name;
    string new_name;
    int settings_menu = 0;

    // UID Generator
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> dis_uid(1000000, 9999999);
    int uid = dis_uid(gen);

    // Random generator for shooter
    std::random_device shoot;
    std::mt19937 lol(shoot());

    // Inventory
    int inventory = 25; // Starting inventory space

    // Start Game
    std::cout << "====== Wish Emulator ======" << endl;
    std::cout << "\nWelcome to Wish Emulator! What do you want to be called? ";
    cin >> ingame_name;
    system("cls");

    while (true) {
        std::cout << "1. Play\n2. Wish\n3. Check Inventory\n4. Shop\n5. Profile\n6. Settings\n7. Logout/Exit" << endl;
        std::cout << "\nEnter choice (1-7): ";
        cin >> main_menu;
        system("cls");

        switch (main_menu) {
        case 1: {
            int play_menu;
            std::cout << "======= Play Section =======" << endl;
            std::cout << "\"In order to acquire primo gems, you must complete the challenges\"" << endl;
            std::cout << "\nPlease select a challenge to play:" << endl;
            std::cout << "\n1. Minesweeper\n2. Math quiz\n3. Dodge this!\n4. Back" << endl;
            std::cout << "\nEnter choice (1-4): ";
            cin >> play_menu;
            system("cls");
            
            switch (play_menu) {
            case 3: {
                char choice;
                do {
                    int wave = 1;
                    int earnedGems = 0;
                    bool alive = true;

                    std::cout << "\n====== DODGE THIS! ======\n";
                    std::cout << "Avoid enemy attacks from the shooter and survive each wave to earn primo gems!\n";
                    std::cout << "Each wave you survive rewards you with 10 primo gems.\n\n";
                    system("cls");

                    while (alive) {
                        // Generate 3 unique random enemy positions (1–5)
                        std::vector<int> enemies = {1, 2, 3, 4, 5};
                        shuffle(enemies.begin(), enemies.end(), lol);
                        std::vector<int> attackPos = {enemies[0], enemies[1], enemies[2]};

                        std::cout << "\n=========== Wave " << wave << " ===========\n";

                        // Shooter design
                        int n = 5;
                        for (int i = 1; i <= n; i++) {
                            std::cout << "[" << i << "]";
                            for (int space = 1; space <= n * 4; space++)
                                std::cout << " ";
                            for (int j = 1; j <= n; j++)
                                std::cout << "* ";
                            std::cout << endl;
                        }

                        int guess;
                        while (true) { //ensures that the loop only runs within the guess loop section not the whole wave loop
                            std::cout << "Pick a position (1-5): ";
                            std::cin >> guess;

                            if (std::cin.fail() || guess < 1 || guess > 5) { //checks for invalid input like out of range numbers or nonnumeric char or both (1a%[])
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove invalid input from buffer
                                std::cout << "Invalid! Try again.\n";
                                continue;
                            }
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input buffer for valid input
                            break; 
                        }

                        bool hit = false;
                        for (int pos : attackPos) {
                            if (guess == pos) {
                                hit = true;
                                break;
                            }
                        }

                        if (hit) {
                            std::cout << "\nGame Over!\n";
                            std::cout << "Enemy attacks were at: ";
                            for (int pos : attackPos)
                                std::cout << pos << " ";
                            std::cout << "\n";
                            alive = false;
                        } else {
                            earnedGems += 10;
                            wave++;
                            system("cls");
                        }
                    }

                    gems += earnedGems;
                    std::cout << "\nYou reached Wave " << wave << "!";
                    std::cout << "\nYou earned " << earnedGems << " Primo Gems this run.";
                    std::cout << "\nYour total Primo Gems: " << gems << "\n";

                    std::cout << "\nPlay again? (Y/N): ";
                    cin >> choice;
                    choice = toupper(choice);

                } while (choice == 'Y');

                std::cout << "\nReturning to Play Menu...\n";
                std::cout << "\nPress ESC to continue...";
                while (_getch() != 27);
                system("cls");
                break;
            }
            default:
                break;
            }
            break;
        }

        case 2:
            std::cout << "Primo gems: " << gems << endl;
            std::cout << "\nPress ESC to continue...";
            while (_getch() != 27);
            system("cls");
            break;

        case 3:
        case 4:
            std::cout << "Option not implemented yet." << endl;
            std::cout << "\nPress ESC to continue...";
            while (_getch() != 27);
            system("cls");
            break;

        case 5:
            std::cout << "====== Profile Section ======" << endl;
            std::cout << "\nHello, " << ingame_name << "!" << endl;
            std::cout << "\n---------------------" << endl;
            std::cout << "\nUsername: " << account << endl;
            std::cout << "UID: 84" << uid << endl;
            std::cout << "\nPress ESC to return to the main menu...";
            while (_getch() != 27);
            system("cls");
            break;

        case 6:
            std::cout << "====== Settings Section ======" << endl;
            std::cout << "\n1. Change name\n2. Delete account" << endl;
            std::cout << "\nEnter choice (1-2): ";
            cin >> settings_menu;
            if (settings_menu == 1) {
                std::cout << "\nEnter new in-game name: ";
                cin >> new_name;
                ingame_name = new_name;
                std::cout << "\nIn-game name changed successfully to " << ingame_name << "!" << endl;
            } else {
                std::cout << "\nAccount deleted. Exiting game..." << endl;
                exit(0);
            }
            std::cout << "\nPress ESC to return to the main menu...";
            while (_getch() != 27);
            system("cls");
            break;

        case 7:
            return;

        default:
            std::cout << "Invalid choice." << endl;
            std::cout << "\nPress ESC to continue...";
            while (_getch() != 27);
            system("cls");
            break;
        }
    }
}

int main() {
    string password, account;
    int choice;

    std::cout << "Please register to continue..." << endl;
    std::cout << "\n1. Register an account" << endl;
    std::cout << "2. Exit" << endl;
    std::cout << "\nEnter your choice: ";
    cin >> choice;
    system("cls");

    if (choice == 1) {
        string confirm_Pass;

        std::cout << "====== Register an account ======" << endl;
        std::cout << "\nCreate username: ";
        cin >> account;
                
        do {
            std::cout << "\nCreate password: ";
            cin >> password;
            std::cout << "\nConfirm password: ";
            cin >> confirm_Pass;

            if (password != confirm_Pass) {
                std::cout << "\nPassword does not match.\n";
            } else {
                string enteredUsername, enteredPassword;
                char ch;
                password = confirm_Pass;
                system("cls");

                do {
                    std::cout << "====== Log In ======" << endl;
                    std::cout << "\nEnter username: ";
                    cin >> enteredUsername;

                    enteredPassword = "";
                    std::cout << "\nEnter password: ";
                    while (true) {
                        ch = _getch();
                        if (ch == '\r') {
                            std::cout << endl;
                            break;
                        } else if (ch == '\b') {
                            if (!enteredPassword.empty()) {
                                enteredPassword.pop_back();
                                std::cout << "\b \b";
                            }
                        } else {
                            enteredPassword += ch;
                            std::cout << "*";
                        }
                    }

                    if (enteredUsername != account || enteredPassword != password)
                        std::cout << "\nSign in failed. Please check your credentials.\n";

                } while (enteredUsername != account || enteredPassword != password);

                std::cout << "\nSign in successful!" << endl;
                system("cls");
            }
        } while (password != confirm_Pass);

        mainMenu(account);
    }
    else if (choice == 2) {
        std::cout << "Exiting..." << endl;
        return 0;
    } else {
        std::cout << "Invalid choice" << endl;
        return 1;
    }

    std::cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();
    return 0;
}
