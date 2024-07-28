#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Job
{
    string jobName;
    int deadLine;
    int profit;
};

bool comparison(Job a, Job b) {
    return (a.profit > b.profit);
}

void createJobSequence(Job jobs[], int n) {
    // sort the jobs in descening order of their profits
    sort(jobs, jobs + n, comparison);

    // finding max deadline
    int maxDeadLine = jobs[0].deadLine;
    for (int i=1;i<n;i++) {
        if (maxDeadLine < jobs[i].deadLine) {
            maxDeadLine = jobs[i].deadLine;
        }
    }

    maxDeadLine += 1;

    // for (int i=0;i<n;i++) {
    //     cout << jobs[i].jobName << " " << jobs[i].profit << " " << jobs[i].deadLine << "\n";
    // }

    // iterate all jobs and assign it to free job slot
    string ans[maxDeadLine];
    bool slot[maxDeadLine];

    for (int i=0;i<maxDeadLine;i++) {
        slot[i] = false;
    }

    for (int i=0;i<n;i++) {
        int k = min(maxDeadLine, jobs[i].deadLine);
        while (k >= 1) {
            // cout << k << "\n";
            if (slot[k] == false) {
                slot[k] = true;
                ans[k] = jobs[i].jobName;
                break;
            }
            k = k - 1;
        }
        // cout << "completed for i = " << i << "\n";
    }

    cout << "Sequence:\n";

    for (int i=0;i<maxDeadLine;i++) {
        cout << ans[i] << " ";
    }
}

int main() {
    cout << "Job sequencing problem\n";

    Job jobs[] = {
        {"J1", 1, 3},
        {"J2", 3, 5},
        {"J3", 4, 20},
        {"J4", 3, 18},
        {"J5", 2, 0},
        {"J6", 1, 6},
        {"J7", 2, 30},
    };

    int n = 7;
    createJobSequence(jobs, n);
}
