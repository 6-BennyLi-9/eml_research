# eml_research
You have to learn this((arxiv 2603.21852)[https://arxiv.org/abs/2603.21852] first.

# The "emllib"
After reading the paper, I realized that the elementary functions can be solved in
such simple case. The function eml(x, y) is simply a binary tree. Researches proved
that we can use a number to describe a binary tree(the solution is using pairing 
function, which means f(x,y) = z, ∀a,c,b,d ∈ R, if (a,b) != (c,d), then f(a,b)
!= f(c,d)).

In this case, we can use a number to describe the tree. We define the "1" as the 
leaves. I defined such numbers as  "emllib"s as the function is likely a big library.

```
eml expression: eml(1,eml(1,1))
emllib: f(1,f(1,1))
```

The emllib is calculated by a paring function, we set ```f(x,y)``` as a paring 
function. The expression has the same structure as eml's, which can be easily written
by code. You may notice that we use the result of f(...) as a parameter of itself,
which means the range of f is a subset of the domain of definition(D) of f.

# Describe all the elementary functions using a number
I chose the cantor paring function to describe the tree.

#Lincense
MIT
