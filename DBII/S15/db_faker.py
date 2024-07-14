import psycopg2
from faker import Faker
import random
from datetime import date

# Configuracion de la conexion a la base de datos
conn = psycopg2.connect(
    host="localhost",
    database="db2",
    user="postgres",
    password="123"
)

cursor = conn.cursor()
schema = "lab15"
cursor.execute(f"SET search_path TO {schema}")

fake = Faker('es_ES')

ventas = []
reclamos = []

# 12 codigos diferentes para CodLocal
cod_locales = [f"LOC{str(i).zfill(2)}" for i in range(1, 13)]  
start_date = date(2000, 1, 1)
end_date = date(2025, 1, 1)
estados = ['Pendiente', 'En Proceso', 'Cerrado']

# Generar datos aleatorios con id incremental
for i in range(1000000):
    dni_cliente = str(random.randint(70000000, 77500000))
    fecha_venta = fake.date_between(start_date=start_date, end_date=end_date)
    cod_local = random.choice(cod_locales)
    importe_total = random.randint(1, 1000)
    id_empleado = f"EMP{str(fake.random_number(digits=3, fix_len=True)).zfill(3)}"

    ventas.append((i + 1, dni_cliente, fecha_venta, cod_local, importe_total, id_empleado))

    dni_cliente = str(random.randint(70000000, 79999999))
    fecha_reclamo = fake.date_between(start_date=start_date, end_date=end_date)
    cod_local = random.choice(cod_locales)
    descripcion = fake.text(max_nb_chars=100)
    estado = random.choice(estados)

    reclamos.append((i + 1, dni_cliente, fecha_reclamo, cod_local, descripcion, estado))

# Insertar las tuplas en la base de datos
insert_query_venta = """
INSERT INTO venta (IdVenta, DNI_Cliente, FechaVenta, CodLocal, ImporteTotal, IdEmpleado)
VALUES (%s, %s, %s, %s, %s, %s)
"""

insert_query_reclamo = """
INSERT INTO reclamo (IdReclamo, DNI_Cliente, FechaReclamo, CodLocal, Descripcion, Estado)
VALUES (%s, %s, %s, %s, %s, %s)
"""

# Insertar los datos en bloques de 10000 tuplas
batch_size = 10000
for i in range(0, len(reclamos), batch_size):
    batch_v = ventas[i:i + batch_size]
    batch_r = reclamos[i:i + batch_size]
    try:
        cursor.executemany(insert_query_venta, batch_v)
        cursor.executemany(insert_query_reclamo, batch_r)
        conn.commit()
    except Exception as e:
        print(f"Error al insertar los datos: {e}")
        conn.rollback()

print("Datos insertados correctamente en la tabla venta y reclamo")

# Cerrar la conexion
cursor.close()
conn.close()
