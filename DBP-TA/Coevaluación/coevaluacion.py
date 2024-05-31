import numpy as np

nota_final = 15
n = 4

# |    | E1 | E2 | E3 |
# |----|----|----|----|
# | E1 | 18 | 19 | 16 | -> Calificaciones que puso el E1 a sí mismo y a los demás
# | E2 | 14 | 15 | 16 | -> Calificaciones que puso el E2 a sí mismo y a los demás
# | E3 | 16 | 18 | 17 | -> Calificaciones que puso el E3 a sí mismo y a los demás

## Autoevaluaciones: notas[i][i]
## Coevaluaciones: notas[i][j], i != j

notas = np.array([
    [100, 85, 70, 100],  # Evaluaciones del estudiante 1 (auto, coevaluaciones de 2 y 3)
    [40, 100, 60, 100],  # Evaluaciones del estudiante 2
    [55, 90, 100, 100],  # Evaluaciones del estudiante 3
    [50, 80, 80, 100],  # Evaluaciones del estudiante 4
])


# Autoevaluación - promedio de coevaluación
# promedios = [P1, P2, P3]
# Si el promedio de un estudiante es negativo, autoevaluación < prom(coevaluación) [SE PREMIA, porque se calificó bajo y recibió mejores calificaciones de los demás]
# Si el promedio de un estudiante es positivo, autoevaluación > prom(coevaluación) [SE CASTIGA, porque se calificó alto y recibió peores calificaciones de los demás]

promedios = []

for i in range(n):
    prom = 0
    auto = notas[i][i]
    for j in range(n):
        if i != j:
            prom += notas[j][i]
    prom = prom / (n - 1)
    promedios.append(auto - prom)

promedios = np.array(promedios)

# Calcular desviación estándar
std_dev = np.std(notas, axis=1, ddof=1) 

# Calcular factores multiplicativos
factores = 1 - 0.1 * promedios / std_dev

# Ajustar los factores para que el promedio sea 1
factores = factores / np.mean(factores)

# Limitar el factor multiplicativo entre 0.8 y 1.2
factores = np.clip(factores, 0.8, 1.2)

notas_finales = np.ceil(nota_final * factores)

print("Factores multiplicativos:", factores)
print("Notas finales:", notas_finales)