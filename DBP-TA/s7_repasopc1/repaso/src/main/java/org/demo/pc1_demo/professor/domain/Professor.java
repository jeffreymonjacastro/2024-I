package org.demo.pc1_demo.professor.domain;

import jakarta.persistence.*;
import org.demo.pc1_demo.course.domain.Course;

import java.util.List;

@Entity
public class Professor {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    private Long id;

    @Column(name = "name", nullable = false)
    private String name;

    @Column(name = "email", nullable = false)
    private String email;

    @Column(name = "password", nullable = false)
    private String password;

    @OneToMany(mappedBy = "professor", cascade = CascadeType.ALL)
    private List<Course> cursos;
}
