package org.demo.pc1_demo.course.application;

import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.course.domain.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/course")
public class CourseController {

    @Autowired
    CourseService courseService;

    @GetMapping()
    public ResponseEntity<List<Course>> getCourseSpotsAvailable() {
        return ResponseEntity.ok(courseService.getCourseSpotsAvailable());
    }

}