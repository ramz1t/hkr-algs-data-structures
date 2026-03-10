#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

const int ROW_DELTA[] = { 0,  0,  1, -1,  1,  1, -1, -1};
const int COL_DELTA[] = { 1, -1,  0,  0,  1, -1,  1, -1};
const string DIR_NAME[] = {"right","left","down","up","down-right","down-left","up-right","up-left"};
const int NUM_DIRECTIONS = 8;

int main() {
    vector<string> grid = {
        "this",
        "wats",
        "oahg",
        "fgdt"
    };
    int numRows = (int)grid.size(), numCols = (int)grid[0].size();

    vector<string> dictionary = {"this", "two", "fat", "that"};

    unordered_set<string> wordSet(dictionary.begin(), dictionary.end());
    unordered_set<string> prefixSet;
    for (const string& word : dictionary)
        for (int len = 1; len <= (int)word.size(); len++)
            prefixSet.insert(word.substr(0, len));

    cout << "=== Task 3: Word Puzzle ===\n\nGrid:\n";
    for (int row = 0; row < numRows; row++) {
        cout << "  ";
        for (char letter : grid[row]) cout << letter << " ";
        cout << "\n";
    }
    cout << "\nWords: ";
    for (const string& word : dictionary) cout << word << " ";
    cout << "\n\nFound:\n";

    for (int startRow = 0; startRow < numRows; startRow++) {
        for (int startCol = 0; startCol < numCols; startCol++) {
            for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
                string candidate;
                int row = startRow, col = startCol;
                while (row >= 0 && row < numRows && col >= 0 && col < numCols) {
                    candidate += grid[row][col];
                    if (!prefixSet.count(candidate)) break;
                    if (wordSet.count(candidate))
                        cout << "  \"" << candidate << "\" starts at (" << startRow+1 << "," << startCol+1
                             << ") going " << DIR_NAME[dir] << "\n";
                    row += ROW_DELTA[dir];
                    col += COL_DELTA[dir];
                }
            }
        }
    }

    return 0;
}
