import os, subprocess

tests_dir = "./tests/"

for filename in os.listdir(tests_dir):
    subprocess.call(["python3", "main.py", tests_dir + filename])

    with open("output.txt", "r") as f:
        print(f.readlines())

    print("\n")
