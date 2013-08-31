#pragma coliru "data"
1 2 3 4 5 6 7 8 9 10

#pragma coliru "main.py"
if __name__ == '__main__':
    with open('data') as f:
        for x in f.read().split():
            print(int(x) * 2)
