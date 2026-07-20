# 고급과제 2 수정 전

# 책 이름과 남은 수량 저장
books = {}

# 책 등록 순서 저장
book_order = []

# 사용자별 대출 목록 저장
users = {}


# 책 등록
def add(cmd):
    # 명령어 형식 확인
    if len(cmd) != 3:
        print("ERROR")
        return

    title = cmd[1]

    # 수량이 정수인지 확인
    try:
        count = int(cmd[2])
        if count < 0:
            print("ERROR")
            return
    except:
        print("ERROR")
        return

    # 이미 등록된 책이면 수량 추가
    if title in books:
        books[title] += count
    else:
        # 새로운 책 등록
        books[title] = count
        book_order.append(title)


# 책 대출
def borrow(cmd):
    # 명령어 형식 확인
    if len(cmd) != 3:
        print("ERROR")
        return

    user = cmd[1]
    title = cmd[2]

    # 책이 존재하는지 확인
    if title not in books:
        print("ERROR 책이 존재하지 않습니다.")
        return

    # 남은 수량 확인
    if books[title] == 0:
        print("ERROR 수량이 없습니다.")
        return

    # 처음 대출하는 사용자 등록
    if user not in users:
        users[user] = []

    # 같은 책 중복 대출 방지
    if title in users[user]:
        print("ERROR 이미 대출 중입니다.")
        return

    users[user].append(title)
    books[title] -= 1


# 책 반납
def return_book(cmd):
    # 명령어 형식 확인
    if len(cmd) != 3:
        print("ERROR")
        return

    user = cmd[1]
    title = cmd[2]

    # 사용자 존재 여부 확인
    if user not in users:
        print("ERROR 사용자가 존재하지 않습니다.")
        return

    # 실제 대출한 책인지 확인
    if title not in users[user]:
        print("ERROR 대출하지 않은 책입니다.")
        return

    users[user].remove(title)
    books[title] += 1


# 책의 남은 수량 조회
def status(cmd):
    if len(cmd) != 2:
        print("ERROR")
        return

    title = cmd[1]

    if title not in books:
        print("ERROR")
        return

    print(books[title])


# 사용자 대출 목록 조회
def user(cmd):
    if len(cmd) != 2:
        print("ERROR")
        return

    name = cmd[1]

    if name not in users:
        print("ERROR")
        return

    if len(users[name]) == 0:
        print("EMPTY")
        return

    for book in users[name]:
        print(book)


# 등록된 모든 책 출력
def list_book(cmd):
    if len(cmd) != 1:
        print("ERROR")
        return

    if len(book_order) == 0:
        print("EMPTY")
        return

    # 등록된 순서대로 출력
    for book in book_order:
        print(book, books[book])


# Exit 입력 전까지 반복 실행
while True:
    command = input().split()

    # 빈 입력 처리
    if len(command) == 0:
        print("ERROR")
        continue

    # 프로그램 종료
    if command[0] == "Exit":
        break

    # 명령어에 따라 함수 호출
    elif command[0] == "add":
        add(command)

    elif command[0] == "borrow":
        borrow(command)

    elif command[0] == "return":
        return_book(command)

    elif command[0] == "status":
        status(command)

    elif command[0] == "user":
        user(command)

    elif command[0] == "list":
        list_book(command)

    # 존재하지 않는 명령어 처리
    else:
        print("ERROR")