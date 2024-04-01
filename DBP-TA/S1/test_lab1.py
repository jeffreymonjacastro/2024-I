import pytest
from fastapi.testclient import TestClient
from uuid import uuid4
from lab1 import app


@pytest.fixture
def client():
    return TestClient(app)

def test_crear_producto(client):
    producto = {
        "nombre": "Café",
        "descripcion":
        "Café Arábica de alta calidad",
        "precio": 2.5,
        "stock": 100
        }

    response = client.post("/productos", json=producto)

    assert response.status_code == 200
    assert response.json()["nombre"] == "Café"
    assert response.json()["stock"] == 100
    global producto_id
    producto_id = response.json()["id"]

def test_actualizar_producto(client):
    producto_actualizado = {
        "nombre": "Café Mejorado",
        "descripcion": "Café Arábica premium",
        "precio": 3.0,
        "stock": 150
        }

    response = client.put(f"/productos/{producto_id}", json=producto_actualizado)

    assert response.status_code == 200
    assert response.json()["nombre"] == "Café Mejorado"

def test_actualizar_parcialmente_producto(client):
    datos_parciales = {"precio": 3.5}

    response = client.patch(f"/productos/{producto_id}", json=datos_parciales)

    assert response.status_code == 200
    assert response.json()["precio"] == 3.5

def test_eliminar_producto(client):
    response = client.delete(f"/productos/{producto_id}")

    assert response.status_code == 204

def test_listar_todos_los_productos(client):
    response = client.get("/productos")
    assert response.status_code == 200
    assert isinstance(response.json(), list)

def test_listar_producto_por_id(client):
    response = client.get(f"/productos/{producto_id}")
    assert response.status_code == 404

# Pruebas de endpoints bonus
def test_listar_productos_con_stock_cero(client):
    global new_item_id

    items = [{
        "nombre": "Café en granos",
        "descripcion": "Café Arábica de alta calidad en grano",
        "precio": 3.0,
        "stock": 0
        },
        {
        "nombre": "Café molido",
        "descripcion": "Café Arábica de alta calidad molido",
        "precio": 3.5,
        "stock": 10
        }]

    client.post("/productos", json=items[1])
    new_item_id = client.post("/productos", json=items[0]).json()["id"]

    response = client.get("/productos/?stock=0")
    if response.json() == []:
        assert False

    ids = [item["id"] for item in response.json()]

    assert response.status_code == 200
    assert len(ids) == 1
    assert new_item_id in ids

def test_comprar_producto(client):
    client.patch(f"/productos/{new_item_id}", json={"stock": 10})

    response = client.post(f"/productos/{new_item_id}/comprar")
    id_stock = { new_item_id : response.json()["stock"] }

    assert response.status_code == 200
    assert id_stock == {new_item_id : 9}


def test_reponer_stock(client):
    cantidad_a_reponer = 10

    response = client.post(f"/productos/{new_item_id}/reponer?cantidad={cantidad_a_reponer}")

    assert response.status_code == 200
    assert response.json()["stock"] == 19