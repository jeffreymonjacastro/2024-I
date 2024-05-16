package org.demo.pc1_demo.course.domain;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import org.demo.pc1_demo.student.domain.Student;
import org.demo.pc1_demo.professor.domain.Professor;

import java.util.List;

@Entity
@AllArgsConstructor
@NoArgsConstructor
public class Course {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    private long id;

    @Column(nullable = false)
    private String name;

    @Column(nullable = false)
    private String description;

    @Column(nullable = false)
    private String code;

    @Column(nullable = false)
    private Integer remainingSpots = 10;

    // Muchos cursos tienen solo un profesor
    // Many pertenece a la entidad actual
    // One pertenece a la entidad relacionada
    @ManyToOne(fetch = FetchType.LAZY)
    private Professor professor;

    @ManyToMany(
            fetch = FetchType.LAZY,
            cascade = {
                    CascadeType.PERSIST,
                    CascadeType.MERGE
            },
            mappedBy = "courses"
    )
    private List<Student> students;
}
