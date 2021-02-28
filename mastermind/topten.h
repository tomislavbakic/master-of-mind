#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>

using namespace std;

struct TopTen {
	string name;
	long score;
};

bool compareByScore(const TopTen& a, const TopTen& b) {
	return a.score > b.score;
}

bool isEmpty(ifstream& file) {
	return file.peek() == ifstream::traits_type::eof();
}

void readFile(vector<TopTen>& competitors) {
	TopTen inputCompetitor;
	ifstream file;

	if (competitors.size() > 0) {
		competitors.clear();
	}

	file.open("results.txt");

	if (!file) {
		cout << "File doesn't exist!";
		exit(EXIT_FAILURE);
	}

	if (!isEmpty(file)) {
		while (!file.eof()) {
			file >> inputCompetitor.name;
			file >> inputCompetitor.score;

			competitors.push_back(inputCompetitor);
		}
	}

	file.close();
}

void insertSorted(vector<TopTen>& competitors, TopTen value) {
	if (competitors.size() == 0) {
		competitors.push_back(value);
	}
	else {
		vector<TopTen>::iterator itr = upper_bound(competitors.begin(), competitors.end(), value, compareByScore);
		competitors.insert(itr, value);

		if (competitors.size() > 10) {
			competitors.resize(10);
		}
	}
}

void updateScoresInFile(vector<TopTen> competitors) {
	ofstream file;

	file.open("results.txt", ios::trunc);

	if (!file) {
		cout << "File doesn't exist!";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < competitors.size(); i++) {
		file << competitors[i].name << " " << competitors[i].score;

		if (i < competitors.size() - 1) {
			file << endl;
		}
	}

	file.close();
}

int findPosition(vector<TopTen> competitors, int score) {
	int i;
	for (i = 0; i < competitors.size(); i++) {
		if (competitors[i].score < score)
			return i + 1;
	}

	if (i < 10) 
		return i + 1;

	return -1;
}
