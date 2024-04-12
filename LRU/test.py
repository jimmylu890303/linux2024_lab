#!/usr/bin/env python3
import subprocess
import matplotlib.pyplot as plt
import numpy as np
import statistics

hash_type = {0:'division',1:'multiplication'}

def test(command):
    completedProcess = subprocess.run(command.split(), capture_output=True, text=True, input=None)
    s = completedProcess.stdout
    lines = s.strip().split('\n')

    collision_counts = []

    for line in lines[:-1]:
        parts = line.split()
        count = int(parts[-1])
        collision_counts.append(count)

    # Draw bar of collision_counts
    x = np.arange(len(collision_counts))
    width = 0.5
    plt.bar(x, collision_counts)
    plt.xticks(fontsize=8, rotation=0)
    plt.xlabel('Hash Buckets')
    plt.ylabel('Counts')
    plt.title(f'Collision Counts_{hash_type[int(command.split()[-1])]}')
    plt.savefig(f'./Collision_Counts_{hash_type[int(command.split()[-1])]}.png') 
    plt.close()
    print(f"Total count of {hash_type[int(command.split()[-1])]} : {int(lines[-1].split()[-1])}")
    return collision_counts
    
size = 2048
command=f'./lru {size} 0'
counts_division = test(command)
variance = statistics.variance(counts_division)
mean = statistics.mean(counts_division)
print(f'mean : {mean},variance : {variance}')
command=f'./lru {size} 1'
counts_multiplication = test(command)
variance = statistics.variance(counts_multiplication)
mean = statistics.mean(counts_multiplication)
print(f'mean : {mean},variance : {variance}')

x1 = np.arange(len(counts_division))
x2 = np.arange(len(counts_multiplication))
plt.plot(x1, counts_division, 'b')  
plt.plot(x2, counts_multiplication, 'r')
plt.xlabel('Hash Buckets')
plt.ylabel('Counts')
plt.legend(['counts_division','counts_multiplication'])
plt.savefig(f'./result.png') 
plt.close()