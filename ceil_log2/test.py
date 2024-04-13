#!/usr/bin/env python3
import subprocess
import math

def check(x):
    if x==0:
        return 0
    return math.ceil(math.log2(x))

def test(command,x):
    completedProcess = subprocess.run(command.split(), capture_output=True, text=True, input=None)
    s = completedProcess.stdout
    output = int(s.strip())
    assert output==check(x), f"Error : the values are different ({output},{check(x)})"
for i in range(65537):
    x = i
    command=f'./main {x}'
    test(command,x)

print("All tests is passed !")