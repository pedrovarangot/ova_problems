import sys

def main():
    vertices = int(input())
    if vertices == 0:
        sys.exit(0)
    nedges = int(input())

    edges = {}
    for _ in range(nedges):
        x,y = map(int, input().split())
        try:
            edges[x].append(y)
        except KeyError:
            edges[x] = [y]

    reds = set([0])
    blacks = set()
    paint_black = True
    queue = [0]
    while True:
        v = queue.pop()
        if v in edges.keys():
            if paint_black:
                for v2 in edges[v]:
                    if v2 in reds:
                        print("NOT BICOLORABLE.")
                        return
                    blacks.add(v2)
                    if v2 not in queue:
                        queue.append(v2)
                    paint_black = False
            else:
                for v2 in edges[v]:
                    if v2 in blacks:
                        print("NOT BICOLORABLE.")
                        return
                    reds.add(v2)
                    if v2 not in queue:
                        queue.append(v2)
                    paint_black = True
        if queue == []:
            break
    print("BICOLORABLE.")


if __name__ == "__main__":
    while True:
        main()
