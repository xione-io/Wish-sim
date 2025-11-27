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

void escKey(){
    std::cout << "\nPress ESC to continue...";
    while (_getch() != 27);
    system("cls");
}

void buyTickets(int& tickets, int& gems){
    int ticket_quantity;
    std::cout << "How many tickets do you want to buy? ";
    cin >> ticket_quantity;

    if (ticket_quantity <= 0){ //invalid input check for quantity
        std::cout << "Invalid amount.\n";
        return;
    }

    int ticket_value = ticket_quantity * 160;

    if (gems < ticket_value){ //check if user has enough gems
        std::cout << "You do not have enough Primo Gems.\n";
        return;
    }

    gems -= ticket_value;
    tickets += ticket_quantity;

    std::cout << "Successfully purchased " << ticket_quantity << " ticket(s)!\n";
    std::cout << "Remaining Primo Gems: " << gems << "\n";
    std::cout << "Total Tickets: " << tickets << "\n";
}

void shopItems(std::vector<bool>& owned, std::vector<int>& price, int& gems, int& tickets) {

    std::vector<string> gamepass = {
        "VIP - 500 gems",
        "2x Multiplier - 300 gems",
        "50% Luck Boost - 200 gems",
        "Bag capacity +25 - 150 gems",
        "Bag capacity +50 - 250 gems",
        "Companion equip slot +2 - 400 gems"
    };

    int shop_choice = 0; 
    int item_choice = 0;

    std::cout << "====== Shop ======\n";
    std::cout << "1. Exchange tickets\n2. Gamepass\n";
    std::cout << "\nEnter choice: ";
    cin >> shop_choice;

    system("cls");

    if (shop_choice == 2) {
        std::cout << "=== Gamepass Shop ===\n";

        for (int i = 0; i < gamepass.size(); i++){
            std::cout << i + 1 << ". " << gamepass[i];

            if (owned[i] == true)
                std::cout << " (OWNED)";

            std::cout << "\n";
        }

        std::cout << "\nSelect item (1-6): ";
        cin >> item_choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice.\n";

            system("cls");

            return;
        }
        
        if (item_choice < 1 || item_choice > 6) {
            std::cout << "Invalid choice.\n";
           
            system("cls");

            return;
        } else {
            int index = item_choice - 1; //index identifier

            if (owned[index]) {
                std::cout << "You already own this item!\n";
            } else if (gems < price[index]) {
                std::cout << "You do not have enough gems to purchase this item.\n";
            } else {
                owned[index] = true;
                std::cout << "Successfully purchased: " << gamepass[index] << "\n";
                gems -= price[index];
                std::cout << "Remaining Primo Gems: " << gems << "\n";
            }
        }
    } else if (shop_choice == 1) {
        buyTickets(tickets, gems);
    } else {
        std::cout << "Invalid choice.\n";
    }

    escKey();
    return;
}

//Minesweeper VARIABLES AND FUNCTIONS
const int SIZE = 5;     // grid size
const int MINES = 5;    // number of mines

struct Cell {
    bool isMine = false;
    bool revealed = false;
    int nearbyMines = 0;
};

std::vector<std::vector<Cell>> board(SIZE, std::vector<Cell>(SIZE));

// Function to check if a position is inside the grid
bool inBounds(int r, int c) {
    return (r >= 0 && r < SIZE && c >= 0 && c < SIZE);
}

// Place mines randomly
void placeMines() {
    int placed = 0;
    while (placed < MINES) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (!board[r][c].isMine) {
            board[r][c].isMine = true;
            placed++;
        }
    }
}

// Calculate numbers (nearby mines)
void calculateNumbers() {
    int dr[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};
    
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c].isMine) continue;
            int count = 0;
            for (int k = 0; k < 8; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (inBounds(nr,nc) && board[nr][nc].isMine) count++;
            }
            board[r][c].nearbyMines = count;
        }
    }
}

// Print board (hidden vs revealed)
void printBoard(bool revealAll = false) {
    std::cout << "   ";
    for (int c = 0; c < SIZE; c++) std::cout << c << " ";
    std::cout << "\n";
    
    for (int r = 0; r < SIZE; r++) {
        std::cout << r << " |";
        for (int c = 0; c < SIZE; c++) {
            if (revealAll || board[r][c].revealed) {
                if (board[r][c].isMine) std::cout << "* ";
                else std::cout << board[r][c].nearbyMines << " ";
            } else {
                std::cout << "? ";
            }
        }
        std::cout << "\n";
    }
}

// Reveal cell (basic, no flood-fill for zeros yet)
bool reveal(int r, int c) {
    if (!inBounds(r,c) || board[r][c].revealed) return true;
    board[r][c].revealed = true;
    if (board[r][c].isMine) return false;
    return true;
}

// Check win
bool checkWin() {
    int revealedCount = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c].revealed) revealedCount++;
        }
    }
    return (revealedCount == SIZE*SIZE - MINES);
}

// Resets if player wants to play again
void resetBoard() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            board[r][c].isMine = false;
            board[r][c].revealed = false;
            board[r][c].nearbyMines = 0;
        }
    }
}

// MATH mini game time limit functions
void restoreEnergy(int &energy, time_t &lastRestore) {
    time_t now = time(0);
    int secondsPassed = now - lastRestore;

    while (secondsPassed >= 180 && energy < 5) {
        energy++;
        lastRestore += 180;
        secondsPassed -= 180;
        
        std::cout << "\n+1 Energy Restored!" << std::endl;
    }
}

struct Companion { //it's holding properties for a data/s, without typing it again and again
    string name;
    string star;
    bool owned_companion;
};

Companion wishCompanion(std::mt19937& t1,
                        int& pity3, int& pity4, int& pity5, int& pity6)
{
    std::vector<Companion> companions = {
        // 3 Star
        {"Macky", "3 Star", false}, {"Brian", "3 Star", false},
        {"Lemuel", "3 Star", false}, {"Jiehan", "3 Star", false},
        {"Gus", "3 Star", false}, {"Roland", "3 Star", false},
        {"Nathan", "3 Star", false}, {"Arbe", "3 Star", false},

        // 4 Star
        {"Kirk", "4 Star", false}, {"Dae Ho", "4 Star", false},
        {"Fern", "4 Star", false}, {"Jett", "4 Star", false},
        {"Frieren", "4 Star", false}, {"Gojo", "4 Star", false},
        {"Karina", "4 Star", false}, {"Speed", "4 Star", false},

        // 5 Star
        {"Jinx", "5 Star", false}, {"Justine", "5 Star", false},
        {"Christine", "5 Star", false}, {"Diosylle", "5 Star", false},
        {"Alpha", "5 Star", false},

        // 6 Star
        {"Ma'am Karen", "6 Star", false}, {"Ma'am Rofa", "6 Star", false}
    };

    std::uniform_int_distribution<int> dist(1, 10000);
    int roll = dist(t1);

    //RANGE:
    //3 star (1-8869) (88.69%)
    //4 star (8870-9869) (10%)
    //5 star (9870-9980) (1.11%)
    //6 star (9981-10000)(0.2%)
    
    //force/max/guarantee pity in each rarity
    if (pity6 >= 900) //500 * 2 - 10%
        roll = 9981;   //6★

    else if (pity5 >= 162) //90 * 2 - 10%
        roll = 9870;    //5★

    else if (pity4 >= 18) //10 * 2 - 10%
        roll = 8870;    //4★

    // Determine rarity
    std::string rarity;
    if (roll <= 8869) rarity = "3 Star";
    else if (roll <= 9869) rarity = "4 Star";
    else if (roll <= 9980) rarity = "5 Star";
    else rarity = "6 Star";

    // +1 chance each pull [(1/10) > (2/10)]
    pity3++;
    pity4++;
    pity5++;
    pity6++;

    // Reset pity only for the rarity obtained
    if (rarity == "3 Star") pity3 = 0;
    if (rarity == "4 Star") pity4 = 0;
    if (rarity == "5 Star") pity5 = 0;
    if (rarity == "6 Star") pity6 = 0;

    // give random companion based on rarity
    if (rarity == "3 Star")
        return companions[0 + rand() % 8];

    if (rarity == "4 Star")
        return companions[8 + rand() % 8];

    if (rarity == "5 Star")
        return companions[16 + rand() % 5];

    return companions[21 + rand() % 2]; // 6 Star
}

void companionList() {
    // This function is implemented to show the list of companions
    std::vector<string> companions_three = {
        "Macky - 3 Star",
        "Brian - 3 Star",
        "Lemuel - 3 Star",
        "Jiehan - 3 Star",
        "Gus - 3 Star",
        "Roland - 3 Star",
        "Nathan - 3 Star",
        "Arbe - 3 Star"
    };
    std::vector<string> companions_four = {
        "Kirk - 4 Star",
        "Dae Ho - 4 Star",
        "Fern - 4 Star",
        "Jett - 4 Star",
        "Frieren - 4 Star",
        "Gojo - 4 Star",
        "Karina - 4 Star",
        "Speed - 4 Star"
    };
    std::vector<string> companions_five = {
        "Jinx - 5 Star",
        "Justine - 5 Star",
        "Christine - 5 Star",
        "Diosylle - 5 Star",
        "Alpha - 5 Star"
    };
    std::vector<string> companions_six = {
        "Ma'am Karen - 6 Star",
        "Ma'am Rofa - 6 Star"
    };

    std::cout << "====== Companion List ======\n";

    std::cout << "\n--- 6 Star Companions ---\n";
    for (const auto& companion : companions_six) {
        std::cout << companion << std::endl;
    }

    std::cout << "\n--- 5 Star Companions ---\n";
    for (const auto& companion : companions_five) {
        std::cout << companion << std::endl;
    }

    std::cout << "\n--- 4 Star Companions ---\n";
    for (const auto& companion : companions_four) {
        std::cout << companion << std::endl;
    }

    std::cout << "\n--- 3 Star Companions ---\n";
    for (const auto& companion : companions_three) {
        std::cout << companion << std::endl;
    }
}

void mainMenu(string& account) {
    // Main variables
    int main_menu;
    int gems = 99999; // Primo gems starts at 0
    string ingame_name;
    string new_name;
    int settings_menu = 0;

    //wish variables aside from gems
    int tickets = 0;
    std::srand(time(0));
    std::mt19937 t1(time(0));
    //pity counters
    int pull_3star = 0;
    int pull_4star = 0;
    int pull_5star = 0;
    int pull_6star = 0;

    //shop checker if items are owned or not
    std::vector<bool> owned(6, false);
    std::vector<int> price = {500, 300, 200, 150, 250, 400};

    // UID Generator
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> dis_uid(1000000, 9999999);
    int uid = dis_uid(gen);

    // Random generator for shooter
    std::random_device shoot;
    std::mt19937 lol(shoot());

    // Inventory
    int inventory = 99999; // Starting inventory space
    int current_inventory = 0;
    std::vector<Companion> inventory_list;
    std::vector<bool> Companions_owned(23, false); // Placeholder for owned companions

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
        case 1: { //play option
            int play_menu;
            std::cout << "======= Play Section =======" << endl;
            std::cout << "\"In order to acquire primo gems, you must complete the challenges\"" << endl;
            std::cout << "\nPlease select a challenge to play:" << endl;
            std::cout << "\n1. Minesweeper\n2. Math quiz\n3. Dodge this!\n4. Back" << endl;
            std::cout << "\nEnter choice (1-4): ";
            cin >> play_menu;
            system("cls");
            
            switch (play_menu) {
                case 1: {
                    char choice;

                    do {
                        srand(time(0));
                        resetBoard();
                        placeMines();
                        calculateNumbers();
                        bool alive = true;
                        
                        std::cout << "====== MINESWEEPER ======\n";
                        std::cout << "Uncover all safe spots without hitting a mine to win Primo Gems!\n";
                        std::cout << "You will earn 30 Primo Gems upon winning the game.";
                        std::cout << "\n\n\n";
                        escKey();
                        while (alive) {
                            printBoard();
                            int r, c;
                            std::cout << "Enter row and column (e.g. 2 3): ";
                            cin >> r >> c;

                            alive = reveal(r, c);
                            std::cout << "\n";
                            if (!alive) {
                                std::cout << "BOOM! You hit a mine.\n";
                                printBoard(true);
                                break;
                            }

                            if (checkWin()) {
                                std::cout << "Congratulations! You cleared the board!\n";
                                printBoard(true);

                                std::cout << "\nYou earned 30 Primo Gems for clearing Minesweeper!\n";
                                gems += 30;
                                std::cout << "Total Primo Gems: " << gems << "\n";
                                break;
                            }
                        }

                        std::cout << "\nPlay again? (Y/N): ";
                        cin >> choice;
                        choice = toupper(choice);
                        system("cls");
                    } while (choice == 'Y');
                    
                    escKey();
                    break;
                }
                
                //MATHHHHHH mini game
                case 2: {
                    srand(time(0));
    
                    int dif;
                    int energy = 5; 
                    bool quit = false;
                    time_t lastRestore = time (0);

                    std::cout << "\n==================================";
                    std::cout << "\n   WELCOME TO MATH QUIZ!!! (≧∇≦)  ";
                    std::cout << "\n==================================";
                    std::cout << "\n\nINSTRUCTION:" << endl;
                    std::cout << "-Enter the correct number and gain primogems" << endl;
                    std::cout << "-You have only 5 energies so answer carefully" << endl;
                    std::cout << "-Energy will decrease whether you win or lose" << endl;
                    std::cout << "-Every 3 minutes, 1 energy will restore" << endl;
                    std::cout << "\nPlease select a difficulty to start:" << endl;
                    std::cout << "1. Easy" << endl;
                    std::cout << "2. Medium" << endl;
                    std::cout << "3. Hard" << endl;

                    do {

                        restoreEnergy (energy, lastRestore);
                        std::cout << "\nCurrent Energy: " << energy;

                        if (energy <= 0) {
                            std::cout << "\nYou Have 0 Energy left, Please try again later!" << endl;
                            break;
                        } else {

        
                        std::cout << "\nEnter Difficulty: ";
                        std::cin >> dif;
                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore();
                            continue;
                        }

                        system ("cls");

                        switch (dif) {
                        
                            //EASY MODE
                        
                            case 1: {

                            int shape = rand() % 3;
                            double a, b, r, ans, uans;
                            char choice;
                            
                            std::cout << "========================";
                            std::cout << "\n       EASY MODE";
                            std::cout << "\n========================";

                            //RECTANGLE

                            if (shape == 0) {

                                a = rand() % 100 + 1;
                                b = rand() % 100 + 1;
                                ans = a * b;
                                
                                std::cout << "\n[EASY] Find the Area of a Rectangle!" << endl;
                                std::cout << "Length: " << a << endl;
                                std::cout << "Width: " << b << endl;
                                std::cout << "\nYour Answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (uans == ans) {
                                    std::cout << "\nCorrect! You've Gained 10 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 10;
                                    //PRIMOGEMS + 10
                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << ans << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                }
                                break;
                            }

                            //TRIANGLE
                            
                            else if (shape == 1) {
                                a = rand() % 100 + 1;
                                b = rand() % 100 + 1;
                                ans = 0.5 * a * b;

                                std::cout << "\n[EASY] Find the Area of a Triangle!" << endl;
                                std::cout << "Base: " << a << endl;
                                std::cout << "Height: " << b << endl;
                                std::cout << "\nYour Answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (uans == ans) {
                                    std::cout << "\nCorrect! You've Gained 10 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 10;
                                    //PRIMOGEMS + 10
                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << ans << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                }
                                break;
                            }

                            //CIRCLE

                            else if (shape == 2) {
                                r = rand () % 50 + 1;
                                ans = 3.14 * r * r;

                                std::cout << "\n[EASY] Find the Area of a Circle!" << endl;
                                std::cout << "Radius: " << r << endl;
                                std::cout << "Assuming that PI = 3.14"<< endl;
                                std::cout << "\nYour Answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (std::fabs(uans - ans) < 0.01) {
                                    std::cout << "\nCorrect! You've Gained 10 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 10;
                                    //PRIMOGEMS + 10
                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << ans << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                }
                                break;
                            }
                            break;
                        }

                        //MEDIUM MODE

                        case 2: {
                            int type = rand() % 2;
                            int a, b, c, x, y, z, ans, uans;
                            char choice;
                            
                            std::cout << "========================";
                            std::cout << "\n      MEDIUM MODE";
                            std::cout << "\n========================";

                            //FINDING THE VALUE OF X

                            if (type == 0) {
                                a = rand() % 9 + 1;
                                b = rand() % 20 + 1;
                                x = rand() % 10 + 1;
                                c = a * x + b;

                                std::cout << "\n[MEDIUM] Solve for x: " << endl;
                                std::cout << "\n" << a << "x + " << b << " = " << c << endl;
                                std::cout << "\nYour answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (uans == x) {
                                    std::cout << "\nCorrect! You've Gained 20 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 20;
                                    //PRIMOGEMS + 20
                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << x << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                }
                                break;
                            }

                            else if (type == 1) {
                                x = rand() % 9 + 1;
                                y = rand() % 9 + 1;
                                z = rand() % 9 + 1;
                                ans = x * x + 2 * y - z;

                                std::cout << "\n[MEDIUM] Evaluate the Following: " << endl;
                                std::cout << "\n" << "x^2 + 2y - z" << endl;
                                std::cout << "\n" << "If: \nx = " << x << "\ny = " << y << "\nz = " << z << endl;
                                std::cout << "\nYour answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (uans == ans) {
                                    std::cout << "\nCorrect! You've Gained 20 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 20;
                                    //PRIMOGEMS + 20
                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << ans << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                }
                                break;
                            }
                            break;
                        }

                        //HARD MODE
                        
                        case 3: {
                            int type = rand() % 2;
                            double uans, ans;
                            char choice;

                            std::cout << "========================";
                            std::cout << "\n       HARD MODE";
                            std::cout << "\n========================";

                            if (type == 0) {
                                int a = rand() % 20 + 5;
                                int b = rand() % 20 + 5;
                                double c = sqrt(a*a + b*b);

                                std::cout << "\n[HARD] Find the Hypotenuse: " << endl;
                                std::cout << "Leg A = " << a << endl;
                                std::cout << "Leg B = " << b << endl;
                                std::cout << "\nYour Answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (fabs(uans - c) < 0.01) {
                                    std::cout << "\nCorrect! You've Gained 30 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 30;
                                    //PRIMOGEMS + 30

                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << c << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                }
                                break;
                            }

                            else if (type == 1) {
                                int base = rand() % 5 + 2;
                                int exp = rand() % 4 + 2;
                                double ans = pow(base, exp);

                                std::cout << "\n[HARD] Solve the Exponent:" << endl;
                                std::cout << base << "^" << exp << " = ?" << endl;
                                std::cout << "Your Answer: ";
                                std::cin >> uans;

                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(99999, '\n');
                                    uans = -99999999;
                                }

                                energy--;

                                if (uans == ans) {
                                    std::cout << "\nCorrect! You've Gained 30 Primogems" << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                    gems+= 30;
                                    //PRIMOGEMS + 30
                                } else {
                                    std::cout << "\nIncorrect! The correct answer is " << ans << endl;
                                    std::cout << "Current Energy: " << energy << endl;
                                }
                                std::cout << "\nContinue? (Y/n): ";
                                std::cin >> choice;

                                if (choice == 'Y' || choice == 'y') {
                                    system ("cls");

                                } else {
                                    std::cout << "Thank You for Playing!";
                                    quit = true;
                                    escKey();
                                    break;
                                    
                                }
                                break;
                            }
                            break;
                        }
                        default: {
                            std::cout << "\nInvalid Choice!" << endl;
                                 }
                            }
                        }
                    } while (!quit);
                    break;
                }


                case 3: {
                    char choice;
                    int wave = 0;
                    int earnedGems = 0;
                    bool alive;

                    do {
                        wave = 1;
                        earnedGems = 0;
                        alive = true;

                        std::cout << "====== DODGE THIS! ======\n";
                        std::cout << "Avoid enemy attacks from the shooter and survive each wave to earn primo gems!\n";
                        std::cout << "Each wave you survive rewards you with 10 primo gems.";
                        std::cout << "\n\n\n";
                        escKey();

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
                    escKey();
                    break;
                }
                default:
                    break; 
                }
            break; //case 1 break
        }

        case 2: { //wish option
            int choice = 0;

            std::cout << "====== Wish Section ======" << endl;
            std::cout << "\nWelcome to Wish! In here, you can use your Primo Gems and Tickets to obtain companions that will aid you in your adventures.";
            std::cout << "\nThere are four types of companions you can obtain:\n- 3 Star (Common)\n- 4 Star (Epic)\n- 5 Star (Legendary)\n- 6 Star (Secret)";
            std::cout << "\nEach wish costs 160 Primo Gems or 1 Ticket.";
            std::cout << "\n\n\n";
            escKey();

            std::cout << "====== Menu ======";
            std::cout << "\n1. Wish\n2. Wish History\n3. Companion List\n4. Back\n";
            std::cout << "\nEnter choice (1-4): ";
            cin >> choice;
            if (choice == 1){
                char choice;
                
                //number of pulls a player wants to do
                int num_pulls = 0;

                do {
                    std::cout << "\nYou have " << gems << " Primo Gems and " << tickets << " Ticket(s).\n";
                    std::cout << "How many wishes do you want to make? ";
                    cin >> num_pulls;

                    //input validation
                    if (num_pulls <= 0) {
                        std::cout << "Invalid number of wishes.\n";
                        system("cls");
                        continue;
                    }
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input.\n";
                        system("cls");
                        continue;
                    }


                    //check if user has enough gems/tickets
                    if (tickets >= num_pulls) {
                        int total_cost = num_pulls * 160; //amount of gems used
                        tickets -= num_pulls;
                        gems -= total_cost;
                        std::cout << "\nUsing " << num_pulls << " Ticket(s) for your wishes!\n";
                    } else if (tickets < num_pulls) {
                        std::cout << "\nNot enough tickets. Do you want to use Primo Gems for the remaining wishes? (Y/N): ";
                        char gem_choice;
                        cin >> gem_choice;
                        gem_choice = toupper(gem_choice);
                        if (gem_choice == 'Y') {
                            std::cout << "\n\n";
                            buyTickets(tickets, gems);
                            std::cout << "\nYou have " << tickets << " Ticket(s) remaining.\n";
                        } else {
                            std::cout << "Cancelling wish...\n";
                            system("cls");
                            continue;
                        }
                    }
                    else {
                        std::cout << "Not enough Primo Gems or Tickets for " << num_pulls << " wishes.\n";
                        system("cls");
                        continue;
                    }
                    //perform the pulls
                    for (int i = 0; i < num_pulls; i++) {
                        Companion pulled = wishCompanion(t1, pull_3star, pull_4star, pull_5star, pull_6star);
                        
                        std::cout << "You pulled: " << pulled.name << " [" << pulled.star << "]\n";

                        // Reset pity counters if you got that rarity
                        if (pulled.star == "3 Star") pull_3star = 0;
                        if (pulled.star == "4 Star") pull_4star = 0;
                        if (pulled.star == "5 Star") pull_5star = 0;
                        if (pulled.star == "6 Star") pull_6star = 0;

                        // Increment pity counters for next pull
                        pull_3star++;
                        pull_4star++;
                        pull_5star++;
                        pull_6star++;

                        if (current_inventory < inventory) {
                            current_inventory++;
                            pulled.owned_companion = true;
                            inventory_list.push_back(pulled);   
                            std::cout << "Added to inventory. Current inventory: " << current_inventory << " / " << inventory << "\n";
                        } else {
                            std::cout << "Inventory full! Cannot add " << pulled.name << " to inventory.\n";
                        }
                    }
                    std::cout << "\nDo you want to wish again? (Y/N): ";
                    cin >> choice;
                    choice = toupper(choice);
                } while (choice == 'Y');
                
            }
            
            else if (choice == 3) {
                companionList();
            }
            
            escKey();
            break;
        }
        case 3: //check inventory option
            std::cout << "====== Inventory Section ======" << endl;
            std::cout << "Inventory space: " << current_inventory << " / " << inventory << endl;

            if (inventory_list.empty()) {
                std::cout << "Your inventory is empty.\n";
            } else {
                for (size_t i = 0; i < inventory_list.size(); ++i) {
                    const Companion& comp = inventory_list[i];
                    std::cout << (i + 1) << ". " << comp.name << " [" << comp.star << "]" << endl;
                }
            }

            escKey();
            break;
        case 4: //shop option
            shopItems(owned, price, gems, tickets);
            break;
        
        case 5: //profile option
            std::cout << "====== Profile Section ======" << endl;
            std::cout << "\nHello, " << ingame_name << "!" << endl;
            std::cout << "\n---------------------" << endl;
            std::cout << "\nUsername: " << account << endl;
            std::cout << "UID: 84" << uid << endl;
            escKey();
            break;

        case 6: //settings option
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
            escKey();
            break;

        case 7: //exit option
            std::cout << "Logging out..." << endl;
            return;

        default:
            std::cout << "Invalid choice." << endl;
            escKey();
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
                        std::cout << "\n";

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
