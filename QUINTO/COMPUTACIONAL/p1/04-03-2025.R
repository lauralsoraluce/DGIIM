# EXERCISES 04.03.2025

# 1. Create two vectors (u1, u2) of length 10, consisting of random values from a u(0,1).
set.seed(1)
u1<-runif(10)
u2<-runif(10)

# 2. Create a matrix (M) with these two vectors as columns.
M<-cbind(u1, u2)
M

# 3. Add names to the columns "u1" and "u2"
# The names are already there but if they weren't, we could do colnames(M)<-c('u1','u2')

# 4. Add one row at the bottom with  the means of the columns.
M<-rbind(M,c(mean(u1),mean(u2)))

# 5. Add names to the rows: 1, ... 10, means
rownames(M)<-c(1:10,'means')
M

##############################################

A<-matrix(1:9, 3:3); A
B<-A; B
B[A>3]<-NA; B
B[is.na(B)]<-0; B

##############################################

A<-matrix(c(3,5,2,4,-2,-2,-1,1,1),3,3); A
b<-c(8,4,1); b
solve(A,b)

A<-matrix(c(-3,1,4,2),2,2); A
b<-c(2,8); b
solve(A,b)

##############################################

# Create a matrix with 4 columns consisting of the vector (1,2,3,4)^n, n=0,1,2,3.
# Here we have to possible answers
matrix(rep(1:4, times=4)^rep(0:3,each=4),4,4)
outer(1:4,0:3,'^')
options(max.print=100000) # We do this when we need to increase the max number of lines the console is allowed to print
outer(1:100,0:99,'^')

##############################################

A<-matrix(1:9,3,3)
x<-1:3
A%*%x # Gives a column 
A%*%t(x) # Doesn't work
x%*%A # Gives a row
t(x)%*%A # Gives a row
t(x)%*%x # Gives a single number
