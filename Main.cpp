#include <iostream>
#include <vector>
#include <bitset>

const int MAX_NUMBER_OF_ROWS = 42;

const double ERROR_BOUND = 1e-9;
const int WRONG_ANSWER_CODE = 2; // it doesn't actually have to be infinity or a big number

int DoGaussElimination(std::vector<std::vector<double> > matrix, std::vector<double>& answer)
{
	const int numberOfRows = matrix.size();
	const int numberOfCols = matrix[0].size() - 1;

	std::vector<int> pivotIndices(numberOfCols, -1);

	// find the row with the biggest absolute value on col position 
	for (int col = 0, row = 0; col < numberOfCols && row < numberOfRows; ++col)
	{
		int bestCurrentRow = row;

		for (int i = row; i < numberOfRows; ++i)
		{
			if (std::abs(matrix[i][col]) > std::abs(matrix[bestCurrentRow][col]))
			{
				bestCurrentRow = i;
			}
		}

		// if the best row with the max heurestic is less than ERROR_BOUND - then assume it is a zero there
		if (std::abs(matrix[bestCurrentRow][col]) < ERROR_BOUND)
		{
			continue;
		}


		// swap that matrix[currentRow] with matrix[row]
		for (int i = col; i <= numberOfCols; ++i)
		{
			std::swap(matrix[bestCurrentRow][i], matrix[row][i]);
		}

		pivotIndices[col] = row;

		for (int i = 0; i < numberOfRows; ++i)
		{
			if (i != row)
			{
				double c = matrix[i][col] / matrix[row][col];

				for (int j = col; j <= numberOfCols; ++j)
				{
					matrix[i][j] -= matrix[row][j] * c;
				}
			}
		}

		++row;
	}

	answer.assign(numberOfCols, 1);
	std::bitset<MAX_NUMBER_OF_ROWS> foundAnswers;

	for (size_t i = 0; i < numberOfCols; ++i)
	{
		if (pivotIndices[i] != -1)
		{
			foundAnswers[i] = 1;
			
			double sum = 0;
			for (size_t j = 0; j < numberOfCols; ++j)
			{
				if (j == i)
				{
					continue;
				}

				sum += matrix[pivotIndices[i]][j];
			}

			answer[i] = (matrix[pivotIndices[i]][numberOfCols] - sum) / matrix[pivotIndices[i]][i];


		}
	}


	for (size_t i = 0; i < numberOfRows; ++i)
	{
		double sum = 0;

		for (int j = 0; j < numberOfCols; ++j)
		{
			sum += answer[j] * matrix[i][j];
		}

		if (std::abs(sum - matrix[i][numberOfCols]) > ERROR_BOUND)
		{
			return 0;
		}
	}

	for (size_t i = 0; i < numberOfCols; ++i)
	{
		if (answer[i] == 1 && !foundAnswers[i])
		{
			return WRONG_ANSWER_CODE;
		}
	}

	return 1;
}

int main()
{
	int numberOfRows;
	int numberOfCols;
	
	std::cin >> numberOfRows >> numberOfCols;

	std::vector<std::vector<double>> matrix;

	matrix.reserve(numberOfRows);

	for (size_t i = 0; i < numberOfRows; ++i)
	{
		matrix.push_back(std::vector<double>());
		matrix[i].reserve(numberOfCols);

		for (size_t j = 0; j < numberOfCols; ++j)
		{
			double currentElement;
			std::cin >> currentElement;

			matrix[i].push_back(currentElement);
		}
	}

	std::vector<double> answer;
	int res = DoGaussElimination(matrix, answer);

	return 0;
}