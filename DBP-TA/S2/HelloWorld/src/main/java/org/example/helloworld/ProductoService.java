package org.example.helloworld;

import org.springframework.stereotype.Service;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

@Service
public class ProductoService {

    private List<Producto> productos = new ArrayList<>();

    public Producto crearProducto(Producto producto) {
        producto.setId(UUID.randomUUID());
        productos.add(producto);
        return producto;
    }

    public Producto actualizarProducto(UUID productoId, Producto producto) {
        for (Producto p : productos) {
            if (p.getId().equals(productoId)) {
                p.setNombre(producto.getNombre());
                p.setDescripcion(producto.getDescripcion());
                p.setPrecio(producto.getPrecio());
                p.setStock(producto.getStock());
                return p;
            }
        }
        return null;
    }

    public Producto actualizarParcialmenteProducto(UUID productoId, Producto datosParciales) {
        for (Producto p : productos) {
            if (p.getId().equals(productoId)) {
                if (datosParciales.getNombre() != null) {
                    p.setNombre(datosParciales.getNombre());
                }
                if (datosParciales.getDescripcion() != null) {
                    p.setDescripcion(datosParciales.getDescripcion());
                }
                if (datosParciales.getPrecio() != null) {
                    p.setPrecio(datosParciales.getPrecio());
                }
                if (datosParciales.getStock() != null) {
                    p.setStock(datosParciales.getStock());
                }
                return p;
            }
        }
        return null;
    }

    public boolean eliminarProducto(UUID productoId) {
        for (Producto p : productos) {
            if (p.getId().equals(productoId)) {
                productos.remove(p);
                return true;
            }
        }
        return false;
    }

    public List<Producto> listarTodosLosProductos() {
        return productos;
    }

    public Producto listarProductoPorId(UUID productoId) {
        for (Producto p : productos) {
            if (p.getId().equals(productoId)) {
                return p;
            }
        }
        return null;
    }

    public List<Producto> listarProductosConStockCero() {
        List<Producto> productosConStockCero = new ArrayList<>();
        for (Producto p : productos) {
            if (p.getStock() == 0) {
                productosConStockCero.add(p);
            }
        }
        return productosConStockCero;
    }

    public Producto comprarProducto(UUID productoId) {
        for (Producto p : productos) {
            if (p.getId().equals(productoId)) {
                if (p.getStock() > 0) {
                    p.setStock(p.getStock() - 1);
                    return p;
                } else {
                    return null;
                }
            }
        }
        return null;
    }

    public Producto reponerStock(UUID productoId, int cantidad) {
        for (Producto p : productos) {
            if (p.getId().equals(productoId)) {
                p.setStock(p.getStock() + cantidad);
                return p;
            }
        }
        return null;
    }
}

