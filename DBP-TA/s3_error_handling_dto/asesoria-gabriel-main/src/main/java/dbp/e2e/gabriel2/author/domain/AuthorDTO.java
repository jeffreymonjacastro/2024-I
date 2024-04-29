package dbp.e2e.gabriel2.author.domain;

import jakarta.validation.Valid;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Positive;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class AuthorDTO {
    private Long id;

    @NotNull
    @Size(min = 2, max = 50)
    private String firstname;

    @Size(min = 2, max = 50)
    private String lastname;

    @NotNull
    @Positive
    private Integer age;

    @NotNull
    @Valid
    private String email;
}
