#include<bits/stdc++.h>
using namespace std;

struct Process {
    string name;
    int bt, priority, wt, tat;
};

bool compare(Process a, Process b) {
    return a.priority < b.priority;
}

int main() {
    ifstream fin("input2.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;
    vector<Process> p(n);

    for (int i = 0; i < n; i++)
        fin >> p[i].name >> p[i].bt >> p[i].priority;

    sort(p.begin(), p.end(), compare);

    p[0].wt = 0;
    for (int i = 1; i < n; i++)
        p[i].wt = p[i - 1].wt + p[i - 1].bt;

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    fout << "Process\t\tBT\t\tPriority\t\tWT\t\tTAT\n";
    for (auto &pr : p)
        fout << pr.name << "\t\t\t" << pr.bt << "\t\t\t" << pr.priority << "\t\t\t" << pr.wt << "\t\t\t" << pr.tat << "\n";

    fout << "\nAverage Waiting Time: " << totalWT / n;
    fout << "\nAverage Turnaround Time: " << totalTAT / n << "\n";

    fout << "\nGantt Chart:\n";
    for (int i = 0; i < n; i++) {
        fout << p[i].name;
        if (i + 1 < n) {
            fout << " -> ";
        }
    }

    

    return 0;
}
