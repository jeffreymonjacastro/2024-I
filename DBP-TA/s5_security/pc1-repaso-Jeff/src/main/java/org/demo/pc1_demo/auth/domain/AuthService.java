package org.demo.pc1_demo.auth.domain;

import org.demo.pc1_demo.auth.dto.JwtAuthResponse;
import org.demo.pc1_demo.auth.dto.LoginReq;
import org.demo.pc1_demo.auth.dto.RegisterReq;
import org.demo.pc1_demo.auth.exceptions.UserAlreadyExistException;
import org.demo.pc1_demo.config.JwtService;
import org.demo.pc1_demo.student.domain.Student;
import org.demo.pc1_demo.professor.domain.Professor;
import org.demo.pc1_demo.user.domain.User;
import org.demo.pc1_demo.user.domain.Role;
import org.demo.pc1_demo.user.infrastructure.BaseUserRepository;
import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class AuthService {

    private final BaseUserRepository<User> userRepository;
    private final JwtService jwtService;
    private final PasswordEncoder passwordEncoder;
    private final ModelMapper modelMapper;

    @Autowired
    public AuthService(BaseUserRepository<User> userRepository, JwtService jwtService, PasswordEncoder passwordEncoder) {
        this.userRepository = userRepository;
        this.jwtService = jwtService;
        this.passwordEncoder = passwordEncoder;
        this.modelMapper = new ModelMapper();
    }

    public JwtAuthResponse login(LoginReq req) {
        Optional<User> user;
        user = userRepository.findByEmail(req.getEmail());

        if (user.isEmpty()) throw new UsernameNotFoundException("Email is not registered");

        if (!passwordEncoder.matches(req.getPassword(), user.get().getPassword()))
            throw new IllegalArgumentException("Password is incorrect");

        JwtAuthResponse response = new JwtAuthResponse();

        response.setToken(jwtService.generateToken(user.get()));
        return response;
    }

    public JwtAuthResponse register(RegisterReq req){
        Optional<User> user = userRepository.findByEmail(req.getEmail());
        if (user.isPresent()) throw new UserAlreadyExistException("Email is already registered");

        if (req.getIsTeacher()) {
            Professor professor = new Professor();
            professor.setRole(Role.PROFESSOR);
            professor.setName(req.getName());
            professor.setEmail(req.getEmail());
            professor.setPassword(passwordEncoder.encode(req.getPassword()));

            userRepository.save(professor);

            JwtAuthResponse response = new JwtAuthResponse();
            response.setToken(jwtService.generateToken(professor));
            return response;
        }
        else {
            Student student = new Student();
            student.setRole(Role.STUDENT);
            student.setName(req.getName());
            student.setEmail(req.getEmail());
            student.setPassword(passwordEncoder.encode(req.getPassword()));

            userRepository.save(student);

            JwtAuthResponse response = new JwtAuthResponse();
            response.setToken(jwtService.generateToken(student));
            return response;
        }

    }
}
