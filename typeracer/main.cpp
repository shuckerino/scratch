#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "Stopwatch.hpp"

#define WORD_COUNT 20

int main(){
    std::ifstream word_file;
    word_file.open("words.txt");

    std::vector<std::string> file_content;

    stopwatch::Stopwatch sw1;
    sw1.start();
    // Save all words into vector
    if (word_file.is_open()){
        std::string current_line;
        while (word_file) {
            std::getline(word_file, current_line);
            file_content.push_back(current_line);
        }
    }
    auto duration_ms = sw1.elapsed<stopwatch::ms>();
    std::cout << "Vector creation took: " << duration_ms << " ms." << std::endl;
   
    // Generate random sequence of words
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> distrib(0, file_content.size() - 1);
    std::string random_text;
    for (int i = 0; i < WORD_COUNT; i++){
        int random_num = distrib(gen);
        random_text += file_content[random_num];
        random_text += " ";
        // std::cout << file_content[random_num] << " ";
    }
    std::cout << "Generated text:\n" << random_text << std::endl;

    // Read user input into string
    std::string user_input;
    stopwatch::Stopwatch sw2;
    std::cin >> user_input;
    
    // Print results
    // TODO: print the difference in color
    std::cout << user_input;

    // Print the stats
    std::cout << std::endl;
    auto duration_s = sw2.elapsed<stopwatch::s>();
    std::cout << "Duration: " << duration_s << std::endl;
    std::cout << "WPM: " << WORD_COUNT * (60 / duration_s) << std::endl; 

    return 0;
}
