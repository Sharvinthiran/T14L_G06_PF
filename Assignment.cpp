// ******************************************************************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T14L
// Names: KIRTANAH A/P MANALAN | SHARVINTHIRAN A/L RAJAKUMAR | LAKULESHH LEVIS A/L A.SELVARAJAH
// IDs:       1211102813       |           1211103808        |            1211103794
// Emails: 1211102813@student.mmu.edu.my | 1211103808@student.mmu.edu.my | 1211103794@student.mmu.edu.my
// Phones:   011-2627 8517     |          017-572 1595       |           017-291 0250
// *******************************************************************************************************
#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>
#include <math.h>
#include <algorithm>
using namespace std;
// Using struct to carry multiple variables.
// Also use to make multiple zombies to make new input, (make sure attributes are randomized)
struct Zombies
{
    string identifier;
    string number;
    int xcor, ycor;
    int life;
    int attack;
    int range;
};

void displayHelp()
{
    cout << "Available Commands:\n"
         << "- 'up': Move up\n"
         << "- 'down': Move down\n"
         << "- 'left': Move left\n"
         << "- 'right': Move right\n"
         << "- 'A': Alien\n"
         << "- 'Z': Zombie\n"
         << "- '^': Changes Alien's direction of movement to up\n"
         << "- 'v': Changes Alien's direction of movement to down\n"
         << "- '<': Changes Alien's direction of movement to left\n"
         << "- '>': Changes Alien's direction of movement to right\n"
         << "- 'h': Adds 20 life to alien\n"
         << "- 'p' or 'Pod': Instantly inflicts 10 damage to Zombie when hit by Alien\n"
         << "- 'r' or 'Rock': Hides a game object (except Rock and Trail) beneath it\n"
         << "- 't' or 'Terror': Increases zombie HP by 5 every time Alien picks it up\n"
         << "- 'Trail' or '.': Left by Alien when it moves\n"
         << "- 'Empty' or 'Space': Just an empty space on the board\n"
         << "- 'Quit': Quit the game while still in play\n";

    return;
}

int mainmenu()
{
    int startoptions;
    cout << "/###################################################/" << endl;
    cout << "/                                                   /" << endl;
    cout << "/        W E L C O M E  T O  W O R L D  W A R       /" << endl;
    cout << "/                                                   /" << endl;
    cout << "/        A L I E N S  V         V  Z O M B I E S    /" << endl;
    cout << "/                      V       V                    /" << endl;
    cout << "/                       V     V                     /" << endl;
    cout << "/                        V   V                      /" << endl;
    cout << "/                          V                        /" << endl;
    cout << "/                    E D I T I O N                  /" << endl;
    cout << "/                                                   /" << endl;
    cout << "/###################################################/" << endl;
    cout << "/                                                   /" << endl;
    cout << "/     |Main Menu|                                   /" << endl;
    cout << "/                                                   /" << endl;
    cout << "/     1.Start Game                                  /" << endl;
    cout << "/     2.Help                                        /" << endl;
    cout << "/     3.Quit                                        /" << endl;
    cout << "/                                                   /" << endl;
    cout << "/                                                   /" << endl;
    cout << "/###################################################/" << endl;

    while (true)
    {
        cout << "Your option -> ";
        int optioninput;
        cin >> optioninput;
        // test

        // this is when the input stream enters error state
        if (cin.fail())
        {
            cout << "FAILED TO START GAME !\n";
            continue;
        }

        if (optioninput == 1)
        {
            system("CLS");
            return optioninput;
        }
        else if (optioninput == 2)
        {
            displayHelp(); // call function to display help
            continue;
        }
        else if (optioninput == 3)
        {
            char confirm;

            cout << "Are you sure you want to quit the game? (Y/N)" << endl;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                cout << "Thanks for playing!" << endl;
                exit(0);
            }
            else
            {
                continue;
            }
        }
        else
        {
            cout << "ERROR !\n";
            continue;
        }
    }
}

int AlienRow, AlienColumn;

void displayboard(vector<vector<string>> &gameboard)
{
    int row = gameboard.size();
    int column = gameboard[0].size();

    cout << "+";
    for (int j = 0; j < column; ++j)
    {
        cout << "---+";
    }
    cout << endl;

    for (int i = 0; i < row; i++)
    {
        cout << "|";
        for (int j = 0; j < column; j++)
        {
            cout << " " << gameboard[i][j] << " |";
        }
        cout << endl;

        cout << "+";
        for (int j = 0; j < column; ++j)
        {
            cout << "---+";
        }
        cout << endl;
    }
}

// gameboard creation
vector<vector<string>> gameboard()
{

    char objects[] = {'^', 'v', '<', '>', 'h', 'r', 'p', 't', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int numObjects = 16;
    int rows, columns;

    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> columns;

    vector<vector<string>> boardgame(rows, vector<string>(columns));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            // set the coordinates of each box format (x,y)
            boardgame[i][j] = to_string(i) + "," + to_string(j);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            boardgame[i][j] = objects[rand() % numObjects];
        }
    }

    return boardgame;
}

vector<Zombies> spawnZombie(vector<vector<string>> &boardgame)
{

    int row, column, amount;
    row = boardgame.size();
    column = boardgame[0].size();

    vector<vector<string>> nocoordinates(row, vector<string>(column));

    cout << "How many zombies do you want?";
    cin >> amount;

    vector<Zombies> zombie;
    zombie.resize(amount);

    // amount == 9
    for (int i = 0; i < zombie.size(); i++)
    {
        zombie[i].identifier = to_string(i + 1);
        zombie[i].life = rand() % 100 + 50;
        zombie[i].attack = rand() % 30 + 10;
        zombie[i].range = rand() % 5 + 3;
    }

    for (int i = 0; i < zombie.size(); i++)
    {
        int xaxis = rand() % row;
        int yaxis = rand() % column;

        if (!(nocoordinates[xaxis][yaxis] == "no"))
        {
            zombie[i].xcor = xaxis;
            zombie[i].ycor = yaxis;
            boardgame[xaxis][yaxis] = zombie[i].identifier;
        }
        else
        {
            i--;
        }
        nocoordinates[xaxis][yaxis] = "no";
    }
    return zombie;
}

bool PowerupCheck(vector<vector<string>> &boardgame, int ArrowRow, int ArrowColumn, int &life, int &maxhealth, vector<Zombies> &zombie)
{

    int zsize = zombie.size();
    // this is the code to execute when there is an object in the game board. it will return true
    if (boardgame[ArrowRow][ArrowColumn] == "^" || boardgame[ArrowRow][ArrowColumn] == "v" || boardgame[ArrowRow][ArrowColumn] == ">" || boardgame[ArrowRow][ArrowColumn] == "<" || boardgame[ArrowRow][ArrowColumn] == "r")
    {
        return true;
    }
    else if (boardgame[ArrowRow][ArrowColumn] == "h")
    {
        if (life < maxhealth)
        {
            life = life + 20;
        }
    }
    else if (boardgame[ArrowRow][ArrowColumn] == "p")
    {
        for (int i = 0; i < zsize; i++)
        {
            zombie[i].life = zombie[i].life - 10;
        }
    }
    else if (boardgame[ArrowRow][ArrowColumn] == "t")
    {
        for (int i = 0; i < zsize; i++)
        {
            zombie[i].life = zombie[i].life + 5;
        }
    }
    // else it will return false when there is no object in the game board.
    else
    {
        return false;
    }

    // we use this function to check whether got object or not and use it in "if else if" statement
}

bool obstacle(vector<vector<string>> &boardgame, int ObstacleRow, int ObstacleColumn)
{
    if (boardgame[ObstacleRow][ObstacleColumn] == "r")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void trail(int row, int column, vector<vector<string>> &boardgame)
{
    char objects[] = {'^', 'v', '<', '>', 'h', 'r', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int numObjects = 15;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (boardgame[i][j] == ".")
            {
                boardgame[i][j] = objects[rand() % numObjects];
            }
        }
    }
}

string powerup(string &direction)
{
    if (direction == "^")
    {
        return "up";
    }
    else if (direction == "v")
    {
        return "down";
    }
    else if (direction == ">")
    {
        return "right";
    }
    else if (direction == "<")
    {
        return "left";
    }
    else
    {
        return "false";
    }
}

void MovementForZombie(vector<vector<string>> &board, vector<Zombies> &zombies)
{
    int zombienum = zombies.size();
    int prevx, prevy;

    for (int i = 0; i < zombienum; i++)
    {
        int randomnum[3] = {-1, 0, 1};

        prevx = zombies[i].xcor;
        prevy = zombies[i].ycor;
        int randomMove = rand() % 2;

        if (randomMove == 1)
        {
            int randomx = randomnum[rand() % 2];
            for (int j = 0; j < 4; j++)
            {
                if (board[abs(prevx + randomx)][abs(prevy)] == " ")
                {
                    zombies[i].xcor = abs(randomx + prevx);
                    board[zombies[i].xcor][zombies[i].ycor] = zombies[i].identifier;
                    board[prevx][prevy] = " ";
                    break;
                }
            }
        }
        else if (randomMove == 0)
        {
            int randomy = randomnum[rand() % 2];
            for (int j = 0; j < 4; j++)
            {

                if (board[abs(prevx)][abs(prevy + randomy)] == " ")
                {
                    zombies[i].ycor = abs(randomy + prevy);
                    board[zombies[i].xcor][zombies[i].ycor] = zombies[i].identifier;
                    board[prevx][prevy] = " ";
                    break;
                }
            }
        }
    }
}

void AttackForZombie(vector<vector<string>> &boardgame, vector<Zombies> &zombies, int &alienlife)
{
    int row, column, maximum, zombiecap;
    row = boardgame.size();
    column = boardgame[0].size();
    zombiecap = zombies.size();
    cout << endl;
    for (int i = 0; i < zombiecap; i++)
    {
        maximum = zombies[i].range;
        if ((zombies[i].xcor == AlienRow) || (zombies[i].ycor == AlienColumn))
        {
            if ((abs(zombies[i].xcor - AlienRow) < maximum) || (abs(zombies[i].ycor - AlienRow) < maximum))
            {
                cout << endl
                     << "The zombie" << zombies[i].number << " has damaged the alien for " << zombies[i].attack << " HP" << endl;
                Sleep(1000);
                alienlife = alienlife - zombies[i].attack;
            }
        }
    }
    cout << "Current Alien Life : " << alienlife << endl;
    Sleep(3000);
}

bool CheckingForZombie(vector<vector<string>> &board, vector<Zombies> &zombies, int currentrow, int currentcol, int &attack)
{
    int zombiecap = zombies.size();
    for (int i = 0; i < zombiecap; i++)
    {
        // if got zombie on the location it will minus the zombie's life  and return false
        if (board[zombies[i].xcor][zombies[i].ycor] == board[currentrow][currentcol])
        {
            cout << "ZOMBIE HAS BEEN FOUND!" << endl;
            zombies[i].life = zombies[i].life - attack;
            Sleep(1000);
            cout << "The zombie has received" << attack << " damage!" << endl;
            attack = 0;
            cout << "The game will resume in 3..." << endl;
            Sleep(3000);
            return false;
            break;
        }
    }
    return true;
}

void AlienAttack(vector<vector<string>> &board, vector<Zombies> &zombies, int &attack, int x, int y)
{
    vector<int> closestzombie;
    closestzombie.resize(zombies.size());
    for (int i = 0; i < zombies.size(); i++)
    {
        int distance = sqrt(pow((zombies[i].xcor - x), 2) + pow((zombies[i].ycor - y), 2));
        closestzombie[i] = distance;
    }
    auto LeastValue = min_element(closestzombie.begin(), closestzombie.end());
    int index = distance(closestzombie.begin(), LeastValue);
    zombies[index].life -= 20;
    cout << "The Zombie" << zombies[index].number + " receieved 20 damage!" << endl;

}

void alien(vector<vector<string>> &boardgame, vector<Zombies> &zombie)
{
    int row = boardgame.size();
    int column = boardgame[0].size();

    // vector<Zombies> zombie = zombies;

    int life = 350;
    int maxhealth = 400;
    int attack = 0;
    int AlienRow;
    int AlienColumn;
    string Alien = "A";

    if (row % 2 == 0)
    {
        AlienRow = row / 2 - 1;
    }
    else
    {
        AlienRow = row / 2;
    }
    if (column % 2 == 0)
    {
        AlienColumn = column / 2 - 1;
    }
    else
    {
        AlienColumn = column / 2;
    }
    system("CLS");
    boardgame[AlienRow][AlienColumn] = Alien;

    string powers, input;
    // this is our board
    while (true)
    {
        char objects[] = {'^', 'v', '<', '>', 'p', 'h', ' ', ' ', ' ', ' '};
        int numObjects = 10;
        system("CLS");
        displayboard(boardgame);

        cout << "Alien - > "
             << "Life: " << life << "  Attack: " << attack << endl;
        for (int i = 0; i < zombie.size(); i++)
        {
            cout << "Zombie " << i + 1 << ": ";
            cout << "Attack: " << zombie[i].attack;
            cout << " Life: " << zombie[i].life;
            cout << " Range: " << zombie[i].range << endl;
        }
        cout << "Enter direction (up,down,left,right,arrow,quit): ";

        // this is to check whether the upper box of alien ada powerup or not.
        // if got means it will automatically input the powerup, if not it will ask you input
        if (powerup(powers) == "false")
        {
            cin >> input;
        }
        else if (powerup(powers) != "false")
        {
            input = powerup(powers);
            // to empty the powers variable so that you can use it later for other directions
            powers = "nopowerup";
        }

        if (input == "up")
        {
            while (true)
            {

                string movem;
                cout << "Press M/m to continue" << endl;
                cin >> movem;
                // this is to check whether got any object or not. Not POWERUP but objects
                // if false it will just move the alien
                if (obstacle(boardgame, AlienRow - 1, AlienColumn) == true)
                {
                    boardgame[AlienRow - 1][AlienColumn] = objects[rand() % numObjects];
                    MovementForZombie(boardgame, zombie);
                    trail(row, column, boardgame);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (CheckingForZombie(boardgame, zombie, AlienRow - 1, AlienColumn, attack) == false)
                {
                    MovementForZombie(boardgame, zombie);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (PowerupCheck(boardgame, AlienRow - 1, AlienColumn, life, maxhealth, zombie) == false)
                {
                    if (movem == "M" || movem == "m")
                    {
                        if (AlienRow > 0)
                        {
                            boardgame[AlienRow][AlienColumn] = ".";
                            AlienRow--;
                            boardgame[AlienRow][AlienColumn] = Alien;
                        }
                    }
                }
                // if true it will set the power variable based on the box above alien
                // this is so that it will automatically set  the direction of the alien
                else if (PowerupCheck(boardgame, AlienRow - 1, AlienColumn, life, maxhealth, zombie) == true)
                {
                    powers = boardgame[AlienRow - 1][AlienColumn];
                    boardgame[AlienRow][AlienColumn] = ".";
                    AlienRow--;
                    attack = attack + 20;
                    boardgame[AlienRow][AlienColumn] = Alien;
                    trail(row, column, boardgame);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                boardgame[AlienRow][AlienColumn] = Alien;

                system("CLS");
                displayboard(boardgame);
                cout << "Alien - > "
                     << "Life: " << life << "  Attack: " << attack << endl;
                for (int i = 0; i < zombie.size(); i++)
                {
                    cout << "Zombie " << i + 1 << ": ";
                    cout << "Attack: " << zombie[i].attack;
                    cout << " Life: " << zombie[i].life;
                    cout << " Range: " << zombie[i].range << endl;
                }
                cout << "Enter direction (up,down,left,right): ";

                if (AlienRow < 1)
                {
                    trail(row, column, boardgame);
                    break;
                }
            }
        }
        else if (input == "down")
        {
            while (true)
            {
                string movem;
                cout << "Press M/m to continue" << endl;
                cin >> movem;
                if (obstacle(boardgame, AlienRow + 1, AlienColumn) == true)
                {
                    boardgame[AlienRow + 1][AlienColumn] = objects[rand() % numObjects];
                    MovementForZombie(boardgame, zombie);
                    trail(row, column, boardgame);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (CheckingForZombie(boardgame, zombie, AlienRow + 1, AlienColumn, attack) == false)
                {
                    MovementForZombie(boardgame, zombie);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (PowerupCheck(boardgame, AlienRow + 1, AlienColumn, life, maxhealth, zombie) == false)
                {
                    if (movem == "M" || movem == "m")
                    {
                        if (AlienRow < row - 1)
                        {
                            boardgame[AlienRow][AlienColumn] = ".";
                            AlienRow++;
                            boardgame[AlienRow][AlienColumn] = Alien;
                        }
                    }
                }
                // if true it will set the power variable based on the box above alien
                // this is so that it will automatically set  the direction of the alien
                else if (PowerupCheck(boardgame, AlienRow + 1, AlienColumn, life, maxhealth, zombie) == true)
                {
                    powers = boardgame[AlienRow + 1][AlienColumn];
                    boardgame[AlienRow][AlienColumn] = ".";
                    AlienRow++;
                    attack = attack + 20;
                    boardgame[AlienRow][AlienColumn] = Alien;
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                boardgame[AlienRow][AlienColumn] = Alien;

                system("CLS");
                displayboard(boardgame);
                cout << "Alien - > "
                     << "Life: " << life << "  Attack: " << attack << endl;
                for (int i = 0; i < zombie.size(); i++)
                {
                    cout << "Zombie " << i + 1 << ": ";
                    cout << "Attack: " << zombie[i].attack;
                    cout << " Life: " << zombie[i].life;
                    cout << " Range: " << zombie[i].range << endl;
                }
                cout << "Enter direction (up,down,left,right): ";
                if (AlienRow > row - 2)
                {
                    trail(row, column, boardgame);
                    break;
                }
            }
        }
        else if (input == "left")
        {
            while (true)
            {
                string movem;
                cout << "Press M/m to continue" << endl;
                cin >> movem;
                if (obstacle(boardgame, AlienRow, AlienColumn - 1) == true)
                {
                    boardgame[AlienRow][AlienColumn - 1] = objects[rand() % numObjects];
                    MovementForZombie(boardgame, zombie);
                    trail(row, column, boardgame);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (CheckingForZombie(boardgame, zombie, AlienRow, AlienColumn - 1, attack) == false)
                {
                    MovementForZombie(boardgame, zombie);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (PowerupCheck(boardgame, AlienRow, AlienColumn - 1, life, maxhealth, zombie) == false)
                {
                    if (movem == "M" || movem == "m")
                    {
                        if (AlienColumn > 0)
                        {
                            boardgame[AlienRow][AlienColumn] = ".";
                            AlienColumn--;
                            boardgame[AlienRow][AlienColumn] = Alien;
                        }
                    }
                }
                // if true it will set the power variable based on the box above alien
                // this is so that it will automatically set  the direction of the alien
                else if (PowerupCheck(boardgame, AlienRow, AlienColumn - 1, life, maxhealth, zombie) == true)
                {
                    powers = boardgame[AlienRow][AlienColumn - 1];
                    boardgame[AlienRow][AlienColumn] = ".";
                    AlienColumn--;
                    attack = attack + 20;
                    boardgame[AlienRow][AlienColumn] = Alien;
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                boardgame[AlienRow][AlienColumn] = Alien;

                system("CLS");
                displayboard(boardgame);
                cout << "Alien - > "
                     << "Life: " << life << "  Attack: " << attack << endl;
                for (int i = 0; i < zombie.size(); i++)
                {
                    cout << "Zombie " << i + 1 << ": ";
                    cout << "Attack: " << zombie[i].attack;
                    cout << " Life: " << zombie[i].life;
                    cout << " Range: " << zombie[i].range << endl;
                }
                cout << "Enter direction (up,down,left,right): ";
                if (AlienColumn < 1)
                {
                    trail(row, column, boardgame);
                    break;
                }
            }
        }
        else if (input == "right")
        {
            while (true)
            {
                string movem;
                cout << "Press M/m to continue" << endl;
                cin >> movem;
                if (obstacle(boardgame, AlienRow, AlienColumn + 1) == true)
                {
                    boardgame[AlienRow][AlienColumn + 1] = objects[rand() % numObjects];
                    MovementForZombie(boardgame, zombie);
                    trail(row, column, boardgame);
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (CheckingForZombie(boardgame, zombie, AlienRow, AlienColumn + 1, attack) == false)
                {
                    MovementForZombie(boardgame, zombie);
                   AttackForZombie(boardgame, zombie, life);
                    break;
                }

                if (PowerupCheck(boardgame, AlienRow, AlienColumn + 1, life, maxhealth, zombie) == false)
                {
                    if (movem == "M" || movem == "m")
                    {
                        if (AlienColumn < column + 1)
                        {
                            boardgame[AlienRow][AlienColumn] = ".";
                            AlienColumn++;
                            boardgame[AlienRow][AlienColumn] = Alien;
                        }
                    }
                }

                else if (PowerupCheck(boardgame, AlienRow, AlienColumn + 1, life, maxhealth, zombie) == true)
                {
                    powers = boardgame[AlienRow][AlienColumn + 1];
                    boardgame[AlienRow][AlienColumn] = ".";
                    AlienColumn++;
                    attack = attack + 20;
                    boardgame[AlienRow][AlienColumn] = Alien;
                    AttackForZombie(boardgame, zombie, life);
                    break;
                }

                boardgame[AlienRow][AlienColumn] = Alien;

                system("CLS");
                displayboard(boardgame);
                cout << "Alien - > "
                     << "Life: " << life << "  Attack: " << attack << endl;
                for (int i = 0; i < zombie.size(); i++)
                {
                    cout << "Zombie " << i + 1 << ": ";
                    cout << "Attack: " << zombie[i].attack;
                    cout << " Life: " << zombie[i].life;
                    cout << " Range: " << zombie[i].range << endl;
                }
                cout << "Enter direction (up,down,left,right): ";
                if (AlienColumn > column - 2)
                {
                    trail(row, column, boardgame);
                    break;
                }
            }
        }
        else if (input == "arrow")
        {
            while (true)
            {
                int Arow, Acol;
                cout << "Select position to change (Arow, Acol): ";
                cin >> Arow >> Acol;

                if (Arow >= 0 && Arow < boardgame.size() && Acol >= 0 && Acol < boardgame[0].size())
                {
                    if (boardgame[Arow][Acol] == "^" || boardgame[Arow][Acol] == "v" || boardgame[Arow][Acol] == "<" || boardgame[Arow][Acol] == ">")
                    {
                        cout << "Please enter your arrow direction" << endl;
                        string arrowDir;
                        cout << "Enter arrow (up, down, right, left): ";
                        cin >> arrowDir;

                        if (arrowDir == "up" || arrowDir == "down" || arrowDir == "right" || arrowDir == "left")
                        {

                            if (arrowDir == "up")
                            {
                                boardgame[Arow][Acol] = '^';
                            }
                            else if (arrowDir == "down")
                            {
                                boardgame[Arow][Acol] = 'v';
                            }
                            else if (arrowDir == "right")
                            {
                                boardgame[Arow][Acol] = '>';
                            }
                            else if (arrowDir == "left")
                            {
                                boardgame[Arow][Acol] = '<';
                            }

                            system("cls");
                            displayboard(boardgame);

                            string sure;
                            cout << "Arrow done. Do you want to change arrows again? (yes/no): ";
                            cin >> sure;

                            if (sure == "no")
                            {
                                break;
                            }
                        }
                        else
                        {
                            cout << "Invalid.Please enter a valid arrow direction." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid. Please enter a valid position." << endl;
                    }
                }
            }
        }
        else if (input == "quit")
        {
            char confirm;

            cout << "Are you sure you want to quit the game? (Y/N)" << endl;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                cout << "Thanks for playing!" << endl;
                exit(0);
            }
            else
            {
                continue;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int option = mainmenu();
    vector<vector<string>> startgame = gameboard();
    vector<Zombies> startzombie = spawnZombie(startgame);
    if (option == 1)
    {
        alien(startgame, startzombie);
    }
    else if (option == 2)
    {
        displayHelp();
    }
    else if (option == 3)
    {
        char confirm;

        cout << "Are you sure you want to quit the game? (Y/N)" << endl;
        cin >> confirm;
        if (confirm == 'Y' || confirm == 'y')
        {
            cout << "Thanks for playing!" << endl;
            exit(0);
        }
        else
        {
            cout << "ERROR !\n";
        }
        return 0;
    }
}
