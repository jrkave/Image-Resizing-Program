// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <string>
#include <fstream>
#include "Image.h"
#include "processing.h"
using namespace std;

int main(int argc, char *argv[]) {
  assert(argc >= 4);

  // Open filestream
  ifstream in;
  in.open(argv[1]);

  // Check if open was successful
  if (!in.is_open()) {
    cout << "Open failed" << endl;
    exit(1);
  }

  // Create new image
  Image *img = new Image;
  Image_init(img, in);

  // Convert cstrings to ints
  int width = atoi(argv[3]);
  int height = atoi(argv[4]);

  // Modify image
  seam_carve(img, width, height);

  // Print modified image
  ofstream out;
  out.open(argv[2]);
  Image_print(img, out);

  // Close everything
  in.close();
  out.close();
  delete img;

}