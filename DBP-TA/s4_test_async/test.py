import requests, time # Importamos la dependencias
def verificar_enlace(url):
    try:
        respuesta = requests.get(url, timeout=5)
        respuesta.raise_for_status()
    except requests.exceptions.RequestException:
        return True  # El enlace está roto
    return False  # El enlace está funcionando

urls = [f"https://example.com/{i}" for i in range(10)]  # Un billón de URLs
inicio = time.time()

enlaces_rotos = []
for url in urls:
    if verificar_enlace(url):
        enlaces_rotos.append(url)
fin = time.time()
print(f"Tiempo total: {fin - inicio} segundos")
print(f"Número de enlaces rotos: {len(enlaces_rotos)}")