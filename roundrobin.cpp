#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    string name;
    int bt, rt, wt = 0, tat = 0, ct = 0;
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cout << "Error opening input.txt\n";
        return 1;
    }
    if (!fout) {
        cout << "Error opening output.txt\n";
        return 1;
    }

    int n;
    fin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        fin >> p[i].name >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    int tq;
    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    vector<string> gantt;
    vector<int> timeline;

    for (int i = 0; i < n; i++)
        q.push(i);

    int time = 0;
    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (p[i].rt > 0) {
            gantt.push_back(p[i].name);
            timeline.push_back(time);

            if (p[i].rt > tq) {
                time += tq;
                p[i].rt -= tq;
                q.push(i);
            } else {
                time += p[i].rt;
                p[i].ct = time;
                p[i].rt = 0;
            }
        }
    }
    timeline.push_back(time);

    // Calculate WT and TAT
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    // Output to file
    fout << "Process\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        fout << p[i].name << "\t" << p[i].bt << "\t" << p[i].wt << "\t" << p[i].tat << "\n";
    }

    fout << "\nAverage Waiting Time: " << totalWT / n;
    fout << "\nAverage Turnaround Time: " << totalTAT / n;

    fout << "\n\nGantt Chart:\n|";
    for (auto &g : gantt)
        fout << " " << g << " |";

    fout << "\n" << timeline[0];
    for (int i = 1; i < timeline.size(); i++)
        fout << "   " << timeline[i];

    fout.close(); // IMPORTANT
    fin.close();  // Optional, but clean
    return 0;
}
