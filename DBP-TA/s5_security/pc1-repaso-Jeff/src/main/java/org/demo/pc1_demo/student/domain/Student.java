package org.demo.pc1_demo.student.domain;

import jakarta.persistence.*;
import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.user.domain.User;

import java.util.List;

@Entity
public class Student extends User {

    @ManyToMany(fetch = FetchType.LAZY, cascade = {CascadeType.PERSIST, CascadeType.MERGE})
    @JoinTable(
            name = "student_courses",
            joinColumns = {
                    @JoinColumn(name = "student_id")
            },
            inverseJoinColumns = {
                    @JoinColumn(name = "course_id")
            }
    )
    private List<Course> courses;
}
