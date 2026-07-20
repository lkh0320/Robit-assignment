# 과제 2
# 수정전 코드
'''
def add_log(robot_name, battery, logs=[]):
    log = robot_name + " battery: " + battery
    logs.append(log)
    return logs

print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))
'''

#수정 후 코드

def add_log(robot_name, battery, logs=None):
    # 기본값으로 리스트([])를 사용하면 같은 리스트를 계속 공유하므로
    # None을 사용하고 함수 내부에서 새로운 리스트를 생성한다.
    if logs is None:
        logs = []

    # battery는 정수이므로 문자열과 연결하려면 문자열로 변환해야 한다.
    log = robot_name + " battery: " + str(battery)

    logs.append(log)
    return logs

print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))
