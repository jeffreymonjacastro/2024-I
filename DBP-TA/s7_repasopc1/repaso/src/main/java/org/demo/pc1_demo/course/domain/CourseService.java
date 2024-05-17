package org.demo.pc1_demo.course.domain;

import org.demo.pc1_demo.course.exceptions.CourseNotFoundException;
import org.demo.pc1_demo.course.infrastructure.CourseRepository;
import org.demo.pc1_demo.student.domain.Student;
import org.demo.pc1_demo.student.exceptions.StudentNotFoundException;
import org.demo.pc1_demo.student.infrastructure.StudentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CourseService {
    @Autowired
    CourseRepository courseRepository;

    @Autowired
    StudentRepository studentRepository;

    public void createCourse(Course course) {
        courseRepository.save(course);
    }

    public List<Course> getCourseSpotsAvailable(){
        return courseRepository.findCoursesByRemainingSpotsIsGreaterThan(0);
    }

    public String enrollCourse(Long userId, Long courseId) {
        Course course = courseRepository.findById(courseId).orElseThrow(() ->
                new CourseNotFoundException("Course not found"));
        Student student = studentRepository.findById(userId).orElseThrow(() ->
                new StudentNotFoundException("Student not found"));

        if (course.getRemainingSpots() == 0) {
            return "No hay cupos";
        }

        if (course.getStudents().contains(student)) {
            return "Student is already enrolled in this course";
        }

        course.getStudents().add(student);
        course.setRemainingSpots(course.getRemainingSpots() - 1);

        student.getCourses().add(course);
        studentRepository.save(student);
        courseRepository.save(course);

        return "Student enrolled in course";
    }
}

