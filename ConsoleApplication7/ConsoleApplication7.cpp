#include <iostream>
#include <cstdlib>
#include <ctime>

const unsigned int DIM1 = 4, DIM2 = 4;
const double L = 0.5;

int WaldCrit(int array[DIM1][DIM2], int& StrategyNumber) {
	int minArray[DIM1];
	int maxMinValue;

	for (int i = 0; i < DIM1; ++i)
	{
		maxMinValue = array[i][0];
		for (int j = 0; j < DIM2; ++j)
			if (array[i][j] < maxMinValue)
				maxMinValue = array[i][j];
		minArray[i] = maxMinValue;
	}
	for (int& value : minArray)
		if (value > maxMinValue)
			maxMinValue = value;

	StrategyNumber = 0;
	while (minArray[StrategyNumber] != maxMinValue)
		++StrategyNumber;

	return maxMinValue;
}

int SavageCrit(int array[DIM1][DIM2], int& StrategyNumber) {
	int maxArray[DIM1];
	int minMaxValue;

	for (int i = 0; i < DIM1; ++i)
	{
		minMaxValue = array[i][0];
		for (int j = 0; j < DIM2; ++j)
			if (array[i][j] > minMaxValue)
				minMaxValue = array[i][j];
		maxArray[i] = minMaxValue;
	}
	for (int& value : maxArray)
		if (value < minMaxValue)
			minMaxValue = value;

	StrategyNumber = 0;
	while (maxArray[StrategyNumber] != minMaxValue)
		++StrategyNumber;

	return minMaxValue;
}

double HurwitzCrit(int array[DIM1][DIM2], int& StrategyNumber) {
	double balanceArray[DIM1];
	double maxBalanceValue;
	int maxValue, minValue;

	for (int i = 0; i < DIM1; ++i) {
		maxValue = minValue = array[i][0];
		for (int j = 0; j < DIM2; ++j) {
			if (array[i][j] > maxValue)
				maxValue = array[i][j];
			if (array[i][j] < minValue)
				minValue = array[i][j];
		}
		balanceArray[i] = L * maxValue + (1 - L) * minValue;
	}
	maxBalanceValue = balanceArray[0];
	for (double& value : balanceArray)
		if (value > maxBalanceValue)
			maxBalanceValue = value;

	StrategyNumber = 0;
	while (balanceArray[StrategyNumber] != maxBalanceValue)
		++StrategyNumber;

	return maxBalanceValue;
}

int main()
{
	int array[DIM1][DIM2];
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < DIM1; ++i) {
		for (int j = 0; j < DIM2; ++j) {
			array[i][j] = rand() % 100;
			std::cout << array[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	int StrategyNumber = NULL;
	std::cout << "Wald Crit value: " << WaldCrit(array, StrategyNumber) << " Strategy: " << StrategyNumber << std::endl;
	std::cout << "Savage Crit value: " << SavageCrit(array, StrategyNumber) << " Strategy: " << StrategyNumber << std::endl;
	std::cout << "Hurwitz Crit value: " << HurwitzCrit(array, StrategyNumber) << " Strategy: " << StrategyNumber << std::endl;
}


