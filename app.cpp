#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>
#include <random>
#include <limits>

using std::string;
using std::endl;
using std::cin;

void mainMenu(string& account){
    int main_menu;
    string ingame_name;

    //UID Generator
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> dis(1000000, 9999999);
    int uid = dis(gen);

    //In-game name (asked once when entering the menu)
    std::cout << "====== Welcome to Wish Emulator ======" << endl;
    std::cout << "\nWelcome to Wish Emulator! What do you want to be called? ";
    cin >> ingame_name;
    system("cls");

    // Loop the menu so user can go to sections and come back
    while (true) {
        std::cout << "1. Play\n2. Wish\n3. Check Inventory\n4. Shop\n6. Profile\n7. Settings\n8. Logout/Exit" << endl;
        std::cout << "\nEnter choice (1-8): ";
        cin >> main_menu;

        system("cls");

        switch (main_menu){
        case 6: {
            std::cout << "====== Profile Section ======" << endl;
            std::cout << "\nHello, " << ingame_name << "!" << endl;
            std::cout << "\n---------------------" << endl;
            std::cout << "\nUsername: " << account << endl;
            std::cout << "UID: 84" << uid << endl;
            std::cout << "\nPress ESC to return to the main menu...";
            // Wait for ESC (ASCII 27) using _getch()
            int key;
            do { key = _getch(); } while (key != 27);
            system("cls");
            break;
        }
        case 8:
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
