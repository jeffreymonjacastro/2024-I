package org.demo.pc1_demo.student.domain;

import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.course.infrastructure.CourseRepository;
import org.demo.pc1_demo.student.exceptions.StudentNotFoundException;
import org.demo.pc1_demo.student.infrastructure.StudentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StudentService {
    @Autowired
    private StudentRepository studentRepository;

    @Autowired
    private CourseRepository courseRepository;

    public List<Course> getCoursesEnrolled(Long id) {
        Student student = studentRepository.findById(id).orElseThrow(() ->
                new StudentNotFoundException("Student not found"));

        return courseRepository.findByStudentsId(id);
    }

    public Student createStudent(Student student) {
        return studentRepository.save(student);
    }


}
