from cs50 import get_string

people = {
    "Carter": "12344",
    "David": "564"
}

name = get_string("Name: ")
if name in people:
    tel = people[name]
    print(f"Number: {tel}")