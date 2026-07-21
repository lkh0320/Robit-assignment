# 과제 2
import requests

key = "169d64622be5b2c3f93530f0d258f369"

city = input("도시를 입력하세요 : ")

url = "https://api.openweathermap.org/data/2.5/forecast"

data = {
    "q": city,
    "appid": key,
    "units": "metric",
    "lang": "kr"
}

r = requests.get(url, params=data)
weather = r.json()

# 조회 가능한 날짜 출력
dates = []

for i in weather["list"]:
    d = i["dt_txt"].split()[0]

    if d not in dates:
        dates.append(d)

print("\n조회 가능한 날짜")
for d in dates:
    print("-", d)

date = input("\n날짜를 입력하세요(YYYY-MM-DD) : ")

find = False

for i in weather["list"]:

    d = i["dt_txt"]

    if date in d and "12:00:00" in d:

        print("---------------------")
        print("도시 :", city)
        print("날짜 :", date)
        print("날씨 :", i["weather"][0]["description"])
        print("기온 :", i["main"]["temp"], "℃")
        print("최저 :", i["main"]["temp_min"], "℃")
        print("최고 :", i["main"]["temp_max"], "℃")
        print("습도 :", i["main"]["humidity"], "%")
        print("---------------------")

        find = True
        break

if find == False:
    print("해당 날짜의 날씨가 없습니다.")