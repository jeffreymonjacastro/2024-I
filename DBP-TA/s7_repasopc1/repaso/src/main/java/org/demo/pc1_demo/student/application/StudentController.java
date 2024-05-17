package org.demo.pc1_demo.student.application;

import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.student.domain.Student;
import org.demo.pc1_demo.student.domain.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/students")
public class StudentController {
    @Autowired
    private StudentService studentService;

    @GetMapping("/{id}")
    public ResponseEntity<List<Course>> getCoursesEnrolled(@PathVariable Long id) {
        return ResponseEntity.ok(studentService.getCoursesEnrolled(id));
    }

    @PostMapping
    public ResponseEntity<Student> createStudent(@RequestBody Student student) {
        return new ResponseEntity<>(studentService.createStudent(student), HttpStatus.CREATED);
    }


}