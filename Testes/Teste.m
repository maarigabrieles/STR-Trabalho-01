tem_resp_ref = 50; %ms Para o controle de temperatura.
base = importdata('dados_tempo_resposta.txt');
t1 = base(:,1); %(amostras de tempo controle de temperatura)
t2 = base(:,2); %(amostras de tempo controle de nível)
t1=t1./1000;%transforma dados em ms (amostras de tempo controle de temperatura em (ms))
t2=t2./1000;%Transforma dados em ms (amostras de tempo controle de nível em (ms))
%t1=t1.*1000;%transforma dados em ms (amostras de tempo controle de temperatura em (ms))
%t2=t2.*1000;
%%===========================================================================================================%%
%%Plotagem do gráfico HWM e o Histograma para das amostras para o tempo de resposta de controle de temperatura
figure(1);

subplot(2,1,1)
%bar(v)
plot(1:length(t1),t1,1:length(t1),tem_resp_ref.*ones(length(t1),1))
title('HWM e o Histograma para o tempo das resposta de controle de temperatura', 'fontweight','bold','fontsize',10)
%axis([0 length(v) 0 1.1*max(v)])
axis([0 length(t1) 0 120])
xlabel('Casos de Teste','fontweight','bold','fontsize',10)
ylabel('Tempo de Resposta [ms]','fontweight','bold','fontsize',10)

subplot(2,1,2)
[h,x]=hist(t1,[min(t1):0.5:max(t1)]);
bar(x,h);
colormap lines
axis([(min(t1)-0.1) 60 0 1.1*max(h)])
xlabel('Tempo de Resposta [ms]','fontweight','bold','fontsize',10)
ylabel('Frequência','fontweight','bold','fontsize',10)

%%=============================================================================================================================
%Plotar o gráfico com os deadlines perdidos para a tarefa de controle de temperatura

y_temp = 0; %Para a contagem dos deadlines perdidos da tarefa de controle de temperatura
deadline_temp = zeros(length(t1),1); %Recebe a contagem dos deadlines perdidos em cada ídice do vetor isso em um intervalo de 20 em 20
aux_temp = zeros(length(t1),1);
cont = 0;

for i = 1:length(t1)
    if t1(i,1) > tem_resp_ref        %Compara se o valor do tempo em resposta foi maior que o deadline definido, caso sim, insere o valor 
        aux_temp(i,1) = t1(i,1);
        y_temp = y_temp + 1; % Vai somando os deadlines perdidos
        %y_temp = 1 ;
        deadline_temp(i,1) = y_temp; %Vai acrescentando +1 em ordem, ou seja 1,2,3 em cada índice, obs: isso de forma consecultiva, caso não zera o índice
        
    else
        y_temp = 0; %Tarefa cumprida, y recebe zero e recomeça a contagem 
        deadline_temp(i,1) = y_temp; %zera o índice pois não teve deadline perdido
        cont = cont+1;  %Conta o número de deadlines executados, para cálculo da porcentagem
        aux_temp(i,1) = 0;  %caso não, insere zero na posição
    end
end

porcentagem = (cont.*100)./length(t1); %Calcula a porcentagem das amostras que cumpriram o deadline definido no requesito
figure(2);
plot(1:length(aux_temp),aux_temp,1:length(aux_temp),tem_resp_ref.*ones(length(aux_temp),1))
title('Medição do deadline perdido da tarefa periódica do controle de temperatura', 'fontweight','bold','fontsize',10)
%axis([0 length(v) 0 1.1*max(v)])
axis([0 length(aux_temp) 0 120])
xlabel('Casos de Teste','fontweight','bold','fontsize',10)
ylabel('Tempo de Resposta [ms]','fontweight','bold','fontsize',10)

%%================================================================================================================================%%
%  PLOTAGEM DO GRÁFICO (m, k)-firme - PARA TAREFA DE CONTROLE DE TEMPERATURA

%Uma tarefa cumpre "m" deadlines em qualquer janela de "k" ativações consecultivas
%Temos m <= k, caso m = k todos os deadlines precisam ser cumpridos
%Plotagem do gráfico (m,k)-firme para k =20
soma_temp = zeros(length(t1),1);
for k_temp = 20:length(t1)
   soma_temp(k_temp, 1) = sum(deadline_temp(k_temp-19:k_temp, 1)); %Soma os resultados de dos índices 1 - 20, 21 - 40, 41 - 60 e assim vai varrendo 20 elementos
   
end
figure(3);
plot(1:length(t1),soma_temp)
title('Medição do deadline perdido: (m,20)-firme para a tarefa de controle de temperatura','fontweight','bold','fontsize',8)
%axis([0 length(v) 0 1.1*max(v)])
axis([0 length(t1) 0 4])
xlabel('Casos de Teste','fontweight','bold','fontsize',10)
ylabel('Deadline perdido a cada ativação','fontweight','bold','fontsize',10)

%%==============================================================================================================

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %                           THE END