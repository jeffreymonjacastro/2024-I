package org.demo.pc1_demo.course.repository;

import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.student.domain.Student;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface CourseRepository extends JpaRepository<Course, Long> {
    List<Course> findCourseByStudentsContaining(Student student);
    List<Course> findCoursesByRemainingSpotsIsGreaterThan(int spots);
}
