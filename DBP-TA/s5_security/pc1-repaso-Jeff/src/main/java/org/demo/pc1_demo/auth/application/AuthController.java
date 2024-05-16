package org.demo.pc1_demo.auth.application;

import org.demo.pc1_demo.auth.domain.AuthService;
import org.demo.pc1_demo.auth.dto.JwtAuthResponse;
import org.demo.pc1_demo.auth.dto.LoginReq;
import org.demo.pc1_demo.auth.dto.RegisterReq;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/auth")
public class AuthController {

    @Autowired
    private AuthService authService;

    @PostMapping("/login")
    public ResponseEntity<JwtAuthResponse> login(@RequestBody LoginReq req) {
        return ResponseEntity.ok(authService.login(req));
    }

    @PostMapping("/register")
    public ResponseEntity<JwtAuthResponse> register(@RequestBody RegisterReq req) {
        return ResponseEntity.ok(authService.register(req));
    }
}
