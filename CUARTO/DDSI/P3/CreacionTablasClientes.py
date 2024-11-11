import pyodbc

# Función para conectar a la base de datos
def connect_to_db():
    conn = pyodbc.connect('DRIVER=/usr/lib/oracle/12.2/client64/lib/libsqora.so.12.1;'
                              'DBQ=oracle0.ugr.es:1521/practbd.oracle0.ugr.es;'
                              'UID=x9617109;'  # Tu ID de usuario
                              'PWD=x9617109'   # Tu contraseña
        )
    return conn


def drop_if_exists(cursor, object_type, object_name):
    try:
        cursor.execute(f"DROP {object_type} {object_name}")
    except pyodbc.Error as e:
        if "does not exist" not in str(e):
            raise


def create_actividad_table(cursor):
    # Verificar y eliminar la tabla si existe
    drop_if_exists(cursor, "TABLE", "Actividad")

    # Verificar y eliminar la secuencia si existe
    drop_if_exists(cursor, "SEQUENCE", "actividad_seq")

    # Crear secuencia para ID_actividad
    cursor.execute('CREATE SEQUENCE actividad_seq START WITH 1 INCREMENT BY 1')

    # Crear tabla Actividad con Hora_inicio y Hora_fin como TIMESTAMP
    cursor.execute('''
        CREATE TABLE Actividad (
            ID_actividad INT PRIMARY KEY,
            Nombre VARCHAR2(50) NOT NULL, 
            Lugar VARCHAR2(50) NOT NULL,
            Tipo INT NOT NULL CHECK (Tipo BETWEEN 0 AND 5),
            Fecha DATE NOT NULL, 
            Hora_inicio TIMESTAMP NOT NULL, 
            Hora_fin TIMESTAMP NOT NULL,
            Num_max INT NOT NULL CHECK (Num_max > 0),
            ID_trabajador VARCHAR2(12),
            FOREIGN KEY (ID_trabajador) REFERENCES Trabajador(ID),
            CHECK (Hora_inicio < Hora_fin)
        )
    ''')

    # Verificar y eliminar el trigger si existe
    drop_if_exists(cursor, "TRIGGER", "actividad_trigger")

    # Crear trigger para autoincrementar ID_actividad
    cursor.execute('''
        CREATE OR REPLACE TRIGGER actividad_trigger
        BEFORE INSERT ON Actividad
        FOR EACH ROW
        BEGIN
            SELECT actividad_seq.NEXTVAL INTO :new.ID_actividad FROM dual;
        END;
    ''')


def create_inscripcion_table(cursor):
    # Verificar y eliminar la tabla si existe
    drop_if_exists(cursor, "TABLE", "Inscripcion")

    # Crear tabla Inscripcion
    cursor.execute('''
        CREATE TABLE Inscripcion (
            ID_cliente VARCHAR2(12), 
            ID_actividad INT,
            PRIMARY KEY (ID_cliente, ID_actividad),
            FOREIGN KEY (ID_cliente) REFERENCES Cliente(ID),
            FOREIGN KEY (ID_actividad) REFERENCES Actividad(ID_actividad)
        )
    ''')

# Similar para Cliente y Trabajador
def create_cliente_table(cursor):
    # Verificar y eliminar la tabla si existe
    drop_if_exists(cursor, "TABLE", "Cliente")

    # Crear tabla Cliente
    cursor.execute('''
        CREATE TABLE Cliente (
            ID VARCHAR2(12) PRIMARY KEY,
            Nombre VARCHAR2(20) NOT NULL,
            Apellidos VARCHAR2(40) NOT NULL,
            NumeroTelefono VARCHAR2(12) NOT NULL,
            CorreoElectronico VARCHAR2(50) NOT NULL,
            TipoCliente INT CHECK (TipoCliente BETWEEN 0 AND 5),
            Importe FLOAT
        )
    ''')

def create_trabajador_table(cursor):
    # Verificar y eliminar la tabla si existe
    drop_if_exists(cursor, "TABLE", "Trabajador")

    # Crear tabla Trabajador
    cursor.execute('''
        CREATE TABLE Trabajador (
            ID VARCHAR2(12) PRIMARY KEY,
            Nombre VARCHAR2(20) NOT NULL,
            Apellidos VARCHAR2(40) NOT NULL,
            FechaNacimiento DATE NOT NULL,
            Area VARCHAR2(20) NOT NULL,
            FechaFinContrato DATE NOT NULL
        )
    ''')

    # Verificar y eliminar el trigger si existe
    drop_if_exists(cursor, "TRIGGER", "trabajador_age_check")

    # Crear trigger para verificar la edad mínima
    cursor.execute('''
        CREATE OR REPLACE TRIGGER trabajador_age_check
        BEFORE INSERT OR UPDATE ON Trabajador
        FOR EACH ROW
        BEGIN
            IF (MONTHS_BETWEEN(SYSDATE, :new.FechaNacimiento) / 12) < 16 THEN
                RAISE_APPLICATION_ERROR(-20000, 'La edad del trabajador debe ser al menos 16 años.');
            END IF;
        END;
    ''')

def main():
    conn = connect_to_db()
    cursor = conn.cursor()
    
    # Crear tablas
    create_cliente_table(cursor)
    create_trabajador_table(cursor)
    create_actividad_table(cursor)
    create_inscripcion_table(cursor)
    # Similar para Cliente y Trabajador

    conn.commit()
    conn.close()

if __name__ == "__main__":
    main()
