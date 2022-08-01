# While writing implementation of octals in lexer i wonder how they works
# because i did not use them never

print(0o0)
print(0o1)
print(0o2)
print(0o3)
print(0o4)
print(0o5)
print(0o6)
print(0o7)
# print(0o8) SyntaxError: invalid digit '8' in octal literal
# print(0o9) SyntaxError: invalid digit '9' in octal literal

print(0o10000000000000000002617356) # A very very strange and big value here!

# ------
# Conclusion:
# In octal there's numbers 0 to 7 without any characters
# like in hexadecimal values, i get more informations on
# wikipedia page here's a link to it:
#  * https://en.wikipedia.org/wiki/Octal
#
# Before conclusion i was thinking that octal is an difrent
# type than int, yeah that was stupid.
