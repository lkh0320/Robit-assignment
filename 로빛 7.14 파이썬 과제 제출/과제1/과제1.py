# 과제 1
import csv
import json

# students.csv 내용 출력
print("===== students.csv =====")
with open("students.csv", "r", encoding="utf-8") as file:
    reader = csv.reader(file)
    for row in reader:
        print(row)

print()

valid_students = []
scores = []

# CSV 읽기 및 처리
with open("students.csv", "r", encoding="utf-8") as file:
    reader = csv.reader(file)

    next(reader)   # 헤더 건너뛰기

    for row in reader:
        name = row[0]
        score = row[1]

        # 숫자 변환 검사
        try:
            score = int(score)
        except ValueError:
            print(f"# '{row[1]}' → 숫자로 변환실패")
            continue

        # 범위 검사
        if score < 0 or score > 100:
            print(f"# {score} → 허용 범위 초과")
            continue

        valid_students.append([name, score])
        scores.append(score)

# clean_students.csv 저장
with open("clean_students.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file)
    writer.writerow(["name", "score"])
    writer.writerows(valid_students)

# summary.json 저장
summary = {
    "학생수": len(scores),
    "평균": round(sum(scores) / len(scores), 2),
    "최고점": max(scores)
}

with open("summary.json", "w", encoding="utf-8") as file:
    json.dump(summary, file, ensure_ascii=False, indent=4)