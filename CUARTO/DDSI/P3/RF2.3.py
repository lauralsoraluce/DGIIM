import pyodbc
import logging
import os
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox

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

def drop_if_exists(cursor, object_type, object_name):
    try:
        cursor.execute(f"DROP {object_type} {object_name}")
    except pyodbc.Error as e:
        if "does not exist" not in str(e):
            raise
            
def obtenerTipoCliente(handler, id_cliente):
	handler.execute("SELECT TipoCliente FROM Cliente WHERE ID=?", id_cliente)
	resultado=handler.fetchone()
	
	if resultado:
		return resultado
	else:
		return None

def mostrarActividades(handler, id_cliente):
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
        
def reservarActividad(handler, root, id_cliente, id_actividad):
	try:
		
		handler.execute("INSERT INTO Inscripcion (ID_Cliente, ID_Actividad) VALUES (?,?)", (id_cliente, id_actividad))
		
		handler.commit()
		
		messagebox.showinfo("Busqueda Exitosa", f"Actividad reservada correctamente")
		
		root.destroy()
		
	except pyodbc.Error as ex:
		messagebox.showinfo("Error al reservar actividad: ", str(ex))

def actualizar_lista_actividades(handler, ventana, actividades, id_cliente):
    for widget in ventana.winfo_children():
        widget.destroy()
	
    ventana.geometry("500x150")
    tk.Label(ventana, text="Seleccione la actividad para reservar:").pack()

    for actividad in actividades:
        boton_actividad = ttk.Button(
            ventana,
            text=f"Actividad: {actividad[1]}, Fecha: {actividad[2]}, Hora: {actividad[3]}",
            command=lambda a=actividad[0]: reservarActividad(handler, ventana, id_cliente, a)
        )
        boton_actividad.pack()
    
    submit_button2 = ttk.Button(ventana, text="Atrás", command=lambda: on_submit2(handler, ventana)).pack() 

def on_submitM(handler, root, id_entry):
    id_cliente = id_entry.get()
    actividades_disponibles = mostrarActividades(handler, id_cliente)
    
    if actividades_disponibles:
        actualizar_lista_actividades(handler, root, actividades_disponibles, id_cliente)
    else:
        messagebox.showinfo("Información", "No hay actividades disponibles para este cliente.")

def on_submit2(handler, root):
	root.destroy()

def main():
    connection = connectBD()
    handler = connection.cursor()
    
    root = tk.Tk()
    root.title("Ver Actividades")
    root.geometry("300x150")

    tk.Label(root, text="ID del cliente:").grid(row=0, column=0, padx=10, pady=10)
    
    id_entry = ttk.Entry(root)
    id_entry.grid(row=0, column=1, padx=10, pady=10)

    submit_button = ttk.Button(root, text="Mostrar", command=lambda: on_submitM(handler, root, id_entry))
    submit_button.grid(row=1, column=0, columnspan=2, pady=10)
    
    submit_button2 = ttk.Button(root, text="Atrás", command=lambda: on_submit2(handler, root))
    submit_button2.grid(row=2, column=0, columnspan=2, pady=10)    

    root.mainloop()

    connection.commit()
    connection.close()

if __name__ == "__main__":
    main()

