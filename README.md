# Edge Computing: CP02 - Monitorador de luminosidade, temperatura e umidade

### Introdução
Como andamento ao projeto iniciado no CP01, de monitorador de luminosidade (https://github.com/Projetos-Fiap/Edge-Computing-CP01), agora nesta continuação do projeto temos a implementação de um novo sensor de temperatura e umidade, além de um display LCD que exibirá os valores medidos e mensagens. Este projeto é pensado para o case da Vinheria Agnello, para que possa ser usado para um melhor controle do armazenamento de garrafas de vinho.

### Funcionamento
O projeto utiliza como plataforma principal a placa Arduino Uno R3. Conectada nela temos nossos sensores: sensor de luz fotossensível (LDR) para medições de luminosidade; e sensor DHT11 para medições de temperatura e umidade. As medições de luminosidade serão exibidas através dos leds ou acionamento do buzzer, [conforme a primeira iteração do projeto](https://github.com/Projetos-Fiap/Edge-Computing-CP01). Já as medições de temperatura e umidade serão exibidas no display LCD, junto de mensagens informando se os níveis estão adequados ou não. Caso o nível dessas esteja inadequado, também haverá acionamento do buzzer e do led amarelo.

### Sensor DHT11 e Tinkercad
Devido ao fato de o Tinkercad (site onde construímos o protótipo) não possuir integração com o sensor DHT11, para poder simular o funcionamento do mesmo utilizamos [este workaround.](https://www.tinkercad.com/things/9WHnuYNu9yi?sharecode=UuRaVDHLUnUC2ORzrE93pCbKduzNpLg-csoohQ38FVg)

### Grupo
<li>Alessandra Vaiano (RM551497)</li>  
<li>André Lambert (RM99148)</li>  
<li>Bryan Willian (RM551305)</li>
<li>Lucas Feijó (RM99727)</li>
<li>Vitor Maia (RM99658)</li>

### Simulação do Protótipo
[Link para o Tinkercad](https://www.tinkercad.com/things/1vXcAVCbZBl?sharecode=caKTJyt3ogsLfUcALX4isB_AXl_5_HU-LPwECA3DLA0)

### Componentes utilizados
<li>Arduino Uno R3</li>
<li>LCD 16x2</li>
<li>Sensor LDR (para luminosidade)</li>
<li>Sensor DHT11 (para temperatura e umidade)</li>
<li>Protoboard</li>
<li>LEDs</li>
<li>Potênciometros</li>
<li>Resistores</li>
<li>Buzzer</li>
<li>Cabos Jumper</li>

### Código Tinkercad
O código para a simulação se encontra no arquivo "arduino.c". 

### Código Montagem Hands-on
O código utilizado na montagem em sala, com hardware real, se encontra no arquivo "arduinoHandsOn.c". Aqui fizemos algumas substituições de valores para podermos demonstrar o funcionamento do mesmo, (dada Temperatura e Umidade fixos) e também trabalhamos com o sensor DHT11 que já lê nativamente temperatura e umidade (desde que haja importação de sua biblioteca), não necessitando fazer a conversão desses valores como ocorreu na simulação.
Utilize o software Arduino IDE para carregar este código para a placa, via USB.

### Imagem do circuito
![Imagem](https://github.com/Projetos-Fiap/Edge-Computing-CP02/blob/main/circuit_cp02.png?raw=true)
