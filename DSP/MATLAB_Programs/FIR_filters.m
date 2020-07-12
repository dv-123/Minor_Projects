clc;
clear all;
close all;

% FIR filters
% no. of filters
n = 45;  %filtertype
%cutoff freq.
wn1 = 0.43; % cutoff frequency for lpf and hpf
wn2 = [0.30 0.60];% cutoff frequency for bpf and bsf
%filtertype
ftype1 = 'high';ftype2 = 'low';ftype3 = 'bandpass';ftype4 = 'stop'

% using Hamming window to design IIR filters
% calculating output signal from filters
% high pass filter
y1 = fir1(n,wn1,ftype1);fvtool(y1,'freq')
title('Magnitude Response(dB) and Phase Responce of FIR High Pass Filter')
legend('Magnitude','Phase')
% low pass filter
y2 = fir1(n,wn1,ftype2);fvtool(y2,'freq')
title('Magnitude Response(dB) and Phase Responce of FIR Low Pass Filter')
legend('Magnitude','Phase')
% band pass filter
y3 = fir1(n,wn2,ftype3);fvtool(y3,'freq')
title('Magnitude Response(dB) and Phase Responce of FIR Band Pass Filter')
legend('Magnitude','Phase')
% band stop signal
y4 = fir1(n,wn2,ftype4);fvtool(y4,'freq')
title('Magnitude Response(dB) and Phase Responce of FIR Band Stop Filter')
legend('Magnitude','Phase')