import numpy as np

# Datos de ejemplo: autoevaluaciones y coevaluaciones
autoevaluaciones = np.array([20, 20, 20, 20])  # Autoevaluaciones de los estudiantes
coevaluaciones = np.array([
    [19, 16, 15],  # Evaluaciones recibidas por el primer estudiante de los otros tres
    [5, 5, 5],  # Evaluaciones recibidas por el segundo estudiante
    [16, 18, 12],  # Evaluaciones recibidas por el tercer estudiante
    [20, 19, 18]   # Evaluaciones recibidas por el cuarto estudiante
])

# Calcular el promedio de las coevaluaciones para cada estudiante
promedios = np.mean(coevaluaciones, axis=1)

# Calcular las diferencias entre las autoevaluaciones y los promedios
diferencias = autoevaluaciones - promedios

# Determinar los factores multiplicativos base
# Si la autoevaluación está por encima del promedio, se penaliza (< 1)
# Si la autoevaluación está por debajo del promedio, se premia (> 1)
factores = 1 - 0.1 * diferencias / np.std(coevaluaciones, axis=1, ddof=1)

# Ajustar los factores para que el promedio sea 1
factores = factores / np.mean(factores)

# Limitar el factor multiplicativo entre 0.8 y 1.2
factores = np.clip(factores, 0.8, 1.2)

print("Autoevaluaciones:", autoevaluaciones)
print("Promedio de coevaluaciones:", promedios)
print("Diferencias:", diferencias)
print("Factores multiplicativos:", factores)
print("Promedio de los factores:", np.mean(factores))
