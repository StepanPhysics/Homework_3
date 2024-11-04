#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

int main() {

	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	const int max_value = 100;
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % 100;

	int current_value = 0;
	bool not_win = true;
	int attempts = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;
		++attempts;
		if (current_value > random_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < random_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! Attempts = " << attempts << std::endl;
			break;
		}

	} while (true);

	const std::string high_scores_filename = "high_scores_new.txt";
	{
		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		// Append new results to the table:
		out_file << user_name << ' ';
		out_file << attempts;
		out_file << std::endl;
	}

	// Read the high score file and print all results
	{
		std::ifstream in_file{ high_scores_filename };
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "High scores table:" << std::endl;

		std::string username;
		int high_score = 0;
		while (true) {
			// Read the username first
			in_file >> username;
			// Read the high score next
			in_file >> high_score;
			// Ignore the end of line symbol
			in_file.ignore();

			if (in_file.fail()) {
				break;
			}

			// Print the information to the screen
			std::cout << username << '\t' << high_score << std::endl;
		}
	}

	return 0;
}