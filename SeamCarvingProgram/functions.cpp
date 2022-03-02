#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::invalid_argument;


Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  //TODO(student): create a seam
  INFO(length);
  int* Seam = new int[length]{};
  for (int i=0; i<length; i++) {
    Seam[i] = 0;
  }
  return Seam;
}

void deleteSeam(int* seam) {
  // TODO(student): delete a seam
  INFO(seam);
  delete[] seam;
}



bool loadImage(string filename, Pixel** image, int width, int height) {
  INFO(filename);
  INFO(image);
  INFO(width);
  INFO(height);
  // TODO(student): load an image
  cout << "Loading image..." << endl;
  // declare/define and open input file stream
  ifstream ifs (filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  // another file stream for counting rgb values 
  ifstream copied (filename);
  ifstream intcheckstream (filename);
  // get type from preamble
  char type[3];
  ifs >> type; // should be P3
  copied >> type;
  intcheckstream >> type;
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }
  // check for non int read of width and height 
  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  string wstr = "", hstr = "";
  ifs >> w >> h;
  intcheckstream >> w >> h;
  copied >> wstr >> hstr;
  int wcheck = 0;
  int hcheck = 0;
  try{
    wcheck = stoi(wstr);
    hcheck = stoi(hstr);
  }
  catch(std::invalid_argument e){
    cout << "Error: read non-integer value";
    return false;
  }
  w = wcheck;
  h = hcheck;
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width (" << width  << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height  << ") does not match value in file (" << h << ")" << endl;
    return false;
  }
  
  // get maximum value from preamble check for non int read 
  int colorMax = 0;
  string cmax = "";
  ifs >> colorMax;
  intcheckstream >> colorMax;
  copied >> cmax;
  int ccheck = 0;
  try{
    ccheck = stoi(cmax);
  }
  catch(std::invalid_argument e){
    cout << "Error: read non-integer value";
    return false;
  }
  colorMax = ccheck;
  if (colorMax != 255) {
    cout << "Error: file is not using RGB color values." << endl;
    return false;
  }


  // get all rgb values and check for non int read and check for number overflow or underflow
  int number_of_values = (width * height) * 3; 
  int* values = new int[number_of_values]{};
  int rgb_values_inf = 0;
  string i;
  while (copied >> i) 
  {
    string istr = "";
    int colorvcheck = 0;
    intcheckstream >> istr;
    try{
      colorvcheck = stoi(istr);
    }
    catch(std::invalid_argument e){
      cout << "Error: read non-integer value";
      return false;
    }
    if(colorvcheck < 0 || colorvcheck > 255){
      cout << "Error: invalid color value " << colorvcheck;
      return false;
    }
    rgb_values_inf++;
  }

  if(rgb_values_inf > number_of_values){
    cout << "Error: too many color values";
    return false;
  }
  else if(rgb_values_inf < number_of_values){
    cout << "Error: not enough color values";
    return false;
  }

  for(int v = 0; v < number_of_values; v++){
    ifs >> values[v];
  }
  

  int iterator = 0;
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      int dot[3] = {};
      for(int k = 0; k < 3; k++){
        dot[k] = values[iterator];
        iterator++;
      }
      int red = dot[0];
      int green = dot[1];
      int blue = dot[2];
      image[j][i] = {red, green, blue};
    }
  }

  delete[] values;
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height){
  // TODO(student): output an image
  INFO(filename);
  INFO(image);
  INFO(width);
  INFO(height);
  cout << "Outputting image..." << endl;
  // declare/define and open output file stream
  ofstream ofs;
  // check if output stream opened successfully
  ofs.open(filename);
  if (!ofs.is_open()) {
    cout << "Error: failed to open input file " << filename << endl;
    return false;
  }
  //output preamble
  ofs << "P3\n";
  ofs << width;
  ofs << ' ';
  ofs << height << "\n";
  ofs << "255\n";
  //output pixels
  Pixel dot;
  int iterator = 0;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      dot = image[j][i];
      ofs << dot.r;
      ofs << ' ';
      ofs << dot.g;
      ofs << ' ';
      ofs << dot.b;
      ofs << ' ';
      iterator++;
      if(iterator == width){
        ofs << "\n";
        iterator = 0;
      }
    }
  }
  ofs.close();
  return true;
}

int energy(Pixel** image, int column, int row, int width, int height) { 
    // TODO(student): compute the energy of a pixel
    // coordinates j,i
    int y_pix_coordinate_1;
    int y_pix_coordinate_2;
    int y_pix_coordinate_3;
    int y_pix_coordinate_4;

    int x_pix_coordinate_1;
    int x_pix_coordinate_2;
    int x_pix_coordinate_3;
    int x_pix_coordinate_4;

    // check coordinates 
    if(width == 1 || height == 1){// base cases
      if(width == 1 && height == 1){
        return 0;
      } // handling of 1 by height 
      else if(width == 1 && row == 0){
        y_pix_coordinate_1 = 0; // column
        y_pix_coordinate_2 = 1; // row
        
        y_pix_coordinate_3 = 0; // column
        y_pix_coordinate_4 = (height - 1); // row

        Pixel y1 = image[y_pix_coordinate_1][y_pix_coordinate_2];
        Pixel y2 = image[y_pix_coordinate_3][y_pix_coordinate_4];
        int energy_y = (((y1.r - y2.r)*(y1.r - y2.r)) + ((y1.g - y2.g)*(y1.g - y2.g)) + ((y1.b - y2.b)*(y1.b - y2.b)));
        return energy_y;
      }
      else if(width == 1 && row == (height - 1)){
        y_pix_coordinate_1 = 0; // column
        y_pix_coordinate_2 = (height - 2); // row
        
        y_pix_coordinate_3 = 0; // column
        y_pix_coordinate_4 = 0; // row

        Pixel y1 = image[y_pix_coordinate_1][y_pix_coordinate_2];
        Pixel y2 = image[y_pix_coordinate_3][y_pix_coordinate_4];
        int energy_y = (((y1.r - y2.r)*(y1.r - y2.r)) + ((y1.g - y2.g)*(y1.g - y2.g)) + ((y1.b - y2.b)*(y1.b - y2.b)));
        return energy_y;
      }
      else if(width == 1){
        y_pix_coordinate_1 = 0; // column
        y_pix_coordinate_2 = (row - 1); // row
        
        y_pix_coordinate_3 = 0; // column
        y_pix_coordinate_4 = (row + 1); // row

        Pixel y1 = image[y_pix_coordinate_1][y_pix_coordinate_2];
        Pixel y2 = image[y_pix_coordinate_3][y_pix_coordinate_4];
        int energy_y = (((y1.r - y2.r)*(y1.r - y2.r)) + ((y1.g - y2.g)*(y1.g - y2.g)) + ((y1.b - y2.b)*(y1.b - y2.b)));
        return energy_y;
      } // handling of 1 by width images 
      else if(column == 0 && height == 1){
        x_pix_coordinate_1 = 1; // column
        x_pix_coordinate_2 = 0; // row
        
        x_pix_coordinate_3 = (width - 1); // column
        x_pix_coordinate_4 = 0; // row

        Pixel x1 = image[x_pix_coordinate_1][x_pix_coordinate_2];
        Pixel x2 = image[x_pix_coordinate_3][x_pix_coordinate_4];
        int energy_x = (((x1.r - x2.r)*(x1.r - x2.r)) + ((x1.g - x2.g)*(x1.g - x2.g)) + ((x1.b - x2.b)*(x1.b - x2.b)));
        return energy_x;
      }
      else if(column == (width - 1) && height == 1){
        x_pix_coordinate_1 = (width - 2); // column
        x_pix_coordinate_2 = 0; // row
        
        x_pix_coordinate_3 = 0; // column
        x_pix_coordinate_4 = 0; // row

        Pixel x1 = image[x_pix_coordinate_1][x_pix_coordinate_2];
        Pixel x2 = image[x_pix_coordinate_3][x_pix_coordinate_4];
        int energy_x = (((x1.r - x2.r)*(x1.r - x2.r)) + ((x1.g - x2.g)*(x1.g - x2.g)) + ((x1.b - x2.b)*(x1.b - x2.b)));
        return energy_x;
      }
      else if(height == 1){
        x_pix_coordinate_1 = (column - 1); // column
        x_pix_coordinate_2 = 0; // row
        
        x_pix_coordinate_3 = (column + 1); // column
        x_pix_coordinate_4 = 0; // row

        Pixel x1 = image[x_pix_coordinate_1][x_pix_coordinate_2];
        Pixel x2 = image[x_pix_coordinate_3][x_pix_coordinate_4];
        int energy_x = (((x1.r - x2.r)*(x1.r - x2.r)) + ((x1.g - x2.g)*(x1.g - x2.g)) + ((x1.b - x2.b)*(x1.b - x2.b)));
        return energy_x;
      }
      else{
        return 0;
      }
    }
    else if(column == 0 || row == 0 || column == (width - 1) || row == (height - 1)){ // check if on border of image
      if(column == 0 && row == 0){ //top left corner 
        y_pix_coordinate_1 = 0; // column
        y_pix_coordinate_2 = 1; // row

        y_pix_coordinate_3 = 0; // column
        y_pix_coordinate_4 = (height - 1); // row

        x_pix_coordinate_1 = 1; // column 
        x_pix_coordinate_2 = 0; // row

        x_pix_coordinate_3 = (width - 1); // column
        x_pix_coordinate_4 = 0; // row
      }
      else if(column == (width - 1) && row == 0){ //top right corner 
        y_pix_coordinate_1 = (width - 1); // column
        y_pix_coordinate_2 = 1; // row

        y_pix_coordinate_3 = (width - 1); // column
        y_pix_coordinate_4 = (height - 1); // row

        x_pix_coordinate_1 = (width - 2); // column 
        x_pix_coordinate_2 = 0; // row

        x_pix_coordinate_3 = 0; // column
        x_pix_coordinate_4 = 0; // row 
      }
      else if(column == (width - 1) && row == (height - 1)){ //bottom right corner 
        y_pix_coordinate_1 = (width - 1); // column
        y_pix_coordinate_2 = 0; // row

        y_pix_coordinate_3 = (width - 1); // column
        y_pix_coordinate_4 = (height - 2); // row

        x_pix_coordinate_1 = (width -2); // column 
        x_pix_coordinate_2 = (height - 1); // row

        x_pix_coordinate_3 = 0; // column
        x_pix_coordinate_4 = (height - 1); // row
      }
      else if(column == 0 && row == (height - 1)){ //bottom left corner 

        y_pix_coordinate_1 = 0; // column
        y_pix_coordinate_2 = 0; // row

        y_pix_coordinate_3 = 0; // column
        y_pix_coordinate_4 = (height - 2); // row

        x_pix_coordinate_1 = 1; // column 
        x_pix_coordinate_2 = (height - 1); // row

        x_pix_coordinate_3 = (width - 1); // column
        x_pix_coordinate_4 = (height - 1); // row 
         
      }
      else if(row == 0){//top border
        y_pix_coordinate_1 = column; // column
        y_pix_coordinate_2 = (row + 1); // row

        y_pix_coordinate_3 = column; // column
        y_pix_coordinate_4 = (height - 1); // row

        x_pix_coordinate_1 = (column + 1); // column 
        x_pix_coordinate_2 = row; // row

        x_pix_coordinate_3 = (column - 1); // column
        x_pix_coordinate_4 = row; // row 
      }
      else if(row == (height - 1)){//bottom border
        y_pix_coordinate_1 = column; // column
        y_pix_coordinate_2 = (row - 1); // row

        y_pix_coordinate_3 = column; // column
        y_pix_coordinate_4 = 0; // row

        x_pix_coordinate_1 = (column + 1); // column 
        x_pix_coordinate_2 = row; // row

        x_pix_coordinate_3 = (column - 1); // column
        x_pix_coordinate_4 = row; // row 
      }
      else if(column == 0){//left border
        y_pix_coordinate_1 = column; // column
        y_pix_coordinate_2 = (row - 1); // row

        y_pix_coordinate_3 = column; // column
        y_pix_coordinate_4 = (row + 1); // row

        x_pix_coordinate_1 = (column + 1); // column 
        x_pix_coordinate_2 = row; // row

        x_pix_coordinate_3 = (width - 1); // column
        x_pix_coordinate_4 = row; // row 
      }
      else if(column == (width - 1)){//right border
        y_pix_coordinate_1 = column; // column
        y_pix_coordinate_2 = (row - 1); // row

        y_pix_coordinate_3 = column; // column
        y_pix_coordinate_4 = (row + 1); // row

        x_pix_coordinate_1 = (column - 1); // column 
        x_pix_coordinate_2 = row; // row

        x_pix_coordinate_3 = 0; // column
        x_pix_coordinate_4 = row; // row 
      }
    }
    else{
      y_pix_coordinate_1 = column; // column
      y_pix_coordinate_2 = (row - 1); // row

      y_pix_coordinate_3 = column; // column
      y_pix_coordinate_4 = (row + 1); // row

      x_pix_coordinate_1 = (column - 1); // column 
      x_pix_coordinate_2 = row; // row

      x_pix_coordinate_3 = (column + 1); // column
      x_pix_coordinate_4 = row; // row 
    }
    Pixel y1 = image[y_pix_coordinate_1][y_pix_coordinate_2];
    Pixel y2 = image[y_pix_coordinate_3][y_pix_coordinate_4];
    Pixel x1 = image[x_pix_coordinate_1][x_pix_coordinate_2];
    Pixel x2 = image[x_pix_coordinate_3][x_pix_coordinate_4];
    int energy_y = (((y1.r - y2.r)*(y1.r - y2.r)) + ((y1.g - y2.g)*(y1.g - y2.g)) + ((y1.b - y2.b)*(y1.b - y2.b)));
    int energy_x = (((x1.r - x2.r)*(x1.r - x2.r)) + ((x1.g - x2.g)*(x1.g - x2.g)) + ((x1.b - x2.b)*(x1.b - x2.b)));
    int energy = energy_x + energy_y;

  return energy;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  // TODO(student): load a vertical seam
  INFO(image);
  INFO(start_col);
  INFO(width);
  INFO(height);
  INFO(seam);
  int total_energy = 0;
  int starting_energy = energy(image, start_col, 0, width, height);
  total_energy += starting_energy;
  seam[0] = start_col;
  int current_col = start_col;
  for(int i = 1; i < height; i++){
    if(current_col == 0){
      // handle first edge case 
      int energy_1 = energy(image, current_col, i, width, height);
      int energy_2 = energy(image, (current_col + 1), i, width, height);
      if(energy_1 < energy_2){
        current_col = current_col;
      }
      else if(energy_2 < energy_1){
        current_col = current_col + 1;
      }
      else{
        current_col = current_col;
      }
      seam[i] = current_col;
      total_energy += energy(image, current_col, i, width, height);
    }
    else if(current_col == (width - 1)){
      // handle second edge case
      int energy_1 = energy(image, current_col, i, width, height);
      int energy_2 = energy(image, (current_col - 1), i, width, height);
      if(energy_1 < energy_2){
        current_col = current_col;
      }
      else if(energy_2 < energy_1){
        current_col = current_col - 1;
      }
      else{
        current_col = current_col;
      }
      seam[i] = current_col;
      total_energy += energy(image, current_col, i, width, height);
    }
    else{
      // non edge cases 
      int energy_1 = energy(image, current_col, i, width, height);
      int energy_2 = energy(image, (current_col - 1), i, width, height);
      int energy_3 = energy(image, (current_col + 1), i, width, height);
      if(energy_1 < energy_2 && energy_1 < energy_3){
        current_col = current_col;
      }
      else if(energy_2 < energy_1 && energy_2 < energy_3){
        current_col = current_col - 1;
      }
      else if(energy_3 < energy_1 && energy_3 < energy_2){
        current_col = current_col + 1;
      }
      else if(energy_1 > energy_3 && energy_1 > energy_2 && energy_2 == energy_3){
        current_col = current_col + 1;
      }
      else{
        current_col = current_col;
      }
      seam[i] = current_col;
      total_energy += energy(image, current_col, i, width, height);
    }
  }
  return total_energy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  // TODO(student): load a horizontal seam
  INFO(image);
  INFO(start_row);
  INFO(width);
  INFO(height);
  INFO(seam);
   int total_energy = 0;
  int starting_energy = energy(image, 0, start_row, width, height);
  total_energy += starting_energy;
  seam[0] = start_row;
  int current_row = start_row;
  for(int i = 1; i < width; i++){
    if(current_row == 0){
      // handle first edge case 
      int energy_1 = energy(image, i, current_row, width, height);
      int energy_2 = energy(image, i, (current_row + 1), width, height);
      if(energy_1 < energy_2){
        current_row = current_row;
      }
      else if(energy_2 < energy_1){
        current_row = current_row + 1;
      }
      else{
        current_row = current_row;
      }
      seam[i] = current_row;
      total_energy += energy(image, i, current_row, width, height);
    }
    else if(current_row == (height - 1)){
      // handle second edge case
      int energy_1 = energy(image, i, current_row, width, height);
      int energy_2 = energy(image, i, (current_row - 1),  width, height);
      if(energy_1 < energy_2){
        current_row = current_row;
      }
      else if(energy_2 < energy_1){
        current_row = current_row - 1;
      }
      else{
        current_row = current_row;
      }
      seam[i] = current_row;
      total_energy += energy(image, i, current_row, width, height);
    }
    else{
      // non edge cases 
      int energy_1 = energy(image, i, current_row, width, height);
      int energy_2 = energy(image, i, (current_row - 1), width, height);
      int energy_3 = energy(image, i, (current_row + 1), width, height);
      if(energy_1 < energy_2 && energy_1 < energy_3){
        current_row = current_row;
      }
      else if(energy_2 < energy_1 && energy_2 < energy_3){
        current_row = current_row - 1;
      }
      else if(energy_3 < energy_1 && energy_3 < energy_2){
        current_row = current_row + 1;
      }
      else if(energy_1 > energy_3 && energy_1 > energy_2 && energy_2 == energy_3){
        current_row = current_row  - 1;
      }
      else{
        current_row = current_row;
      }
      seam[i] = current_row;
      total_energy += energy(image, i, current_row, width, height);
    }
  }
  return total_energy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  //TODO(student): find min vertical seam
  INFO(image);
  INFO(width);
  INFO(height);
  int* seam = createSeam(height);
  int min = loadVerticalSeam(image, 0, width, height, seam);
  int curr;
  int index_of_min;
  for(int j = 1; j < width; j++){
    curr = loadVerticalSeam(image, j, width, height, seam);
    if(curr < min){
      min = curr;
      index_of_min = j;
    }
  }
  min = loadVerticalSeam(image, index_of_min, width, height, seam);
  return seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  //TODO(student): find min horizontal seam
  INFO(image);
  INFO(width);
  INFO(height);
  int* seam = createSeam(width);
  int min = loadHorizontalSeam(image, 0, width, height, seam);
  int curr;
  int index_of_min;
  for(int j = 1; j < height; j++){
    curr = loadHorizontalSeam(image, j, width, height, seam);
    if(curr < min){
      min = curr;
      index_of_min = j;
    }
  }
  min = loadHorizontalSeam(image, index_of_min, width, height, seam);
  return seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam){
  // TODO(student): remove a vertical seam
  //INFO(image);
  //INFO(width);
  //INFO(height);
  //INFO(v_Seam);

  Pixel oneless;
  for (int row = 0; row < height; row++) {
    oneless = image[verticalSeam[row]][row];
    for (int column = verticalSeam[row]; column < width - 1; column++) {
      image[column][row] = image[column + 1][row];
    }
    image[width - 1][row] = oneless;
  }
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  // TODO(student): remove a horizontal seam
  INFO(image);
  INFO(width);
  INFO(height);
  INFO(horizontalSeam);
  Pixel oneless;
  for (int col = 0; col < width; col++) {
    oneless = image[col][horizontalSeam[col]];
    for (int row = horizontalSeam[col]; row < height - 1; row++) {
      image[col][row] = image[col][row + 1];
    }
    image[col][height -1] = oneless;
  }
}