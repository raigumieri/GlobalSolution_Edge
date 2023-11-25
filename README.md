<h1 align="center"> MedSearch - Gerenciamento de Estoque de Medicamentos - (Aplicação para Posto de Saúde) </h1>
<div align="center">
  <img src="https://github.com/raigumieri/GlobalSolution_Edge/assets/127215645/6d55232a-71ba-4542-8c88-8bc85dd0f0ed">
</div>
 
<h3> Integrantes do grupo: </h3>
<ul> 
  <li> Luiza Cristina da Silva RM:99367 1ESPI </li>
  <li> Raí Gumieri dos Santos RM:98287 1ESPI </li>
</ul>

<h4> Link do Wokwi: https://wokwi.com/projects/382291261738383361 </h4>

<br>

<h2 align="center"> Descrição do Problema de Saúde Abordado </h2>

<p align="justify"> O gerenciamento eficiente de medicamentos é crucial para garantir que os pacientes recebam os tratamentos necessários no momento certo. A falta de um medicamento pode impactar negativamente a saúde do paciente. Portanto, é essencial ter um sistema que permita aos pacientes verificar a disponibilidade de medicamentos em um posto de saúde sem sair de casa. </p>

<br>

<h2 align="center"> Visão Geral da Solução Proposta </h2>

<p align="justify"> A solução proposta é uma aplicação que utiliza um ESP32, uma balança HX711, um resistor e um LED verde para criar um sistema de gerenciamento de estoque de medicamentos. A balança HX711 será usada para medir o peso do medicamento, fornecendo assim uma estimativa do número de unidades disponíveis no estoque. O LED verde indicará se o medicamento está disponível ou não. </p>

<br>

<h2 align="center"> Configuração e Execução da Aplicação </h2>
<h3> Materiais Necessários: </h3>
<ul> 
  <li> ESP32; </li>
  <li> HX711 (com biblioteca HX711 instalada na IDE do Arduino); </li>
  <li> Resistor 330Ω </li>
  <li> LED verde; </li>
  <li> Conexões e cabos necessários. </li>
</ul>

<br>

<h3> Configuração do Hardware: </h3>
<h4> 1. Conecte o HX711 ao ESP32: </h4>
<ul> 
  <li> VCC do HX711 ao 3V3 do ESP32; </li>
  <li> GND do HX711 ao GND do ESP32; </li>
  <li> DT do HX711 ao pino digital (por exemplo, D2) do ESP32; </li>
  <li> SCK do HX711 ao pino digital (por exemplo, D3) do ESP32. </li>
</ul>

<h4> 2. Conecte o LED verde ao ESP32: </h4>
<ul> 
  <li> Anodo (maior perna) do LED ao resistor e, em seguida, a um pino digital (por exemplo, D4) do ESP32; </li>
  <li> Cátodo (menor perna) do LED ao GND do ESP32. </li>
</ul>

<br>

<h3>  Configuração do Software: </h3>
<h4> 1. Instale as Bibliotecas Necessárias: </h4>
<ul> 
  <li> - Instale as bibliotecas necessárias do ESP32, incluindo a biblioteca HX711. </li>
</ul>

<h4> 2. Carregue o Código no ESP32: </h4>
<ul> 
  <li> Abra o arquivo do código-fonte (Arduino sketch) na IDE do Arduino; </li>
  <li> Selecione a placa correta (ESP32) e a porta serial correta; </li>
  <li> Carregue o código no ESP32. </li>
</ul>

<h4> 3. Configurações Adicionais: </h4>
<ul> 
  <li> No código, ajuste os pinos usados para a conexão do HX711 e do LED, se necessário. </li>
</ul>

<h4> 4. Alimentação: </h4>
<ul> 
  <li> Alimente o ESP32 de acordo com as especificações. </li>
</ul>

<h4> 5. Montagem Física: </h4>
<ul> 
  <li> Monte a balança de forma a suportar os medicamentos; </li>
  <li> Certifique-se de que a balança está nivelada e calibrada. </li>
</ul>

<br>

<h3> Execução da Aplicação: </h3>
<ol>
  <li> Ligue o ESP32; </li>
  <li> A aplicação medirá o peso na balança HX711 e acenderá o LED verde se o medicamento estiver disponível; </li>
  <li> Os pacientes podem verificar a disponibilidade do medicamento por meio de uma interface online, que exibirá o dados coletados pelo protótipo; </li>
  <li> Certifique-se de manter a ESP32 conectada à Internet para que os dados possam ser acessados remotamente. </li>
</ol>

<h2 align="center"> Notas Adicionais </h2>

<ul> 
  <li> Certifique-se de seguir as práticas de segurança ao lidar com eletrônicos e conexões; </li>
  <li> Realize a calibração da balança para obter resultados precisos; </li>
  <li> Documente o endereço IP ou o hostname da ESP32 para que os pacientes possam acessar a interface online. </li>
</ul>

<br>

<h4 align="center"> Esperamos que essa solução facilite o acesso dos pacientes aos medicamentos necessários, proporcionando uma experiência mais conveniente e eficiente. </h4>
