package org.demo.pc1_demo.student.application;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.demo.pc1_demo.course.domain.Course;
import org.demo.pc1_demo.course.infrastructure.CourseRepository;
import org.demo.pc1_demo.student.domain.Student;
import org.demo.pc1_demo.student.infrastructure.StudentRepository;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
        import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest
@AutoConfigureMockMvc
@Transactional
public class TestStudentController {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private StudentRepository studentRepository;

    @Autowired
    private CourseRepository courseRepository;

    @Autowired
    private ObjectMapper objectMapper;

    private Student student1;

    @BeforeEach
    public void setUp() {
        Student student = new Student();
        student.setName("Joe");
        student.setEmail("Joe@gmail.com");
        student.setPassword("Joe123");

        Course course = new Course();
        course.setName("DBP");
        course.setDescription("Curso de CS");
        course.setCode("CS2031");

        student.getCourses().add(course);
        course.getStudents().add(student);

        studentRepository.save(student);
        courseRepository.save(course);
        student1 = student;
    }

    @Test
    public void testGetStudent() throws Exception {
        mockMvc.perform(get("/students/1"))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.id").value(1));
    }

    @Test
    public void testCreateStudent() throws Exception {
        mockMvc.perform(post("/students")
                    .contentType(MediaType.APPLICATION_JSON)
                    .content(objectMapper.writeValueAsString(student1)))
                .andExpect(status().isCreated())
                .andExpect(jsonPath("$.id").value(student1.getId()));

    }

//    @Test
//    public void testGetDriver() throws Exception {
//        Driver savedDriver = driverRepository.save(driver);
//
//        mockMvc.perform(get("/driver/{id}", savedDriver.getId()))
//                .andExpect(status().isOk())
//                .andExpect(jsonPath("$.firstName").value(driver.getFirstName()))
//                .andExpect(jsonPath("$.lastName").value(driver.getLastName()));
//    }
//
//    @Test
//    public void testSaveDriver() throws Exception {
//
//        Driver currentDriver = driverRepository.save(driver);
//
//
//        mockMvc.perform(post("/driver")
//                        .contentType(MediaType.APPLICATION_JSON)
//                        .content(objectMapper.writeValueAsString(currentDriver)))
//                .andExpect(status().isCreated());
//
//        List<Driver> drivers = driverRepository.findAll();
//        Assertions.assertEquals(drivers.size(), 1);
//        Assertions.assertEquals(drivers.get(0).getFirstName(), currentDriver.getFirstName());
//        Assertions.assertEquals(drivers.get(0).getLastName(), currentDriver.getLastName());
//    }
}