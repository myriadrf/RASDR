from rss import rss
"""
Simple tester for the rss module which connects to rasdproc.
Data is read and output in the rtl_power format.
"""

r = rss()

print('rasdproc state:')
keys = r.parameters.keys()
values = [str(value) for value in r.parameters.values()]
print(' '.join(keys))
print(' '.join(values))
while True:
    rtl_power_lines = r.read_data()
    for line in rtl_power_lines:
        print(line)
