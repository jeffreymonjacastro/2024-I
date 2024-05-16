package org.demo.pc1_demo.course.domain;

import org.demo.pc1_demo.auth.exceptions.UnauthorizeOperationException;
import org.demo.pc1_demo.auth.utils.AuthorizationUtils;
import org.demo.pc1_demo.course.repository.CourseRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CourseService {

    @Autowired
    CourseRepository courseRepository;

    @Autowired
    AuthorizationUtils authorizationUtils;

    public List<Course> getCourseSpotsAvailable(){
        String username = authorizationUtils.getCurrentUserEmail();
        if(username == null)
            throw new UnauthorizeOperationException("Anonymous User not allowed to access this resource");

        return courseRepository.findCoursesByRemainingSpotsIsGreaterThan(0);
    }
}