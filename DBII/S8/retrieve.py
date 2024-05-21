def retrieve(Query, Collection, k):
  #busqueda secuencial
  result = []

  for doc in Collection:
    # [0,1], [0, +INF]
    # 1: similitud máxima
    doc = procesar(doc)
    sim = Score(Query, doc)
    result.append(doc.ID, sim)

  sortBySim(result)
  return result[:k]


# La query ya no es una consulta booleana, ahora es un texto libre.
# Se procesa como si fuera un documento más
Query = "Algoritmos y estructura de datos para indexación de textos"

# Eliminar stopwords, reducción, transformamos
Query = procesar(Query) 

result = retrieve(Query, Collection, 10)



# Colección N = 100 documentos

# Noticia   => 95 docs
# Peru      => 60 docs
# UTEC      => 3 docs

# TF = [0, +INF]: Cuantas veces aparece el término en el documento
# DF: En cuantos documentos se encuentra el termino en función de la colección 
# IDF = N/DF = [1, N]: Cuanto már raro es el término, más grande es el IDF 

# Noticia   => DF = 95,   IDF = 100/95 = 1.05
# Peru      => DF = 60,   IDF = 100/60 = 1.66
# UTEC      => DF = 3,    IDF = 100/3  = 33.33

# Query = "Noticias sobre UTEC en Peru"

## Si solo usamos la frecuencia (TF), es probable que los documentos en donde se menciona "UTEC" no estén en el TOP




index_tf = 
{
  'w1' : [(), (), ()],
  'w2' : [(), (), ()],
}


# Añadir un (lenght[] + lenght[q]) norma de la query