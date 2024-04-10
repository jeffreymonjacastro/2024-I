package com.example.helloworld2.Producto.application;

import com.example.helloworld2.Producto.domain.Producto;
import com.example.helloworld2.Producto.domain.ProductoService;
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
    public ResponseEntity<Producto> crearProducto(@RequestBody Producto producto){
        return new ResponseEntity<>(productoService.crearProducto(producto), HttpStatus.CREATED);
    }

    @GetMapping
    public ResponseEntity<List<Producto>> listarTodosLosProductos(){
        return new ResponseEntity(productoService.listarTodosLosProductos(), HttpStatus.OK);
    }

    @DeleteMapping("/{producto_id}")
    public ResponseEntity<String> eliminarProducto(@PathVariable("producto_id") UUID id){
        return new ResponseEntity(productoService.eliminarProducto(id), HttpStatus.OK);
    }
}
