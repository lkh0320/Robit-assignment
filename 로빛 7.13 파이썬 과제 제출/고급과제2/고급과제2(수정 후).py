# 고급과제 2 (수정 후)


# 책 이름과 남은 수량 저장
books = {}

# 책 등록 순서 저장
book_order = []

# 사용자별 대출 목록 저장
users = {}


# 책 등록
def add_book(command):

    # 명령어 형식 확인
    if len(command) != 3:
        print("ERROR : 잘못된 명령어 형식입니다.")
        return

    title = command[1]

    # 수량이 정수인지 확인
    try:
        count = int(command[2])
        if count < 0:
            print("ERROR : 수량은 0 이상의 정수여야 합니다.")
            return
    except:
        print("ERROR : 수량은 정수여야 합니다.")
        return

    # 이미 등록된 책이면 수량 추가
    if title in books:
        books[title] += count
        print(f"[ADD SUCCESS] {title}의 수량이 {books[title]}권이 되었습니다.")
    else:
        # 새로운 책 등록
        books[title] = count
        book_order.append(title)
        print(f"[ADD SUCCESS] {title} {count}권 등록 완료.")


# 책 대출
def borrow_book(command):

    if len(command) != 3:
        print("ERROR : 잘못된 명령어 형식입니다.")
        return

    user = command[1]
    title = command[2]

    # 책 존재 여부 확인
    if title not in books:
        print("ERROR : 존재하지 않는 책입니다.")
        return

    # 남은 수량 확인
    if books[title] == 0:
        print("ERROR : 남은 수량이 없습니다.")
        return

    # 새로운 사용자 등록
    if user not in users:
        users[user] = []

    # 같은 책 중복 대출 방지
    if title in users[user]:
        print("ERROR : 이미 대출 중인 책입니다.")
        return

    users[user].append(title)
    books[title] -= 1

    print(f"[BORROW SUCCESS] {user}님이 '{title}'을(를) 대출했습니다.")


# 책 반납
def return_book(command):

    if len(command) != 3:
        print("ERROR : 잘못된 명령어 형식입니다.")
        return

    user = command[1]
    title = command[2]

    # 사용자 존재 여부 확인
    if user not in users:
        print("ERROR : 존재하지 않는 사용자입니다.")
        return

    # 실제 대출 여부 확인
    if title not in users[user]:
        print("ERROR : 대출하지 않은 책입니다.")
        return

    users[user].remove(title)
    books[title] += 1

    print(f"[RETURN SUCCESS] {user}님이 '{title}'을(를) 반납했습니다.")


# 책 남은 수량 조회
def check_status(command):

    if len(command) != 2:
        print("ERROR : 잘못된 명령어 형식입니다.")
        return

    title = command[1]

    if title not in books:
        print("ERROR : 존재하지 않는 책입니다.")
        return

    print(f"{title} : {books[title]}권 남음")


# 사용자 대출 목록 조회
def show_user(command):

    if len(command) != 2:
        print("ERROR : 잘못된 명령어 형식입니다.")
        return

    name = command[1]

    if name not in users:
        print("ERROR : 존재하지 않는 사용자입니다.")
        return

    if len(users[name]) == 0:
        print("EMPTY")
        return

    print(f"{name}님의 대출 목록")

    for book in users[name]:
        print(f"- {book}")


# 전체 책 목록 출력
def show_book_list(command):

    if len(command) != 1:
        print("ERROR : 잘못된 명령어 형식입니다.")
        return

    if len(book_order) == 0:
        print("EMPTY")
        return

    print("===== BOOK LIST =====")

    # 등록 순서대로 출력
    for book in book_order:
        print(f"{book} : {books[book]}권")

    print("=====================")


# 프로그램 실행
def main():

    print("===== 도서 대출 관리 시스템 =====")
    print("사용 가능한 명령어")
    print("add")
    print("borrow")
    print("return")
    print("status")
    print("user")
    print("list")
    print("Exit")
    print("==============================")

    # Exit 입력 전까지 반복
    while True:

        command = input(">> ").split()

        if len(command) == 0:
            print("ERROR : 명령어를 입력하세요.")
            continue

        if command[0] == "Exit":
            print("프로그램을 종료합니다.")
            break

        elif command[0] == "add":
            add_book(command)

        elif command[0] == "borrow":
            borrow_book(command)

        elif command[0] == "return":
            return_book(command)

        elif command[0] == "status":
            check_status(command)

        elif command[0] == "user":
            show_user(command)

        elif command[0] == "list":
            show_book_list(command)

        else:
            print("ERROR : 존재하지 않는 명령어입니다.")


main()