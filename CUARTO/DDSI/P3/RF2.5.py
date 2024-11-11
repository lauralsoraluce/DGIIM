import pyodbc
import logging
import os
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox, Label, Button

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

def obtenerTipoCliente(handler, id_cliente):
    handler.execute("SELECT TipoCliente FROM Cliente WHERE ID=?", id_cliente)
    resultado = handler.fetchone()

    if resultado:
        return resultado
    else:
        return None

def mostrarActividades(handler, tipo_cliente):
    handler.execute("SELECT ID_actividad, Nombre, Fecha, Hora_inicio FROM Actividad WHERE Tipo<=?", tipo_cliente)
    resultado = handler.fetchall()

    for actividad in resultado:
        actividad[2] = actividad[2].strftime('%d/%m/%Y')
        actividad[3] = actividad[3].strftime('%H:%M:%S')
    return resultado
    
def mostrarActividadesCliente(handler, id_cliente):
    tipo_cliente = obtenerTipoCliente(handler, id_cliente)

    if tipo_cliente:
        tipo_cliente = tipo_cliente[0]  # Obtener el valor del tipo de cliente
        handler.execute("""
            SELECT ID_actividad, Nombre, Fecha, Hora_inicio
            FROM Actividad
            WHERE Tipo <= ? AND ID_actividad NOT IN (
                SELECT ID_actividad FROM Inscripcion WHERE ID_cliente=?
            )
        """, tipo_cliente, id_cliente)
        resultado = handler.fetchall()

        for actividad in resultado:
            actividad[2] = actividad[2].strftime('%d/%m/%Y')
            actividad[3] = actividad[3].strftime('%H:%M:%S')
        return resultado
    else:
        messagebox.showinfo("Información", "No se encontró el tipo de cliente para el ID proporcionado.")
        return []

def actualizar_lista_actividades(handler, ventana, actividades, id_cliente=None, tipo_cliente=None):
    for widget in ventana.winfo_children():
        widget.destroy()

    ventana.geometry("550x150")
    tk.Label(ventana, text="Actividades disponibles para el cliente:").pack()

    for actividad in actividades:
        texto_actividad = f"ID: {actividad[0]}, Nombre: {actividad[1]}, Fecha: {actividad[2]}, Hora: {actividad[3]}"
        Label(ventana, text=texto_actividad).pack()

    back_button = Button(ventana, text="Back", command=lambda: volver_pantalla_inicial(ventana))
    back_button.pack()

def volver_pantalla_inicial(ventana):
    ventana.destroy()
    main()

def on_submitM(handler, root, id_entry, tipo_entry):
    id_cliente = id_entry.get()
    tipo_cliente = tipo_entry.get()

    if not id_cliente and tipo_cliente:
        # Si no se introduce id_cliente pero se introduce tipo_cliente, mostrar directamente las actividades
        actividades_disponibles = mostrarActividades(handler, tipo_cliente)
        actualizar_lista_actividades(handler, root, actividades_disponibles)
    elif id_cliente:
        actividades_disponibles = mostrarActividadesCliente(handler, id_cliente)
        actualizar_lista_actividades(handler, root, actividades_disponibles, id_cliente, tipo_cliente)
    else:
        messagebox.showinfo("Información", "Por favor, proporcione al menos el ID del cliente o el Tipo de cliente.")

def on_submit2(handler, root):
	root.destroy()

def main():
    connection = connectBD()
    handler = connection.cursor()
    
    root = tk.Tk()
    root.title("Ver Actividades")
    root.geometry("350x180")

    tk.Label(root, text="ID del cliente:").grid(row=0, column=0, padx=10, pady=10)
    
    id_entry = ttk.Entry(root)
    id_entry.grid(row=0, column=1, padx=10, pady=10)
    
    tk.Label(root, text="Tipo de cliente:").grid(row=1, column=0, padx=10, pady=10)
    
    tipo_entry = ttk.Entry(root)
    tipo_entry.grid(row=1, column=1, padx=10, pady=10)
		
	
    submit_button = ttk.Button(root, text="Mostrar", command=lambda: on_submitM(handler, root, id_entry, tipo_entry))
    submit_button.grid(row=2, column=0, columnspan=2, pady=10)
    
    submit_button2 = ttk.Button(root, text="Atrás", command=lambda: on_submit2(handler, root))
    submit_button2.grid(row=8, column=0, columnspan=2, pady=10)

    root.mainloop()

    connection.commit()
    connection.close()

if __name__ == "__main__":
    main()

