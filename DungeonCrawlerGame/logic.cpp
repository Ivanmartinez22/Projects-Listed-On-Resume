#include "logic.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = {" << X.row << "," << X.col << "," << X.treasure << "}" << endl;

/**
 * This function is provided; do not change
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  2D dynamic array representation of dungeon map with player's location.
 */
char** loadLevel(const string fileName, int& maxRow, int& maxCol, Player& player) {
    // INFO(maxRow);
    // INFO(maxCol);

    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cout << "ERROR: Unable to open: " << fileName << endl;
        return nullptr;
    }
    ifs >> maxRow >> maxCol;
    ifs >> player.row >> player.col;

    char** dungeon = createMap(maxRow,maxCol);
    if (dungeon == nullptr) {
        cout << "ERROR: Map did not load." << endl;
        return nullptr;
    }

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            ifs >> dungeon[i][j];
            if (i == player.row && j == player.col) {
                dungeon[i][j] = TILE_PLAYER;
            }
        }
    }

    return dungeon;
}

/**
 * This function is provided; do not change
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch(input) {
        case MOVE_UP:
            nextRow--;
            break;
        case MOVE_DOWN:
            nextRow++;
            break;
        case MOVE_LEFT:
            nextCol--;
            break;
        case MOVE_RIGHT:
            nextCol++;
            break;
    }
}

/**
 * TODO: Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    // INFO(maxRow);
    // INFO(maxCol);
    char** map = new char*[maxRow];
    bool fail = false;
    for (int i=0; i < maxRow; ++i) { // loop through each column
        // assign that column to a one dimensional array on the heap of Pixels
        //  that has height elements (i.e. the number of rows)
        map[i] = new char[maxCol];
    }
    
  
    // if(fail) { // if any allocation fails, clean up and avoid memory leak
    // // deallocate any arrays created in for loop
    //     for (int i=0; i < maxCol; ++i) {
    //         delete [] map[i]; // deleting nullptr is not a problem
    //     }
    //     delete [] map; // dlete array of pointers
    // }
    // initialize cells
    //cout << "Initializing cells..." << endl;
    for (int row=0; row<maxRow; ++row) {
        for (int col=0; col<maxCol; ++col) {
            map[row][col] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 */
void deleteMap(char** map, int maxRow) {
    // INFO(map);
    // INFO(maxRow);
    // avoid memory leak by deleting the array
    for (int i=0; i<maxRow; ++i) {
        delete [] map[i]; // delete each individual array placed on the heap
    }
    delete [] map;
    map = nullptr;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can call your createMap and deleteMap functions to help with this one!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  An updated 2D map that has twice as many columns and rows in size.
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    // INFO(map);
    // INFO(maxRow);
    // INFO(maxCol);
    int o_Rows = maxRow;
    int o_Cols = maxCol;
    maxRow = 2 * maxRow;
    maxCol = 2 * maxCol;
    char** resizedMap = new char*[maxRow];
    for(int i=0; i < maxRow; ++i) { // loop through each column
        // assign that column to a one dimensional array on the heap of Pixels
        //  that has height elements (i.e. the number of rows)
        resizedMap[i] = new char[maxCol];
    }
    // A
    for(int row=0; row<o_Rows; ++row){
        for (int col=0; col<o_Cols; ++col) {
            resizedMap[row][col] = map[row][col];
        }
    }
    //B
    for (int row=0; row<o_Rows; ++row) {
        for(int col=o_Cols; col<maxCol; ++col) {
            if(map[row][col - o_Cols] != TILE_PLAYER){
                resizedMap[row][col] = map[row][col - o_Cols];
            }
            else{
                resizedMap[row][col] = TILE_OPEN;
            }
        }
    }
    //C
    for (int row=o_Rows; row<maxRow; ++row) {
        for (int col=0; col<o_Cols; ++col) {
            if(map[row - o_Rows][col] != TILE_PLAYER){
                resizedMap[row][col] = map[row - o_Rows][col];
            }
            else{
                resizedMap[row][col] = TILE_OPEN;
            }
        }
    }
    //D
    for (int row=o_Rows; row<maxRow; ++row) {
        for (int col=o_Cols; col<maxCol; ++col) {
            if(map[row - o_Rows][col - o_Cols] != TILE_PLAYER){
                resizedMap[row][col] = map[row - o_Rows][col - o_Cols];
            }
            else{
                resizedMap[row][col] = TILE_OPEN;
            }
        }
    }
    deleteMap(map, o_Rows);
    return resizedMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int& nextRow, int& nextCol) {
    // INFO(map);
    // INFO(maxRow);
    // INFO(maxCol);
    // INFO_STRUCT(player);
    // INFO(nextRow);
    // INFO(nextCol);
    int status = 0; 
    int previous_pos1 = player.row;
    int previous_pos2 = player.col;
    if( nextRow > maxRow || nextCol > maxCol || nextRow < 0 || nextCol < 0 || nextCol == maxCol || nextRow == maxRow){
        nextRow = previous_pos1;
        nextCol = previous_pos2;
        status = STATUS_STAY;
        player.row = nextRow;
        player.col = nextCol; 
    }
    else if(map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER ){
        nextRow = previous_pos1;
        nextCol = previous_pos2;
        status = STATUS_STAY;
    }
    else if(map[nextRow][nextCol] == TILE_TREASURE){
        player.treasure++;
        status = STATUS_TREASURE;
    }
    else if(map[nextRow][nextCol] == TILE_AMULET){
        status = STATUS_AMULET;
    }
    else if(map[nextRow][nextCol] == TILE_DOOR){
        status = STATUS_LEAVE;
    }
    else if(map[nextRow][nextCol] == TILE_EXIT){
        if(player.treasure >= 1){
            status = STATUS_ESCAPE;
        }
        else{
            nextRow = previous_pos1;
            nextCol = previous_pos2;
        }
    }
    else{
        status = STATUS_MOVE;
    }
    player.row = nextRow;
    player.col = nextCol;
    map[previous_pos1][previous_pos2] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    return status; // update to use STATUS consts from logic.h!
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, Player& player) {
    // INFO(map);
    // INFO(maxRow);
    // INFO(maxCol);
    // INFO_STRUCT(player);
    int row = player.row;
    int col = player.col;

    // check up
    bool pillar = false;
    int m_row = 0;
    for(int i = (row - 1); i >= 0; i--){
        if(map[i][col] == TILE_PILLAR){
            pillar = true;
        }
        else if(map[i][col] == TILE_MONSTER && pillar == false){
            m_row = i;
            map[m_row + 1][col] = TILE_MONSTER;
            map[m_row][col] = TILE_OPEN;
        }
    }
    // check down
    bool pillar2 = false;
    m_row = 0;
    for(int i = (row + 1); i < maxRow; i++){
        if(map[i][col] == TILE_PILLAR){
            pillar2 = true;
        }
        else if(map[i][col] == TILE_MONSTER && pillar2 == false){
            m_row = i;
            map[m_row][col] = TILE_OPEN;
            map[m_row - 1][col] = TILE_MONSTER;
        }
    }
    // check left
    bool pillar3 = false;
    bool monster_move3 = false;
    int m_col = 0;
    for(int i = (col - 1); i >= 0; i--){
        if(map[row][i] == TILE_PILLAR){
            pillar3 = true;
        }
        else if(map[row][i] == TILE_MONSTER && pillar3 == false){
            m_col = i;
            map[row][m_col] = TILE_OPEN;
            map[row][m_col + 1] = TILE_MONSTER;
        }
    }
    // check right
    bool pillar4 = false;
    m_col = 0;
    for(int i = (col + 1); i < maxCol; i++){
        if(map[row][i] == TILE_PILLAR){
            pillar4 = true;
        }
        else if(map[row][i] == TILE_MONSTER && pillar4 == false){
            m_col = i;
            map[row][m_col] = TILE_OPEN;
            map[row][m_col - 1] = TILE_MONSTER;
            
        }
    }
    // check if any monster is on player
    if(map[row][col] == TILE_MONSTER){
        return true;
    }
    return false;
}