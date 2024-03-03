#include <iostream>
#include <fstream>
#include <random>

void writeTxtFile(std::vector<std::string> passwordList) {
	std::ofstream writeFile("GeneratedPasswords.txt");

	//Size of password
	size_t n = passwordList.size();

	int passwordCounter = 0;

	writeFile << "Generated list of passwords:" << '\n';

	//Iterates through passwordList
	for (std::string passwordInList : passwordList) {

		writeFile << passwordCounter+1 << ". " << passwordInList << '\n';
		passwordCounter++;
	}

	writeFile.close();
}

int main(int argc, char *argv[]) {
	
	int passwordAmount = 0;
	std::cout << "Welcome to the password generator program!" << '\n';
	std::cout << "Please enter the amount of passwords you want to generate" << '\n';
	//Iterates through while when passwordAmount is below 0 or equal 0
	while (passwordAmount <= 0 || passwordAmount > 10000) {
		std::cin >> passwordAmount;
		if (passwordAmount <= 0)
			std::cout << "Inserted amount of passwords can't be below 0 or equal 0" << '\n' << "Try again" << '\n';
		else if (passwordAmount > 10000)
			std::cout << "Inserted amount of passwords can't be above 10000" << '\n' << "Try again" << '\n';
	}


	//Choosing maximum length of password
	int maxPasswordLength = 0;
	std::cout << "Enter maximum length of password (Minimum 20)" << '\n';
	while (maxPasswordLength < 20) {
		std::cin >> maxPasswordLength;
		if (maxPasswordLength < 20)
			std::cout << "maximum length of password can't be bellow 20" << '\n' << "Try again" << '\n';
	}

	std::random_device dev;
	std::mt19937 rng(dev());

	//Initializing ranges of numbers.
	std::uniform_int_distribution<std::mt19937::result_type> distASCIIChar(33, 126);

	std::uniform_int_distribution<std::mt19937::result_type> distASCIINumbers(48, 57);
	std::uniform_int_distribution<std::mt19937::result_type> distASCIIUpperCaseLetters(65, 90);
	std::uniform_int_distribution<std::mt19937::result_type> distASCIILowerCaseLetters(97, 122);

	std::uniform_int_distribution<std::mt19937::result_type> distLengthOfPassword(20, maxPasswordLength);

	//List
	std::vector<std::string> passwordList;

	//Empty string for a while.
	std::string password = "";
	
	std::cout << "Generated passwords: " << '\n';
	
	//For cycle 
	for (int i = 0; i < passwordAmount; i++) {
		
		//Generates random numbers
		int randomLengthOfPassword = distLengthOfPassword(rng);

		std::uniform_int_distribution<std::mt19937::result_type> distASCIINumbersRandomPosition(0, randomLengthOfPassword);
		std::uniform_int_distribution<std::mt19937::result_type> distASCIIUpperCaseLettersRandomPosition(0, randomLengthOfPassword);

		int ASCIINumbersPosition = distASCIINumbersRandomPosition(rng);
		int ASCIIUpperCaseLettersPosition = distASCIIUpperCaseLettersRandomPosition(rng);

		//if Both ASCIINumbersPostion and ASCIIUpperCaseLettersPosition are same, then ASCIIUpperCaseLettersPosition changes again. 
		while (ASCIINumbersPosition == ASCIIUpperCaseLettersPosition) {
			ASCIIUpperCaseLettersPosition = distASCIIUpperCaseLettersRandomPosition(rng);
		}

		for (int j = 0; j < randomLengthOfPassword; j++) {

			if (j == ASCIINumbersPosition) {
				int randomASCIINumbers = distASCIINumbers(rng);
				char randomChar = static_cast<char> (randomASCIINumbers);
				//Adds every char to string
				password += randomChar;
			}
			else if (j == ASCIIUpperCaseLettersPosition){
				int randomASCIIUpperCaseLetters = distASCIIUpperCaseLetters(rng);
				char randomChar = static_cast<char> (randomASCIIUpperCaseLetters);
				//Adds every char to string
				password += randomChar;
			}
			else {
				int randomASCIILowerCaseLetters = distASCIILowerCaseLetters(rng);
				char randomChar = static_cast<char> (randomASCIILowerCaseLetters);
				//Adds every char to string
				password += randomChar;
			}

		}

		std::cout << i+1 << ". " << password << '\n';
		passwordList.push_back(password);
		password = "";
		
	}

	writeTxtFile(passwordList);

	return 0;
}
