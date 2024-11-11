import pyodbc
import datetime

# Función para conectar a la base de datos
def connect_to_db():
    conn = pyodbc.connect('DRIVER=/usr/lib/oracle/12.2/client64/lib/libsqora.so.12.1;'
                              'DBQ=oracle0.ugr.es:1521/practbd.oracle0.ugr.es;'
                              'UID=x5350527;'
                              'PWD=x5350527'
        )
    return conn

def insert_trabajadores(cursor):
    # Insertar datos en Trabajador
    cursor.execute('''
        INSERT INTO Trabajador (ID, Nombre, Apellidos, FechaNacimiento, Area, FechaFinContrato)
        VALUES ('123456789012', 'Juan Andres', 'Mauricio Martin', TO_DATE('2001-07-03', 'YYYY-MM-DD'), 'Administración', TO_DATE('2025-01-11', 'YYYY-MM-DD'));
    ''')

    cursor.execute('''
        INSERT INTO Trabajador (ID, Nombre, Apellidos, FechaNacimiento, Area, FechaFinContrato) 
        VALUES ('234567890123', 'Dani', 'Alconchel Calvo', TO_DATE('2001-11-18', 'YYYY-MM-DD'), 'Mantenimiento', TO_DATE('2025-06-15', 'YYYY-MM-DD'));
    ''')

    cursor.execute('''
        INSERT INTO Trabajador (ID, Nombre, Apellidos, FechaNacimiento, Area, FechaFinContrato) 
        VALUES ('345678901234', 'Luis', 'Crespo Ortiz', TO_DATE('1931-04-06', 'YYYY-MM-DD'), 'Hostelería', TO_DATE('2024-12-31', 'YYYY-MM-DD'));
    ''')

    cursor.execute('''
        INSERT INTO Trabajador (ID, Nombre, Apellidos, FechaNacimiento, Area, FechaFinContrato)
        VALUES ('456789012345', 'Ximo', 'San Olivares', TO_DATE('2002-11-11', 'YYYY-MM-DD'), 'Recepción', TO_DATE('2026-05-10', 'YYYY-MM-DD'));
    ''')

    try:
        # Intentar insertar datos que puedan disparar el trigger
        cursor.execute('''
            INSERT INTO Trabajador (ID, Nombre, Apellidos, FechaNacimiento, Area, FechaFinContrato) 
            VALUES ('T001', 'Juan', 'Pérez', TO_DATE('2010-01-15', 'YYYY-MM-DD'), 'Administración', TO_DATE('2002-11-11', 'YYYY-MM-DD'));
        ''')
    except pyodbc.Error as e:
        # Capturar y manejar la excepción específica
        if "ORA-20000" in str(e):
            print("Error de trigger: La edad del trabajador debe ser al menos 16 años.")
        else:
            raise


def insert_clientes(cursor):
    try:
        # Insertar datos en Cliente
        cursor.execute('''
            INSERT INTO Cliente (ID, Nombre, Apellidos, NumeroTelefono, CorreoElectronico, TipoCliente, Importe) 
            VALUES ('C001', 'Ana', 'García Ruiz', '600123456', 'ana.garcia@mail.com', 3, 1200.00)
        ''')
        cursor.execute('''
            INSERT INTO Cliente (ID, Nombre, Apellidos, NumeroTelefono, CorreoElectronico, TipoCliente, Importe) 
            VALUES ('C002', 'Luis', 'Martínez López', '610234567', 'luis.martinez@mail.com', 2, 800.50)
        ''')
        cursor.execute('''
            INSERT INTO Cliente (ID, Nombre, Apellidos, NumeroTelefono, CorreoElectronico, TipoCliente, Importe) 
            VALUES ('C003', 'María', 'Pérez Jiménez', '620345678', 'maria.perez@mail.com', 5, 500.00)
        ''')
        cursor.execute('''
            INSERT INTO Cliente (ID, Nombre, Apellidos, NumeroTelefono, CorreoElectronico, TipoCliente, Importe) 
            VALUES ('C004', 'Jorge', 'Fernández Álvarez', '630456789', 'jorge.fernandez@mail.com', 1, 1500.25)
        ''')
    except pyodbc.Error as e:
        print("Error al insertar cliente:", e)
        raise


def insert_actividades(cursor):
    try:
        # Insertar datos en Actividad
        cursor.execute("""
            INSERT INTO Actividad (Nombre, Lugar, Tipo, Fecha, Hora_inicio, Hora_fin, Num_max, ID_trabajador) 
            VALUES ('Aquagym Avanzado', 'Piscina interior', 4, TO_DATE('2023-12-05', 'YYYY-MM-DD'), 
                    TO_TIMESTAMP('08:00:00', 'HH24:MI:SS'), TO_TIMESTAMP('10:00:00', 'HH24:MI:SS'), 30, '123456789012')
        """)
        
        cursor.execute("""
            INSERT INTO Actividad (Nombre, Lugar, Tipo, Fecha, Hora_inicio, Hora_fin, Num_max, ID_trabajador) 
            VALUES ('Conferencia de Ximo Sanz', 'Sala de conferencias 1', 1, TO_DATE('2023-12-10', 'YYYY-MM-DD'), 
                    TO_TIMESTAMP('09:30:00', 'HH24:MI:SS'), TO_TIMESTAMP('10:30:00', 'HH24:MI:SS'), 150, '345678901234')
        """)
        
        cursor.execute("""
            INSERT INTO Actividad (Nombre, Lugar, Tipo, Fecha, Hora_inicio, Hora_fin, Num_max, ID_trabajador) 
            VALUES ('Parapente', 'Azotea', 5, TO_DATE('2023-12-15', 'YYYY-MM-DD'), 
                    TO_TIMESTAMP('17:30:00', 'HH24:MI:SS'), TO_TIMESTAMP('18:00:00', 'HH24:MI:SS'), 3, '345678901234')
        """)
        
        cursor.execute("""
            INSERT INTO Actividad (Nombre, Lugar, Tipo, Fecha, Hora_inicio, Hora_fin, Num_max) 
            VALUES ('Taller de Fotografía', 'Planta Subterránea', 2, TO_DATE('2024-01-10', 'YYYY-MM-DD'), 
                    TO_TIMESTAMP('12:00:00', 'HH24:MI:SS'), TO_TIMESTAMP('14:00:00', 'HH24:MI:SS'), 15)
        """)
    except pyodbc.Error as e:
        print("Error al insertar actividades:", e)
        raise


def insert_inscripciones(cursor):
    try:
        # Insertar datos en Inscripcion
        cursor.execute("INSERT INTO Inscripcion (ID_cliente, ID_actividad) VALUES ('C001', 1)")
        cursor.execute("INSERT INTO Inscripcion (ID_cliente, ID_actividad) VALUES ('C002', 1)")
        cursor.execute("INSERT INTO Inscripcion (ID_cliente, ID_actividad) VALUES ('C003', 2)")
        cursor.execute("INSERT INTO Inscripcion (ID_cliente, ID_actividad) VALUES ('C004', 2)")
        cursor.execute("INSERT INTO Inscripcion (ID_cliente, ID_actividad) VALUES ('C002', 3)")
    except pyodbc.Error as e:
        print("Error al insertar inscripciones:", e)
        raise

def main():
    conn = connect_to_db()
    cursor = conn.cursor()
    
    insert_trabajadores(cursor)
    insert_clientes(cursor)
    insert_actividades(cursor)
    insert_inscripciones(cursor)

    conn.commit()
    conn.close()

if __name__ == "__main__":
    main()
