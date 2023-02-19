Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtu.be/wX4fQJq9Jgc).

## Minimum Requirements

### Completed

List all the features completed.

1. Dynamic Game Board with objects randomly placed on it.
2. Game Characters
 - Zombie and Alien Attributes (life,range,attack)
3. Alien and Zombie movement
4. Alien leaving trails and the trail reset.
5. Multiple spawn of Zombies
6. Game objects
7. Game controls
8. Game flow
9. 1 Additional features
   - new game objects

### To Do
1. Save and Load

## Additional Features

-New Powerup (t)- Terror : Adds 5 hp to all zombies on the board once alien hits it so this is a disadvantage to the alien.

## Contributions

List down the contribution of each group members.

For example:

### KIRTANAH A/P MANALAN

1. Alien movement
2. Alien picking powerup
3. Alien health
4. Alien adding 20 to attack each time it hit arrow
5. Powerup check
6. Alien trail changing 
7. Placement of objects on the board randomly.
8. Switching arrow direction

### LAKULESHH LEVIS A/L SELVARAJAH

1. Dynamic Gameboard creation
2. Main menu
3. Documentations

### SHARVINTHIRAN A/L RAJAKUMAR

1. Zombie  movement
2. Zombie attack
3. Spawning of zombie on board
4. Alien pod powerup
5. Powerup t (additional feature)
6. Alien Placement in the middle of the board
7. Alien attack


## Problems Encountered & Solutions

Problems encountered : 
1. Alien did not add 20 attack when it hits the arrow but added 60 instead.
   Solution : Instead of adding the alien in the string powerup function, I added it to the void alien function under the up movement.

2. Placing a powerup under the rock
   Solution : Adding under movement instead of using a separate function

3. Zombie wont be able to move at certain times
   Solution : Adding abs so it will take only the posiive interger from the coordinate

4. Alien trail wasn't reset when reach the boundary of the board
    Solution : Create a separate function to replace the trail with empty spaces then generate random objects on the empty spaces

5. Trouble combining main menu
    Solution : placed it under int main()  function.