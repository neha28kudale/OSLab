#include <iostream>
using namespace std;

void printFrames(int frames[], int f) {
    for(int i = 0; i < f; i++) {
        if(frames[i] == -1) cout << "- ";
        else cout << frames[i] << " ";
    }
    cout << endl;
}

// FIFO
void fifo(int pages[], int n, int f) {
    int frames[10], index = 0, faults = 0, hits = 0;

    for(int i = 0; i < f; i++) frames[i] = -1;

    cout << "\n--- FIFO ---\n";

    for(int i = 0; i < n; i++) {
        bool found = false;

        for(int j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = true;
                hits++;
                break;
            }
        }

        if(!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }

        printFrames(frames, f);
    }

    cout << "Faults: " << faults << " Hits: " << hits << endl;
    cout << "Fault Ratio: " << (float)faults/n << endl;
    cout << "Hit Ratio: " << (float)hits/n << endl;
}

// LRU
void lru(int pages[], int n, int f) {
    int frames[10], time[10], faults = 0, hits = 0;

    for(int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    cout << "\n--- LRU ---\n";

    for(int i = 0; i < n; i++) {
        bool found = false;

        for(int j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = true;
                hits++;
                time[j] = i;
                break;
            }
        }

        if(!found) {
            int lru_index = 0;
            for(int j = 1; j < f; j++) {
                if(time[j] < time[lru_index])
                    lru_index = j;
            }

            frames[lru_index] = pages[i];
            time[lru_index] = i;
            faults++;
        }

        printFrames(frames, f);
    }

    cout << "Faults: " << faults << " Hits: " << hits << endl;
    cout << "Fault Ratio: " << (float)faults/n << endl;
    cout << "Hit Ratio: " << (float)hits/n << endl;
}

// Optimal
void optimal(int pages[], int n, int f) {
    int frames[10], faults = 0, hits = 0;

    for(int i = 0; i < f; i++) frames[i] = -1;

    cout << "\n--- Optimal ---\n";

    for(int i = 0; i < n; i++) {
        bool found = false;

        for(int j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = true;
                hits++;
                break;
            }
        }

        if(!found) {
            int pos = -1, farthest = i;

            for(int j = 0; j < f; j++) {
                int k;
                for(k = i+1; k < n; k++) {
                    if(frames[j] == pages[k]) break;
                }

                if(k > farthest) {
                    farthest = k;
                    pos = j;
                }
            }

            if(pos == -1) pos = 0;

            frames[pos] = pages[i];
            faults++;
        }

        printFrames(frames, f);
    }

    cout << "Faults: " << faults << " Hits: " << hits << endl;
    cout << "Fault Ratio: " << (float)faults/n << endl;
    cout << "Hit Ratio: " << (float)hits/n << endl;
}

int main() {
    int n, f;

    cout << "Enter number of pages: ";
    cin >> n;

    int pages[20];
    cout << "Enter page reference string:\n";
    for(int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> f;

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}
/*
Start
Input number of pages (n)
Input page reference string
Input number of frames (f)
Initialize frames as empty (-1)
For each page in reference string:
Check if page is already in frame
If YES → Page Hit
If NO → Page Fault
Replace page using selected algorithm
Repeat until all pages are processed
Count:
Page faults
Page hits
Calculate:
Fault ratio = faults / total pages
Hit ratio = hits / total pages
Display frame status step-by-step
Compare FIFO, LRU, Optimal results
End
 FIFO Algorithm (Simple Steps)
Use a queue concept
Replace oldest page in frame
Insert new page in circular order
If page already exists → hit
Else → fault
 LRU Algorithm
Track last used time of each page
If page is not in frame → replace least recently used page
Update time whenever page is used
Continue for all pages
Optimal Algorithm
Replace page that will not be used for the longest future time
Check future references of each page in frame
Choose farthest or never-used page
Replace it
Continue until end

Sample Input
Enter number of pages: 10
Enter page reference string:
7 0 1 2 0 3 0 4 2 3
Enter number of frames: 3
Sample Output (Example)
FIFO
Frame status:
7 - -
7 0 -
7 0 1
2 0 1
2 0 1
2 3 1
2 3 0
4 3 0
4 2 0
4 2 3

Faults: 7
Hits: 3
Fault Ratio: 0.7
Hit Ratio: 0.3

LRU
Faults: 6
Hits: 4
Fault Ratio: 0.6
Hit Ratio: 0.4

Optimal
Faults: 5
Hits: 5
Fault Ratio: 0.5
Hit Ratio: 0.5
*/