#include <iostream>
#include <climits>
using namespace std;

struct P {
    int pid, bt, at, pr;
    int ct, wt, tat, done;
};

/* ================= DISPLAY ================= */
void display(P p[], int n) {
    float awt = 0, atat = 0;

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].pr << "\t" << p[i].ct << "\t"
             << p[i].tat << "\t" << p[i].wt << endl;

        awt += p[i].wt;
        atat += p[i].tat;
    }

    cout << "\nAvg WT = " << awt/n;
    cout << "\nAvg TAT = " << atat/n << endl;
}

/* ================= RESET ================= */
void reset(P p[], int n) {
    for(int i = 0; i < n; i++) {
        p[i].ct = p[i].wt = p[i].tat = 0;
        p[i].done = 0;
    }
}

/* ================= FCFS ================= */
void fcfs(P p[], int n) {
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        time = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }
}

/* ================= SJF (Non-Preemptive) ================= */
void sjf(P p[], int n) {
    int completed = 0, time = 0;

    while(completed < n) {
        int idx = -1;
        int minBT = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !p[i].done && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if(idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;

        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;

        p[idx].done = 1;
        completed++;
    }
}

/* ================= SRTF (Preemptive SJF) ================= */
void srtf(P p[], int n) {
    int time = 0, completed = 0;
    int rem[20];

    for(int i=0;i<n;i++) rem[i] = p[i].bt;

    while(completed != n) {
        int idx = -1, min = INT_MAX;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && rem[i] > 0 && rem[i] < min) {
                min = rem[i];
                idx = i;
            }
        }

        if(idx == -1) { time++; continue; }

        rem[idx]--;
        time++;

        if(rem[idx] == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
}

/* ================= Priority (Non-Preemptive) ================= */
void priorityNP(P p[], int n) {
    int completed = 0, time = 0;

    while(completed < n) {
        int idx = -1, best = INT_MAX;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && !p[i].done && p[i].pr < best) {
                best = p[i].pr;
                idx = i;
            }
        }

        if(idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;

        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;

        p[idx].done = 1;
        completed++;
    }
}

/* ================= Priority (Preemptive) ================= */
void priorityP(P p[], int n) {
    int time = 0, completed = 0;
    int rem[20];

    for(int i=0;i<n;i++) rem[i] = p[i].bt;

    while(completed != n) {
        int idx = -1, best = INT_MAX;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && rem[i] > 0 && p[i].pr < best) {
                best = p[i].pr;
                idx = i;
            }
        }

        if(idx == -1) { time++; continue; }

        rem[idx]--;
        time++;

        if(rem[idx] == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
}

/* ================= ROUND ROBIN ================= */
void roundRobin(P p[], int n, int tq) {
    int rem[20], time = 0, done = 0;

    for(int i=0;i<n;i++) rem[i] = p[i].bt;

    while(done != n) {
        done = 0;

        for(int i=0;i<n;i++) {
            if(rem[i] > 0) {
                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt  = p[i].tat - p[i].bt;

                    done++;
                }
            } else done++;
        }
    }
}

/* ================= MAIN ================= */
int main() {
    P p[20];
    int n, ch, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    for(int i=0;i<n;i++) {
        p[i].pid = i+1;
        cout << "Enter AT BT PR for P" << i+1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }

    while(true) {
        cout << "\n1.FCFS 2.SJF 3.SRTF 4.Priority NP 5.Priority P 6.RR 7.Exit\n";
        cin >> ch;

        reset(p,n);

        if(ch==1){ fcfs(p,n); display(p,n); }
        else if(ch==2){ sjf(p,n); display(p,n); }
        else if(ch==3){ srtf(p,n); display(p,n); }
        else if(ch==4){ priorityNP(p,n); display(p,n); }
        else if(ch==5){ priorityP(p,n); display(p,n); }
        else if(ch==6){ cout<<"Enter TQ: "; cin>>tq; roundRobin(p,n,tq); display(p,n); }
        else break;
    }
}

/*Sample Input : 
Number of processes = 4

P1: AT=0  BT=5  PR=2
P2: AT=1  BT=3  PR=1
P3: AT=2  BT=8  PR=4
P4: AT=3  BT=6  PR=3
https://github.com/omkar1kadam/OSL-Lab/tree/main/Main_Practical*/
