

# Sistema em tempo real para monitoramento da qualidade da água em caixas-d'água residenciais

## Problema • Arquitetura • Instalação • Uso • API

### 🎯 Problema e Justificativa

A qualidade da água consumida é um fator crítico para a saúde pública. A negligência na limpeza e monitoramento das caixas-d'água residenciais pode ser uma fonte de contaminação, aumentando a probabilidade de riscos à segurança hídrica.
Alinhado com ODS 6 da ONU: Garantir a disponibilidade e gestão sustentável da água potável para todos

---------------------------------------------
### 🔬 Parâmetros Monitorados
#### Parâmetro	Faixa Ideal	Limite Crítico	Relevância
##### pH	6.5 - 8.5	<6.0 ou >9.0	Valores fora favorecem corrosão e reduzem eficácia do cloro
##### Turbidez	< 1 NTU	> 5 NTU	Indica riscos microbiológicos e prejudica desinfecção
##### Temperatura	< 25°C	> 30°C	Temperaturas elevadas favorecem proliferação bacteriana
---------------------------------------

### ⚙️ Arquitetura do Sistema

<img width="740" height="451" alt="image" src="https://github.com/user-attachments/assets/0cdabd75-3e80-4e6f-9f14-2b6fa76a9526" />

                            

### 🛠️ Componentes de Hardware
#### Componente	Função	Especificações

  - ESP32	Microcontrolador principal	Wi-Fi integrado, ADC 12-bit
  - Sensor de pH	Medir acidez/alcalinidade	Escala 0-14, sinal analógico
  - Sensor de Turbidez	Partículas em suspensão	Infravermelho, 0-1000 NTU
  - DS18B20	Temperatura da água	One-Wire, ±0.5°C precisão

### 💻 Componentes de Software
#### Componente	Tecnologia	Função

 - MQTT Broker	Node-RED	Comunicação IoT
 - Time Series	InfluxDB	Dados temporais
 - Dashboard	Grafana	Visualização em tempo real
   
### 🚀 Instalação

###### Instale as bibliotecas necessárias:
   ###### - PubSubClient (MQTT)
   ###### - OneWire
   ###### - DallasTemperature
   ###### - ArduinoJson


#### 📈 Resultados e Validação
O sistema demonstrou:

✅ Detecção precisa de variações de pH

✅ Identificação de turbidez anormal

✅ Monitoramento contínuo de temperatura

✅ Alertas automáticos via WhatsApp

✅ Dashboard em tempo real no Grafana

#### 🚧 Desafios e Aprendizados

1.Calibração de sensores requer procedimentos rigorosos

2.Estabilidade de conexões elétricas em ambiente úmido

3.Processamento de dados em tempo real com baixa latência

### Trabalhos Futuros
Integração com machine learning para predição de anomalias

Sensor de cloro residual

Monitoramento de nível de água

Expansão para condomínios e uso coletivo

App mobile nativo

Grupo 
Bruna Franca Martinez 
Geovanna da Silva Lima 
Guilherme Soares Santos 
Lucas Cesar Kato 
Pedro Henrique Mansano Fernandes 

Link do video do projeto : https://youtu.be/nbTk0TtNAxI

##### Inovação em monitoramento hídrico para um futuro mais seguro e sustentável

