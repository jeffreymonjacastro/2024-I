package org.demo.pc1_demo.student.infrastructure;

import org.demo.pc1_demo.student.domain.Student;
import org.springframework.data.jpa.repository.JpaRepository;

public interface StudentRepository extends JpaRepository<Student, Long> {

}