package org.demo.pc1_demo.user.infrastructure;

import org.demo.pc1_demo.user.domain.User;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface BaseUserRepository<T extends User> extends JpaRepository<T, Long> {
    Optional<T> findByEmail(String email);
}
