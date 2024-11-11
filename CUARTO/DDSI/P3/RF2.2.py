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

def borrarCliente(handler, id_cliente):
    try:
    
    	# Verificar y eliminar el trigger si existe
        drop_if_exists(handler, "TRIGGER", "deudas_check")
        # Crear trigger para verificar si hay deudas
        handler.execute('''
		    CREATE OR REPLACE TRIGGER deudas_check
		    BEFORE DELETE ON Cliente
		    FOR EACH ROW
		    BEGIN
		        IF :OLD.importe > 0 THEN 
		            raise_application_error(-19998, 'No se puede eliminar a un cliente con deudas.');
		        END IF;
		    END;
		''')
		
        handler.execute("SELECT COUNT(*) FROM Cliente WHERE ID = ?", id_cliente)
        resultado = handler.fetchone()
        
        if resultado[0] > 0:
            handler.execute("DELETE FROM Cliente WHERE ID = ?", id_cliente)
            handler.execute("DELETE FROM Inscripcion WHERE ID_cliente = ?", id_cliente)
		
        messagebox.showinfo("Inserción Exitosa", f"Cliente con ID {id_cliente} ha sido borrado correctamente.")
    except pyodbc.Error as ex:
        messagebox.showinfo("Error al borrar cliente: ", str(ex))
        
def on_submit(handler, root, id_entry):
    id_cliente = id_entry.get()

    if not id_cliente:
        messagebox.showinfo("Error", "Por favor, complete el campo necesario.")
        return

    # Insertar el trabajador
    borrarCliente(handler, id_cliente)

    # Cerrar la ventana
    root.destroy()
    
def on_submit2(handler, root):
	root.destroy()

def main():
    connection = connectBD()
    handler = connection.cursor()

    root = tk.Tk()
    root.title("Borrar Cliente")
    root.geometry("300x200")

    tk.Label(root, text="ID del cliente:").grid(row=0, column=0, padx=10, pady=10)

    id_entry = ttk.Entry(root)
    id_entry.grid(row=1, column=0, padx=10, pady=10)

    borrar_button = ttk.Button(root, text="Borrar Cliente", command=lambda: on_submit(handler, root, id_entry))
    borrar_button.grid(row=2, column=0, columnspan=2, pady=10)
    
    submit_button2 = ttk.Button(root, text="Atrás", command=lambda: on_submit2(handler, root))
    submit_button2.grid(row=3, column=0, columnspan=2, pady=10)


    root.grid_rowconfigure(3, weight=1)
    root.grid_columnconfigure(0, weight=1)

    root.mainloop()

    connection.commit()
    connection.close()

if __name__ == "__main__":
    main()

