package org.demo.pc1_demo.user.domain;

import org.demo.pc1_demo.professor.infrastructure.ProfessorRepository;
import org.demo.pc1_demo.student.infrastructure.StudentRepository;
import org.demo.pc1_demo.user.infrastructure.BaseUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class UserService {

    @Autowired
    private BaseUserRepository<User> userRepository;

    @Autowired
    private StudentRepository studentRepository;

    @Autowired
    private ProfessorRepository professorRepository;


    public User findByEmail(String username, String role) {
        User user;
        if (role.equals("ROLE_PROFESSOR"))
            user = professorRepository.findByEmail(username).orElseThrow(() -> new UsernameNotFoundException("User not found"));
        else
            user = studentRepository.findByEmail(username).orElseThrow(() -> new UsernameNotFoundException("User not found"));

        return user;
    }

    @Bean(name = "UserDetailsService")
    public UserDetailsService userDetailsService() {
        return username -> {
            User user = userRepository
                    .findByEmail(username)
                    .orElseThrow(() -> new UsernameNotFoundException("User not found"));
            return (UserDetails) user;
        };
    }
}
