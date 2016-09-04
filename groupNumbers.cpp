#include <iostream>
#include <vector>

static struct TempStorageForRecursion {
	int maxInGroup;
	std::vector<int> numbers;
	std::vector<int> selectedNumbers;
} TSFR;

int recursivePick(int startNum = 0, int prev = 0) {
	static int max;
	static std::vector<int> tempNumbers;
	if (startNum == 0) {
		max = 0;
		tempNumbers.clear();
		TSFR.selectedNumbers.clear();
	}
	int sum;
	for (unsigned int i = startNum; i < TSFR.numbers.size(); i++) {
		sum = prev + TSFR.numbers[i];
		if (sum > TSFR.maxInGroup) continue;
		tempNumbers.push_back(i);
		if (sum > max) {
			max = sum;
			TSFR.selectedNumbers = tempNumbers;
		}
		if (sum == TSFR.maxInGroup) return 1;
		if (recursivePick(i+1, sum) == 1) return 1;
		tempNumbers.pop_back();
	}
	return 0;
}

int groupNumbers(int _maxInGroup, std::vector<int> _numbers) {
	for (auto i : _numbers) {
		if (i > _maxInGroup)
			return -1;
	}
#ifdef _DEBUG
	std::cout << "Numbers: ";
	for (unsigned int i = 0; i < _numbers.size(); i++)
		std::cout << _numbers[i] << ((i + 1 < _numbers.size()) ? ',' : ' ');
	std::cout << "\nMax in group: " << _maxInGroup << '\n';
	int sumNumbersInGroup;
#endif //Debug output
	TSFR.maxInGroup = _maxInGroup;
	TSFR.numbers = _numbers;
	int numberOfGroups = 0;

	while (TSFR.numbers.empty() == false) {
		recursivePick();
		numberOfGroups++;
#ifdef _DEBUG
		sumNumbersInGroup = 0;
		std::cout << "\nGroup " << numberOfGroups << ":  ";
		for (unsigned int i = 0; i < TSFR.selectedNumbers.size(); i++)
			std::cout << TSFR.numbers[TSFR.selectedNumbers[i]] << ((i + 1 < TSFR.selectedNumbers.size()) ? '+' : ' ');
		for (int i : TSFR.selectedNumbers)
			sumNumbersInGroup += TSFR.numbers[i];
		std::cout << '=' << sumNumbersInGroup;
#endif //Debug output
		while (TSFR.selectedNumbers.empty() == false) {
			TSFR.numbers.erase(TSFR.numbers.begin() + TSFR.selectedNumbers[TSFR.selectedNumbers.size() - 1]);
			TSFR.selectedNumbers.pop_back();
		}
	}
	return numberOfGroups;
}

int main()
{
	std::cout << "\n\nNumber of groups: " << groupNumbers(60, { 31,4,2,22,19,6,26,14,18,30,56,11,14,6,3,9,1,5,8,36,2,45,5,6,3,6,7,8,4,7,7,8,9,5,2,3,4,2,2,44,5,6,2,6,2,6,1,5,6 }) << "\n\n";
	system("pause");
    return 0;
}
