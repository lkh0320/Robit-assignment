# 과제 4

# 미로를 저장할 리스트
maze = []

# 10x10 미로 입력
for j in range(10):
    maze.append(input().split())

    # 한 줄에 10개의 값이 입력될 때까지 다시 입력
    while len(maze[j]) != 10:
        print("미로 범위를 벗어났습니다. (10 x 10)")
        print("다시 입력해주세요.")
        maze[j] = input().split()

# 시작 위치
x, y = 1, 1

while True:

    # 먹이를 찾으면 표시 후 종료
    if maze[y][x] == "2":
        maze[y][x] = "9"
        break

    # 현재 위치를 이동 경로로 표시
    maze[y][x] = "9"

    # 오른쪽으로 이동 가능하면 이동
    if x + 1 < 10 and maze[y][x + 1] != "1":
        x += 1

    # 오른쪽이 막혀 있으면 아래로 이동
    elif y + 1 < 10 and maze[y + 1][x] != "1":
        y += 1

    # 더 이상 이동할 수 없으면 종료
    else:
        break

# 이동 결과 출력
for i in range(len(maze)):
    for j in range(len(maze[i])):
        print(maze[i][j], end=" ")
    print()