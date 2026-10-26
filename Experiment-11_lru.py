#!/usr/bin/env python3
"""LRU page replacement; least-recently-used resident page is evicted."""

def main():
    capacity = int(input("Number of frames: "))
    refs = list(map(int, input("Page reference string (space-separated): ").split()))
    if capacity <= 0 or not refs or any(x < 0 for x in refs):
        raise SystemExit("Frames must be positive and references non-negative.")
    frames, last_used, faults = [], {}, 0
    print("Page\tFrames\t\tStatus")
    for t, page in enumerate(refs):
        if page in frames:
            status = "HIT"
        else:
            status, faults = "FAULT", faults + 1
            if len(frames) < capacity:
                frames.append(page)
            else:
                victim = min(frames, key=lambda x: last_used[x])
                frames[frames.index(victim)] = page
        last_used[page] = t
        print(f"{page}\t{' '.join(map(str, frames)):<16}\t{status}")
    print(f"Total page faults = {faults}\nTotal page hits = {len(refs) - faults}")

if __name__ == "__main__":
    main()
