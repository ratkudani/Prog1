#include <iostream>
#include "ql.hpp"
#include <png++/png.hpp>

int main(int argc, char **argv)
{
	png::image <png::rgb_pixel> png_image(argv[1]);
	int size = png_image.get_width() *png_image.get_height();
	Perceptron* p = new Perceptron (3, size, 256, 1);
	double* image  new double(size);
	for(int i(0); i<png_image.get_width(); ++i)
		for(int j(0); j<png_image.get_width(); ++j)
			image[i*png_image.get_width()+j] = png_image[i][j].red;

double value = (*p) (image);

std::cout << value << std::end;

delete p;
delete [] image;
}