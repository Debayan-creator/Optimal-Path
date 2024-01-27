#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

int getRandomNumber(int min, int max) 
{
    return rand() % max;
}

float getRandomFloat(float min, float max) 
{
    int x = (rand() % (1000 - 2000) + 1000);
    seed_seq seed{ x };
    mt19937 gen(seed);
    uniform_real_distribution<float> dis(min, max);
    float randomFloat = dis(gen);
    return randomFloat;
}

void writeToCSV(const string& filename, const vector<tuple<int, int, float, float>>& data) {
    ofstream csvFile(filename);

    if (!csvFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Write data to the CSV file
    for (const auto& entry : data) {
        csvFile << get<0>(entry) << ","
                << get<1>(entry) << ","
                << fixed << setprecision(2) << get<2>(entry)<<","
                << fixed << setprecision(2) << get<3>(entry) << endl;
    }

    csvFile.close();
}

int main() {
    int x;
    cout << "Enter value for x: ";
    cin >> x;

    vector<tuple<int, int, float, float>> data;

    // Seed the random number generator with the current time
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    srand(seed);

    for (int i = 0; i < 2000; i++) {
        int rand = getRandomNumber(1, 3);

        if (rand == 1) {
            data.push_back(make_tuple(30, 1, x + getRandomFloat(0.75, 0.95), x+getRandomFloat(0.75, 0.95)+getRandomFloat(-0.20,0.20)));
        } else if (rand == 2) {
            data.push_back(make_tuple(30, 2, x + getRandomFloat(0.55, 0.75), x+getRandomFloat(0.55, 0.75)+getRandomFloat(-0.20,0.20)));
        } else {
            data.push_back(make_tuple(30, 3, x + getRandomFloat(0.35, 0.55), x+getRandomFloat(0.35, 0.55)+getRandomFloat(-0.20,0.20)));
        }
    }

    // Specify the CSV file name
    string filename = "output10.csv";

    // Write data to the CSV file
    writeToCSV(filename, data);

    cout << "CSV file created: " << filename << endl;

    return 0;
}
