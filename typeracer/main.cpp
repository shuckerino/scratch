#include <cstdio>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "Stopwatch.hpp"
#include <bits/stdc++.h>
#include <stdio.h>

#define WORD_COUNT 20


// Function to split the string to words in a vector
// separated by the delimiter
std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> v;
    if (!str.empty()) {
        int start = 0;
        do {
            // Find the index of occurrence
            int idx = str.find(delimiter, start);
            if (idx == std::string::npos) {
                break;
            }

            // If found add the substring till that
            // occurrence in the vector
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }

    return v;
}

int main(){
    std::ifstream word_file;
    word_file.open("words.txt");

    std::vector<std::string> file_content;

    // Save all words into vector
    if (word_file.is_open()){
        std::string current_line;
        while (word_file) {
            std::getline(word_file, current_line);
            file_content.push_back(current_line);
        }
    }
    // Generate random sequence of words
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> distrib(0, file_content.size() - 1);
    std::string random_text;
    for (int i = 0; i < WORD_COUNT; i++){
        int random_num = distrib(gen);
        random_text += file_content[random_num];
        random_text += " ";
    }
    std::cout << random_text << std::endl;

    // Read user input into string
    std::string user_input;
    stopwatch::Stopwatch sw2;

    // Cin only reads next token, so read entire line
    std::getline(std::cin, user_input);

    // std::cout << "User Input: " << user_input << std::endl;
    // Compare user text with random text (compare word for word)
    std::vector<std::string> random_text_vec = split(random_text, " ");
    std::vector<std::string> user_text_vec = split(user_input, " ");
    // std::cout << "Debug Info: " << std::endl;
    // for (std::string s: random_text_vec) {
    //    std::cout << s + " ";
    // }
    // std::cout << std::endl;
    // for (std::string s: user_text_vec) {
    //    std::cout << s + " ";
    // }
    // std::cout << std::endl;
    float count_of_matches = 0;
    for (int i = 0; i < user_text_vec.size(); i++) {
       if (i >= random_text_vec.size()){
           break;
       }
       if (random_text_vec[i] == user_text_vec[i]){
           count_of_matches++;
       }
    }

    // std::cout << "Count of matches: " << count_of_matches << std::endl;
    // Print the stats
    auto duration_s = sw2.elapsed<stopwatch::s>();
    std::cout << std::endl;
    std::cout << "Your stats: " << std::endl;
    std::cout << "Duration: " << duration_s << " sec" << std::endl;
    std::cout << "WPM: " << user_text_vec.size() * (60 / duration_s) << std::endl;
    // std::cout << "Matches: " << count_of_matches << " and texted word count: " << user_text_vec.size() << std::endl;
    std::cout << "Accuracy: " << count_of_matches / user_text_vec.size() * 100 << " %" << std::endl;

    return 0;
}
