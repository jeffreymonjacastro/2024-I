package org.example.helloworld;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping("/productos")
public class ProductoController {

    @Autowired
    private ProductoService productoService;

    @PostMapping
    public ResponseEntity<Producto> crearProducto(@RequestBody Producto producto) {
        return new ResponseEntity<>(productoService.crearProducto(producto), HttpStatus.CREATED);
    }

    @PutMapping("/{productoId}")
    public ResponseEntity<Producto> actualizarProducto(@PathVariable UUID productoId, @RequestBody Producto producto) {
        Producto updatedProducto = productoService.actualizarProducto(productoId, producto);
        if (updatedProducto != null) {
            return new ResponseEntity<>(updatedProducto, HttpStatus.OK);
        }
        return new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    @PatchMapping("/{productoId}")
    public ResponseEntity<Producto> actualizarParcialmenteProducto(@PathVariable UUID productoId, @RequestBody Producto datosParciales) {
        Producto updatedProducto = productoService.actualizarParcialmenteProducto(productoId, datosParciales);
        if (updatedProducto != null) {
            return new ResponseEntity<>(updatedProducto, HttpStatus.OK);
        }
        return new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    @DeleteMapping("/{productoId}")
    public ResponseEntity<Void> eliminarProducto(@PathVariable UUID productoId) {
        boolean success = productoService.eliminarProducto(productoId);
        if (success) {
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    @GetMapping
    public ResponseEntity<List<Producto>> listarTodosLosProductos() {
        return new ResponseEntity<>(productoService.listarTodosLosProductos(), HttpStatus.OK);
    }

    @GetMapping("/{productoId}")
    public ResponseEntity<Producto> listarProductoPorId(@PathVariable UUID productoId) {
        Producto producto = productoService.listarProductoPorId(productoId);
        if (producto != null) {
            return new ResponseEntity<>(producto, HttpStatus.OK);
        }
        return new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    // Bonus endpoints
    @GetMapping("/con-stock-cero")
    public ResponseEntity<List<Producto>> listarProductosConStockCero() {
        return new ResponseEntity<>(productoService.listarProductosConStockCero(), HttpStatus.OK);
    }

    @PostMapping("/{productoId}/comprar")
    public ResponseEntity<Producto> comprarProducto(@PathVariable UUID productoId) {
        Producto producto = productoService.comprarProducto(productoId);
        if (producto != null) {
            return new ResponseEntity<>(producto, HttpStatus.OK);
        }
        return new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    @PostMapping("/{productoId}/reponer")
    public ResponseEntity<Producto> reponerStock(@PathVariable UUID productoId, @RequestParam int cantidad) {
        Producto producto = productoService.reponerStock(productoId, cantidad);
        if (producto != null) {
            return new ResponseEntity<>(producto, HttpStatus.OK);
        }
        return new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }
}
