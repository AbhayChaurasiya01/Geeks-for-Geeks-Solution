class Solution:
    def minCostPath(self, mat):
        import heapq
        
        n = len(mat)
        m = len(mat[0])

        # Min-heap: (effort, x, y)
        pq = [(0, 0, 0)]

        # Distance matrix
        dist = [[float('inf')] * m for _ in range(n)]
        dist[0][0] = 0

        directions = [(1,0), (-1,0), (0,1), (0,-1)]

        while pq:
            effort, x, y = heapq.heappop(pq)

            # Reached destination
            if x == n - 1 and y == m - 1:
                return effort

            for dx, dy in directions:
                nx = x + dx
                ny = y + dy

                if 0 <= nx < n and 0 <= ny < m:
                    cost = abs(mat[x][y] - mat[nx][ny])
                    new_effort = max(effort, cost)

                    if new_effort < dist[nx][ny]:
                        dist[nx][ny] = new_effort
                        heapq.heappush(pq, (new_effort, nx, ny))

        return 0
