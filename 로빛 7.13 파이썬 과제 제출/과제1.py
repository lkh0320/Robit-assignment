# 과제 1

# 배터리 상태를 판별하는 함수
def Battery(num):
    if robot_status[num]["battery"] >= 60:
        return "배터리 충분"
    elif robot_status[num]["battery"] < 60 and robot_status[num]["battery"] >= 20:
        return "배터리 주의"
    else:
        return "충전 필요"

# 장애물 여부를 판별하는 함수
def Status(num):
    if robot_status[num]["distance"] >= 0.5:
        return "전진 가능"
    else:
        return "장애물 감지"

# 로봇 정보 저장
robot_status = [
    {"name": "mobiliebot", "battery": 82, "position": (1.2, 0.5), "distance": 0.8},
    {"name": "drone", "battery": 18, "position": (0.3, 1.5), "distance": 0.4},
    {"name": "manipulator", "battery": 45, "position": (2.0, 1.0), "distance": 1.2}
]

# 각 로봇의 정보를 출력
for robot in (0, 1, 2):
    print("[" + robot_status[robot]["name"] + "]")
    print("배터리: " + Battery(robot))
    # x, y 좌표 출력
    print("위치: x= " + str(robot_status[robot]["position"][0]) +
          ", y=" + str(robot_status[robot]["position"][1]))
    print("상태: " + Status(robot))
    print("")