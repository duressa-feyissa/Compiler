a = 10
b = 5
c = 3

d = (a + b) * (b - c) / (a % c)  # d = (10 + 5) * (5 - 3) / (10 % 3) = 15 * 2 / 1 = 30.0
e = d + (c * 2) - (b * c)  # e = 30.0 + (3 * 2) - (5 * 3) = 30.0 + 6 - 15 = 21.0
f = d * e + (c / d)  # f = (30.0 * 21.0) + (3 / 30.0) = 630.0 + 0.1 = 630.1
g = (a + b) * (b - c) / (a % c)  # g = (10 + 5) * (5 - 3) / (10 % 3) = 15 * 2 / 1 = 30.0
h = g + (c * 2) - (b * c)  # h = 30.0 + (3 * 2) - (5 * 3) = 30.0 + 6 - 15 = 21.0
i = g * h + (c / g)  # i = (30.0 * 21.0) + (3 / 30.0) = 630.0 + 0.1 = 630.1

j = f > i and g < h  
k = f < i and g > h  
l = f >= i and g <= h and i == f  
m = f <= i and g >= h and i != f  
n = f == i and g != h 
o = f != i and g == h  

print("Test Case 8: Logical operators and Boolean variables")
print(d)  # Should print 30.0
print(e)  # Should print 21.0
print(f)  # Should print 630.1
print(g)  # Should print 30.0
print(h)  # Should print 21.0
print(i)  # Should print 630.1
print(j)  # Should print False
print(k)  # Should print False
print(l)  # Should print False
print(m)  # Should print False
print(n)  # Should print True
print(o)  # Should print False
