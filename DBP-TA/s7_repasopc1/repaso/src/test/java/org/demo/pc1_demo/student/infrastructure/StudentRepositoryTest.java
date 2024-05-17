package org.demo.pc1_demo.student.infrastructure;

import org.demo.pc1_demo.AbstractContainerBaseTest;
import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.course.infrastructure.CourseRepository;
import org.demo.pc1_demo.student.domain.Student;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

@DataJpaTest
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
class StudentRepositoryTest extends AbstractContainerBaseTest {

    @Autowired
    private StudentRepository studentRepository;

    @Autowired
    private CourseRepository courseRepository;

    @Autowired
    private TestEntityManager entityManager;


    private Student student1;


    @BeforeEach
    public void setUp() {
        Student student = new Student();
        student.setName("John Doe");
        student.setEmail("johndoe@gmail.com");
        student.setPassword("123");
        student1 = student;
        entityManager.persist(student);

        Course course = new Course();
        course.setName("Math");
        course.setDescription("Math course");
        course.setCode("CS1234");
        course.setRemainingSpots(5);
        entityManager.persist(course);

        entityManager.flush();
    }

    @Test
    public void testExistStudent() {
        List<Student> students = studentRepository.findAll();

        assertEquals(1, students.size());
    }

    @Test
    public void testGetCourses() {
        List<Course> course = courseRepository.findAll();

        assertEquals(1, course.size());
    }

}
