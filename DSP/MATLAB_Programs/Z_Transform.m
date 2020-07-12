clc;
clear all;
close all;

n = -20:20; % define a range for input sequence
z = sym('z'); % define symbol

%part1
% z_transform for exponential signal
exp_n = exp(n)
l_a = length(exp_n); % length of input
Y_a = 0; % initilize output
for i = 0:l_a-1
    Y_a = Y_a+exp_n(i+1)*z^(-i);
end
disp('input sequence');disp(n)
disp('z_transform of exponential signal')
disp(Y_a)
subplot(411)
stem(n,exp_n,'filled')
title('exponential signal')

% part 2
% z_transform for ramp signal
ramp_n = (n>=0).*n;
l_b = length(ramp_n);
Y_b = 0; % initilize output
for i = 0:l_b-1
    Y_b = Y_b+ramp_n(i+1)*z^(-i);
end
disp('z_transform of ramp signal')
disp(Y_b)
subplot(412)
stem(n,ramp_n,'filled')
title('ramp signal')


% part 3
% z_transform for unit step signal
step_n = (n>=0);
l_c = length(step_n);
Y_c = 0; % initilize output
for i = 0:l_c-1
    Y_c = Y_c+step_n(i+1)*z^(-i);
end
disp('z_transform of unit step signal')
disp(Y_c)
subplot(413)
stem(n,step_n,'filled')
title('unit step signal')


% part 4
% z_transform for delta signal
delta_n = (n==0);
l_d = length(delta_n);
Y_d = 0; % initilize output
for i = 0:l_d-1
    Y_d = Y_d+delta_n(i+1)*z^(-i);
end
disp('z_transform of direc-delta signal')
disp(Y_d)
subplot(414)
stem(n,delta_n,'filled')
title('direc-delta signal')
