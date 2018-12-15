clear;
close all;

fs = 1000000; %Sampling time para o vetor de tempo
t = [0:1/fs:0.1]; %Vetor de tempo
f = 2000; %Frequ�ncia do sinal principal
fr = 60; %Frequencia do Ruido (motor)
As = 3; %Amplitude do sinal principal
Ae = 1.5; %Amplitude do sinal de eco
Ar = 3; %Amplitude do ruido (motor)
acc = 0; %acumulador para gera��o do sinal principal
acc1 = 0; %acumulador para gera��o do sinal de eco
acc2 = 0; %acumulador para gera��o do sinal de ru�do (motor)

%%Gera��o do sinal principal. Foi modificado o par�metro de parada do FOR
%%para testar quantas harmonicas eram necessarias para a gera��o de um
%%sinal aproximadamente quadrado
for i=1:2:100
% for i=1:2:3
  v = (As/i)*sin(2*pi*i*f*t);
  acc = acc + v;
end

%%Plot do sinal principal

% plot(t,acc);
% title('Sinal digital formado pelo somat�riode sen�ides');

%%Plot do espectro de frequencia do sinal principal
%my_fft(acc, fs);

%%Gera��o do sinal de eco

% for i=1:2:100
%   eco = (Ae/i)*sin(2*pi*i*f*t+pi/2);
%   acc1 = acc1 + eco;
% end  
% 
%%Plot do sinal de Eco

% figure 
% plot(t,acc1)
% title('Sinal de eco')
% 
%%Plot do sinal + Eco

% figure
% plot(t,acc+acc1)
% title('Sinal + eco')

%Gera��o do sinal de ru�do (motor)
for i=1:2:1
  noise = (Ar/i)*sin(2*pi*i*60*t);
  acc2 = acc2 + noise;
end  

%%Plot do Ru�do
figure
plot(t,acc2);
title('Ru�do');

%%Plot do Sinal + Ru�do
figure;
plot(t,acc+acc2);
title('Sinal + Ru�do');