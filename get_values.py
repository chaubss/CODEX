
# read grammar.txt
with (open('grammar.txt', 'r')) as f:
    grammar = f.readlines()
    for g in grammar:
        g = g.strip()
        g = g.split('->')
        name = g[0]
        g = g[1]
        g = g.strip()
        num = 0
        if (g != "''"):
            g = g.split(' ')
            num = len(g)
        print(f'{name} {num}')
