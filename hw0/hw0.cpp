#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void initialize(unsigned int, float*);
void smooth(unsigned int, float*, float*, float, float, float);
void count(unsigned int, float*, float, unsigned int*);

int main() {

	//======================
	// Timing the code
	clock_t nt1;
	clock_t nt2;
	clock_t nt3;
	clock_t nt4;
	clock_t nt5;
	clock_t nt6;
	//======================

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

	// Number of elements under threshold
	unsigned int belowThresholdCountX;
	unsigned int belowThresholdCountY;

	// Initialize the arrays
	initialize(n, x);
	initialize(n, y);

	// Smoothing the array x
	smooth(n, x, y, a, b, c);

	// Count the elements under the threshold
	count(n, x, t, &belowThresholdCountX);
	count(n, y, t, &belowThresholdCountY);

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

void smooth(unsigned int nDim, float* x, float* y, float aCoeff, float bCoeff, float cCoeff) {
	for (unsigned int i = 1; i < nDim - 1; i++) {
		for (unsigned int j = 1; j < nDim -1; j++) {
			*(y + i*nDim + j) =
			aCoeff * (*(x + (i-1)*nDim + (j-1)) + *(x + (i-1)*nDim + (j+1)) + *(x + (i+1)*nDim + (j-1)) + *(x + (i+1)*nDim + (j+1))) +
			bCoeff * (*(x + (i-1)*nDim + (j+0)) + *(x + (i+1)*nDim + (j+0)) + *(x + (i+0)*nDim + (j-1)) + *(x + (i+0)*nDim + (j+1))) +
			cCoeff * (*(x + (i+0)*nDim + (j+0)));
		}
	}

	return;
}

void count(unsigned int nDim, float *theArray, float theThreshold, unsigned int* theCount) {
	int count = 0;
	for (unsigned int i = 0; i < nDim; i++) {
		for (unsigned int j = 0; j < nDim; j++) {
			if (*(theArray + i * nDim + j) < theThreshold) {
				count++;
			}
		}
	}

	*(theCount) = count;

	return;
}
