package org.demo.pc1_demo.student.domain;

import org.demo.pc1_demo.auth.utils.AuthorizationUtils;
import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.course.repository.CourseRepository;
import org.demo.pc1_demo.student.exceptions.StudentNotFoundException;
import org.demo.pc1_demo.student.infrastructure.StudentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.demo.pc1_demo.auth.exceptions.UnauthorizeOperationException;

import java.util.List;

@Service
public class StudentService {
    @Autowired
    private StudentRepository studentRepository;

    @Autowired
    private CourseRepository courseRepository;

    @Autowired
    private AuthorizationUtils authorizationUtils;

    public List<Course> getCoursesEnrolled(Long id) {
        if (!authorizationUtils.isAdminOrResourceOwner(id))
            throw new UnauthorizeOperationException("User has no permission to modify this resource");

        Student student = studentRepository.findById(id).orElseThrow(() ->
                new StudentNotFoundException("Student not found"));

        return courseRepository.findCourseByStudentsContaining(student);
    }
}
