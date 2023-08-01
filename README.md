# LCD-1602-serie
Interfase entre cualquier micro y un display alfanumerico de 16x2 en modo serie por pines cualquiera del micro
La idea es comunicar el display con cualquier micro utilizando la menor cantidad de pines, esto se logra con una 
comunicacion serie mas un circuito integrado que en principio utilizaria 3 pines de control y datos pero manejando los estados de 
2 de esos pines comandamos el tercero.
Este tercer pin es el latch de registro de desplazamiento y hay que tener en cuenta los valores de los componentes asociados al mismo
y tambien hay que tener en cuenta los tiempos de conmutacion entre estados manejados por el software. Asi como esta todo, elcircuito 
esta funcionando con un ATMega168A a 8Mhz y con un ESP32 a 240Mhz, este circuito y software esta en etapa de prueba  y debera ser testeado
por quien quiera utilizarlo, y sera responsabilidad del mismo por su uso en cualquier aplicacion, critica y no critica.
