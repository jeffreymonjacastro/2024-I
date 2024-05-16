package org.demo.pc1_demo.auth.dto;

import lombok.Data;

@Data
public class RegisterReq {
    private String name;
    private String email;
    private String password;
    private Boolean isTeacher=false;
}
