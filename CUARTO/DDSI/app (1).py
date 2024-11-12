import pyodbc
import logging
import os

# Configuración del logger para DEBUG

logging.basicConfig(filename="funcionamiento.log",level=logging.DEBUG)
logger = logging.getLogger(__name__)

# Función para mostrar el contenido de una tabla de la BD

def mostrarTablaBD(handler, nombre_tabla):
    try:
        handler.execute("SELECT * FROM " + nombre_tabla)
        logger.debug("Se ejecuta la consulta " + nombre_tabla)
        for row in handler.fetchall():
            print(row)
    except pyodbc.Error as e:
        logger.debug("Error en la consulta ", nombre_tabla, ":", e)
        print("Error en la consulta ", nombre_tabla, ":", e)

# Función para borrar las tablas, crearlas de nuevo e insertar 10 tuplas predefinidas a la tabla Stock
def resetearBD(handler):
    # Eliminar tabla DetallePedido
    # Hay que eliminar esta primera poque cuneta con foerign keys
    handler.execute("SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='DETALLEPEDIDO'")
    if len(handler.fetchall()) == 1:
        handler.execute("DROP TABLE DETALLEPEDIDO")
        logger.debug("Eliminada tabla detallepedido")
    else:
        logger.debug("No existe la tabla detallepedido")

    # Eliminar tabla Stock
    handler.execute("SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='STOCK'")
    if len(handler.fetchall()) == 1:
        handler.execute("DROP TABLE STOCK")
        logger.debug("Eliminada tabla stock")
    else:
        logger.debug("No existe la tabla stock")

    # Eliminar tabla Pedido
    handler.execute("SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='PEDIDO'")
    if len(handler.fetchall()) == 1:
        handler.execute("DROP TABLE PEDIDO")
        logger.debug("Eliminada tabla pedido")
    else:
        logger.debug("No existe la tabla pedido")

    # Crear tabla Stock e insertar 10 elementos
    handler.execute("CREATE TABLE STOCK (Cproducto int constraint pk_stock primary key, Cantidad int)")
    for i in range(1, 11):
        handler.execute("INSERT INTO STOCK VALUES (" + str(i) + "," + str(i+5) + ")")
    logger.debug("Creada tabla stock e insertados 10 elementos")

    # Crear tabla Pedido
    handler.execute("CREATE TABLE PEDIDO (Cpedido int constraint pk_pedido primary key, Ccliente int, FechaPedido date)")
    logger.debug("Creada tabla pedido")

    # Crear tabla DetallePedido
    handler.execute("CREATE TABLE DETALLEPEDIDO (Cpedido int, Cproducto int, Cantidad int, constraint pk_detallepedido primary key (Cpedido, Cproducto), constraint fk_detallepedido_pedido foreign key (Cpedido) references PEDIDO(Cpedido), constraint fk_detallepedido_stock foreign key (Cproducto) references STOCK(Cproducto))")
    logger.debug("Creada tabla detallepedido")

# Función para dar de alta un pedido en la BD
def darAltaPedido(handler, cpedido, ccliente, fecha_pedido):
    try:
        handler.execute("INSERT INTO PEDIDO VALUES (" + str(cpedido) + "," + str(ccliente) + "," + fecha_pedido + ")")
        logger.debug("Insertado pedido " + str(cpedido))
    except pyodbc.Error as e:
        logger.debug("Error al insertar pedido " + str(cpedido) + ":", e)
        print("Error al insertar pedido " + str(cpedido) + ":", e)


########################### App.py ###########################

connection = None

try:
    cnxn = pyodbc.connect('DRIVER={Devart ODBC Driver for Oracle};Direct=True;Host=oracle0.ugr.es;Service Name=practbd.oracle0.ugr.es;User ID=x9617109;Password=x9617109')
    handler = cnxn.cursor()
    logger.debug("Se establece el cursor de conexión")
except pyodbc.Error as e:
    logger.debug("Error connecting to Oracle:", e)
    print("Error connecting to Oracle:", e)
    exit()


while True:
    print("\nSelecciona una opción:\n")
    print("1. Borrar y crear tablas de la BD")
    print("2. Dar de alta un pedido")
    print("3. Mostrar contenido de las tablas de la BD")
    print("4. Limpiar Terminal")
    print("5. Salir\n")

    opcion = int(input("Opción: "))
    # os.system('clear')

    if opcion == 1:
        resetearBD(handler)
    elif opcion == 2:
        # Introducir datos del pedido
        cpedido = input("Introduce el código del pedido: ")
        ccliente = input("Introduce el código del cliente: ")
        fecha_pedido = input("Introduce la fecha del pedido (DD/MM/YYYY): ")

        # Desactivar autocommit para poder hacer rollback
        cnxn.autocommit = False
        handler.execute("SAVEPOINT inicio")
        logger.debug("Se crea el punto de guardado inicio")
        handler.execute("INSERT INTO PEDIDO VALUES (" + str(cpedido) + "," + str(ccliente) + ",TO_DATE('" + str(fecha_pedido) + "','DD/MM/YYYY'))")
        logger.debug("Se inserta el pedido " + str(cpedido))
        handler.execute("SAVEPOINT pedido")
        logger.debug("Se crea el punto de guardado pedido")

        opcion_aux = 0

        while opcion_aux != 3 and opcion_aux != 4:
            print("\nSelecciona una opción:\n")
            print("1. Añadir detalle de producto")
            print("2. Eliminar todos los detalles del producto")
            print("3. Cancelar pedido")
            print("4. Confirmar pedido\n")

            opcion_aux = int(input("Opción: "))

            if opcion_aux == 1:
                print("\n Productos: \n")
                mostrarTablaBD(handler,"STOCK")
                cproducto = input("Introduce el código del producto: ")
                cantidad = input("Introduce la cantidad: ")
                handler.execute("SELECT CANTIDAD FROM STOCK WHERE CPRODUCTO=" + str(cproducto))

                if handler.fetchall()[0][0] >= int(cantidad):
                    logger.debug("Coge bien la cantidad " + str(cantidad))
                    handler.execute("INSERT INTO DETALLEPEDIDO VALUES (" + str(cpedido) + "," + str(cproducto) + "," + str(cantidad) + ")")
                    logger.debug("Se inserta el detalle de pedido " + str(cpedido) + " " + str(cproducto) + " " + str(cantidad))
                    handler.execute("UPDATE STOCK SET CANTIDAD=CANTIDAD-" + str(cantidad) + " WHERE CPRODUCTO=" + str(cproducto))
                    logger.debug("Se actualiza el stock del producto " + str(cproducto))
                else:
                    print("No queda esa cantidad en Stock")
                mostrarTablaBD(handler, "DETALLEPEDIDO")
            elif opcion_aux == 2:
                handler.execute("ROLLBACK TO pedido")
                logger.debug("Se hace rollback al punto de guardado pedido")
                print("\nTabla Pedido:\n")
                mostrarTablaBD(handler, "PEDIDO")
                print("\nTabla DetallePedido:\n")
                mostrarTablaBD(handler, "DETALLEPEDIDO")
                print("\nTabla Stock:\n")
                mostrarTablaBD(handler, "STOCK")
            elif opcion_aux == 3:
                handler.execute("ROLLBACK TO inicio")
                logger.debug("Se hace rollback al punto de guardado inicio")
                cnxn.autocommit = True
            elif opcion_aux == 4:
                cnxn.commit()
                logger.debug("Se hace commit")
                cnxn.autocommit = True

    elif opcion == 3:
        print("\nTabla STOCK:\n")
        mostrarTablaBD(handler, "STOCK")
        print("\nTabla PEDIDO:\n")
        mostrarTablaBD(handler, "PEDIDO")
        print("\nTabla DETALLEPEDIDO:\n")
        mostrarTablaBD(handler, "DETALLEPEDIDO")
    elif opcion == 5:
        handler.close()
        cnxn.close()
        del handler
        del cnxn
        exit()
    elif opcion == 4:
        os.system("clear")
