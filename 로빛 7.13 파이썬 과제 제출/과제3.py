# 과제 3

# 리스트 생성
my_list = []

while True:
    # 사용자 명령 입력
    command = input().split()

    # 리스트 맨 뒤에 값 추가
    if command[0] == "append":
        my_list.append(command[1])

    # 원하는 위치에 값 삽입
    elif command[0] == "insert":
        index = int(command[1])

        # 인덱스 범위 확인
        if 0 <= index <= len(my_list):
            my_list.insert(index, command[2])
        else:
            print("인덱스 범위를 벗어났습니다.")

    # 값 삭제
    elif command[0] == "remove":
        if command[1] in my_list:
            my_list.remove(command[1])
        else:
            print("존재하지 않는 값입니다.")

    # 값 삭제(pop)
    elif command[0] == "pop":
        # 빈 리스트 예외 처리
        if len(my_list) == 0:
            print("리스트가 비어있습니다.")
        else:
            # 인덱스를 입력하지 않으면 마지막 값 삭제
            if len(command) == 1:
                my_list.pop()
            else:
                index = int(command[1])

                # 인덱스 범위 확인
                if 0 <= index < len(my_list):
                    my_list.pop(index)
                else:
                    print("인덱스 범위를 벗어났습니다.")

    # 리스트 길이 출력
    elif command[0] == "len":
        print(len(my_list))

    # 리스트 전체 출력
    elif command[0] == "print":
        print(my_list)

    # 리스트 비우기
    elif command[0] == "clear":
        my_list.clear()

    # 프로그램 종료
    elif command[0] == "exit":
        break

    # 지원하지 않는 명령어
    else:
        print("지원하지 않는 명령어입니다.")