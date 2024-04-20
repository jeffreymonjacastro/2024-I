package com.example.helloworld2.Producto.domain;

import org.springframework.data.jpa.repository.JpaRepository;

import java.util.UUID;

public interface ProductoRepository extends JpaRepository<Producto, UUID> {
}
