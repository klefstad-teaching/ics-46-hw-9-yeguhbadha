#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "Error with words: " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d)
{
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) return false;

    int diff_count = 0;

    if (len1 == len2) {
        // Direct comparison for words of equal length
        for (int i = 0; i < len1; ++i) {
            if (tolower(str1[i]) != tolower(str2[i])) {
                if (++diff_count > d) return false;
            }
        }
        return true;
    }

    // Ensure str1 is the shorter word
    const string& shorter = (len1 < len2) ? str1 : str2;
    const string& longer = (len1 < len2) ? str2 : str1;

    int i = 0, j = 0;
    while (i < shorter.length() && j < longer.length()) {
        if (tolower(shorter[i]) != tolower(longer[j])) {
            if (++diff_count > d) return false;
            ++j;  // Skip the extra character in the longer word
        } else {
            ++i;
            ++j;
        }
    }
    return true;
}


bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word) { return {begin_word}; }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);
    // if target word is in word list
    if (word_list.find(end_word) != word_list.end()) 
    {
        while (ladder_queue.empty() == false)
        {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();

            string last_word = ladder.back();
            if (last_word == end_word) { return ladder; }
            for (string word : word_list)
            {
                if (is_adjacent(last_word, word))
                {
                    if (visited.find(word) == visited.end())
                    {
                        visited.insert(word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(word);

                        if (word == end_word) { return new_ladder; }

                        ladder_queue.push(new_ladder);
                    }
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream infile(file_name);
    if (!infile.is_open()) {
        cerr << "Error: failed to open file";
        return;
    }

    string word;
    while (infile >> word)
    {
        string lower_word = word;
        transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
        word_list.insert(lower_word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.size() == 0)
    {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (int i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder()
{
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

    my_assert(generate_word_ladder("were", "were", word_list).size() == 1);
}