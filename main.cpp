#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

# define MODE 0     // 0 or 1

int main() {
    auto start = std::chrono::steady_clock::now();
    vector<int> vector[100000];
    int index = 0;
#if MODE == 0
    ifstream ifs("bbs-test-input.txt", ios::in);
#elif MODE == 1
    ifstream ifs("bbs-test-big-input.txt", ios::in);
#endif
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else {
        int dist;
        int price;
        while (ifs >> dist >> price) {
            vector[index].push_back(dist);
            vector[index].push_back(price);
            index++;
        }
        ifs.close();
    }
    ifs.close();

    for (int i = 0; i < index; i++) {
        for (int j = 0; j < index; j++) {
            if (vector[i][0] <= vector[j][0] && vector[i][1] <= vector[j][1] && i != j && vector[j][0] >= 0 &&
                vector[j][1] >= 0 && vector[i][0] >= 0 && vector[i][1] >= 0) {
                vector[i].push_back(vector[j][0]);
                vector[i].push_back(vector[j][1]);
                vector[j][0] = -1;
                vector[j][1] = -1;
            }
        }
    }
    ofstream ofs;
#if MODE == 0
    ofs.open("bbs-test-output.txt");
#elif MODE == 1
    ofs.open("bbs-test-big-output.txt");
#endif
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
    } else {
        for (int k = 0; k < index; k++) {
            if (vector[k][0] >= 0) {
                ofs << vector[k][0] << " ";
                ofs << vector[k][1] << " ";
                ofs << endl;
            }
        }
        ofs.close();
    }

    auto end = chrono::steady_clock::now();
    cout << endl << endl << "Time taken: " << chrono::duration<double>(end - start).count() << " s"
         << endl;
}
