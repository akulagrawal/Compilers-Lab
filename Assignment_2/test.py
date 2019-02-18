import os, subprocess

tests_dir = "./tests/"

for filename in os.listdir(tests_dir):
    subprocess.call(["python3", "main.py", tests_dir + filename])

    print("Test File:", filename)
    with open(tests_dir + filename, "r") as inp_f:
        lines = inp_f.readlines()
        for index, line in enumerate(lines):
            if index > 5:
                break
            else:
                print(line, end="")

    with open("output.txt", "r") as out_f:
        lines = out_f.readlines()
        for line in lines:
            print(line, end="")
        
    print("\n")