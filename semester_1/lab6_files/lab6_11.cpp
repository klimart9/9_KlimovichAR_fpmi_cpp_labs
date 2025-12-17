#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> split_line(const std::string& line) {
    std::vector<std::string> words;
    std::string word;

    int line_len = line.length();
    for (int i = 0; i < line_len; i++) {
        if (line[i] != ' ') {
            word += line[i];
        }
        else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
            while (i + 1 < line_len && line[i + 1] == ' ') {
                i++;
            }
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

int find_min_word_length(const std::vector<std::string>& words) {
    if (words.empty()) return 1;

    int min_length = 1000000;
    int words_count = words.size();
    for (int i = 0; i < words_count; i++) {
        int word_len = words[i].length();
        if (word_len < min_length) {
            min_length = word_len;
        }
    }
    return min_length;
}

int find_max_word_length(const std::vector<std::string>& words) {
    if (words.empty()) return 1;

    int max_length = 0;
    int words_count = words.size();
    for (int i = 0; i < words_count; i++) {
        int word_len = words[i].length();
        if (word_len > max_length) {
            max_length = word_len;
        }
    }
    return max_length;
}

std::string find_first_word_of_length(const std::vector<std::string>& words, int length) {
    int words_count = words.size();
    for (int i = 0; i < words_count; i++) {
        if (words[i].length() == length) {
            return words[i];
        }
    }
}
void swap_lines(std::vector<std::string>& lines, int line1, int line2) {
    std::string temp = lines[line1];
    lines[line1] = lines[line2];
    lines[line2] = temp;
}



int main() {
    try {
        setlocale(LC_ALL, "Russian");
        std::ifstream input_file("input.txt");
        if (!input_file.is_open()) {
            throw "Cant open file input.txt";
        }
        if(input_file.peek() == EOF) {
            throw "File is empty";
        }

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(input_file, line)) {
            lines.push_back(line);
        }

        input_file.close();

        

        int global_min_length = 1000000;
        int global_max_length = 0;
        int min_line_index = -1;
        int max_line_index = -1;
        std::string min_word, max_word;

        int lines_count = lines.size();
        for (int i = 0; i < lines_count; i++) {
            std::vector<std::string> words = split_line(lines[i]);

            if (words.empty()) continue;

            int current_min_length = find_min_word_length(words);
            int current_max_length = find_max_word_length(words);

            std::string current_min_word = find_first_word_of_length(words, current_min_length);
            std::string current_max_word = find_first_word_of_length(words, current_max_length);

            if (current_min_length < global_min_length) {
                global_min_length = current_min_length;
                min_line_index = i;
                min_word = current_min_word;
            }

            if (current_max_length > global_max_length) {
                global_max_length = current_max_length;
                max_line_index = i;
                max_word = current_max_word;
            }
        }

        std::cout << "Found lines:" << std::endl;

        if (min_line_index != -1) {
            std::cout << "Line with shortest word (length " << global_min_length << "):" << std::endl;
            std::cout << "Line index: " << min_line_index + 1 << std::endl;
            std::cout << "Word: \"" << min_word << "\"" << std::endl;
            std::cout << "Line content: " << lines[min_line_index] << std::endl;
        }

        if (max_line_index != -1) {
            std::cout << "\nLine with longest word (length " << global_max_length << "):" << std::endl;
            std::cout << "Line index: " << max_line_index + 1 << std::endl;
            std::cout << "Word: \"" << max_word << "\"" << std::endl;
            std::cout << "Line content: " << lines[max_line_index] << std::endl;
        }

        if (min_line_index != -1 && max_line_index != -1 && min_line_index != max_line_index) {
            std::cout << "Swapping lines " << min_line_index + 1 << " and " << max_line_index + 1 << std::endl;
            swap_lines(lines, min_line_index, max_line_index);
            std::cout << "\nResult after swap:" << std::endl;

            for (int i = 0; i < lines_count; i++) {
                std::cout << "Line " << i + 1 << ": " << lines[i] << std::endl;
            }


        }
        else if (min_line_index == max_line_index && min_line_index != -1) {
            std::cout << "Shortest and longest words are in the same line." << std::endl;
            std::cout << "No need to swap lines." << std::endl;
        }
        else {
            std::cout << "Could not find lines to swap." << std::endl;
        }
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
    }

    return 0;
}
