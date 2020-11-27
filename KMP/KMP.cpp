#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief KMP algorithm: Generate PMT sequence.
 * 
 * @param p Search pattern.
 * @return vector<int> PMT sequence.
 */
vector<int> genPMT(string p) {
    vector<int> PMT{ 0 };       /** PMT[0] = 0 always stand up. */
    int x = 1;                  /** Index of pattern string */
    int now = 0;

    while(x < p.length()) {
        if(p[now] == p[x]) {    /** If p[now] == p[x], go step forward */
            now++;
            x++;
            PMT.push_back(now);
        }
        else if(now)            /** Failed map, go to the last map index of p */
            now = PMT[now - 1];
        else {                  /** p[0] failed map, no intersection */
            PMT.push_back(0);
            x++;
        }
    }
    return PMT;
}

/**
 * @brief KMP algorithm: A string-searching algorithm.
 * 
 * @param s Source string.
 * @param p Search pattern.
 * @return int The first index of s's substring, which equals to p. If not found, return -1.
 */
int KMP(string s, string p) {
    int tar = 0;                    /** Index of source string s */
    int pos = 0;                    /** Index of pattern string p */

    vector<int> PMT = genPMT(p);    /** Pattern p's PMT sequence */

    while(tar < s.length()) {
        if(s[tar] == p[pos]) {      /** If s[tar] == p[pos], go step forward */
            tar++;
            pos++;
        }
        else if(pos)                /** Failed map, go to the last map index of p */
            pos = PMT[pos - 1];
        else                        /** pos[0] failed map, go to the next s's index */
            tar++;

        if(pos == p.length())       /** Mapping success */
            return tar - pos;
    }
}

int main(int argc, char** argv) {
    string s = "ababcabababca";
    string p = "abababca";

    int res = KMP(s, p);
    cout << res << endl;

    return 0;
}