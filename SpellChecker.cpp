/*
Problem: Spell Checker Problem

Write a spell-checker class that stores a set of words, W, in a hash table and implements a function, spellCheck(s), which performs a spell check on the string s with respect to the set of words, W. If s is in W, then the call to spellCheck(s) returns an iterable collection that contains only s, since it is assumed to be spelled correctly in this case. Otherwise, if s is not in W, then the call to spellCheck(s) returns a list of every word in W that could be a correct spelling of s. Your program should be able to handle all the common ways that s might be a misspelling of a word in W, including swapping adjacent characters in a word, inserting a single character inbetween two adjacent characters in a word, deleting a single character from a word, and replacing a character in a word with another character.

Project assessment and marks:

Correction of the string that exactly match with words according to the number of characters with miss spelled of only one character. 5 Marks
      Example:

      User Input: tast

     Program suggestion: test, task, past

Correction of a string that will match with all words from the right, left, or middle of the words. You can limit the maximum word length to 6 characters. 5 Marks
     Example:

    User Input: te

    Program suggestion: tea, teer, test, winter, prate, mute
*/

#include <bits/stdc++.h>
#define MAX_WORDS 10
// Make sure to include a wordlist named words.txt
// which contains words separated by newline.
// Here's a good one: curl http://www.mieliestronk.com/corncob_lowercase.txt > 
words.txt
using namespace std;
bool contains(list<string>* candidates, string word) {
  for (auto candidate : *candidates)
    if (candidate == word)
      return true;
  return false;
}
class HashTable {
  int buckets;
  list<string>* table;
public:
  HashTable(int buckets) {
    this->buckets = buckets;
    this->table = new list<string>[buckets];
  }
  // djb2 hashing function
  int hash(std::string input) {
    unsigned int key = 5381;
    int length = input.length();
    for (int i = 0; i < length; i++)
      key = key * 33 ^ input[i];
    return key % (this->buckets);
  }
  void insert(string key) {
    int index = hash(key);
    this->table[index].push_back(key);
  }
  bool exists(string key) {
    int index = hash(key);
    for (auto word = this->table[index].begin(); word != this->table[index].end(); 
word++)
      if (*word == key)
        return true;
    return false;
  }
  list<string> spell_check(string word) {
    list<string> candidates;
    int length = word.length();
    
    // Check swapping adjacent characters
    for (int i = 0; i < length; i++) {
      string candidate = word;
      swap(candidate[i], candidate[i + 1]);
      if (candidates.size() < MAX_WORDS && exists(candidate) && !
contains(&candidates, candidate))
        candidates.push_back(candidate);
    }
    
    // Check insert single character inbetween characters
    for (int i = 1; i < length; i++) {
      for (auto letter : "abcdefghijklmnopqrstuvwxyz") {
        string candidate = word;
        candidate.insert(i, 1, letter);
        if (candidates.size() < MAX_WORDS && exists(candidate) && !
contains(&candidates, candidate))
          candidates.push_back(candidate);
      }
    }
    
    // Check deleting a single characters from a word
    for (int i = 0; i < length; i++) {
      string candidate = word;
      candidate.erase(i, 1);
      if (candidates.size() < MAX_WORDS && exists(candidate) && !
contains(&candidates, candidate))
        candidates.push_back(candidate);
    }
    
    // Check replacing a character in a word
    for (int i = 0; i < length; i++) {
      string candidate = word;
      for (auto letter : "abcdefghijklmnopqrstuvwxyz") {
        if (letter == candidate[i])
          continue;
        candidate[i] = letter;
        if (candidates.size() < MAX_WORDS && exists(candidate) && !
contains(&candidates, candidate))
          candidates.push_back(candidate);
      }
    }
    // Check match with all words from the right, left, or middle of the words
    for (int bucket = 0; bucket < this->buckets; bucket++)
      for (auto candidate : this->table[bucket])
        if (candidates.size() < MAX_WORDS && candidate.find(word) != 
std::string::npos && !contains(&candidates, candidate))
          candidates.push_back(candidate);
    return candidates;
  }
};
int main() {
  // Create dictionary
  HashTable dictionary = HashTable(1024);
  // Initialize with words
  ifstream file("words.txt");
  if (file.is_open()) {
    string word;
    while (file >> word)
      dictionary.insert(word);
    file.close();
  }
  // Ask user for input
  cout << "Word: ";
  string word;
  cin >> word;
  // Check spelling of word
  if (!dictionary.exists(word)) {
    list<string> candidates = dictionary.spell_check(word);
    // For this part: `If s is in W, then the call to spellCheck(s) returns an 
iterable
    //                 collection that contains only s, since it is assumed to be 
spelled
    //                 correctly in this case`.
    // We check if the work doesn't exist and spellcheck in that case instead.
    if (candidates.size() == 0)
      return 0;
    cout << "'" << word << "' is incorrect, did you mean ";
    int i = 0;
    for (auto word : candidates) {
      cout << word;
      if (++i < candidates.size())
        cout << ", ";
    }
    cout << "?" << endl; 
  }
  return 0;
}