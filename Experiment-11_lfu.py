#!/usr/bin/env python3
"""LFU page replacement; equal frequencies are broken by least recent use."""

def main():
    capacity = int(input("Number of frames: "))
    refs = list(map(int, input("Page reference string (space-separated): ").split()))
    if capacity <= 0 or not refs or any(x < 0 for x in refs):
        raise SystemExit("Frames must be positive and references non-negative.")
    frames, frequency, last_used, faults = [], {}, {}, 0
    print("Page\tFrames\t\tStatus")
    for t, page in enumerate(refs):
        if page in frames:
            frequency[page] += 1
            last_used[page] = t
            status = "HIT"
        else:
            status, faults = "FAULT", faults + 1
            if len(frames) == capacity:
                victim = min(frames, key=lambda x: (frequency[x], last_used[x]))
                frames[frames.index(victim)] = page
                del frequency[victim]
                del last_used[victim]
            else:
                frames.append(page)
            frequency[page], last_used[page] = 1, t
        print(f"{page}\t{' '.join(map(str, frames)):<16}\t{status}")
    print("Tie rule: among equal-frequency resident pages, evict the least recently used.")
    print(f"Total page faults = {faults}\nTotal page hits = {len(refs) - faults}")

if __name__ == "__main__":
    main()
