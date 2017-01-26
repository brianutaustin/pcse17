#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

void initialize(unsigned int, float*);
void smooth(unsigned int, float*, float*, float, float, float);
void count(unsigned int, float*, float, unsigned int*);

int main() {

	//======================
	// Timing the code
	time_t Start;
	time_t End;

	float allocXTime;
	float allocYTime;
	float initializeTime;
	float smoothTime;
	float countXTime;
	float countYTime;
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
	/*Timing*/ Start = clock();
	float* x = (float*) malloc(n * n * sizeof(float));
	/*Timing*/ End = clock();
	/*Timing*/ allocXTime = (End - Start) / (float)CLOCKS_PER_SEC;

	/*Timing*/ Start = clock();
	float* y = (float*) malloc(n * n * sizeof(float));
	/*Timing*/ End = clock();
	/*Timing*/ allocYTime = (End - Start) / (float)CLOCKS_PER_SEC;

	// Number of elements under threshold
	unsigned int belowThresholdCountX;
	unsigned int belowThresholdCountY;

	// Initialize the array x
	/*Timing*/ Start = clock();
	initialize(n, x);
	/*Timing*/ End = clock();
	/*Timing*/ initializeTime = (End - Start) / (float)CLOCKS_PER_SEC;

	// Smoothing the array x
	/*Timing*/ Start = clock();
	smooth(n, x, y, a, b, c);
	/*Timing*/ End = clock();
	/*Timing*/ smoothTime = (End - Start) / (float)CLOCKS_PER_SEC;

	// Count the elements under the threshold
	/*Timing*/ Start = clock();
	count(n, x, t, &belowThresholdCountX);
	/*Timing*/ End = clock();
	/*Timing*/ countXTime = (End - Start) / (float)CLOCKS_PER_SEC;

	/*Timing*/ Start = clock();
	count(n, y, t, &belowThresholdCountY);
	/*Timing*/ End = clock();
	/*Timing*/ countYTime = (End - Start) / (float)CLOCKS_PER_SEC;

	//======================
	// Display Benchmark
	std::cout << std::endl;
	std::cout << std::setw(40) << std::left << "Summary" << std::endl;
	std::cout << std::setw(40) << std::left << "-------" << std::endl;
	std::cout << std::setw(40) << std::left << "Number of elements in a row/column" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << n << std::endl;
	std::cout << std::setw(40) << std::left << "Number of inner elements in a row/column" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << n - 2 << std::endl;
	std::cout << std::setw(40) << std::left << "Total number of elements" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << n * n << std::endl;
	std::cout << std::setw(40) << std::left << "Total number of inner elements" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << (n - 2) * (n - 2) << std::endl;
	std::cout << std::setw(40) << std::left << "Memory (GB) used per array" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << n * n * sizeof(float) / (float)1073741824 << std::endl;
	std::cout << std::setw(40) << std::left << "Threshold" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << t << std::endl;
	std::cout << std::setw(40) << std::left << "Smoothing constants (a, b, c)" << std::setw(3) << std::right << " ::" << std::setw(5) << std::right << a << std::setw(5) << std::right << b << std::setw(5) << std::right << c << std::endl;
	std::cout << std::setw(40) << std::left << "Number of elements below threshold (X)" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << belowThresholdCountX << std::endl;
	std::cout << std::setw(40) << std::left << "Fraction of elements below threshold" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << (float) belowThresholdCountX / (float) (n * n) << std::endl;
	std::cout << std::setw(40) << std::left << "Number of elements below threshold (Y)" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << belowThresholdCountY << std::endl;
	std::cout << std::setw(40) << std::left << "Fraction of elements below threshold" << std::setw(3) << std::right << " ::" << std::setw(15) << std::right << (float) belowThresholdCountY / (float) (n * n) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(15) << std::left << "Action" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << "time/s" << std::endl;
	std::cout << std::setw(15) << std::left << "------" << std::endl;
	std::cout << std::setw(15) << std::left << "CPU: Alloc-X" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << std::fixed << std::setprecision(4) << allocXTime << std::endl;
	std::cout << std::setw(15) << std::left << "CPU: Alloc-X" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << std::fixed << std::setprecision(4) << allocYTime << std::endl;
	std::cout << std::setw(15) << std::left << "CPU: Init-X" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << std::fixed << std::setprecision(4) << initializeTime << std::endl;
	std::cout << std::setw(15) << std::left << "CPU: Smooth" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << std::fixed << std::setprecision(4) << smoothTime << std::endl;
	std::cout << std::setw(15) << std::left << "CPU: Count-X" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << std::fixed << std::setprecision(4) << countXTime << std::endl;
	std::cout << std::setw(15) << std::left << "CPU: Count-Y" << std::setw(2) << std::right << "::" << std::setw(8) << std::right << std::fixed << std::setprecision(4) << countYTime << std::endl;
	std::cout << std::endl;
	//======================

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
	for (unsigned int i = 1; i < nDim - 1; i++) {
		for (unsigned int j = 1; j < nDim - 1; j++) {
			if (*(theArray + i * nDim + j) < theThreshold) {
				count++;
			}
		}
	}

	*(theCount) = count;

	return;
}
