package org.demo.pc1_demo.professor.domain;

import jakarta.persistence.*;
import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.user.domain.User;

import java.util.List;

@Entity
public class Professor extends User {

    @OneToMany(mappedBy = "professor", cascade = CascadeType.ALL)
    private List<Course> cursos;
}
