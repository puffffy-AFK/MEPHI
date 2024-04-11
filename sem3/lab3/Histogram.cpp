#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <random>
#include <sstream>
#include <map>


#include "CustomHashTable.hpp"

using namespace std;

template<typename T, typename K>
class Histogram {
private:
    string criteriaName;
    K rangeStart;
    K rangeEnd;
    K rangeStep;
    function<K(const T&)> getProperty;
    CustomHashTable<K, int> histogram;

public:
    Histogram(const string& criteriaName, K rangeStart, K rangeEnd, K rangeStep, function<K(const T&)> getProperty)
        : criteriaName(criteriaName), rangeStart(rangeStart), rangeEnd(rangeEnd), rangeStep(rangeStep), getProperty(getProperty) {}

    void create(const vector<T>& data) {
        for (const auto& element : data) {
            K property = getProperty(element);
            K range = rangeStart;
            while (range < rangeEnd) {
                if (property >= range && property < range + rangeStep) {
                    histogram[range]++;
                    break;
                }
                range += rangeStep;
            }
        }
    }

    K getRangeStart() const {
        return rangeStart;
    }

    K getRangeEnd() const {
        return rangeEnd;
    }

    K getRangeStep() const {
        return rangeStep;
    }

    int getAmount(K key) {
        return histogram[key];
    }

    void print() const {
        cout << "Histogram for " << criteriaName << ":" << endl;
        for (K i = rangeStart; i < rangeEnd; i += rangeStep) {
            cout << i << "-" << i + rangeStep << ": " << histogram[i] << " elements" << endl;
        }
    }
};

class Person {
public:
    string name;
    int age;
    double height;

    Person(const string& n, int a, double h) : name(n), age(a), height(h) {}

    string toString() const {
        ostringstream oss;
        oss << "<" << name << ": " << age << ", " << height << ">";
        return oss.str();
    }
};


void printPeople(const vector<Person>& people) {
    cout << "People:\n[ ";
    string separator = "";
    for (size_t i = 0; i < people.size(); ++i) {
        cout << separator << people[i].toString();
        separator = ", ";
    }
    cout << " ]\n";
}

void test(const vector<Person>& people) {
    Histogram<Person, int> histogram("Age", 10, 40, 5, [](const Person& p) { return p.age; });
    map<int, int> expected;
    for (const auto& person : people) {
        int age = person.age;
        int range = histogram.getRangeStart();
        while (range < histogram.getRangeEnd()) {
            if (age >= range && age < range + histogram.getRangeStep()) {
                expected[range]++;
                break;
            }
            range += histogram.getRangeStep();
        }
    }

    histogram.create(people);

    for (int i = histogram.getRangeStart(); i < histogram.getRangeEnd(); i += histogram.getRangeStep()) {
        if (histogram.getAmount(i) != expected[i]) {
            cout << "Test failed\n";
            return;
        }
    }

    cout << "Tests passed\n";
    return;
}

int main() {

    vector<Person> people = {
        Person("Alice", 25, 160.5),
        Person("Bob", 30, 175.0),
        Person("Charlie", 25, 180.0),
        Person("Anna", 28, 165.0),
        Person("Alex", 22, 170.0)
    };

    test(people);
    return 0;

    cout << "Choose mode:\n1. Automatic\n2. Manual\n";
    int choice;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> ageDist(10, 40);
        uniform_real_distribution<> heightDist(150.0, 200.0);

        vector<Person> randomPeople;
        for (int i = 0; i < 5; ++i) {
            randomPeople.push_back(Person("Person" + to_string(i + 1), ageDist(gen), heightDist(gen)));
        }

        cout << "Input data for automatic mode:\n";
        printPeople(randomPeople);

        // Create histograms
        Histogram<Person, int> ageHistogram("Age", 10, 40, 5, [](const Person& p) { return p.age; });
        ageHistogram.create(randomPeople);
        ageHistogram.print();

        Histogram<Person, int> heightHistogram("Height", 150.0, 200.0, 10.0, [](const Person& p) { return p.height; });
        heightHistogram.create(randomPeople);
        heightHistogram.print();
    } else if (choice == 2) {
        cout << "Input data for manual mode:\n";
        printPeople(people);

        // Manual mode
        int minAge, maxAge, ageInterval;
        cout << "Enter minimum age: ";
        cin >> minAge;
        cout << "Enter maximum age: ";
        cin >> maxAge;
        cout << "Enter age interval: ";
        cin >> ageInterval;

        Histogram<Person, int> ageHistogram("Age", minAge, maxAge, ageInterval, [](const Person& p) { return p.age; });
        ageHistogram.create(people);
        ageHistogram.print();
    } else {
        cout << "Invalid choice\n";
    }

    return 0;
}
