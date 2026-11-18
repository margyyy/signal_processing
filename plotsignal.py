import csv
import sys
import matplotlib.pyplot as plt

time_path = sys.argv[1]
signal_path = sys.argv[2]
output_path = sys.argv[3]

def read_csv(path):
    with open(path, newline='') as f:
        reader = csv.reader(f)
        return [float(row[0]) for row in reader if row]

time_data = read_csv(time_path)
signal_data = read_csv(signal_path)

print(len(time_data))
print(len(signal_data))

if len(time_data) != len(signal_data):
    raise ValueError("Time e signal hanno lunghezze diverse")

plt.plot(time_data, signal_data)
plt.grid(True)
plt.xlabel("time")
plt.ylabel("ampl")
plt.savefig(output_path, dpi=300, bbox_inches="tight")