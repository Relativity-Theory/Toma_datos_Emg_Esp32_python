import serial
import time
import csv

# Configuración de la conexión serial
COM = 'COM3'  # Cambia el puerto según sea necesario
BAUD = 921600  # Asegúrate de que coincida con la velocidad de la ESP32

# Inicializar la conexión con el ESP32
try:
    esp = serial.Serial(COM, BAUD, timeout=1)
    print(f"Conectado a {COM} a {BAUD} baudios.")
except serial.SerialException:
    print(f"No se pudo conectar a {COM}.")
    exit()

# Abrir el archivo CSV para escritura (modo 'a' para añadir datos)
try:
    with open('voltajes.csv', mode='a', newline='') as file:
        # Crear el objeto escritor de CSV
        writer = csv.writer(file)

        # Escribir la cabecera solo si el archivo está vacío
        if file.tell() == 0:
            writer.writerow(['Tiempo (ms)', 'Voltaje (V)'])  # Cambiar a milisegundos en la cabecera

        # Obtener el tiempo inicial en milisegundos desde el inicio del programa
        tiempo_inicial = time.time() * 1000  # Guardar el tiempo inicial en milisegundos

        # Leer datos continuamente
        try:
            while True:
                # Leer una línea desde el ESP32
                esp_leido = esp.readline().decode("utf-8").strip()

                # Si se lee algo, convertir a flotante
                if esp_leido:
                    try:
                        Volts = float(esp_leido)
                    except ValueError:
                        # Si el dato no puede ser convertido a float, continuar
                        print("Dato inválido recibido:", esp_leido)
                        continue

                    # Obtener el tiempo transcurrido en milisegundos
                    tiempo_actual_ms = (time.time() * 1000) - tiempo_inicial  # Calcular tiempo transcurrido

                    # Imprimir los datos en la terminal
                    print(f"Tiempo: {tiempo_actual_ms:.2f} ms, Voltaje: {Volts:.4f} V")

                    # Escribir los datos en el CSV
                    writer.writerow([tiempo_actual_ms, Volts])

                    # Forzar escritura en el archivo inmediatamente
                    file.flush()

                # Pequeño retraso para no saturar el procesamiento
                time.sleep(0.000125)  # Ajusta el retraso según sea necesario

        except KeyboardInterrupt:
            print("Lectura interrumpida por el usuario.")

finally:
    # Cerrar la conexión serial al salir
    esp.close()
    print("Conexión serial cerrada.")
