# Educational-Practice

Just simple C++ program for educational practice. All input and output text on russian language.

It can be used for count words from input text and sort them alphabetically. Result files contain sorted word array, and analysis - time of sort and the number of words starting with this letter.

In this project was used a comb sort. Code below.


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

Considering that the quick sort is performed on average for time O(n^2/2^p), tests of this algorithm on 10 different texts showed very good results that you can see in this graph below. It is based on data from analysis files.

![диаграмма](https://user-images.githubusercontent.com/89856595/171388134-2880f955-72eb-4cdf-a071-15a64e1e6109.PNG)

From this graph, we can conclude that the comb sorting algorithm written for this program has a time complexity, at best close to O(logn*n), at worst close to O(n^2). On average, quick sort has O(n^2/2^p) complexity. It also has minimal memory costs – O(1).
