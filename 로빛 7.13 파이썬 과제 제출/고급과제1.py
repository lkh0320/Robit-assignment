# 고급과제 1

# 입력된 명령어를 함수명과 인자로 분리
def INput():
    command = input()

    command = command.replace("(", " ")
    command = command.replace(")", " ")
    command = command.replace('"', "")

    result = command.split()
    return result


# 문자열 압축
def compress(text):
    texts = list(text)
    result = ""
    count = 1

    # 연속된 문자의 개수 세기
    for i in range(len(texts)):
        if i < len(texts) - 1 and texts[i] == texts[i + 1]:
            count += 1
        else:
            result += texts[i] + str(count)
            count = 1

    # 압축 결과가 더 길면 원본 반환
    if len(result) >= len(text):
        return text

    return result


# 압축 문자열 복원
def decompress(code):

    # 올바른 형식인지 확인
    if not is_valid_code(code):
        return "ERROR"

    result = ""
    i = 0

    while i < len(code):

        ch = code[i]
        i += 1

        num = ""

        # 숫자가 여러 자리인 경우 처리
        while i < len(code) and code[i].isdigit():
            num += code[i]
            i += 1

        # 반복 횟수는 1 이상이어야 함
        if int(num) < 1:
            return "ERROR"

        result += ch * int(num)

    return result


# 압축 문자열 형식 검사
def is_valid_code(code):
    i = 0

    while i < len(code):

        # 문자가 아니면 오류
        if not code[i].isalpha():
            return False

        i += 1

        # 문자 뒤에는 반드시 숫자가 와야 함
        if i >= len(code) or not code[i].isdigit():
            return False

        # 숫자가 여러 자리인 경우 모두 건너뜀
        while i < len(code) and code[i].isdigit():
            i += 1

    return True


# 명령어 실행
while 1:
    command = INput()

    # 프로그램 종료
    if command[0] == "exit" or command[0] == "":
        break

    # print 명령어만 허용
    elif command[0].lower() != "print":
        print("다시 입력해주세요.")
        continue

    # 문자열 압축
    elif command[1] == "compress":
        print(compress(command[2]))

    # 문자열 복원
    elif command[1] == "decompress":
        print(decompress(command[2]))

    # 잘못된 명령어 처리
    else:
        print("잘못된 명령어입니다. \n 다시 입력해주세요.")
        continue