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

def crearCliente(handler, id_cliente, nombre, apellidos, num_tfno, correo_electronico, tipo_cliente, importe):
    try:
        handler.execute("""
            INSERT INTO Cliente (ID, Nombre, Apellidos, NumeroTelefono, CorreoElectronico, TipoCliente, Importe) 
            VALUES (?, ?, ?, ?, ?, ?, ?)
            """, 
            (id_cliente, nombre, apellidos, num_tfno, correo_electronico, tipo_cliente, importe))
        
        handler.commit()
        
        messagebox.showinfo("Inserción Exitosa", f"Cliente con ID {id_cliente} ha sido insertado correctamente.")
    except pyodbc.Error as ex:
        messagebox.showinfo("Error al insertar cliente: ", str(ex))
        
def on_submit(handler, root, id_entry, nombre_entry, apellidos_entry, tfno_entry, correo_entry, tipo_entry, importe_entry):
    id_cliente = id_entry.get()
    nombre = nombre_entry.get()
    apellidos = apellidos_entry.get()
    num_tfno = tfno_entry.get()
    correo_electronico = correo_entry.get()
    tipo_cliente = tipo_entry.get()
    importe = importe_entry.get()

    if not all([id_cliente, nombre, apellidos, num_tfno, correo_electronico, tipo_cliente]):
        messagebox.showinfo("Error", "Por favor, complete todos los campos.")
        return

    # Insertar el cliente
    crearCliente(handler, id_cliente, nombre, apellidos, num_tfno, correo_electronico, tipo_cliente, importe)

    # Cerrar la ventana
    root.destroy()
    
def on_submit2(handler, root):
	root.destroy()

def main():
    connection = connectBD()
    handler = connection.cursor()

    root = tk.Tk()
    root.title("Alta de Cliente")
    root.geometry("400x400")

    tk.Label(root, text="ID del cliente:").grid(row=0, column=0, padx=10, pady=10)
    tk.Label(root, text="Nombre:").grid(row=1, column=0, padx=10, pady=10)
    tk.Label(root, text="Apellidos:").grid(row=2, column=0, padx=10, pady=10)
    tk.Label(root, text="Número de teléfono:").grid(row=3, column=0, padx=10, pady=10)
    tk.Label(root, text="Correo electrónico:").grid(row=4, column=0, padx=10, pady=10)
    tk.Label(root, text="Tipo de cliente:").grid(row=5, column=0, padx=10, pady=10)
    tk.Label(root, text="Importe:").grid(row=6, column=0, padx=10, pady=10)

    id_entry = ttk.Entry(root)
    id_entry.grid(row=0, column=1, padx=10, pady=10)

    nombre_entry = ttk.Entry(root)
    nombre_entry.grid(row=1, column=1, padx=10, pady=10)

    apellidos_entry = ttk.Entry(root)
    apellidos_entry.grid(row=2, column=1, padx=10, pady=10)

    tfno_entry = ttk.Entry(root)
    tfno_entry.grid(row=3, column=1, padx=10, pady=10)

    correo_entry = ttk.Entry(root)
    correo_entry.grid(row=4, column=1, padx=10, pady=10)

    tipo_entry = ttk.Entry(root)
    tipo_entry.grid(row=5, column=1, padx=10, pady=10)
    
    importe_entry = ttk.Entry(root)
    importe_entry.grid(row=6, column=1, padx=10, pady=10)

    submit_button = ttk.Button(root, text="Dar de Alta", command=lambda: on_submit(handler, root, id_entry, nombre_entry, apellidos_entry, tfno_entry, correo_entry, tipo_entry, importe_entry))
    submit_button.grid(row=7, column=0, columnspan=2, pady=10)
    
    submit_button2 = ttk.Button(root, text="Atrás", command=lambda: on_submit2(handler, root))
    submit_button2.grid(row=8, column=0, columnspan=2, pady=10)

    root.grid_rowconfigure(82, weight=1)
    root.grid_columnconfigure(1, weight=1)

    root.mainloop()

    connection.commit()
    connection.close()

if __name__ == "__main__":
    main()

