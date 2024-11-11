import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import subprocess

def ejecutar_script(script_path):
    try:
        script = script_path + ".py"
        subprocess.run(["python3", script])
    except Exception as e:
        messagebox.showinfo(f"Error al ejecutar el script {script}: {e}")

if __name__ == "__main__":
    root_menu = tk.Tk()
    root_menu.title("Menú Clientes")
    root_menu.geometry("300x300")

    button = ttk.Button(root_menu, text=f" Dar de Alta Cliente ", command=lambda: ejecutar_script("RF2.1"))
    button.pack(pady=10)
    button = ttk.Button(root_menu, text=f" Dar de Baja Cliente ", command=lambda: ejecutar_script("RF2.2"))
    button.pack(pady=10)
    button = ttk.Button(root_menu, text=f" Reservar Actividad ", command=lambda: ejecutar_script("RF2.3"))
    button.pack(pady=10)
    button = ttk.Button(root_menu, text=f" Liquidar Pagos Cliente ", command=lambda: ejecutar_script("RF2.4"))
    button.pack(pady=10)
    button = ttk.Button(root_menu, text=f" Consultar Actividades Cliente ", command=lambda: ejecutar_script("RF2.5"))
    button.pack(pady=10)
    button = ttk.Button(root_menu, text=f" Cambiar Tipo de Cliente ", command=lambda: ejecutar_script("RF2.6"))
    button.pack(pady=10)

    root_menu.mainloop()
