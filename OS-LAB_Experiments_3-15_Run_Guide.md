# OS-LAB Experiments 3–15 Run Guide

Run each program in Terminal from `~/Desktop/OS-LAB`. The report contains your supplied Mac screenshots and clearly labeled illustrative output text where a Mac screenshot has not been supplied. Experiment 13 is one experiment with one menu-driven program containing six disk scheduling algorithms.

## Experiment 9

Priority:

```sh
gcc Experiment-09/priority.c -Wall -Wextra -Wpedantic -o Experiment-09/priority
./Experiment-09/priority
```

Enter `4`, then task burst/priority pairs `5 3`, `3 1`, `8 4`, `6 2`. Expected order: P2, P4, P1, P3. Average WT 6.50; average TAT 12.00.

Round Robin:

```sh
gcc Experiment-09/round_robin.c -Wall -Wextra -Wpedantic -o Experiment-09/round_robin
./Experiment-09/round_robin
```

Enter `3`; pairs `0 5`, `0 3`, `0 8` (arrival time then burst time); quantum `2`. Expected completion times: P1 12, P2 9, P3 16. Average WT 7.00; average TAT 12.33.

## Experiment 10

```sh
gcc Experiment-10/fifo.c -Wall -Wextra -Wpedantic -o Experiment-10/fifo
./Experiment-10/fifo
```

Enter reference count `8`, frames `3`, then `1 2 3 1 4 5 2 1`. Expected: 7 faults, 1 hit.

## Experiment 11

Run `python3 Experiment-11/lru.py` and `python3 Experiment-11/lfu.py` separately. For each, enter frames `3` and reference string `1 2 3 1 4 5 2 1`. Expected LRU: 7 faults, 1 hit. Expected LFU with least-recently-used tie-breaking: 6 faults, 2 hits.

## Experiment 12

Run `python3 Experiment-12/best_fit.py` and `python3 Experiment-12/worst_fit.py` separately. For each, enter blocks `100 500 200 300 600` and processes `212 417 112 426`.

Expected Best Fit: P1→B4, P2→B2, P3→B3, P4→B5; remaining block space 100, 83, 88, 88, 174.

Expected Worst Fit: P1→B5, P2→B2, P3→B5, P4 not allocated; remaining space 100, 83, 200, 300, 276.

## Experiment 13

Experiment 13 is one menu-driven program containing all six algorithms. Run `python3 Experiment-13/disk_scheduling.py`, choose FCFS, SSTF, SCAN, C-SCAN, LOOK, or C-LOOK, then enter request queue `98 183 37 122 14 124 65 67`, head `53`, low `0`, and high `199`. For SCAN, C-SCAN, LOOK, and C-LOOK, enter direction `right`.

Expected total movement in cylinders: FCFS 640; SSTF 236; SCAN 331; C-SCAN 382; LOOK 299; C-LOOK 322.

## Experiment 14

Sequential allocation:

```sh
gcc Experiment-14/sequential_allocation.c -Wall -Wextra -Wpedantic -o Experiment-14/sequential_allocation
./Experiment-14/sequential_allocation
```

Enter 2 files, then `midterm 3` and `final 2`. Expected blocks: midterm 8–10, final 11–12.

Indexed allocation (C++):

```sh
g++ Experiment-14/indexed_allocation.cpp -Wall -Wextra -Wpedantic -o Experiment-14/indexed_allocation
./Experiment-14/indexed_allocation
```

Enter 2 files; `midterm 0 3`, data blocks `1 2 3`; then `final 4 2`, data blocks `5 6`. Expected index/data mappings: 0→1,2,3 and 4→5,6.

## Experiment 15

For each program, compile with the matching `gcc` command in `README.md`, then run it.

Single-level directory: enter directory `projects`; choose 1 and add `report.pdf`; choose 2 to list; choose 3 and search `report.pdf`; choose 5 to exit. Expected list/search show the file.

Two-level directory: create directories `alice` and `bob` (choice 1 each); add `project.c` to each (choice 2); list each (choice 3); choose 6 to exit. The same file name is allowed in different user directories.

Capture the terminal output after every program completes. Do not alter the screenshots; store them with clear names such as `outputs/Experiment-10/fifo-run.png`.
