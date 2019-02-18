import os, subprocess

tests_dir = "~/Documents/CompilersLab/Assignment_2/tests"

for filename in os.listdir(tests_dir):
    subprocess.call(["python3", "main.py", filename])

    with open("output.txt", "r") as f:
        print(f.readlines())

    print("\n")