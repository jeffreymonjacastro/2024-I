package org.demo.pc1_demo.student.application;

import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.student.domain.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

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


}
