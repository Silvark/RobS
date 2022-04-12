#include "lodepng.h"
#include <iostream>

int main() {
  const char* filename = "Untitled.png";

  std::vector<unsigned char> png;
  std::vector<unsigned char> image; //the raw pixels
  unsigned width, height;
  int pixptr;
  int r, g, b, grayscale;
  int iterator = 0;

  //load and decode
  unsigned error = lodepng::load_file(png, filename);
  if(!error) error = lodepng::decode(image, width, height, png);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA...
  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      iterator++;
      pixptr = (width*i + j)*4;
      r = (unsigned int)image[pixptr + 0];
      g = (unsigned int)image[pixptr + 1];
      b = (unsigned int)image[pixptr + 2];
      grayscale = (int) ((r+g+b)/3);
      switch (grayscale) {
        case 0:
          printf("@");
          break;
        case 255:
          printf(".");
          break;
        default:
          printf("?");
          break;
      }
    }
    printf("\n");
  }
}
