#!/usr/bin/env python3
"""Worst Fit allocation. A block's remainder can be used by later processes."""

def allocate(blocks, processes):
    remaining = blocks[:]
    result = []
    for process_id, size in enumerate(processes, 1):
        candidates = [i for i, free in enumerate(remaining) if free >= size]
        if not candidates:
            result.append((process_id, size, None))
            continue
        # Lowest-index block breaks equal-size ties.
        block = max(candidates, key=lambda i: (remaining[i], -i))
        remaining[block] -= size
        result.append((process_id, size, block + 1))
    return result, remaining

def read_sizes(prompt):
    values = list(map(int, input(prompt).split()))
    if not values or any(x <= 0 for x in values):
        raise ValueError("Enter one or more positive sizes.")
    return values

def main():
    print("Hospital Emergency Application Memory Allocation - Worst Fit")
    try:
        blocks = read_sizes("Memory block sizes (space-separated): ")
        processes = read_sizes("Process sizes (space-separated): ")
    except ValueError as error:
        raise SystemExit(str(error))
    result, remaining = allocate(blocks, processes)
    print("\nProcess\tSize\tAllocated block")
    for pid, size, block in result:
        print(f"P{pid}\t{size}\t{block if block is not None else 'Not allocated'}")
    print("Remaining block space: " + " ".join(f"B{i+1}={x}" for i, x in enumerate(remaining)))
    print("Assumption: blocks are variable-sized; each leftover region remains available.")

if __name__ == "__main__":
    main()
