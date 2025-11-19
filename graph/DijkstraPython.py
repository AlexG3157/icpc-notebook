from heapq import heappop
from heapq import heappush
# SSSP $O((V+E) \ log V)$
def dijkstra(graph, weight, source=0, target=None):
    n = len(graph)
    assert all(weight[u][v] >= 0 for u in range(n) for v in graph[u])
    prec = [None] * n
    black = [False] * n
    dist = [float('inf')] * n
    dist[source] = 0
    heap = [(0, source)]
    while heap:
        dist_node, node = heappop(heap) # Closest node from source
        if not black[node]:
            black[node] = True
        if node == target:
            break
        for neighbor in graph[node]:
            dist_neighbor = dist_node + weight[node][neighbor]
            if dist_neighbor < dist[neighbor]:
                dist[neighbor] = dist_neighbor
                prec[neighbor] = node
                heappush(heap, (dist_neighbor, neighbor))
    return dist, prec