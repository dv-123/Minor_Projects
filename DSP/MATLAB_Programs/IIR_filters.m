clc;
clear all;
close all;

% IIR filters
% no. of filters
n = 8;  
%cutoff freq.
Wn1 = 400/650; % cutoff frequency for lpf and hpf
Wn2 = [400 580]/650;% cutoff frequency for bpf and bsf
%filtertype
ftype1 = 'high';ftype2 = 'low';ftype3 = 'bandpass';ftype4 = 'stop'
% using butterworth design for IIR filters
% Zero-Pole-Gain design
% coonvert zero-pole to second order state for representation
[z1,p1,k1] = butter(n,Wn1,ftype1);sos1 = zp2sos(z1,p1,k1);% hpf
[z2,p2,k2] = butter(n,Wn1,ftype2);sos2 = zp2sos(z2,p2,k2);% lpf
[z3,p3,k3] = butter(n,Wn2,ftype3);sos3 = zp2sos(z3,p3,k3);% bpf
[z4,p4,k4] = butter(n,Wn2,ftype4);sos4 = zp2sos(z4,p4,k4);% bsf
% Display magnitude and phase
fvtool(sos1,'freq') % ploting high pass filter
title('Magnitude Response(dB) and Phase Responce of IIR High Pass Filter')
legend('Magnitude','Phase')
fvtool(sos2,'freq')% ploting low pass filter
title('Magnitude Response(dB) and Phase Responce of IIR Low Pass Filter')
legend('Magnitude','Phase')
fvtool(sos3,'freq') % ploting band pass filter
title('Magnitude Response(dB) and Phase Responce of IIR Band-Pass Filter')
legend('Magnitude','Phase')
fvtool(sos4,'freq')% ploting band stop filter
title('Magnitude Response(dB) and Phase Responce of IIR Band-Stop Filter')
legend('Magnitude','Phase')