package dbp.e2e.gabriel2.author;

import dbp.e2e.gabriel2.author.domain.AuthorDTO;
import jakarta.validation.ConstraintViolation;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;

import javax.xml.validation.Validator;

import java.util.Set;

public class AuthorDTOValidationTest {
    private Validator validator;

    @Test
    void shouldFail() {
        AuthorDTO authorDTO = new AuthorDTO();
        authorDTO.setFirstname("Jesús");
        authorDTO.setLastname(null);
        authorDTO.setAge(-10);
        authorDTO.setEmail("@gmail.com");

        Set<ConstraintViolation<AuthorDTO>> violations;

        violations = validator.validate(authorDTO);

        System.out.println(violations.size());
    }
}
