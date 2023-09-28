def sum_between(x, y):
    result = 0
    for i in range(x,y+1):
        result += i
    return result
print(sum_between(1,3))