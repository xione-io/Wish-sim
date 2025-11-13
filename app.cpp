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

void mainMenu(string& account){
    /*Variables for main menu*/
    //main variables
    int main_menu;
    int gems = 0; //Primo gems starts at 0

    //Profile variables
    string ingame_name;
    //if in game name changes, variables to hold new name
    int settings_menu;
    string new_name;
    if (settings_menu == 1){
        ingame_name = new_name;
    }
    
    //UID Generator
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> dis_uid(1000000, 9999999);
    int uid = dis_uid(gen);

    //random 3 shots of robot
    std::random_device shoot;
    std::mt19937 lol(shoot());

    /*Start Game*/
    //In-game name (asked once when entering the menu)
    std::cout << "====== Wish Emulator ======" << endl;
    std::cout << "\nWelcome to Wish Emulator! What do you want to be called? ";
    cin >> ingame_name;
    system("cls");

    // Loop the menu so user can go to sections and come back
    while (true) {
        std::cout << "1. Play\n2. Wish\n3. Check Inventory\n4. Shop\n5. Profile\n6. Settings\n7. Logout/Exit" << endl;
        std::cout << "\nEnter choice (1-7): ";
        cin >> main_menu;

        system("cls");

        switch (main_menu){
        case 1: {
            int play_menu;
            std::cout << "======= Play Section =======" << endl;
            std::cout << "\"In order to aquire primo gems, you must complete the challenges\"" << endl;
            std::cout << "\n\n1. Minesweeper\n2. Math quiz\n3. Dodge this!\n4. Back" << endl;
            std::cout << "\nEnter choice (1-4): ";
            cin >> play_menu;
            system("cls");
            
            //play case
            switch (play_menu){
            case 3: {
                char choice;
                do {
                    std::cout << "\n====== DODGE THIS! ======" << endl;
                    std::cout << "\nThe robot will strike at 3 random positions (1-5) each wave.";
                    std::cout << "\nObjective: Must avoid the attacks and survive each wave to obtain 10 primo gems!\n\n";

                    int wave = 1;
                    bool alive = true;

                    while (alive) {
                        // Generate 3 unique random enemy positions (1–5)
                        std::vector<int> enemies = {1, 2, 3, 4, 5};
                        shuffle(enemies.begin(), enemies.end(), lol);  // randomize order using the Mersenne Twister engine

                        // Take only the first 3 numbers as enemy attacks
                        std::vector<int> attackPos = {enemies[0], enemies[1], enemies[2]};

                        std::cout << "\n      ====== Wave " << wave << "======"<< endl;
                        std::cout << "\n\n";
                        //Robot design
                        int n = 5;
                        for (int i = 1; i <= n; i++) {
                            for (int num = 1; num <= (n - n) + 1; num++) {
                                std::cout << "[" << i << "]";
                            }
                            for (int space = 1; space <= n * 4; space++) {
                                std::cout << " ";
                            }
                            for (int j = 1; j <= n; j++) {
                                std::cout << "* ";
                            }
                            std::cout << endl;
                        }

                        //Position input of player
                        int guess;
                        std::cout << "\nSelect a position to dodge (1-5): ";
                        cin >> guess;

                        // Check if guess does not matches any of the 3 attack positions
                        bool hit = false;
                        for (int pos : attackPos) {
                            if (guess == pos) {
                                hit = true;
                                break;
                            }
                        }

                        if (hit) {
                            std::cout << "\nGame Over! ";
                            std::cout << "Enemy attacks were at: ";
                            for (int pos : attackPos)
                                std::cout << pos << " ";
                            std::cout << "\n";
                            alive = false;

                        } else {
                            std::cout << "\nMoving on to the next wave...";
                            wave++;
                            system("cls");
                        }
                    }

                    std::cout << "-----------------------\n";
                    std::cout << "Game Over at Wave " << wave << "!\n";
                    std::cout << "Play again? (Y/N): ";
                    cin >> choice;
                    choice = toupper(choice); // Convert to uppercase for consistency

                } while (choice == 'Y');
                std::cout << "Returning to Play Menu..." << endl;
                std::cout << "\nPress ESC to continue...";
                int key;
                do { key = _getch(); } while (key != 27);
                system("cls");
                break;
            }
                        
            default: 
                break;
            }

            break; //case 1 break
        }
        case 5: {
            if (settings_menu != 1){
                std::cout << "====== Profile Section ======" << endl;
                std::cout << "\nHello, " << ingame_name << "!" << endl;
                std::cout << "\n---------------------" << endl;
                std::cout << "\nUsername: " << account << endl;
                std::cout << "UID: 84" << uid << endl;
            }
            else if (settings_menu == 1){
                std::cout << "====== Profile Section ======" << endl;
                std::cout << "\nHello, " << ingame_name << "!" << endl;
                std::cout << "\n---------------------" << endl;
                std::cout << "\nUsername: " << account << endl;
                std::cout << "UID: 84" << uid << endl;
            }
            // Back to main menu prompt
            std::cout << "\nPress ESC to return to the main menu...";
            int key;
            do { key = _getch(); } while (key != 27);
            system("cls");
            break;
        }
        case 6: {
            std::cout << "====== Settings Section ======" << endl;
            std::cout << "\n1. Change name\n2. Delete account" << endl;
            std::cout << "\nEnter choice (1-2): ";
            cin >> settings_menu;
            if (settings_menu == 1){
                std::cout << "\nEnter new in-game name: ";
                cin >> new_name;
                ingame_name = new_name;
                std::cout << "\nIn-game name changed successfully to " << ingame_name << "!" << endl;
            } else {
                std::cout << "\nAccount deleted. Exiting game..." << endl;
                exit(0); // Exit the program immediately
            }
            std::cout << "\nPress ESC to return to the main menu...";
            int key;
            do { key = _getch(); } while (key != 27);
            system("cls");
            break;
        }
        case 7:
            // Logout/exit menu and return to caller
            return;
        default: 
            std::cout << "Option not implemented yet." << endl;
            std::cout << "\nPress ESC to continue...";
            int key2;
            do { key2 = _getch(); } while (key2 != 27);
            system("cls");
            break;
        }
    }
}
int main() { 
    string password; 
    string account; 
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
                
        do{
            std::cout << "\nCreate password: ";
            cin >> password;
            std::cout << "\nConfirm password: ";
            cin >> confirm_Pass;

            /*If password does not match the confirmed password*/
            if(password != confirm_Pass){
                std::cout << "\nPassword does not match.";
                std::cout << endl;
            }
            /*If password does match the confirmed password*/
            else{
                string enteredUsername; 
                string enteredPassword;
                char ch;
                password = confirm_Pass; // Store the confirmed password
                
                system("cls");

                do{ // Log in loop
                    std::cout << "====== Log In ======" << endl;
                    std::cout << "\nEnter username: ";
                    cin >> enteredUsername;

                    enteredPassword = "";  // Clear the password string for each attempt
                    std::cout << "\nEnter password: ";
                    while (true) {
                        ch = _getch();  // get character without showing it on screen

                        // If ENTER is pressed, break the loop
                        if (ch == '\r') {  
                            std::cout << endl;
                            break;
                        }

                        // If BACKSPACE is pressed and password is not empty
                        else if (ch == '\b') {
                            if (!enteredPassword.empty()) {
                                enteredPassword.pop_back();   // remove last char from string
                                std::cout << "\b \b";       // move cursor back, overwrite with space, move back again
                            }
                        }

                        // Otherwise, add the character to password
                        else {
                            enteredPassword += ch;
                            std::cout << "*";
                        }
                    }

                    std::cout << "\nSign in failed. Please check your credentials." << endl;
                            
                } while (enteredUsername != account || enteredPassword != password);
                    
                std::cout << "\nSign in successful!" << endl;

                system("cls");

            }
        } while (password != confirm_Pass);

        mainMenu(account);

        
    }
    else if (choice == 2){
        std::cout << "Exiting..." << endl;
        return 0;
    }
    else{
        std::cout << "Invalid choice" << endl;
        return 1;
    }
    std::cout << "\nPress Enter to exit...";
    cin.ignore();  // Clear the input buffer
    cin.get();     // Wait for user to press Enter
    return 0;
}
