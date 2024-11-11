import pyodbc
import tkinter as tk
from tkinter import ttk, Label, Entry, Button, messagebox

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

def cambiar_tipo_cliente(handler, id_cliente, nuevo_tipo, root):
    try:
        handler.execute("UPDATE Cliente SET TipoCliente = ? WHERE ID = ?", nuevo_tipo, id_cliente)
        handler.commit()
        messagebox.showinfo("Éxito", "Tipo de cliente actualizado correctamente.")
        root.destroy()
    except pyodbc.Error as ex:
        messagebox.showinfo("Error", f"Error al actualizar el tipo de cliente: {str(ex)}")

def on_submitCambioTipo(handler, root, id_entry, nuevo_tipo_entry):
    id_cliente = id_entry.get()
    nuevo_tipo = nuevo_tipo_entry.get()

    if id_cliente and nuevo_tipo:
        cambiar_tipo_cliente(handler, id_cliente, nuevo_tipo, root)
    else:
        messagebox.showinfo("Información", "Por favor, complete todos los campos.")

def on_submit2(handler, root):
	root.destroy()

def main():
    connection = connectBD()
    handler = connection.cursor()

    root = tk.Tk()
    root.title("Cambiar Tipo de Cliente")
    root.geometry("300x180")

    Label(root, text="ID del cliente:").pack()
    id_entry = Entry(root)
    id_entry.pack()

    Label(root, text="Nuevo Tipo de Cliente:").pack()
    nuevo_tipo_entry = Entry(root)
    nuevo_tipo_entry.pack()

    cambiar_tipo_button = Button(root, text="Cambiar Tipo de Cliente", command=lambda: on_submitCambioTipo(handler, root, id_entry, nuevo_tipo_entry))
    cambiar_tipo_button.pack(pady=10)
    
    Button(root, text="Atrás", command=lambda: on_submit2(handler, root)).pack()

    root.mainloop()

    connection.commit()
    connection.close()

if __name__ == "__main__":
    main()

