#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Process {
    string name;
    int bt, wt, tat;
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin || !fout) {
        cout << "File error.\n";
        return 1;
    }

    int n;
    fin >> n;
    vector<Process> p(n);

    for (int i = 0; i < n; i++)
        fin >> p[i].name >> p[i].bt;

    p[0].wt = 0;
    for (int i = 1; i < n; i++)
        p[i].wt = p[i-1].wt + p[i-1].bt;

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    fout << "Process\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        fout << p[i].name << "\t" << p[i].bt << "\t" << p[i].wt << "\t" << p[i].tat << "\n";

    fout << "\nAverage Waiting Time: " << totalWT / n;
    fout << "\nAverage Turnaround Time: " << totalTAT / n << "\n";

    // Gantt Chart
    fout << "\nGantt Chart:\n";
    for (int i = 0; i < n; i++) {
        fout << p[i].name;
        if (i + 1 < n) {
            fout << " -> ";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
