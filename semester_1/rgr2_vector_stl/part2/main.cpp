#include "time_utility.h"
#include "train.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);
    std::cout << "t2: ";
    PrintTime(t2);
    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';
    try {

        std::ifstream fin("trains.txt");
        if (!(fin.is_open())) {
            throw "Can't open file trains.txt";
        }
        if (fin.peek() == EOF) {
            throw "trains.txt is empty";
        }

        std::vector<Train> trains;
        std::string line;
        while (std::getline(fin, line)) {
            if (!line.empty()) {
                trains.push_back(Train::FromString(line));
            }
        }

        std::sort(trains.begin(), trains.end(), [](const Train& a, const Train& b) {
            return a.GetDispatchTime() < b.GetDispatchTime();
        });

        std::cout << "\nTrains sorted by dispatch time\n";
        for (std::vector<Train>::iterator it = trains.begin(); it != trains.end(); ++it) {
            it->Print();
        }

        std::time_t start = SetTime(7, 0);
        std::time_t end = SetTime(9, 0);

        std::cout << "\nTrains between 07:00 and 09:00\n";
        for (std::vector<Train>::iterator it = trains.begin(); it != trains.end(); ++it) {
            if (it->GetDispatchTime() >= start && it->GetDispatchTime() <= end) {
                it->Print();
            }
        }

        std::cout << "\nTrains in Minsk\n";
        for (std::vector<Train>::iterator it = trains.begin(); it != trains.end(); ++it) {
            if (it->GetDestination() == "Minsk") {
                it->Print();
            }
        }

        std::cout << "\nPassenger trains in Minsk\n";
        for (std::vector<Train>::const_iterator it = trains.cbegin(); it != trains.cend(); ++it) {
            if (it->GetDestination() == "Minsk" && it->GetType() == TrainType::PASSENGER) {
                it->Print();
            }
        }

        std::vector<Train>::iterator fastest =
            std::min_element(trains.begin(), trains.end(), [](const Train& a, const Train& b) {
                return a.GetTravellingTime() < b.GetTravellingTime();
            });

        std::cout << "\nFastest train in Minsk\n";
        if (fastest != trains.end() && fastest->GetDestination() == "Minsk") {
            fastest->Print();
        }
        fin.close();
    } catch (const char* msg) {
        std::cout << msg;
    }
    return EXIT_SUCCESS;
}
