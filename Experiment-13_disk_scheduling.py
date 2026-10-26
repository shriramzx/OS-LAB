#!/usr/bin/env python3
"""Run one of six disk scheduling algorithms for a railway server example."""

def movement(start, stops):
    total = 0
    position = start
    for stop in stops:
        total += abs(stop - position)
        position = stop
    return total


def schedule(algorithm, requests, head, low, high, direction):
    if algorithm == "FCFS":
        order = requests[:]
        return order, movement(head, order)

    if algorithm == "SSTF":
        pending, order, position = requests[:], [], head
        while pending:
            request = min(pending, key=lambda value: (abs(value - position), value))
            order.append(request)
            pending.remove(request)
            position = request
        return order, movement(head, order)

    at_head = [request for request in requests if request == head]
    left = sorted((request for request in requests if request < head), reverse=True)
    right = sorted(request for request in requests if request > head)

    if algorithm == "SCAN":
        if direction == "right":
            order = at_head + right + left
            route = at_head + right + ([high] if left else []) + left
        else:
            order = at_head + left + right
            route = at_head + left + ([low] if right else []) + right
        return order, movement(head, route)

    if algorithm == "C-SCAN":
        if direction == "right":
            order = at_head + right + sorted(left)
            route = at_head + right
            if left:
                route += [high, low] + sorted(left)
        else:
            order = at_head + left + sorted(right, reverse=True)
            route = at_head + left
            if right:
                route += [low, high] + sorted(right, reverse=True)
        return order, movement(head, route)

    if algorithm == "LOOK":
        order = at_head + (right + left if direction == "right" else left + right)
        return order, movement(head, order)

    if algorithm == "C-LOOK":
        if direction == "right":
            order = at_head + right + (sorted(left) if left else [])
        else:
            order = at_head + left + (sorted(right, reverse=True) if right else [])
        return order, movement(head, order)

    raise ValueError("Unknown algorithm")


def main():
    choices = ("FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK")
    print("Railway Ticket Reservation Server - Disk Scheduling")
    print("Algorithms: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK")
    algorithm = input("Choose algorithm: ").strip().upper()
    if algorithm not in choices:
        raise SystemExit("Choose one of the listed algorithms.")
    try:
        requests = list(map(int, input("Disk request queue (space-separated): ").split()))
        head = int(input("Initial head position: "))
        low = int(input("Lowest cylinder number (inclusive): "))
        high = int(input("Highest cylinder number (inclusive): "))
        direction = "right"
        if algorithm in ("SCAN", "C-SCAN", "LOOK", "C-LOOK"):
            direction = input("Initial direction (left/right): ").strip().lower()
    except ValueError:
        raise SystemExit("Enter integer cylinder numbers.")

    if not requests or low >= high or not (low <= head <= high):
        raise SystemExit("Enter a non-empty queue, valid bounds, and a head within the bounds.")
    if any(request < low or request > high for request in requests):
        raise SystemExit("Every request must be within the cylinder bounds.")
    if direction not in ("left", "right"):
        raise SystemExit("Direction must be left or right.")

    order, total = schedule(algorithm, requests, head, low, high, direction)
    print(f"\n{algorithm} disk scheduling")
    print("Service order: " + " -> ".join(map(str, order)))
    print(f"Total head movement = {total} cylinders")
    print(f"Average head movement per request = {total / len(requests):.2f} cylinders")
    if algorithm in ("SCAN", "C-SCAN"):
        print("Direction: " + direction)
    if algorithm == "C-SCAN":
        print("Circular wrap movement is included in the total.")
    if algorithm in ("SCAN", "C-SCAN"):
        print("Boundary handling: disk limits are visited when the sweep requires them to reach pending requests.")


if __name__ == "__main__":
    main()
