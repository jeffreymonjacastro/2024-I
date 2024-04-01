from fastapi import FastAPI, HTTPException, status, Response
from pydantic import BaseModel
from typing import Optional
from uuid import uuid4, UUID

app = FastAPI()

# Modelo para los productos
class Producto(BaseModel):
    id: Optional[UUID] = None
    nombre: Optional[str] = None
    descripcion: Optional[str] = None
    precio: Optional[float] = None
    stock: Optional[int]= None

productos = []

@app.get("/productos")
def get_productos():
    return productos

@app.get("/productos/{producto_id}")
def get_producto(producto_id: UUID):
    for producto in productos:
        if producto["id"] == producto_id:
            return producto
    raise HTTPException(status_code=404, detail="Producto no encontrado")

@app.post("/productos")
def create_producto(producto: Producto):
    producto.id = uuid4()
    productos.append(producto.model_dump())
    return producto

@app.put("/productos/{producto_id}")
def update_producto(producto_id: UUID, producto: Producto):
    for index, product in enumerate(productos):
        if product["id"] == producto_id:
            productos[index] = producto.model_dump()
            productos[index]["id"] = producto_id
            return productos[index]
    raise HTTPException(status_code=404, detail="Producto no encontrado")

@app.patch("/productos/{producto_id}")
def patch_producto(producto_id: UUID, producto: Producto):
    for index, product in enumerate(productos):
        if product["id"] == producto_id:
            productos[index] = producto.model_dump()
            productos[index]["id"] = producto_id
            return productos[index]
    raise HTTPException(status_code=404, detail="Producto no encontrado")

@app.delete("/productos/{producto_id}")
def delete_producto(producto_id: UUID):
    for index, producto in enumerate(productos):
        if producto["id"] == producto_id:
            del productos[index]
            return Response(status_code=status.HTTP_204_NO_CONTENT)
    raise HTTPException(status_code=404, detail="Producto no encontrado")


## ADICIONAL

@app.get("/productos/")
def get_productos(stock: int | None = None):
    if stock == None:
        return productos

    productos_agotados = []
    for producto in productos:
        if producto["stock"] == stock:
            productos_agotados.append(producto)
    return productos_agotados


@app.post("/productos/{producto_id}/comprar")
def comprar_producto(producto_id: UUID):
    for index, producto in enumerate(productos):
        if producto["id"] == producto_id:
            if producto["stock"] == 0:
                return {"message": "No hay suficiente stock"}
            productos[index]["stock"] -= 1
            return productos[index]
    raise HTTPException(status_code=404, detail="Producto no encontrado")

@app.post("/productos/{producto_id}/reponer")
def reponer_producto(producto_id: UUID, cantidad: int):
    for index, producto in enumerate(productos):
        if producto["id"] == producto_id:
            productos[index]["stock"] += cantidad
            return productos[index]
    raise HTTPException(status_code=404, detail="Producto no encontrado")