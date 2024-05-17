package org.demo.pc1_demo.course.application;

import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.course.domain.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/course")
public class CourseController {
    @Autowired
    CourseService courseService;

    @PostMapping
    public ResponseEntity<Void> createCourse(@RequestBody Course course) {
        courseService.createCourse(course);
        return new ResponseEntity<>(HttpStatus.CREATED);
    }

    @GetMapping()
    public ResponseEntity<List<Course>> getCourseSpotsAvailable() {
        return ResponseEntity.ok(courseService.getCourseSpotsAvailable());
    }

    @PostMapping("/{userId}")
    public ResponseEntity<String> enrollCourse(@PathVariable Long userId, @RequestParam Long courseId) {
        return ResponseEntity.ok(courseService.enrollCourse(userId, courseId));
    }
}
