clc;
clear all;
close all;

x = [-1 1 2 3]; % first sequence
h = [-1 1 1 -1]; % second sequence

m=length(x);%length of sequence x(n)
n=length(h);%length of sequence h(n)
N=max(m,n);%length of output sequence y(n)

%For equating both sequence length
x=[x,zeros(1,N-m)];
h=[h,zeros(1,N-n)];

% circular convolution using formula
for n=1:N
    Y(n)=0;
    for i=1:N
        j=n-i+1;
        if(j<=0)
            j=N+j;
        end
        Y(n)=[Y(n)+x(i)*h(j)];
    end
end
n=0:N-1;%Range of all Sequences

% display and ploting signals
subplot(411)
stem(n,x)
xlabel('n')
ylabel('x(n)')
title('First Sequence')
grid on;

subplot(412)
stem(n,h)
xlabel('n')
ylabel('h(n)')
title('Second Sequence')
grid on;

subplot(413)
stem(n,Y)
xlabel('n')
ylabel('Y(n)')
title('Circular Convoluted Sequence without using built in function')
grid on;

subplot(414)
stem(n,cconv(x,h,N))
xlabel('n')
ylabel('Y(n)')
title('Circular Convoluted Sequence using built in function')
grid on;

disp('first sequence');disp(x);
disp('second sequence');disp(h)
disp('Circular Convoluted Sequence without using built in function');disp(Y)
disp('Circular Convoluted Sequence using built in function');disp(cconv(x,h,N))