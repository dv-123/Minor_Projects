clc;
clear all;
close all;

% Sequence
x = [0 2 3 1 3 -1 1]

y = fft(x);        % Compute DFT of x
z = ifft(x)        % Compute IDFT of Y

% plot graphs
subplot(3,1,1);stem(x,'filled');title('input sequence')
subplot(3,1,2);stem(y,'filled');title('DFT using FFT');
subplot(3,1,3);stem(z,'filled');title('IDFT using FFT');

% display outputs
disp('input sequence');disp(x)
disp('DFT using FFT');disp(y)
disp('IDFT using FFT');disp(z)