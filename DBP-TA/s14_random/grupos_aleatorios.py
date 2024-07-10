import random

def ordenar_aleatoriamente(grupos):
  grupos_aleatorios = grupos.copy()
  random.shuffle(grupos_aleatorios)
  return grupos_aleatorios

sec1 = ["Grupo 1", "Grupo 2", "Grupo 4", "Grupo 7", "Grupo 16", "Grupo 19", "Grupo 23"]
sec2 = ["Grupo 3", "Grupo 5", "Grupo 8", "Grupo 11", "Grupo 15", "Grupo 21", "Grupo 22"]
sec3 = ["Grupo 9", "Grupo 13", "Grupo 14", "Grupo 18", "Grupo 20", "Grupo 25"]
sec4 = ["Grupo 6", "Grupo 10", "Grupo 12", "Grupo 17", "Grupo 24"]

sec1_aleatorio = ordenar_aleatoriamente(sec1)
sec2_aleatorio = ordenar_aleatoriamente(sec2)
sec3_aleatorio = ordenar_aleatoriamente(sec3)
sec4_aleatorio = ordenar_aleatoriamente(sec4)

exposicion = [sec1_aleatorio, sec2_aleatorio, sec3_aleatorio, sec4_aleatorio]

print("Orden de exposiciones:")

for i, sec in enumerate(exposicion):
  print(f"Sección {i + 1}")
  for j, grupo in enumerate(sec):
    print(f"{j + 1}. {grupo}")
