package org.demo.pc1_demo.professor.infrastructure;

import org.demo.pc1_demo.professor.domain.Professor;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ProfessorRepository extends JpaRepository<Professor, Long> {
}
