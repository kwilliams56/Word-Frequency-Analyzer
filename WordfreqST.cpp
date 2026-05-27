/*
 Name: Kravion Williams
 Email: kwilliams56@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 2
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <chrono>
#include "ST.hpp"

std::string normalize(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(c);
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    ST<std::string, int> freqTable;
    std::string word;

    auto start = std::chrono::high_resolution_clock::now();

    // === word frequency logic ===
    while (file >> word) {
        word = normalize(word);
        if (!word.empty())
            freqTable[word]++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Distinct words: " << freqTable.size() << std::endl;
    std::cout << "Time taken: " << duration << " ms" << std::endl;

    // Optional: print top 10 frequent words
    auto vec = freqTable.toVector();
    std::sort(vec.begin(), vec.end(), [](auto& a, auto& b){ return a.second > b.second; });

    std::cout << "\nTop 10 Words:\n";
    for (int i = 0; i < 10 && i < (int)vec.size(); ++i)
        std::cout << vec[i].first << ": " << vec[i].second << std::endl;

    return 0;
}
