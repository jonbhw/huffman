#include "encoder.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
  freq_hashmap char_freq = text_file_to_frequency_hashmap("a.txt");
  return 0;
}

freq_hashmap text_file_to_frequency_hashmap(char filename[]) {
  freq_hashmap char_freq;
  char ch;
  ifstream fin;
  fin.open(filename);

  while (fin.get(ch)) {
    char_freq[ch]++;
  }

  fin.close();
  return char_freq;
}