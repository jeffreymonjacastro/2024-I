package com.example.helloworld2.Producto.domain;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.UUID;

@Service
public class ProductoService {
    private final ProductoRepository productoRepository;

    @Autowired
    public ProductoService(ProductoRepository productoRepository){
        this.productoRepository = productoRepository;
    }

    public Producto crearProducto(Producto producto){
        producto.setId(UUID.randomUUID());
        return productoRepository.save(producto);
    }
}
