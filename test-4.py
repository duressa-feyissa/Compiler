a = 23
b = 56
c = 13
d = 24
e = 57
f = 14

print("Test Case 5: Print variables and BODMAS operations")
g = (a + b) * (b - c) / (a % c)
print(g)  # prints 339.7

h = g + (c * 2) - (b * c)
print(h)  # prints 313.7

i = g * h + (c / g)
print(i)  # prints 101.7

j = (a + b) * (b - c)
print(j)  # prints 2283

k = j + (c * 2) - (b * c)
print(k)  # prints 2257

l = j * k + (c / j)
print(l)  # prints 5171

m = (a + b) * (b - c)
print(m)  # prints 2283

n = m + (c * 2) - (b * c)
print(n)  # prints 2257

o = m * n + (c / m)
print(o)  # prints 5171