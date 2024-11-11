import pyodbc
from tkinter import Tk, Label, Button, Entry, messagebox

def connectBD():
    try:
        cnxn = pyodbc.connect('DRIVER=/usr/lib/oracle/12.2/client64/lib/libsqora.so.12.1;'
                              'DBQ=oracle0.ugr.es:1521/practbd.oracle0.ugr.es;'
                              'UID=x5350527;'
                              'PWD=x5350527'
        )
    except pyodbc.Error as ex:
        print("Error al conectar con la base de datos: ", ex)
        return None
    return cnxn

def obtener_importe_deuda(handler, id_cliente):
    handler.execute("SELECT Importe FROM Cliente WHERE ID=?", id_cliente)
    importe_cliente = handler.fetchone()

    if importe_cliente:
        return importe_cliente[0]
    else:
        return 0

def ver_importe_deuda(handler, id_cliente):
    # Obtener importe pendiente
    importe_pendiente = obtener_importe_deuda(handler, id_cliente)

    if importe_pendiente > 0:
        # Mostrar importe pendiente
        messagebox.showinfo("Importe Pendiente", f"El cliente debe: {importe_pendiente} €.")

        # Solicitar Método de Pago
        solicitar_metodo_pago(handler, id_cliente)
    else:
        messagebox.showinfo("Sin Deuda", "El cliente no tiene deudas pendientes.")

def solicitar_metodo_pago(handler, id_cliente):
    # Crear nueva ventana para solicitar el Método de Pago
    ventana_metodo_pago = Tk()
    ventana_metodo_pago.title("Solicitar Método de Pago")
    ventana_metodo_pago.geometry("300x120")

    # Configurar interfaz
    Label(ventana_metodo_pago, text="Método de Pago:").pack()
    metodo_pago_entry = Entry(ventana_metodo_pago)
    metodo_pago_entry.pack()

    Button(ventana_metodo_pago, text="Liquidar Pagos", command=lambda: liquidar_pagos(handler, id_cliente, metodo_pago_entry, ventana_metodo_pago)).pack()
    
    submit_button2 = Button(ventana_metodo_pago, text="Atrás", command=lambda: on_submit2(handler, ventana_metodo_pago)).pack()

    # Iniciar bucle principal de la interfaz gráfica
    ventana_metodo_pago.mainloop()

def liquidar_pagos(handler, id_cliente, metodo_pago_entry, ventana_metodo_pago):
    try:
        # Obtener Método de Pago ingresado por el usuario
        metodo_pago = metodo_pago_entry.get()

        if metodo_pago:
            # Realizar acciones de liquidación, por ejemplo, actualizar importes, generar registros de pagos, etc.

            # Establecer el importe del cliente a 0
            handler.execute("UPDATE Cliente SET Importe = 0 WHERE ID=?", id_cliente)
            handler.commit()

            # Mostrar confirmación de resultado
            messagebox.showinfo("Liquidación Exitosa", "Pagos liquidados correctamente.")
            
            # Cerrar la ventana de solicitud de Método de Pago
            ventana_metodo_pago.destroy()
        else:
            messagebox.showinfo("Error", "Debe ingresar un Método de Pago.")

    except pyodbc.Error as ex:
        messagebox.showinfo("Error al liquidar pagos: ", str(ex))
        
def on_submit2(handler, root):
	root.destroy()

def main():
    # Configuración de la conexión a la base de datos
    connection = connectBD()
    handler = connection.cursor()

    # Crear ventana
    ventana = Tk()
    ventana.title("Liquidar Pagos")
    ventana.geometry("300x120")

    # Configurar interfaz
    Label(ventana, text="ID del Cliente:").pack()
    entrada_id_cliente = Entry(ventana)
    entrada_id_cliente.pack()

    Button(ventana, text="Ver Deuda y Liquidar", command=lambda: ver_importe_deuda(handler, entrada_id_cliente.get())).pack()
    
    Button(ventana, text="Atrás", command=lambda: on_submit2(handler, ventana)).pack()
    
    # Iniciar bucle principal de la interfaz gráfica
    ventana.mainloop()

    # Cerrar la conexión a la base de datos al salir de la aplicación
    handler.close()

if __name__ == "__main__":
    main()

