package org.demo.pc1_demo.auth.dto;


import lombok.Data;

@Data
public class LoginReq {
    private String email;
    private String password;
}
