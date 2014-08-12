R = open('graph.graphml','r')
f1 = open('adj.txt','w')
f2 = open('vmap.txt','w')
for line in R:
  if len(line) < 5:
    continue
  if line[1:5] == 'node':
    parts = line.split('"')
    f2.write(parts[1] + " " + parts[3] + " " + parts[5] + "\n")
  elif line[1:5] == 'edge':
    parts = line.split('"')
    f1.write(parts[1] + " " + parts[3] + "\n")