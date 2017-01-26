#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void initialize(unsigned int, float*);
void smooth();
void count();

int main() {

	// Smoothing coeffs
	const float a = 0.05;
	const float b = 0.1;
	const float c = 0.4;

	// Smoothing threshold
	float t = 0.1;

	// Number of array dimension in each direction
	unsigned int n = 16384 + 2;

	// Allocate memory for arrays x and y
	float* x = (float*) malloc(n * n * sizeof(float));
	float* y = (float*) malloc(n * n * sizeof(float));

	initialize(n, x);
	initialize(n, y);
	
	return 0;
}

void initialize(unsigned int nDim, float* theArray) {
	for (unsigned int i = 0; i < nDim; i++) {			// Row index
		for (unsigned int j = 0; j < nDim; j++) {		// Col index
			*(theArray + i*nDim + j) = random() / (float)RAND_MAX;
		}
	}

	return;
}
