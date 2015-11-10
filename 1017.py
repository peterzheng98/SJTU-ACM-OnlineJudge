a,b,c,N = (int(s) for s in raw_input().split())
n0,n1,n2,n3 = 1,0,0,0
for i in range(N):
    n3 += n2
    n2 = n1
    n1 = n0
    n0 = n1*a+n2*b+n3*c
print n0+n1+n2+n3
