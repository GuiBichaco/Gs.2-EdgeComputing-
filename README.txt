Projeto para a matéria de Edge computing e computer Systems da faculdade FIAP - para o trabalho Global Solution do Segundo Semestres 2023 em conjunto e parceria com a hapvida e NotreDame Intermédica

APLICAÇÃO IoT - DermaTech


Nós fundadores e desenvolvedores da  DermaTech, produzimos um projeto em IoT com a placa ESP32, onde com o sensor de distância simulamos uma camêra aclopada a uma IA onde irá executar funções,
de acordo com a gravidade do caso do paciente. Ela inclui sinais luminosos e sonoros para assim chamar a atenção do usuário sobre algo que possa afetar gravimente sua saúde e qualidade de vida.

Entendimento do Problema:

O câncer de pele e outras condições dermatológicas são comuns, mas nem sempre são detectados precocemente. 
Muitas pessoas podem não ter acesso imediato a cuidados médicos especializados, levando a atrasos no diagnóstico e tratamento. 
Este aplicativo visa fornecer uma solução acessível e rápida para a detecção preliminar de problemas de pele usando a câmera do celular. 
Além disso, o aplicativo busca facilitar o acesso a clínicas dermatológicas especializadas.

Objetivo do Produto:

Desenvolver um aplicativo móvel que utilize inteligência artificial para analisar imagens da pele capturadas pela câmera do celular, 
oferecendo aos usuários uma avaliação preliminar de possíveis problemas dermatológicos. 
O aplicativo também incluirá um sistema de mapeamento de clínicas dermatológicas para facilitar o agendamento de consultas.


ATENÇÃO : 

Essa aplicação pode ser facilmente projetada por pessoas fora da área com esta documentação.
Em caso de ter os sistemas listados em sua máquina no site dos mesmos, é de fácil compreensão a instalação.


Conceito de IoT:

A Internet das Coisas (IoT) é uma rede de objetos físicos com sensores e conectividade à internet, que coletam dados do ambiente ou do próprio dispositivo e os enviam para servidores ou outros dispositivos para tomada de decisões. A IoT desempenha um papel importante em áreas como automação, saúde, sustentabilidade e cidades inteligentes, melhorando a eficiência e a qualidade de vida da sociedade.


-> Wokwi

Com o software online de acesso (https://wokwi.com) WOKWI, você deverá desenvolver seu código de acordo com o uso da sua placa. A linguagem adequada é o C++ (nossos códigos-fonte estarão mais abaixo desta documentação). A plataforma Wokwi é responsável pela compilação do código programado para o seu circuito em C++ para ser lido pela firmware da placa.
Ele já da o suporte para a construção do código em .ino, próprio para a aplicação no software ARDUINO para aplicação em projetos físicos. 

Montagem - 

1 - Buzzer
1 - Resistor ( 1 KΩ )
3 - Resistor ( 220 Ω )
14 - Cabos
1 - Placa ESP32
1 - Sensor de Distancia Ultrassonico
3 - Leds (Amarela, Verde, Vermelha)

O código da aplicação está aplicado no mesmo link abaixo e no repositório do projeto. 
Siga a montagem do esquema proposto no link a seguir -> https://wokwi.com/projects/381523421085532161

Ao terminar o código no wokwi, vá em "Save". Logo em seguida, vá no "Play" verde e execute o projeto.


-> Node-Red

Ele será responsável pela construção do fluxo do servidor local, onde conecta todos os passos até aqui em um único nó de conexão. Via protocolo de comunicação MQTT, ele será conectado a um servidor próprio para a construção das devices e do dashboard.

A instalação do Node-Red é simples:

- Faça a instalação do Node.js (Versão LTS) (node-version) - [www.nodejs.org](www.nodejs.org)
- Abra o CMD e digite (npm install -g --unsafe-perm node-red)
- Para acessar o serviço, após instalado, digite no cmd: node-red
- Acesse no browser: [http://localhost:1880](http://localhost:1880)

Após abrir o programa, vá nas três barrinhas no canto superior direito, "Gerenciar Paletas" e baixe a biblioteca node-red-dashboard.

O código fonte de exemplo está na documentação do projeto.

Nele foram implementados:

A comunicação de entrada do MQTT ao topic do código, MQTT IN, ligado a uma função onde irá executar a lógica do projeto, por fim o flow se conecta a um delay para o MQTT OUT que é a saida 
da conexão e ao painel do dashboard onde tudo é exibido de forma clara e monitorada. 

Para dúvidas, contate a equipe técnica:

- Guilherme Catelli Bichaco - 97989
- Vinicius Sobreira Borges - 97767