# Testing mathematical operations and variable assignments

# Initialize variables
a = 10
b = 5
c = 3

# Perform mathematical operations
d = (a + b) * (b - c) / (a % c)  # d = (10 + 5) * (5 - 3) / (10 % 3) = 15 * 2 / 1 = 30.0
e = d + (c * 2) - (b * c)  # e = 30.0 + (3 * 2) - (5 * 3) = 30.0 + 6 - 15 = 21.0
f = d * e + (c / d)  # f = (30.0 * 21.0) + (3 / 30.0) = 630.0 + 0.1 = 630.1

# Print the results
print("Test Case 3: Print variables and BODMAS operations")
print(d)  # Should print 30.0
print(e)  # Should print 21.0
print(f)  # Should print 630.1

x = 45
y = 69
z = 84

a = z + y
print(a) # prints 153

b = x + y

print(b)  # prints 114

c = 2 * (x + y)

print(c) # prints 228

d = x * y * c

print(d) #prints 707940

e = a * b

print(e) # prints 17442


g = (a + b) * (b - c)

print(g) # prints -22884
