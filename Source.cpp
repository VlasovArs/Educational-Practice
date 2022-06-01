/*Program for sort text on russian language with the help sorting with a comb, ignoring the numbers*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <map>
#include <ctime>
#include <chrono>

using namespace std;

int for_reading_a_file(vector<string>* words, string* start_text) {
    char ch;
    int i = 0, j = 0, count_words;
    string pathIn = "input1.txt";
    ifstream file_in;
    file_in.open(pathIn);

    // testing
    string tmp;

    // filling in char array our text.
    while (file_in.get(ch)) {
        (*start_text) += ch; // writing start text in result file.
        if (ch != ' ' && ch != '\n') {
            if (ch == 'Ё') ch = (char)((int)ch + 16);
            if (ch >= 'А' && ch <= 'Я') {
                ch = (char)((int)ch + 32);
            }
            if (ch >= 'а' && ch <= 'я' || ch == 'ё') {
                tmp += ch;
                j++;
            }
        }
        else {
            j = 0;
            if (tmp.length() > 0) {
                (*words)[i] = tmp;
                tmp.clear();
                i++;
            }
        }
    }if (tmp.length() > 0) {
        (*words)[i] = tmp;
        tmp.clear();
        i++;
    }
    file_in.close(); // close file with start text
    return count_words = i;
}


int sorting_with_a_comb(vector<string>* words, int count_words) { // function for sorting with a comb
    // засечь время сортировки
    int size = count_words;
    int jump = count_words;
    bool swapped = true;
    auto start_time = chrono::high_resolution_clock::now();
    while (jump > 1 || swapped)
    {
        if (jump > 1)
            jump = (int)(jump / 1.25);
        swapped = false;
        for (int i = 0; i + jump < size; i++)
            if ((*words)[i][0] > (*words)[i + jump][0])
                swap((*words)[i], (*words)[i + jump]), swapped = true; // Method swap changed words
    }
    auto end_time = chrono::high_resolution_clock::now();
    // конечное время
    auto search_time = chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    return search_time;
}


void for_writing_in_result_and_analysis_files(vector<string>* words, string* start_text, int count_words, long long search_time) {
    map <char, int> count_letter = {
    {'а', 0},
    {'б', 0},
    {'в', 0},
    {'г', 0},
    {'д', 0},
    {'е', 0},
    {'ё', 0},
    {'ж', 0},
    {'з', 0},
    {'и', 0},
    {'й', 0},
    {'к', 0},
    {'л', 0},
    {'м', 0},
    {'н', 0},
    {'о', 0},
    {'п', 0},
    {'р', 0},
    {'с', 0},
    {'т', 0},
    {'у', 0},
    {'ф', 0},
    {'х', 0},
    {'ц', 0},
    {'ч', 0},
    {'ш', 0},
    {'щ', 0},
    {'ъ', 0},
    {'ы', 0},
    {'ь', 0},
    {'э', 0},
    {'ю', 0},
    {'я', 0},
    };
    map <char, int> ::iterator iter = count_letter.begin();
    // output in analysis file
    bool letter_is_find = false;
    for (int i = 0; i < count_words - 1; i++) {
        letter_is_find = false;
        while (!letter_is_find) {
            if ((*words)[i][0] == iter->first) {
                iter->second++;
                letter_is_find = true;
            }
            iter++;
        }
        iter = count_letter.begin();
    }


    // output in result file
    string pathResult = "result1.txt";
    ofstream file_result;
    file_result.open(pathResult);

    // output in result file
    int i = 0;
    while (i < count_words - 1) {
        if (iter->second != 0) {
            for (int j = 0; j < iter->second; j++) {
                file_result << (*words)[i] << ' ';
                i++;
            }
            file_result << '\n';
        }
        iter++;
    }
    
    file_result.close();
    
    // output in analysis file
    string pathAnalysis = "analysis1.txt";
    ofstream file_analysis;
    file_analysis.open(pathAnalysis);

    file_analysis << "Введённый текст:" << '\n';

    file_analysis << (*start_text).c_str() << '\n'; // output start text

    file_analysis << "\nВариант 8: кириллица, по алфавиту, по возрастанию, игнорировать числа, сортировка расчёской.\n";
    
    file_analysis << "Количество слов: " << count_words << '\n';

    file_analysis << "Время сортировки: " << search_time << " миллисекунд" << '\n';

    file_analysis << "Статистика (количество слов на каждую букву алфавита)" << '\n';
    iter = count_letter.begin();
    iter++;
    for (int i = 1; i < 33; i++, iter++) {
        file_analysis << iter->first << " - " << iter->second << '\n';
        if (i == 6) { // add letter 'ё', because this letter in char have the smallest value and she in map went on first place.
            file_analysis << (count_letter.begin())->first << " - " << (count_letter.begin())->second << '\n';
        }
    }
    file_analysis.close();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    string start_text;
    vector<string> words (10000);
    int count_words = for_reading_a_file(&words, &start_text);
    long long search_time = sorting_with_a_comb(&words, count_words);
    for_writing_in_result_and_analysis_files(&words, &start_text, count_words, search_time);
    return 0;
}