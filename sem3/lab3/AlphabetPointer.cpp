#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "CustomHashTable.hpp"


int main () {
    CustomHashTable<string, vector<pair<int, int>>> hashTable(100);
    int linesPerPage = 5;
    cout << "Give me amount of lines per page: ";
    cin >> linesPerPage;

    std::ifstream input("input.txt");
    std::string line;
    int lineNum = 1, wordNum = 1, pageNum = 1;
    std::vector<string> pages;
    std::string currentPage;
    
    while (getline(input, line)) {
        std::istringstream iss(line);
        std::string word;
        std::vector<string> words;
        while (iss >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            hashTable[word].push_back({pageNum, lineNum});
        }
        currentPage += line + "\n";
        lineNum++;
        if ((lineNum - 1) % linesPerPage == 0) {
            pages.push_back(currentPage);
            currentPage = "";
            pageNum++;
            lineNum = 1;
        }
    }

    if (!currentPage.empty()) {
        pages.push_back(currentPage);
    }

    int currentPageNum = 0;
    int totalPages = pages.size();
    bool showAlphabetPointer = false;

    while (true) {
        std::cout << "\n\n\n";
        std::cout << "\033[2J\033[1;1H";
        std::cout << "=====================================================================" << endl;
        std::cout << pages[currentPageNum] << endl;
        std::cout << currentPageNum + 1 << "/" << totalPages << endl << endl;

        std::cout << "1. Next page" << endl;
        std::cout << "2. Previous page" << endl;
        std::cout << "3. Go to current page" << endl;
        std::cout << (showAlphabetPointer ? "4. Hide alphabet pointer" : "4. Show alphabet pointer") << endl;
        std::cout << "0. Exit" << endl;

        if (showAlphabetPointer) {
            std::cout << endl << "Alphabet Pointer:" << endl;
            for (auto it = hashTable.begin(); it != hashTable.end(); ++it) {
                std::cout << it->first << ": ";
                for (auto& pair : it->second) {
                    std::cout << "(" << pair.first << ", " << pair.second << ") ";
                }
                std::cout << endl;
            }
        }
        
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Goodbye!" << endl;
                return 0;
            case 1:
                if (currentPageNum < totalPages - 1) {
                    currentPageNum++;
                }
                break;
            case 2:
                if (currentPageNum > 0) {
                    currentPageNum--;
                }
                break;
            case 3:
                std::cout << "Enter page number: ";
                int pageNum;
                std::cin >> pageNum;
                if (pageNum >= 1 && pageNum <= totalPages) {
                    currentPageNum = pageNum - 1;
                }
                break;
            case 4:
                showAlphabetPointer = !showAlphabetPointer;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
